#include "GB/GB.h"

// ******************************
// ******************************
// ******************************

GB::GB() {
    this->cpu = new SM83Cpu();
    this->cartridge = NULL;
}

GB::~GB() {
    delete this->cpu;
    delete this->cartridge;
}

// ******************************
// ******************************
// ******************************

void GB::setCartridge(Cartridge* cart) {
    this->cartridge = cart;
}