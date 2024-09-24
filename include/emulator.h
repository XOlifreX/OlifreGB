#pragma once
#ifndef EMULATOR_H
#define EMULATOR_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "GB/cartridge.h"
#include "GB/SM83.h"
#include "GB/bus.h"

class Emulator {
private:
    Bus* bus;
    SM83Cpu* cpu;
    Cartridge* cartridge;

    bool paused;
    bool running;
    u64 ticks;
    
    // UI
    GLFWwindow* window;
    static unsigned int SCR_WIDTH;
    static unsigned int SCR_HEIGHT;

    int initWindow();
    void processInput();

public:
    Emulator();
    ~Emulator();

    void loadRom(const char* rom);
    void run();
    void pause();
    void reset();

    void tick();
};

#endif // EMULATOR_H