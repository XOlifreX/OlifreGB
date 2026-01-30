#include "GB/SM83.h"

SM83Cpu::SM83Cpu(Bus* bus) {
    this->bus = bus;

    // *******************
    // Register file setup
    RegisterFile rf;
    rf.FA = 0x00;
    rf.BC = 0x00;
    rf.DE = 0x00;
    rf.HL = 0x00;
    rf.SP = 0x00;
    rf.PC = 0x100;
    rf.WZ = 0x00;
    
    this->registers = rf;

    // *************
    // Context setup
    CpuContext c;
    c.currentStep = 0;
    c.currentInstruction = &opcodesTable[0x00]; // Always start with the NOP instruction
    c.TP = 0x0;
    c.instruction_exit_early = false;
    c.CBMode = false;

    this->context = c;

    this->IME = true;

    this->tCycle = 0;
    this->mCycle = 0;
    this->tCycleNumForOneMCycle = SM83_DEFAULT_N_TCYCLES_FOR_1_MCYCLE;
}

SM83Cpu::~SM83Cpu() {
    delete bus;
}

// *****

// Perform one M-cycle
void SM83Cpu::tick() {
    // Get CB prefix instruction
    if (this->context.CBMode) {
        u8 instruction = this->bus->readMemoryU8(this->registers.PC);
        this->context.currentInstruction = &opcodesCbTable[instruction];

        this->context.currentStep = 0;
        this->context.CBMode = false;
        this->context.instruction_exit_early = false;
      
        std::cout << "PC:  0x" << std::hex << this->registers.PC << ": " << this->context.currentInstruction->name << " (CB Prefix)" << std::endl;
    }

    // Execute one instruction M-cycle
    std::cout << "    Executing " << std::dec << this->context.currentStep << " of " << this->context.currentInstruction->name << std::endl;
    (*(this->context.currentInstruction->steps)[this->context.currentStep])(this);

    this->context.currentStep++;
    
    // Early instruction exit
    if (this->context.instruction_exit_early) {
        std::cout << "    Early exit" << std::endl;
        this->context.currentStep = this->context.currentInstruction->cycles;
    }

    this->tCycle += 4;
    this->mCycle++;

    // Fetch next instruction if previous completed
    if (this->context.currentStep == this->context.currentInstruction->cycles) {
        u8 instruction = this->bus->readMemoryU8(this->registers.PC - 1);
        this->context.currentInstruction = &opcodesTable[instruction];
        
        this->context.currentStep = 0;
        this->context.CBMode = false;
        this->context.instruction_exit_early = false;
        
        std::cout << std::endl << std::endl << "PC:  0x" << std::hex << this->registers.PC << ": " << this->context.currentInstruction->name << std::endl;
    }

    this->debug_print_state();
}

void SM83Cpu::debug_print_state() {
    std::cout << "*************************" << std::endl;
    std::cout << "Steps: " << std::dec << this->context.currentStep << std::endl;
    std::cout << "TP:    0x" << std::hex << this->context.TP << std::endl;
    std::cout << "*************************" << std::endl;
    std::cout << "PC:    0x" << std::hex << this->registers.PC << std::endl;
    std::cout << "SP:    0x" << std::hex << this->registers.SP << std::endl;
    std::cout << "AF:    0x" << std::hex << this->registers.FA << std::endl;
    std::cout << "BC:    0x" << std::hex << this->registers.BC << std::endl;
    std::cout << "DE:    0x" << std::hex << this->registers.DE << std::endl;
    std::cout << "HL:    0x" << std::hex << this->registers.HL << std::endl;
    std::cout << "**************************************************" << std::endl;
}