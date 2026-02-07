#include "GB/memory/memory.h"

// *****

Memory::Memory(u16 range_from, u16 range_to) : RANGE_FROM(range_from), RANGE_TO(range_to) {
    this->data = new u8[sizeof(u8) * ((range_to - range_from) + 1)];
}

Memory::~Memory() {
    if (this->data != NULL)
        delete[] this->data;
}

// *****

bool Memory::isAddressInRange(u16 address) {
    return (address >= this->RANGE_FROM && address <= this->RANGE_TO);
}

// *****
