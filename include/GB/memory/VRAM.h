#include "global.h"

class VRAM {
private:
    u8* data;
    const u16 MIN_VRAM = 0x8000;
    const u16 MAX_VRAM = 0x9FFF;

public:
    VRAM();
    ~VRAM();

    u8 readMemoryU8(u16 address);
    void writeMemoryU8(u16 address, u8 data);
}