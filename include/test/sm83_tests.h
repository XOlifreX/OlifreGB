#pragma once
#ifndef SM83_TESTS_H
#define SM83_TESTS_H

#include "global.h"
#include "lib/fs.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cstdlib>

extern void run_sm83_tests();

// *****

struct SM83RamEntry {
    u16 address;
    u8 value;
};

struct SM83CycleEntry {
    bool is_null;
    u16 address;
    u8 value;
    std::string type; // "read" or "write"

    SM83CycleEntry() : is_null(true), address(0), value(0), type("") {}
};

struct SM83TestCaseRegisters {
    u8 a, b, c, d, e, f, h, l; 
    u16 pc, sp;
    std::vector<SM83RamEntry> ram;
};

struct SM83TestCase {
    std::string name;
    SM83TestCaseRegisters initial;
    SM83TestCaseRegisters final;
    std::vector<SM83CycleEntry> cycles;
};

// *****

class SM83Test {
    
};

#endif // SM83_TESTS_H