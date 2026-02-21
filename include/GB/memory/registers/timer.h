#pragma once
#ifndef TIMERS_H
#define TIMERS_H

#include "GB/memory/memory.h"

#define TIMER_RANGE_FROM 0xFF04
#define TIMER_RANGE_TO 0xFF07

#define TIMER_IS_IN_REGION(ADDRESS) \
    ADDRESS >= TIMER_RANGE_FROM && ADDRESS <= TIMER_RANGE_TO

class Timer;

struct TimerState {
    i8 div;
    u8 tima;

    u8 tma;

    union {
        u8 _ : 5;
        u8 timerEnable : 1;
        u8 tacClockSelect : 2;

        u8 tac;
    };

    Timer* memory;
};

class Timer : public Memory {
private:
    TimerState* state;

    u32 translateAddress(u32 address);
    
public:
    Timer(TimerState* state);
    ~Timer();

    u8 readMemoryU8(u32 address);
    void writeMemoryU8(u32 address, u8 data);
    
    bool isAddressInRange(u32 address);

    void handleDiv();
    void handleTima();
};

#endif // TIMERS_H