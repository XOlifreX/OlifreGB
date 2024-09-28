#include "RAM.h"

// *****

RAM::RAM() {
    this->data = (u8*) malloc(sizeof(u8) * this->MAX_RAM_SIZE);
}

RAM::~RAM() {
    delete this->data;
}

// *****

u8 RAM::readMemoryU8(u16 address) {

}

void RAM::writeMemoryU8(u16 address, u8 data) {


}