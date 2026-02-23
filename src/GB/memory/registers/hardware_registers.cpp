#include "GB/memory/registers/hardware_registers.h"

// *****

HardwareRegistors::HardwareRegistors() : Memory(HR_RANGE_FROM, HR_RANGE_TO) {
    this->intr = new Interrupt(&this->state.intrState);
    this->timer = new Timer(&this->state.timerState, &this->state.intrState);
}

HardwareRegistors::~HardwareRegistors() {
    delete this->intr;
    delete this->timer;
}

// *****

HardwareRegisterState* HardwareRegistors::getStateRef() {
    return &this->state;
}

u8 HardwareRegistors::readMemoryU8(u32 address) {
    if (!this->isAddressInRange(address)) {
        std::cerr << "Out of bounds HARDWARE REGISTER READ:" << std::endl;
        std::cerr << "Address:  0x" << std::hex << address << std::endl;

        exit(1);
    }

    // Interrupt stuff
    if (this->intr->isAddressInRange(address))
        return this->intr->readMemoryU8(address);
    // Timer stuff
    if (this->timer->isAddressInRange(address))
        return this->timer->readMemoryU8(address);

    return this->data[address - HR_RANGE_FROM];
}

void HardwareRegistors::writeMemoryU8(u32 address, u8 value) {
    if (!this->isAddressInRange(address)) {
        std::cerr << "Out of bounds HARDWARE REGISTER WRITE:" << std::endl;
        std::cerr << "Address:  0x" << std::hex << address << std::endl;

        exit(1);
    }

    // Interrupt stuff
    if (this->intr->isAddressInRange(address)) {
        this->intr->writeMemoryU8(address, value);
        return;
    }
    // Timer stuff
    if (this->timer->isAddressInRange(address)) {
        this->timer->writeMemoryU8(address, value);
        return;
    }

    this->data[address - HR_RANGE_FROM] = value;
}