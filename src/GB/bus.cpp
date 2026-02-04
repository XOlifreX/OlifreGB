#include "GB/bus.h"

// ******************************
// ******************************
// ******************************

Bus::Bus() {
    this->init(NULL);
}

Bus::Bus(Cartridge* cartridge) {
    this->init(cartridge);
}

Bus::~Bus() {
    if (this->cartridge != NULL)
        delete this->cartridge;

    delete this->rom;
    delete this->ram;
}


void Bus::init(Cartridge* cartridge) {
    this->ram = new RAM();
    this->rom = new ROM();

    if (cartridge != NULL)
        this->setCartridge(cartridge);

    this->lastAction.action = BA_None;
    this->lastAction.address = 0xFFFF;
    this->lastAction.value = 0xFF;
}

// ******************************
// ******************************
// ******************************

void Bus::setCartridge(Cartridge* cartridge) {
    this->cartridge = cartridge;

    u8* temp = this->cartridge->getROMBank(0);
    dynamic_cast<ROM*>(this->rom)->writeROM(temp);
}

Memory* Bus::getMemoryDestination(u16 address) {
    if (this->rom->isAddressInRange(address))
        return this->rom;
    if (this->ram->isAddressInRange(address))
        return this->ram;

    std::cerr << "Out of bounds MEMORY READ:" << std::endl;
    std::cerr << "Address:  0x" << std::hex << address << std::endl;
    
    exit(1);

    return NULL;
}

// ******************************

u8 Bus::readMemoryU8(u16 address, bool saveAction) {
    u8 value = 0xFF;

    Memory* dest = this->getMemoryDestination(address);

    if (dest == NULL)
        return value;

    value = (u8) dest->readMemoryU8(address);

    if (saveAction) {
        this->lastAction.action = BA_Read;
        this->lastAction.address = address;
        this->lastAction.value = value;
    }

    return value;
}

s8 Bus::readMemoryS8(u16 address, bool saveAction) {
    u8 value = 0xFF;

    Memory* dest = this->getMemoryDestination(address);

    if (dest == NULL)
        return value;

    value = (s8) dest->readMemoryU8(address);

    if (saveAction) {
        this->lastAction.action = BA_Read;
        this->lastAction.address = address;
        this->lastAction.value = value;
    }

    return value;
}

void Bus::writeMemoryU8(u16 address, u8 value, bool saveAction) {
    Memory* dest = this->getMemoryDestination(address);

    if (dest == NULL)
        return;

    dest->writeMemoryU8(address, value);

    if (saveAction) {
        this->lastAction.action = BA_Write;
        this->lastAction.address = address;
        this->lastAction.value = value;
    }
}

// ******************************
// ******************************
// ******************************
