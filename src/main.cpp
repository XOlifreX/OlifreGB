#include <iostream>
#include <emulator.h>

int main()
{
    Emulator* e = new Emulator();
    e->run();

    delete e;

    return 0;
}