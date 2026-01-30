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
    if (this->cartridge != NULL) {
        delete this->cartridge;
    }
}


void Bus::init(Cartridge* cartridge) {
    this->cartridge = cartridge;
    this->ram = new RAM();

    this->lastAction.action = BA_None;
    this->lastAction.address = 0xFFFF;
    this->lastAction.value = 0xFF;
}

// ******************************
// ******************************
// ******************************

void Bus::setCartridge(Cartridge* cartridge) {
    this->cartridge = cartridge;
}

u8 Bus::readMemoryU8(u16 address, bool saveAction) {
    u8 value = 0xFF;

    if (address >= CARTRIDGE_RANGE_FROM && address <= CARTRIDGE_RANGE_TO) {
        if (this->cartridge == NULL) {
            std::cout << "WARNING: Trying to access cartridge data when no ROM is available. Returning 0xFF" << std::endl;

            return value;
        }

        value = (u8) this->cartridge->readByte(address);
    }
    else {
        value = (u8) this->ram->readMemoryU8(address - CARTRIDGE_RANGE_TO);
    }

    if (saveAction) {
        this->lastAction.action = BA_Read;
        this->lastAction.address = address;
        this->lastAction.value = value;
    }

    return value;
}

s8 Bus::readMemoryS8(u16 address, bool saveAction) {
    u8 value = 0xFF;

    if (address >= CARTRIDGE_RANGE_FROM && address <= CARTRIDGE_RANGE_TO) {
        if (this->cartridge == NULL) {
            std::cout << "WARNING: Trying to access cartridge data when no ROM is available. Returning 0xFF" << std::endl;

            return value;
        }
        
        value = (s8) this->cartridge->readByte(address);
    }
    else {
        value = (s8) this->ram->readMemoryU8(address - CARTRIDGE_RANGE_TO);
    }

    if (saveAction) {
        this->lastAction.action = BA_Read;
        this->lastAction.address = address;
        this->lastAction.value = value;
    }
    return value;
}

void Bus::writeMemoryU8(u16 address, u8 value, bool saveAction) {
    if (address >= CARTRIDGE_RANGE_FROM && address <= CARTRIDGE_RANGE_TO) {
        if (this->cartridge == NULL) {
            std::cout << "WARNING: Trying to write to cartridge data when no ROM is available." << std::endl;
            return;
        }
        
        this->cartridge->writeByte(address, value);
    }
    else {
        this->ram->writeMemoryU8(address - CARTRIDGE_RANGE_TO, value);
    }

    if (saveAction) {
        this->lastAction.action = BA_Write;
        this->lastAction.address = address;
        this->lastAction.value = value;
    }
}