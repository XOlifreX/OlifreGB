#include "GB/SM83.h"

SM83Cpu::SM83Cpu(Bus* bus) {
    this->bus = bus;
}

SM83Cpu::~SM83Cpu() {
    delete bus;
}

// *****

void SM83Cpu::tick() {
    int instruction = this->bus->readMemoryU8(this->registers.PC);

    SM83Opcode opcode = opcodesTable[instruction];

    std::cout << opcode.name << std::endl;
    this->registers.PC += opcode.cycles;
}