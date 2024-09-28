#include "global.h"

#define INTERUPT_ENABLE_REGISTER = 0xFFFF;

class RAM {
private:
    u8* data;
    const u16 MAX_RAM_SIZE = 0xFFFF;

    

public:
    RAM();
    ~RAM();

    u8 readMemoryU8(u16 address);
    void writeMemoryU8(u16 address, u8 data);
}

// https://gbdev.io/pandocs/Memory_Map.html#fea0feff-range
