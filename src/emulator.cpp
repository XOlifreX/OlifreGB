#include "emulator.h"

// ******************************
// ******************************
// ******************************

Emulator::Emulator() {
    this->bus = new Bus();
    this->cpu = new SM83Cpu(this->bus);

    this->paused = false;
    this->running = true;
    this->ticks = 0;

    this->windowInitialized = false;
}
Emulator::~Emulator() {
    delete this->cpu;
    delete this->bus;

    if (this->windowInitialized)
        glfwTerminate();
}

// ******************************

void Emulator::initWindow() {
    if (this->windowInitialized)
        return;

    this->initWindow();
}

void Emulator::loadRom(const char* rom) {
    this->cartridge = new Cartridge(rom);

    this->bus->setCartridge(this->cartridge);
}

void Emulator::tick() {
    this->cpu->tick();
}

// ******************************
// ******************************
// ******************************