#include "GB/bus.h"

// ******************************
// ******************************
// ******************************

Bus::Bus() {
    this->cartridge = NULL;
}

Bus::Bus(Cartridge* cartridge) {
    this->cartridge = cartridge;
}

Bus::~Bus() {
    if (this->cartridge != NULL) {
        delete this->cartridge;
    }
}

// ******************************
// ******************************
// ******************************

void Bus::setCartridge(Cartridge* cartridge) {
    this->cartridge = cartridge;
}

u8 Bus::readMemoryU8(int address) {
    this->cartridge->readByte(address);
}

void Bus::writeMemoryU8(int address, u8 data) {
    return this->cartridge->writeByte(address, data);
}