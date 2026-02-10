#include "GB/memory/NotUsableRAM.h"

// *****

NotUsableRAM::NotUsableRAM() : Memory(NOTUSABLERAM_RANGE_FROM, NOTUSABLERAM_RANGE_TO) {}
NotUsableRAM::~NotUsableRAM() {}

// *****

u8 NotUsableRAM::readMemoryU8(u32 address) {
    if (!this->isAddressInRange(address)) {
        std::cerr << "Out of bounds NotUsableRAM READ:" << std::endl;
        std::cerr << "Address:  0x" << std::hex << address << std::endl;

        exit(1);
    }

    return this->data[address - NOTUSABLERAM_RANGE_FROM];
}

void NotUsableRAM::writeMemoryU8(u32 address, u8 value) {
    if (!this->isAddressInRange(address)) {
        std::cerr << "Out of bounds NotUsableRAM WRITE:" << std::endl;
        std::cerr << "Address:  0x" << std::hex << address << std::endl;

        exit(1);
    }

    this->data[address - NOTUSABLERAM_RANGE_FROM] = value;
}