#include "GB/opcodes/opcodes.h"

// **********************************

SM83_INSTRUCTION_IMPLEMENTATION(NOP,)

SM83_INSTRUCTION_IMPLEMENTATION(LDBC_PART2, 
    cpu->BC.PAIR = cpu->read16(cpu->PC.PAIR);
    cpu->PC.PAIR += 2;
    cpu->executionState = SM83_READ_PC;
    cpu->instruction = 
)

SM83_INSTRUCTION_IMPLEMENTATION(LDBC, 
    cpu->executionState = SM83_READ_PC;
    cpu->instruction = SM83_INSTRUCTION_DECLARATION(LDBC_PART2)
)

// **********************************

const SM83Opcode* opcodesTable8Bit[] = {
    new SM83Opcode {
        0x00,
        "NOP",
        SM83_INSTRUCTION_DECLARATION(NOP),
        1,
        1
    },
    new SM83Opcode {
        0x01,
        "LD BC, d16",
        SM83_INSTRUCTION_DECLARATION(LDBC),
        3,
        3
    }
};