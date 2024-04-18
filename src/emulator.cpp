#include "emulator.h"

Emulator::Emulator() {
    this->gameboy = new GB();
    this->window = new EmuWindow();
}
Emulator::~Emulator() {
    delete this->gameboy;
    delete this->window;
}

void Emulator::run() {
    this->window->runWindow();
}