#pragma once
#include "SM83.h"
#include "cartridge.h"
#include "bus.h"

class GB {
private:
    SM83Cpu* cpu;
    Bus* bus;
    
    bool paused;
    bool running;
    u64 ticks;

public:
    GB();
    ~GB();

    void run();
    void pause();
    void reset();
    void setCartridge(Cartridge* cart);
    void saveState(const char* path);
    void loadState(const char* path);
};
