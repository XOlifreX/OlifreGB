#include "emulator.h"

// ******************************
// ******************************
// ******************************

Emulator::Emulator() {
    this->bus = new Bus();
    this->cpu = new SM83Cpu(this->bus);
    
    this->ppu = new PPU(this->bus);

    this->paused = false;
    this->running = true;
    this->ticks = 0;

    this->windowInitialized = false;
}
Emulator::~Emulator() {
    delete this->cpu;

    if (this->bus != NULL)
        delete this->bus;

    delete this->ppu;

    if (this->windowInitialized)
        glfwTerminate();
}

// ******************************

void Emulator::initWindow() {
    if (this->windowInitialized)
        return;

    this->initGLWindow();
}

void Emulator::loadRom(const char* rom) {
    this->cartridge = new Cartridge(rom);
    this->cartridge->printCartridgeData();

    this->bus->setCartridge(this->cartridge);
}

void Emulator::tick() {
    this->cpu->tick();

    // Do a ppu dot 4 times per one M-Cycle
    // TODO: If in Double Speed Mode, this 4 needs to become 2, so make it dynamic 
    for (u8 i = 0; i < 4; i++)
        this->ppu->execDot();
}

// ******************************
// ******************************
// ******************************