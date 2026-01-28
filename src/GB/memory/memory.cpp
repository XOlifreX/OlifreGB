#include "GB/memory/memory.h"

// *****

Memory::Memory(u16 range_from, u16 range_to) : RANGE_FROM(range_from), RANGE_TO(range_to) {}

// *****

bool Memory::isAddressInRange(u16 address) {
    return (address >= this->RANGE_FROM && address <= this->RANGE_TO);
}

// *****
