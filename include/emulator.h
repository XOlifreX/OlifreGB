#pragma once
#ifndef EMULATOR_H
#define EMULATOR_H

#include "GB/GB.h"
#include "GB/cartridge.h"
#include "window/emu_window.h"

class Emulator {
private:
    GB* gameboy;
    Cartridge* cartridge;
    EmuWindow* window;

public:
    Emulator();
    ~Emulator();

    void loadRom(const char* rom);
    void run();
};

#endif // EMULATOR_H