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

bool Emulator::loadRom(const char* rom) {
    std::ifstream file(rom, std::ios::binary | std::ios::ate);
    if (!file) {
        std::cerr << "Error: Could not open rom " << rom << std::endl;
        return false;
    }

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    char* buffer = new char[size];

    if (!file.read(buffer, size)) {
        std::cerr << "Error: Could not read file " << rom << std::endl;
        delete[] buffer;
        
        return false;
    }

    Cartridge* cartridge = new Cartridge();
    cartridge->setCartridge(buffer, size);

    file.close();

    std::cout << size << std::endl;

    return true;
}

void Emulator::run() {
    this->window->runWindow();
}