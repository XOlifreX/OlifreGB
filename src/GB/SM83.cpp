#include "GB/SM83.h"

SM83Cpu::SM83Cpu(Bus* bus) {
    this->bus = bus;

    // *******************
    // Register file setup
    RegisterFile rf;
    rf.FA = 0x0;
    rf.BC = 0x0;
    rf.DE = 0x0;
    rf.HL = 0x0;
    rf.SP = 0x0;
    rf.PC = 0x100;
    
    this->registers = rf;

    // *************
    // Context setup
    CpuContext c;
    c.currentStep = 0;
    c.currentInstruction = NULL;
    c.TP = 0x0;
    c.instruction_exit_early = false;
    c.CBMode = false;

    this->context = c;

    this->IME = true;
}

SM83Cpu::~SM83Cpu() {
    delete bus;
}

// *****

void SM83Cpu::tick() {
    int instruction = this->bus->readMemoryU8(this->registers.PC);

    SM83Opcode opcode = opcodesTable[instruction];

    std::cout << "PC:  0x" << std::hex << this->registers.PC << ": " << opcode.name << std::endl;
    for (u8 i = 0; i < opcode.cycles; i++) {
        std::cout << "    Executing " << std::dec << i+1 << " of " << opcode.name << std::endl;
        (*(opcode.steps)[i])(this);
    }
}