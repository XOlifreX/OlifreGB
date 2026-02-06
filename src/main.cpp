#include <iostream>
#include <csignal>
#include <emulator.h>

#include <test/sm83_tests.h>

// ******************************
// ******************************
// ******************************

int main(int argc, char* argv[])
{
    // run_sm83_tests();
    // return 0;

    std::cout << "Starting" << std::endl;
    
    if (argc <= 4) {
        std::cerr << "Please provide a valid path to a .gb rom." << std::endl;
        return 1;
    }

    char* rom = argv[1];
    std::cout << argc << std::endl;

    Emulator* e = new Emulator();
    e->initWindow();
    e->loadRom(rom);
    
    e->run();

    delete e;

    return 0;
}

// ******************************
// ******************************
// ******************************