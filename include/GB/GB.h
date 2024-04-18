#pragma once
#include "SM83.h"

class GB {
private:
    SM83Cpu* cpu;
    
    bool paused;
    bool running;
    u64 ticks;

public:
    GB();
    ~GB();
};