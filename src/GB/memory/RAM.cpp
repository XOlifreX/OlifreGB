#include "GB/memory/RAM.h"

// *****

RAM::RAM() : Memory(RAM_RANGE_FROM, RAM_RANGE_TO) {
    this->data = (u8*) malloc(sizeof(u8) * RAM_FULL_SIZE);
}

RAM::~RAM() {
    delete this->data;
}

// *****

u8 RAM::readMemoryU8(u16 address) {
    // TODO: Add seperation
    if (address < 0x00 || RAM_FULL_SIZE < address) {
        std::cerr << "Out of bounds RAM READ:" << std::endl;
        std::cerr << "Address:  0x" << std::hex << address << std::endl;

        exit(1);
    }

    return this->data[address];
}

void RAM::writeMemoryU8(u16 address, u8 value) {
    // TODO: Add seperation
    if (address < 0x00 || RAM_FULL_SIZE < address) {
        std::cerr << "Out of bounds RAM WRITE:" << std::endl;
        std::cerr << "Address:  0x" << std::hex << address << std::endl;

        exit(1);
    }

    this->data[address] = value;
}