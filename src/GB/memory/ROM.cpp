#include "GB/memory/ROM.h"

// *****

ROM::ROM() : Memory(ROM_RANGE_FROM, ROM_RANGE_TO) {}
ROM::~ROM() {}

// *****

void ROM::writeROM(u8* rom) {
    if (this->data != NULL)
        free(this->data);

    this->data = rom;
}

u8 ROM::readMemoryU8(u16 address) {
    if (!this->isAddressInRange(address)) {
        std::cerr << "Out of bounds ROM READ:" << std::endl;
        std::cerr << "Address:  0x" << std::hex << address << std::endl;

        exit(1);
    }

    return this->data[address - ROM_RANGE_FROM];
}

void ROM::writeMemoryU8(u16 address, u8 value) {
    if (!this->isAddressInRange(address)) {
        std::cerr << "Out of bounds ROM WRITE:" << std::endl;
        std::cerr << "Address:  0x" << std::hex << address << std::endl;

        exit(1);
    }

    this->data[address - ROM_RANGE_FROM] = value;
}