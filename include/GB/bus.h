#pragma once
#ifndef BUS_H
#define BUS_H

#include "GB/memory/cartridge.h"
#include "GB/memory/RAM.h"
#include "GB/memory/ROM.h"

// **********

enum BusAction {
    BA_None = 0,
    BA_Read,
    BA_Write,
};

struct BusLastAction {
    BusAction action;
    u16 address;
    u8 value;
};

// *****

class Bus {
private:
    Cartridge* cartridge;
    RAM* ram;

    void init(Cartridge* cartridge);
    Memory* getMemoryDestination(u16 address);
public:
    Bus();
    Bus(Cartridge* cartridge);
    ~Bus();

    BusLastAction lastAction;

    void setCartridge(Cartridge* cartridge);

    virtual u8 readMemoryU8(u16 address, bool saveAction = true);
    virtual s8 readMemoryS8(u16 address, bool saveAction = true);
    virtual void writeMemoryU8(u16 address, u8 data, bool saveAction = true);
};

// **********

#endif // BUS_H