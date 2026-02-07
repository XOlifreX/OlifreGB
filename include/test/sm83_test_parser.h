#pragma once
#ifndef SM83_TEST_PARSER_H
#define SM83_TEST_PARSER_H

#include "global.h"
#include "lib/fs.h"
#include "GB/bus.h"
#include "test/test_mode.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cstdlib>

// *****

struct SM83RamEntry {
    u16 address;
    u8 value;
};

struct SM83CycleEntry {
    bool is_null;
    u16 address;
    u8 value;
    BusAction action; // "read" or "write"

    SM83CycleEntry() : is_null(true), address(0), value(0), action(BA_None) {}
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

extern std::vector<SM83TestCase> parse_sm83_test(const std::string& file);

// *****

#endif // SM83_TEST_PARSER_H