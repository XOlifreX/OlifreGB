#pragma once
#ifndef PPU_H
#define PPU_H

#include <iostream>

#include "GB/memory/registers/hardware_registers.h"
#include "GB/memory/registers/lcd.h"
#include "GB/bus.h"

#define MODE2_MAX_DOT_COUNT     80

#define MODE3_MIN_DOT_COUNT     172
#define MODE3_MAX_DOT_COUNT     289

#define SCANLINE_MAX_DOT_COUNT  456

#define LY_MODE_1               144
#define LY_LAST_INDEX           153

enum PPUModes {
    PPU_Mode2,
    PPU_Mode3,
    PPU_Mode0,
    PPU_Mode1
};

struct PPUState {
    PPUModes mode;
    
    u16 currModeEstimatedTotalDotCount;
    u16 currModeDotCount;
    u16 currScanLineDotCount;
    u32 currFrameDotCount;

    bool earlyModeExit;
};

class PPU {
private:
    PPUState state;
    LcdState* lcdState;

    Bus* bus;

    void execMode2();
    void execMode3();
    void execMode0();
    void execMode1();

    void tryModeChange();
public:
    PPU(Bus* bus);
    ~PPU();

    void execDot();
};

#endif // PPU_H