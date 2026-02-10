#include "GB/memory/io.h"

// *****

IO::IO() : Memory(IO_RANGE_FROM, IO_RANGE_TO) {}
IO::~IO() {}

// *****

u8 IO::readMemoryU8(u32 address) {
    if (!this->isAddressInRange(address)) {
        std::cerr << "Out of bounds IO READ:" << std::endl;
        std::cerr << "Address:  0x" << std::hex << address << std::endl;

        exit(1);
    }

    return this->data[address - IO_RANGE_FROM];
}

void IO::writeMemoryU8(u32 address, u8 value) {
    if (!this->isAddressInRange(address)) {
        std::cerr << "Out of bounds IO WRITE:" << std::endl;
        std::cerr << "Address:  0x" << std::hex << address << std::endl;

        exit(1);
    }

    this->data[address - IO_RANGE_FROM] = value;
}