#include "GB/GB.h"

// ******************************
// ******************************
// ******************************

GB::GB() {
    this->bus = new Bus();
    this->cpu = new SM83Cpu(this->bus);
}

GB::~GB() {
    delete this->cpu;
}

// ******************************
// ******************************
// ******************************

void GB::setCartridge(Cartridge* cart) {
    this->bus->setCartridge(cart);
}