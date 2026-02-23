#include "GB/memory/registers/timer.h"

// *****

Timer::Timer(TimerState* state, InterruptState* intrState) : Memory(TIMER_RANGE_FROM, TIMER_RANGE_TO) {
    this->state = state;
    this->state->memory = this;

    this->intrState = intrState;
}

Timer::~Timer() {}

// *****

u32 Timer::translateAddress(u32 address) {
    return TIMER_IS_IN_REGION(address) ? (address - TIMER_RANGE_FROM) : address;
}

// *****

u8 Timer::readMemoryU8(u32 address) {
    if (!this->isAddressInRange(address)) {
        std::cerr << "Out of bounds TIMER READ:" << std::endl;
        std::cerr << "Address:  0x" << std::hex << address << std::endl;

        exit(1);
    }

    u32 location = this->translateAddress(address);
    return this->data[location];
}

void Timer::writeMemoryU8(u32 address, u8 value) {
    if (!this->isAddressInRange(address)) {
        std::cerr << "Out of bounds TIMER WRITE:" << std::endl;
        std::cerr << "Address:  0x" << std::hex << address << std::endl;

        exit(1);
    }

    switch (address) {
        case TIMER_REG_DIV:
            if (!is_test_mode) {
                this->state->div = 0;
                value = 0;
            } 
            else {
                this->state->div = value;
            }
            break;
        case TIMER_REG_TIMA:
            this->state->tima = value;
            break;
        case TIMER_REG_TMA:
            this->state->tmaWrittenTo = true;
            this->state->prevTma = this->state->tma;
            this->state->tma = value;
            break;
        case TIMER_REG_TAC:
            this->state->tac = value;

            u8 temp = this->state->tacClockSelect;
            if (temp == 0x0)
                temp = 0x4;

            this->state->tacCycles = (1 << (temp * 2));

            break;
    }
    
    u32 location = this->translateAddress(address);
    this->data[location] = value;
}

bool Timer::isAddressInRange(u32 address) {
    return TIMER_IS_IN_REGION(address);
}

void Timer::handleDiv() {
    if (this->state->divCycleCounter < 0x0100)
        return;
    
    this->state->div++;
    this->data[TIMER_REG_DIV - TIMER_RANGE_FROM] = this->state->div;
    this->state->divCycleCounter = 0;
}

void Timer::resetDiv() {
    this->data[TIMER_REG_DIV - TIMER_RANGE_FROM] = 0x00;
}

void Timer::handleTima() {
    if (this->state->timerEnable)
        return;

    // Trigger interrupt
    if (this->state->timaOverflowed) {
        this->intrState->intrFlagTimer = 1;

        // If the TMA value was just written manually, then we take the previous value of TMA
        if (this->state->tmaWrittenTo) {
            this->state->tima = this->state->prevTma;
        }
        else {
            this->state->tima = this->state->tma;
        }
        
        // Reset TMA Written to flag
        this->state->tmaWrittenTo = false;
    }
    else {
        if (this->state->timaCycleCounter < this->state->tacCycles)
            return;
        
        if ((this->state->tima + 1) == 0x00) {
            this->state->timaOverflowed = true;

            this->state->tima = 0x00;
        }
        else {
            this->state->tima++;
        }
    }

    this->data[TIMER_REG_TIMA - TIMER_RANGE_FROM] = this->state->tima;
    this->state->timaCycleCounter = 0;
}