#include "GB/SM83.h"

SM83Cpu::SM83Cpu(Bus* bus) {
    this->bus = bus;
}

SM83Cpu::~SM83Cpu() {
    delete bus;
}