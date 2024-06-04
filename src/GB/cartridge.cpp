#include "GB/cartridge.h"

// ******************************
// ******************************
// ******************************

Cartridge::Cartridge(char* path) {
    this->initialized = false;

    if (path == NULL) return;

    this->loadCartridge(path);
}

Cartridge::~Cartridge() {
    delete this->data;
}

void Cartridge::loadCartridge(char* path) {
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
        delete[] buffer;
        
        exit(1);
    }

    file.close();

    this->entrypoint = charsToInt(buffer, size, 0x100);
    this->nLogo = spliceChars(buffer, size, 0x104, 0x2F);
    this->title = spliceChars(buffer, size, 0x134, 0xF);
    this->mCode = spliceChars(buffer, size, 0x13F, 0x4);
    this->gbcFlag = buffer[0x143];
    this->licenseCode = charsToShort(buffer, size, 0x144);
    this->sgbFlag = buffer[0x146];
    this->type = buffer[0x147];
    this->romSize = buffer[0x148];
    this->ramSize = buffer[0x149];
    this->destinationCode = buffer[0x14A];
    this->oldLicenseCode = buffer[0x14B];
    this->romVersion = buffer[0x14C];
    this->checksum = buffer[0x14D];
    this->gChecksum = charsToShort(buffer, size, 0x14E);

    int i = 0;
}

// ******************************
// ******************************
// ******************************


void Cartridge::printCartridgeData() {
    
}

char Cartridge::readByte(int address) {
    if (address > this->romSize || address < 0) {
        std::cerr << "Out of bounds READ:" << std::endl;
        std::cerr << "Address:  0x" << std::hex << address << std::endl;
        std::cerr << "ROM size: 0x" << std::hex << this->romSize;

        exit(1);
    }

    return this->data[address];
}

void Cartridge::writeByte(int address, char value) {
    if (address > this->romSize || address < 0) {
        std::cerr << "Out of bounds WRITE:" << std::endl;
        std::cerr << "Address:  0x" << std::hex << address << std::endl;
        std::cerr << "ROM size: 0x" << std::hex << this->romSize;

        exit(1);
    }

    this->data[address] = value;
}