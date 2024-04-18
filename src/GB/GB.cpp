#include "GB/GB.h"

GB::GB() {
    this->cpu = new SM83Cpu();
}

GB::~GB() {
    delete this->cpu;
}