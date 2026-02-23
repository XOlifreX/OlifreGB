#pragma once
#ifndef TIMERS_H
#define TIMERS_H

#include "GB/memory/memory.h"
#include "GB/memory/registers/interrupt.h"

#include "test/test_mode.h"

#define TIMER_RANGE_FROM    0xFF04
#define TIMER_RANGE_TO      0xFF07

#define TIMER_IS_IN_REGION(ADDRESS) \
    ADDRESS >= TIMER_RANGE_FROM && ADDRESS <= TIMER_RANGE_TO

#define TIMER_REG_DIV       0xFF04
#define TIMER_REG_TIMA      0xFF05
#define TIMER_REG_TMA       0xFF06
#define TIMER_REG_TAC       0xFF07

class Timer;

struct TimerState {
    // DIV
    u8 div;
    u16 divCycleCounter;

    // TIMA
    u8 tima;
    bool timaOverflowed;
    u16 timaCycleCounter;

    // TMA
    u8 tma;
    bool tmaWrittenTo;
    u8 prevTma;

    // TAC
    union {
        u8 _ : 5;
        u8 timerEnable : 1;
        u8 tacClockSelect : 2;

        u8 tac;
    };
    u16 tacCycles;

    Timer* memory;
};

class Timer : public Memory {
private:
    TimerState* state;
    InterruptState* intrState;

    u32 translateAddress(u32 address);
    
public:
    Timer(TimerState* state, InterruptState* intrState);
    ~Timer();

    u8 readMemoryU8(u32 address);
    void writeMemoryU8(u32 address, u8 data);
    
    bool isAddressInRange(u32 address);

    void handleDiv();
    void resetDiv();
    void handleTima();
};

#endif // TIMERS_H