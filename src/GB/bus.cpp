#include "GB/bus.h"

// ******************************
// ******************************
// ******************************

Bus::Bus() {
    this->cartridge = NULL;
    this->ram = new RAM();
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
    if (address >= 0x0000 && address <= 0x3FFF) {
        if (this->cartridge == NULL) {
            std::cout << "WARNING: Trying to access cartridge data when no ROM is available. Returning 0xFF" << std::endl;

            return 0xFF;
        }

        return (u8) this->cartridge->readByte(address);
    }

    return (u8) this->ram->readMemoryU8(address);
}

s8 Bus::readMemoryS8(u16 address) {
    if (address >= 0x0000 && address <= 0x3FFF) {
        if (this->cartridge == NULL) {
            std::cout << "WARNING: Trying to access cartridge data when no ROM is available. Returning 0xFF" << std::endl;

            return 0xFF;
        }
        
        return (s8) this->cartridge->readByte(address);
    }
    
    return (s8) this->ram->readMemoryU8(address);
}

void Bus::writeMemoryU8(u16 address, u8 data) {
    if (address >= 0x0000 && address <= 0x3FFF) {
        if (this->cartridge == NULL) {
            std::cout << "WARNING: Trying to write to cartridge data when no ROM is available." << std::endl;
            return;
        }
        
        this->cartridge->writeByte(address, data);
        return;
    }
}