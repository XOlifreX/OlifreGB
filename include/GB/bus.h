#pragma once
#ifndef BUS_H
#define BUS_H

#include "GB/cartridge.h"

class Bus {
private:
    Cartridge* cartridge;

public:
    Bus();
    Bus(Cartridge* cartridge);
    ~Bus();

    void setCartridge(Cartridge* cartridge);

    u8 readMemoryU8(int address);
    void writeMemoryU8(int address, u8 data);
};

#endif // SM83_H