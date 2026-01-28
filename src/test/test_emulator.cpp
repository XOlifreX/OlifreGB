#include "test/test_emulator.h"

// ******************************
// ******************************
// ******************************

TestEmulator::TestEmulator() {}
TestEmulator::~TestEmulator() {}

// ******************************

void TestEmulator::setCPU(SM83Cpu* _cpu) {
    this->cpu = _cpu;
}

void TestEmulator::setBus(Bus* _bus) {
    this->bus = _bus;
}

// ****************

SM83Cpu* TestEmulator::getCPU() {
    return this->cpu;
}

Bus* TestEmulator::getBus() {
    return this->bus;
}

// ******************************
// ******************************
// ******************************