#pragma once
#ifndef IO_H
#define IO_H

#include "GB/memory/memory.h"
#include "GB/memory/registers/interrupt.h"
#include "GB/memory/registers/timer.h"

#define HR_RANGE_FROM 0xFF00
#define HR_RANGE_TO 0xFF7F

struct HardwareRegisterState {
    InterruptState intrState;
    TimerState timerState;
};

// Only used in test-mode
class HardwareRegistors: public Memory {
private:
    HardwareRegisterState state;

    Interrupt* intr;
    Timer* timer;

public:
    HardwareRegistors();
    ~HardwareRegistors();

    HardwareRegisterState* getStateRef();

    u8 readMemoryU8(u32 address);
    void writeMemoryU8(u32 address, u8 data);
};

#endif // IO_H