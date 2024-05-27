#pragma once
#include "SM83.h"
#include "Cartridge.h"

class GB {
private:
    SM83Cpu* cpu;
    Cartridge* cartridge;
    
    bool paused;
    bool running;
    u64 ticks;

public:
    GB();
    ~GB();

    void setCartridge(Cartridge* cart);
};