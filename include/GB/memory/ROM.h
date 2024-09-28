#include "global.h"

class ROM {
private:
    u8* data;
    const u16 MIN_ROM_BANK0 = 0x0;
    const u16 MAX_ROM_BANK0 = 0x3FFF;
    
    const u16 MIN_ROM_BANKN = 0x4000;
    const u16 MAX_ROM_BANKN = 0x7FFF;

public:
    ROM();
    ~ROM();

    u8 readMemoryU8(u16 address);
    void writeMemoryU8(u16 address, u8 data);
}