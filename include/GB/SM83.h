#ifndef SM83_H
#define SM83_H

#include <vector>

#include "global.h"

#pragma pack(push, 1);
union FlagRegister {
    struct {
#ifdef __BIG_ENDIAN__
        u8 Z : 1;
        u8 N : 1;
        u8 H : 1;
        u8 C : 1;
        u8 _ : 4;
#else
        u8 _ : 4;
        u8 C : 1;
        u8 H : 1;
        u8 N : 1;
        u8 Z : 1;
#endif // __BIG_ENDIAN__
    };
    u8 flag;
};
#pragma pack(pop);

#ifdef __BIG_ENDIAN__
#define SM83_AF_REGISTER union { \
    struct { \
        u8 A; \
        union FlagRegister F; \
    }; \
    u16 AF; \
};

#define SM83_REGISTER_PAIR(HIGH, LOW) union { \
    struct { \
        u8 HIGH; \
        u8 LOW; \
    }; \
    u16 PAIR; \
};
#else
#define SM83_AF_REGISTER union { \
    struct { \
        union FlagRegister F; \
        u8 A; \
    }; \
    u16 AF; \
};

#define SM83_REGISTER_PAIR(HIGH, LOW) union { \
    struct { \
        u8 LOW; \
        u8 HIGH; \
    }; \
    u16 PAIR; \
};
#endif // __BIG_ENDIAN__

#define SM83_REGISTER_FILE struct { \
    SM83_AF_REGISTER; \
    SM83_REGISTER_PAIR(B, C); \
    SM83_REGISTER_PAIR(D, E); \
    SM83_REGISTER_PAIR(H, L); \
    u16 SP; \
    u16 PC; \
};

struct RegisterFile {
#pragma pack(push, 1)
    SM83_REGISTER_FILE;
#pragma pack(pop)
};

typedef void (*SM83Instruction)(SM83Cpu*);

enum SM83ExecutionState {
	SM83_FETCH = 3,
	SM83_IDLE_0 = 0,
	SM83_IDLE_1 = 1,
	SM83_EXECUTE = 2,

	SM83_MEMORY_LOAD = 7,
	SM83_MEMORY_STORE = 11,
	SM83_READ_PC = 15,
	SM83_STALL = 19,
	SM83_OP2 = 23,
	SM83_HALT_BUG = 27,
};

class SM83Cpu {
public:
#pragma pack(push, 1)
    union {
        struct RegisterFile registers;
        SM83_REGISTER_FILE;
    };
#pragma pack(pop)

    SM83ExecutionState state;
    SM83Instruction instruction;
};
#undef SM83_REGISTER_FILE

#endif // SM83_H