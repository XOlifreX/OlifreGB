#include "GB/SM83.h"

SM83Cpu::SM83Cpu(Bus* bus, bool debugPrint) {
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

    this->hrState = this->bus->getHRStateRef();

    this->tCycle = 0;
    this->mCycle = 0;
    this->tCycleNumForOneMCycle = SM83_DEFAULT_N_TCYCLES_FOR_1_MCYCLE;
    
    this->isHalted = false;
    this->isHaltJustSet = false;

    this->debugPrint = debugPrint;
}

SM83Cpu::~SM83Cpu() {
    delete bus;
}

// *****

// Perform one M-cycle
void SM83Cpu::tick() {
    // If CPU is on halt state, check if the CPU should wake up
    if (this->isHalted) {
        if (!this->onHaltCheckWakeUp())
            return;
        else {
            this->isHalted = false;
            this->isHaltJustSet = false;
        }
    }

    bool CBModeInstructionExecuted = false;

    // Get CB prefix instruction
    if (this->context.CBMode) {
        u8 instruction = this->bus->readMemoryU8(this->registers.PC - 1);
        this->context.currentInstruction = &opcodesCbTable[instruction];

        CBModeInstructionExecuted = true;
      
        if (this->debugPrint)
            std::cout << "PC:  0x" << std::hex << this->registers.PC << ": " << this->context.currentInstruction->name << " (CB Prefix)" << std::endl;
    }

    // Execute one instruction M-cycle
    if (this->debugPrint)
        std::cout << "    Executing " << std::dec << this->context.currentStep << " of " << this->context.currentInstruction->name << std::endl;
    
    u8 stepCount = this->context.currentStep - CBModeInstructionExecuted;
    (*(this->context.currentInstruction->steps)[stepCount])(this);
    

    // In case an instruction exits early, set steps forward to propper exit M-cycle
    if (this->context.skipSteps > 0) {
        this->context.currentStep += this->context.skipSteps;
        this->context.skipSteps = 0;
    }
    else {
        this->context.currentStep++;
    }
    
    // Early instruction exit
    if (this->context.instruction_exit_early) {
        if (this->debugPrint)
            std::cout << "    Early exit" << std::endl;
        this->context.currentStep = this->context.currentInstruction->cycles;
    }

    this->tCycle += 4;
    this->mCycle++;

    // Fetch next instruction if previous completed
    if (this->context.currentStep == this->context.currentInstruction->cycles) {
        // Check if an interrupt has occured
        if (!this->hasInterrupt()) {
            // Keep some instruction context when the CB mode has been enabled by instruction 0xCB!
            bool isCBModeEnabled = this->context.currentInstruction->opcode == 0xCB;

            u8 instruction = this->bus->readMemoryU8(this->registers.PC - 1);
            this->context.currentInstruction = &opcodesTable[instruction];
            
            if (!isCBModeEnabled) {
                this->context.currentStep = 0;
                this->context.CBMode = false;
                this->context.instruction_exit_early = false;
            }

            // Handle delayed interrupt enable if reenabled
            if (this->hrState->intrState.intrInProgressOfEnable) {
                this->hrState->intrState.intrInProgressStep++;

                if (this->hrState->intrState.intrInProgressStep > 1) {
                    this->hrState->intrState.intrMasterEnable = true;
                
                    this->hrState->intrState.intrInProgressOfEnable = false;
                    this->hrState->intrState.intrInProgressStep = 0;
                }
            }
        }
        else {
            this->prepareInterrupt();
        }
        
        if (this->debugPrint)
            std::cout << std::endl << std::endl << "PC:  0x" << std::hex << this->registers.PC << ": " << this->context.currentInstruction->name << std::endl;
    
    }

    if (this->debugPrint)
        this->debug_print_state();
}

bool SM83Cpu::hasInterrupt() {
    return this->hrState->intrState.intrMasterEnable
        && this->hrState->intrState.intrEnable
        && this->hrState->intrState.intrFlags > 0x0
        && this->canHandleInterrupt();
}

bool SM83Cpu::canHandleInterrupt() {
    if (this->hrState->intrState.intrEnableVBlank && this->hrState->intrState.intrFlagVBlank)
        return true;
    if (this->hrState->intrState.intrEnableLCD && this->hrState->intrState.intrFlagLCD)
        return true;
    if (this->hrState->intrState.intrEnableTimer && this->hrState->intrState.intrFlagTimer)
        return true;
    if (this->hrState->intrState.intrEnableSerial && this->hrState->intrState.intrFlagSerial)
        return true;
    if (this->hrState->intrState.intrEnableJoypad && this->hrState->intrState.intrFlagJoypad)
        return true;

    return false;
}

void SM83Cpu::prepareInterrupt() {
    // Disable all interrupts
    this->hrState->intrState.intrMasterEnable = false;

    // Check which interrupt to handle (prio list)
    if (this->hrState->intrState.intrFlagVBlank) {
        this->hrState->intrState.intrFlagVBlank = 0;

        this->hrState->intrState.curr_req_intr = Intr_VBlank;
    }
    else if (this->hrState->intrState.intrFlagLCD) {
        this->hrState->intrState.intrFlagLCD = 0;

        this->hrState->intrState.curr_req_intr = Intr_STAT;
    }
    else if (this->hrState->intrState.intrFlagTimer) {
        this->hrState->intrState.intrFlagTimer = 0;

        this->hrState->intrState.curr_req_intr = Intr_Timer;
    }
    else if (this->hrState->intrState.intrFlagSerial) {
        this->hrState->intrState.intrFlagSerial = 0;

        this->hrState->intrState.curr_req_intr = Intr_Serial;
    }
    else if (this->hrState->intrState.intrFlagJoypad) {
        this->hrState->intrState.intrFlagJoypad = 0;

        this->hrState->intrState.curr_req_intr = Intr_Joypad;
    }
    else {
        exit(1);
    }

    // Update flags to the actual register memory
    this->hrState->intrState.memory->updateIFFlags();

    // PC will be one ahead after handling an interrupt. So we decrease it by an extra one
    this->registers.PC--;

    this->context.currentInstruction = &opcodesTable[SM83_STRT_INTR_INDEX];

    this->context.currentStep = 0;
    this->context.CBMode = false;
    this->context.instruction_exit_early = false;
}


bool SM83Cpu::onHaltCheckWakeUp() {
    if (!this->isHalted)
        return true;

    if (this->hrState->intrState.intrMasterEnable) {
        // CPU wakes up if IME is true and ANY interrupt is pending that is enabled
        return this->hrState->intrState.intrEnable & this->hrState->intrState.intrFlags != 0;
    }
    
    // Check halt bug
    if (this->isHaltJustSet) {
        // halt bug can only happen if the conditions are met when halt has just been executed
        this->isHaltJustSet = false;

        bool hasPendingIntr = this->hrState->intrState.intrFlags != 0;

        // Halt bug should occure as the HALT has just happened and it had pending interrupts
        if (hasPendingIntr) {
            // the halt bug effect itself
            this->registers.PC--;

            return true;
        }

        return false;
    }
        
    this->isHaltJustSet = false;

     // Same here, but the interrupt will not be handled as IME is 0.
     return this->hrState->intrState.intrEnable & this->hrState->intrState.intrFlags != 0;
}

void SM83Cpu::handleTimers() {

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