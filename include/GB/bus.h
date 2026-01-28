#pragma once
#ifndef BUS_H
#define BUS_H

#include "GB/cartridge.h"
#include "GB/memory/RAM.h"

class Bus {
private:
    Cartridge* cartridge;
    Memory* ram;

public:
    Bus();
    Bus(Cartridge* cartridge);
    ~Bus();

    void setCartridge(Cartridge* cartridge);

    u8 readMemoryU8(u16 address);
    s8 readMemoryS8(u16 address);
    void writeMemoryU8(u16 address, u8 data);
};

#endif // BUS_H