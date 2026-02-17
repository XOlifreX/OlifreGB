#include "GB/memory/interrupt.h"

// *****

Interrupt::Interrupt(InterruptState* state) : Memory(INTR_RANGE_FROM, INTR_RANGE_TO) {
    this->state = state;
}

Interrupt::~Interrupt() {}

// *****

u32 Interrupt::translateAddress(u32 address) {
    return INTR_IS_IN_REGION(address) ? (address - INTR_RANGE_FROM) : address;
}

// *****

u8 Interrupt::readMemoryU8(u32 address) {
    if (!this->isAddressInRange(address)) {
        std::cerr << "Out of bounds INTR READ:" << std::endl;
        std::cerr << "Address:  0x" << std::hex << address << std::endl;

        exit(1);
    }

    u32 location = this->translateAddress(address);
    return this->data[location - INTR_RANGE_FROM];
}

void Interrupt::writeMemoryU8(u32 address, u8 value) {
    if (!this->isAddressInRange(address)) {
        std::cerr << "Out of bounds INTR WRITE:" << std::endl;
        std::cerr << "Address:  0x" << std::hex << address << std::endl;

        exit(1);
    }

    // Change Interrupt Register states
    if (address == INTR_IE_ADDRESS)
        this->state->intrEnable = value;
    else if (address == INTR_IF_ADDRESS)
        this->state->intrFlags = value;
    
    u32 location = this->translateAddress(address);
    this->data[location - INTR_RANGE_FROM] = value;
}

bool Interrupt::isAddressInRange(u32 address) {
    if (address == INTR_IE_ADDRESS)
        return true;

    return address == INTR_IF_ADDRESS;
}