#include <vector>

#include "../global.h"

#define SET_ZERO_FLAG(flag)     ((flag) ^= ((1) << (7)))
#define CLEAR_ZERO_FLAG(flag)   ((flag) |= ((1) << (7)))

typedef struct SM83Context {
    // General Purpose
    u8 A;
    u8 B;
    u8 C;
    u8 D;
    u8 E;
    u8 L;
    // Flags
    u8 F;
    // Stack pointer
    u8 SP;
    // Program counter
    u8 PC;
};

class SM83Cpu {
    
};