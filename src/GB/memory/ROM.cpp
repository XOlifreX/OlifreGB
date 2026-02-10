#include "GB/memory/ROM.h"

// *****

ROM::ROM() : Memory(ROM_RANGE_FROM, ROM_RANGE_TO) {}
ROM::~ROM() {}

// *****

void ROM::writeROM(u8* rom, u32 size) {
    if (this->data != NULL)
        free(this->data);

    this->size = size;
    this->data = rom;
}

u8 ROM::readMemoryU8(u32 address) {
    u32 location = address - ROM_RANGE_FROM;

    if (!this->isAddressInSizeRange(location)) {
        std::cerr << "Out of bounds ROM READ:" << std::endl;
        std::cerr << "Address:  0x" << std::hex << address << std::endl;

        exit(1);
    }

    return this->data[location];
}

void ROM::writeMemoryU8(u32 address, u8 value) {
    u32 location = address - ROM_RANGE_FROM;

    if (!this->isAddressInSizeRange(location)) {
        std::cerr << "Out of bounds ROM WRITE:" << std::endl;
        std::cerr << "Address:  0x" << std::hex << address << std::endl;

        exit(1);
    }

    this->data[location] = value;
}