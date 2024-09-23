#pragma once
#ifndef EMULATOR_H
#define EMULATOR_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "GB/GB.h"
#include "GB/cartridge.h"

class Emulator {
private:
    GB* gameboy;
    Cartridge* cartridge;
    
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

    void tick();
};

#endif // EMULATOR_H