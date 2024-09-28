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

// Perform one CPU cycle
void SM83Cpu::tick() {
    // Get instruction
    if (this->context.currentInstruction == NULL) {
        u8 instruction = this->bus->readMemoryU8(this->registers.PC);
        this->context.currentInstruction = &opcodesTable[instruction];
        
        this->context.currentStep = 0;
        this->context.CBMode = false;
        this->context.instruction_exit_early = false;
        
        std::cout << std::endl << std::endl << "PC:  0x" << std::hex << this->registers.PC << ": " << this->context.currentInstruction->name << std::endl;
    }

    // Get CB prefix instruction
    if (this->context.CBMode) {
        u8 instruction = this->bus->readMemoryU8(this->registers.PC);
        this->context.currentInstruction = &opcodesCbTable[instruction];

        this->context.currentStep = 0;
        this->context.CBMode = false;
        this->context.instruction_exit_early = false;
      
        std::cout << "PC:  0x" << std::hex << this->registers.PC << ": " << this->context.currentInstruction->name << " (CB Prefix)" << std::endl;
    }

    // Execute one instruction cycle
    std::cout << "    Executing " << std::dec << this->context.currentStep << " of " << this->context.currentInstruction->name << std::endl;
    (*(this->context.currentInstruction->steps)[this->context.currentStep])(this);

    this->context.currentStep++;

    // Early instruction exit
    if (this->context.instruction_exit_early) {
        std::cout << "    Early exit" << std::endl;
        this->context.instruction_exit_early = false;
        this->context.currentInstruction = NULL;
    }

    if (this->context.currentStep == this->context.currentInstruction->cycles) {
        this->context.currentInstruction = NULL;
    }
}