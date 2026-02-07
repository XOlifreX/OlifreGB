#include "GB/memory/cartridge.h"

// ******************************
// ******************************
// ******************************

Cartridge::Cartridge(const char* path) : Memory(0x0000, 0x8000) {
    this->info = new CartridgeInfo();

    this->sram = new SRAM();
    this->rom = new ROM();
    
    if (path == NULL) {
        this->info->cartInfo.romSize = 0x06;
    }
    else {
        this->loadCartridge(path);
    }
}

Cartridge::~Cartridge() {
    delete this->info;
}

// ******************************

void Cartridge::loadCartridge(const char* path) {
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    if (!file) {
        std::cerr << "Error: Could not find rom file " << path << std::endl;
        exit(1);
    }

    int size = (int)file.tellg();
    file.seekg(0, std::ios::beg);

    char* buffer = new char[size];

    if (!file.read(buffer, size)) {
        std::cerr << "Error: Could not read rom file " << path << std::endl;
        free(buffer);
        
        exit(1);
    }

    file.close();

    this->info->setCartridgeInfo(buffer, size);
    this->rom->writeROM((u8*) buffer);
}

// ******************************
// ******************************
// ******************************

void Cartridge::printCartridgeData() {
    this->info->printCartridgeData();
}

// ******************************

u8 Cartridge::readMemoryU8(u16 address) {
    int romSize = this->info->getROMSize();
    if (address > romSize || address < 0) {
        std::cerr << "Out of bounds CARTRIDGE READ:" << std::endl;
        std::cerr << "Address:  0x" << std::hex << address << std::endl;
        std::cerr << "ROM size: 0x" << std::hex << romSize;

        exit(1);
    }

    return this->data[address];
}

void Cartridge::writeMemoryU8(u16 address, u8 value) {
    int romSize = this->info->getROMSize();
    if (address > romSize || address < 0) {
        std::cerr << "Out of bounds CARTRIDGE WRITE:" << std::endl;
        std::cerr << "Address:  0x" << std::hex << address << std::endl;
        std::cerr << "ROM size: 0x" << std::hex << romSize;

        exit(1);
    }

    this->data[address] = value;
}

// ******************************

bool Cartridge::isAddressInRange(u16 address) {
    Memory* temp = NULL;

    if (this->rom->isAddressInRange(address))
        temp = this->rom;
    if (this->sram->isAddressInRange(address))
        temp = this->sram;

    return temp != NULL;
}

Memory* Cartridge::getMemoryDestination(u16 address) {
    if (this->rom->isAddressInRange(address))
        return this->rom;
    if (this->sram->isAddressInRange(address))
        return this->sram;

    std::cerr << "Out of bounds CARTRIDGE READ:" << std::endl;
    std::cerr << "Address:  0x" << std::hex << address << std::endl;
    
    exit(1);

    return NULL;
}

// ******************************

u8* Cartridge::getROMBank(u8 bank) {
    if (this->data == NULL)
        return NULL;

    if (bank != 0) {
        // TODO: Support bank switching
        return NULL;
    }

    u8* romData = new u8[sizeof(u8) * 0x8000];
    std::copy(this->data, this->data + 0x8000, romData);

    return romData;
}

void Cartridge::setSRAM(SRAM* sram) {
    if (this->sram != NULL)
        delete this->sram;

    this->sram = sram;
}

// ******************************
// ******************************
// ******************************
