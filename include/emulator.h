#pragma once
#ifndef EMULATOR_H
#define EMULATOR_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "GB/memory/cartridge.h"
#include "GB/SM83.h"
#include "GB/bus.h"

class Emulator {
protected:
    Bus* bus;
    SM83Cpu* cpu;
    Cartridge* cartridge;
    
private:
    bool paused;
    bool running;
    u64 ticks;
    
    // UI
    bool windowInitialized;
    GLFWwindow* window;
    static unsigned int SCR_WIDTH;
    static unsigned int SCR_HEIGHT;

    void processInput();
    int initGLWindow();

public:
    Emulator();
    ~Emulator();

    void initWindow();
    void loadRom(const char* rom);
    void run();
    void pause();
    void reset();

    void tick();
};

#endif // EMULATOR_H