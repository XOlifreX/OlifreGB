#include "emulator.h"

// ******************************
// ******************************
// ******************************

Emulator::Emulator() {
    this->gameboy = new GB();
    this->window = new EmuWindow();
}
Emulator::~Emulator() {
    delete this->gameboy;
    delete this->window;
}

// ******************************
// ******************************
// ******************************

void Emulator::loadRom(const char* rom) {
    this->cartridge = new Cartridge(rom);

    this->cartridge->printCartridgeData();
}

void Emulator::run() {
    this->window->runWindow();
}