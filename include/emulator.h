#pragma once
#include <fstream>

#include "GB/GB.h"
#include "GB/cartridge.h"
#include "window/emu_window.h"

class Emulator {
private:
    GB* gameboy;
    EmuWindow* window;

public:
    Emulator();
    ~Emulator();

    bool loadRom(const char* rom);
    void run();
};