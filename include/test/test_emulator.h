#pragma once
#ifndef TEST_EMULATOR_H
#define TEST_EMULATOR_H

#include <iostream>

#include "../emulator.h"
#include "GB/cartridge.h"
#include "GB/SM83.h"
#include "GB/bus.h"

class TestEmulator: public Emulator {
public:
    TestEmulator();
    ~TestEmulator();

    void setCPU();
    void setBus();

    SM83Cpu* getCPU();
    Bus* getBus();
};

#endif // TEST_EMULATOR_H