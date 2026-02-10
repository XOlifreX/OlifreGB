#include "GB/memory/WRAM.h"

// *****

WRAM::WRAM() : Memory(WRAM_RANGE_FROM, WRAM_GBC_RANGE_TO) {}
WRAM::~WRAM() {}

// *****

u32 WRAM::translateAddress(u32 address) {
    return WRAM_IS_IN_ECHO_REGION(address) ? (address - WRAM_FULL_SIZE) : address;
}

// *****

u8 WRAM::readMemoryU8(u32 address) {
    if (!this->isAddressInRange(address)) {
        std::cerr << "Out of bounds WRAM READ:" << std::endl;
        std::cerr << "Address:  0x" << std::hex << address << std::endl;

        exit(1);
    }

    u32 location = this->translateAddress(address);
    return this->data[location - WRAM_RANGE_FROM];
}

void WRAM::writeMemoryU8(u32 address, u8 value) {
    if (!this->isAddressInRange(address)) {
        std::cerr << "Out of bounds WRAM WRITE:" << std::endl;
        std::cerr << "Address:  0x" << std::hex << address << std::endl;

        exit(1);
    }

    u32 location = this->translateAddress(address);
    this->data[location - WRAM_RANGE_FROM] = value;
}

bool WRAM::isAddressInRange(u32 address) {
    return (address >= WRAM_RANGE_FROM && address <= WRAM_ECHO_RANGE_TO);
}