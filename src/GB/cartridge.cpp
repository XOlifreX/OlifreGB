#include "GB/cartridge.h"

// ******************************
// ******************************
// ******************************

Cartridge::Cartridge() {
    this->initialized = false;
}

Cartridge::~Cartridge() {
    delete this->data;
}

// ******************************
// ******************************
// ******************************

void Cartridge::setCartridge(char* data, int size) {
    this->data = data;
    this->size = size;
    this->initialized = true;
}

char Cartridge::readByte(int address) {
    if (address > this->size || address < 0) {
        std::cerr << "Out of bounds READ:" << std::endl;
        std::cerr << "Address:  0x" << std::hex << address << std::endl;
        std::cerr << "ROM size: 0x" << std::hex << this->size;

        exit(1);
    }

    return this->data[address];
}

void Cartridge::writeByte(int address, char value) {
    if (address > this->size || address < 0) {
        std::cerr << "Out of bounds WRITE:" << std::endl;
        std::cerr << "Address:  0x" << std::hex << address << std::endl;
        std::cerr << "ROM size: 0x" << std::hex << this->size;

        exit(1);
    }

    this->data[address] = value;
}