#include "GB/memory/RAM.h"

// *****

RAM::RAM() : Memory(RAM_RANGE_FROM, RAM_RANGE_TO) {
    this->data = (u8*) malloc(sizeof(u8) * (RAM_RANGE_TO - RAM_RANGE_FROM + 1));
}

RAM::~RAM() {
    delete this->data;
}

// *****

u8 RAM::readMemoryU8(u16 address) {

}

void RAM::writeMemoryU8(u16 address, u8 data) {
    
}