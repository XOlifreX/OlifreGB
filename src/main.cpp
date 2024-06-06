#include <iostream>
#include <csignal>
#include <emulator.h>

int main(int argc, char* argv[])
{
    std::cout << "Starting" << std::endl;
    
    if (argc <= 4) {
        std::cerr << "Please provide a valid path to a .gb rom." << std::endl;
        return 1;
    }

    char* rom = argv[1];
    std::cout << argc << std::endl;

    Emulator* e = new Emulator();
    e->loadRom(rom);

    e->run();

    delete e;

    return 0;
} 