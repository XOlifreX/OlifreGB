#include "global.h"

class WRAM {
private:
    u8* data;
    const u16 MIN_WRAM_BANK0 = 0xC000;
    const u16 MAX_WRAM_BANK0 = 0xCFFF;
    
    const u16 MIN_WRAM_GBC_BANKN = 0xD000;
    const u16 MAX_WRAM_GBC_BANKN = 0xDFFF;

    // Echo RAM => 0xE000 to 0xFDFF
    // Mirrors WRAM 0xF000 => 0xDDFF
    // So, when Echo RAM read/write, use WRAM instead

public:
    WRAM();
    ~WRAM();

    u8 readMemoryU8(u16 address);
    void writeMemoryU8(u16 address, u8 data);
}