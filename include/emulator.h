#pragma once
#include "GB/GB.h"
#include "window/emu_window.h"

class Emulator {
private:
    GB* gameboy;
    EmuWindow* window;

public:
    Emulator();
    ~Emulator();

    void run();
};