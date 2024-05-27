#include <iostream>
#include <emulator.h>

int main(int argc, char* argv[])
{
    if (argc == 1) {
        std::cerr << "Please provide a valid path to a .gb rom." << std::endl;
        return 1;
    }

    char* rom = argv[0];
    std::cout << argc << std::endl;

    Emulator* e = new Emulator();
    bool result = e->loadRom(rom);

    if (!result) {
        return 1;
    }

    e->run();

    delete e;

    return 0;
}