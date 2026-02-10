#include "GB/memory/cartridge.h"

// ******************************
// ******************************
// ******************************

Cartridge::Cartridge(const char* path) : Memory(0x0000, 0x8000) {
    this->info = new CartridgeInfo();

    SRAM* sram = new SRAM();
    ROM* rom = new ROM();
    
    if (path == NULL) {
        // 512 KiB
        this->info->cartInfo.romSize = rom32KiB;
        // 8 KiB
        this->info->cartInfo.ramSize = ram8KiB;
        // No MBC
        this->info->cartInfo.type = 0x00;
        
        this->initROM(rom, NULL);
        this->initSRAM(sram);
    }
    else {
        this->initROM(rom, path);
        this->initSRAM(sram);
    }

    this->initMBC(rom, sram);
}

Cartridge::~Cartridge() {
    delete this->mbc;
    delete this->info;
}

// ******************************

void Cartridge::initROM(ROM* rom, const char* path) {
    if (path == NULL) {
        char* buffer = new char[0x8000];
        rom->writeROM((u8*) buffer, 0x8000);

        return;
    }

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
    rom->writeROM((u8*) buffer, size);
}

void Cartridge::initSRAM(SRAM* sram) {
    u8* temp = NULL;
    u32 size = 0;

    u8 sizeId = this->info->cartInfo.ramSize;

    if (sizeId == ram8KiB) {
        temp = new u8[sizeof(u8) * 0x2000];
        size = 0x2000;
    }

    if (sizeId == ram32KiB) {
        temp = new u8[sizeof(u8) * 0x8000];
        size = 0x8000;
    }

    if (sizeId == ram128KiB) {
        temp = new u8[sizeof(u8) * 0x20000];
        size = 0x20000;
    }

    if (sizeId == ram64KiB) {
        temp = new u8[sizeof(u8) * 0x10000];
        size = 0x10000;
    }

    sram->writeSRAM(temp, size);
}

void Cartridge::initMBC(ROM* rom, SRAM* sram) {
    this->mbc = NULL;

    // No MBC (Mapper)
    if (this->info->cartInfo.type == 0x00) {
        this->mbc = new MBC(this->info, sram, rom);
        return;
    }

    // MBC1
    if (this->info->cartInfo.type >= 0x01 && this->info->cartInfo.type < 0x04) {
        this->mbc = new MBC1(this->info, sram, rom);
        return;
    }

    // MBC2
    if (this->info->cartInfo.type >= 0x05 && this->info->cartInfo.type < 0x07) {
        this->mbc = new MBC2(this->info, sram, rom);
        return;
    }

    // MBC3
    if (this->info->cartInfo.type >= 0x0F && this->info->cartInfo.type < 0x14) {
        this->mbc = new MBC3(this->info, sram, rom);
        return;
    }

    // MBC5
    if (this->info->cartInfo.type >= 0x19 && this->info->cartInfo.type < 0x1F) {
        // this->mbc = new MBC(this->info, sram, rom);
        return;
    }

    // MBC6
    if (this->info->cartInfo.type == 0x20) {
        // this->mbc = new MBC(this->info, sram, rom);
        return;
    }

    // MBC7
    if (this->info->cartInfo.type == 0x22) {
        // this->mbc = new MBC(this->info, sram, rom);
        return;
    }

    // MMM01
    if (this->info->cartInfo.type >= 0x08 && this->info->cartInfo.type < 0x0E) {
        // this->mbc = new MBC(this->info, sram, rom);
        return;
    }

    // M161
    // TODO: Find which ID this mapper uses
    if (false) {
        // this->mbc = new MBC(this->info, sram, rom);
        return;
    }

    // HuC1
    if (this->info->cartInfo.type == 0xFF) {
        // this->mbc = new MBC(this->info, sram, rom);
        return;
    }

    // HuC-3
    if (this->info->cartInfo.type == 0xFE) {
        // this->mbc = new MBC(this->info, sram, rom);
        return;
    }

    // Unknown type, using no MBC
    // Could be MBC1M, EMS, Wisdom Tree, ...
    this->mbc = new MBC(this->info, sram, rom);
}

// ******************************
// ******************************
// ******************************

void Cartridge::printCartridgeData() {
    this->info->printCartridgeData();
}

// ******************************

inline u8 Cartridge::readMemoryU8(u32 address) {
    return this->mbc->readU8(address);
}

inline void Cartridge::writeMemoryU8(u32 address, u8 value) {
    this->mbc->writeU8(address, value);
}

// ******************************

bool Cartridge::isAddressInRange(u32 address) {
    return this->mbc->isAddressInRange(address);
}

// ******************************
// ******************************
// ******************************
