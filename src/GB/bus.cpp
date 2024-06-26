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

u8 Bus::readMemoryU8(u16 address) {
    (u8) this->cartridge->readByte(address);
}

s8 Bus::readMemoryS8(u16 address) {
    (s8) this->cartridge->readByte(address);
}

void Bus::writeMemoryU8(u16 address, u8 data) {
    this->cartridge->writeByte(address, data);
}