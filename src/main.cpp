#include "window/emu_window.h"

#include <iostream>

int main()
{
    EmuWindow* w = new EmuWindow();

    w->runWindow();

    delete w;

    return 0;
}