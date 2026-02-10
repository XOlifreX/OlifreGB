#include "GB/memory/OAM.h"

// *****

OAM::OAM() : Memory(OAM_RANGE_FROM, OAM_RANGE_TO) {}
OAM::~OAM() {}

// *****

u8 OAM::readMemoryU8(u32 address) {
    if (!this->isAddressInRange(address)) {
        std::cerr << "Out of bounds OAM READ:" << std::endl;
        std::cerr << "Address:  0x" << std::hex << address << std::endl;

        exit(1);
    }

    return this->data[address - OAM_RANGE_FROM];
}

void OAM::writeMemoryU8(u32 address, u8 value) {
    if (!this->isAddressInRange(address)) {
        std::cerr << "Out of bounds OAM WRITE:" << std::endl;
        std::cerr << "Address:  0x" << std::hex << address << std::endl;

        exit(1);
    }

    this->data[address - OAM_RANGE_FROM] = value;
}