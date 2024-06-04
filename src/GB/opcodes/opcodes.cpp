#include "GB/opcodes/opcodes.h"

// **********************************

SM83_INSTRUCTION_IMPLEMENTATION(NOP,)

SM83_INSTRUCTION_IMPLEMENTATION(LDBC_PART2, 

)

SM83_INSTRUCTION_IMPLEMENTATION(LDBC, 

)

// **********************************

// const SM83Opcode* opcodesTable8Bit[] = {
//     new SM83Opcode {
//         0x00,
//         "NOP",
//         SM83_INSTRUCTION_DECLARATION(NOP),
//         1,
//         1
//     },
//     new SM83Opcode {
//         0x01,
//         "LD BC, d16",
//         SM83_INSTRUCTION_DECLARATION(LDBC),
//         3,
//         3
//     }
// };