#include "global.h"

class OAM {
private:
    u8* data;
    const u16 MIN_OAM = 0xFE00;
    const u16 MAX_OAM = 0xFE9F;

public:
    OAM();
    ~OAM();

    u8 readMemoryU8(u16 address);
    void writeMemoryU8(u16 address, u8 data);
}