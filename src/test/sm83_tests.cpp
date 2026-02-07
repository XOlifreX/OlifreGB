#include "test/sm83_tests.h"

// ******************************
// ******************************
// ******************************

bool run_sm83_test(SM83TestCase test) {
    Cartridge* cartridge = new Cartridge(NULL);
    Bus* bus = new Bus(cartridge);
    SM83Cpu* cpu = new SM83Cpu(bus, false);

    bool passed = true;

    // **************************
    // Init CPU state
    cpu->registers.A = test.initial.a;
    cpu->registers.B = test.initial.b;
    cpu->registers.C = test.initial.c;
    cpu->registers.D = test.initial.d;
    cpu->registers.E = test.initial.e;
    cpu->registers.F.flag = test.initial.f;
    cpu->registers.H = test.initial.h;
    cpu->registers.L = test.initial.l;

    cpu->registers.PC = test.initial.pc;
    cpu->registers.SP = test.initial.sp;

    // Init RAM
    for (std::vector<SM83RamEntry>::const_iterator it = test.initial.ram.begin(); it != test.initial.ram.end(); ++it) {
        const SM83RamEntry ram = *it;
    
        bus->writeMemoryU8(ram.address, ram.value, false);
    }
    
    cpu->context.currentInstruction = &opcodesTable[bus->readMemoryU8(test.initial.pc - 1, false)];

    // **************************
    // Run test
    for (std::vector<SM83CycleEntry>::const_iterator it = test.cycles.begin(); it != test.cycles.end(); ++it) {
        cpu->tick();

        SM83CycleEntry cycle = *it;
        
        if (cycle.is_null)
            continue;
        
        passed &= bus->lastAction.action == cycle.action;
        passed &= bus->lastAction.address == cycle.address;
        passed &= bus->lastAction.value == cycle.value;
    }
    

    // **************************
    // Check CPU final state
    passed &= cpu->registers.A == test.final.a;
    passed &= cpu->registers.B == test.final.b;
    passed &= cpu->registers.C == test.final.c;
    passed &= cpu->registers.D == test.final.d;
    passed &= cpu->registers.E == test.final.e;
    passed &= cpu->registers.F.flag == test.final.f;
    passed &= cpu->registers.H == test.final.h;
    passed &= cpu->registers.L == test.final.l;

    passed &= cpu->registers.PC == test.final.pc;
    passed &= cpu->registers.SP == test.final.sp;

    // Check RAM
    for (std::vector<SM83RamEntry>::const_iterator it = test.final.ram.begin(); it != test.final.ram.end(); ++it) {
        const SM83RamEntry ram = *it;
    
        u8 val = bus->readMemoryU8(ram.address, false);

        passed &= val == ram.value;
    }

    if (!passed)
        std::cout << "Test " << test.name << ": FAILED" << std::endl;

    // deletes bus too
    delete cpu;

    return passed;
}

u16 run_sm83_test_cases(std::vector<SM83TestCase> tests) {
    u16 successCount = 0;
    
    for (std::vector<SM83TestCase>::const_iterator it2 = tests.begin(); it2 != tests.end(); ++it2) {
        SM83TestCase tCase = *it2;
        
        bool temp = run_sm83_test(tCase);

        successCount += temp ? 1 : 0;
    }

    std::cout << std::dec << successCount << "/" << tests.size() << " (" << ((successCount / tests.size()) * 100) << "%) PASSED!" << std::endl;

    return tests.size() - successCount;
}

// **********

void run_sm83_tests() {
    is_test_mode = true;

    u16 failedTestsCount = 0;
    std::string testPath = "test";
    
    // Get list of JSON files
    std::vector<std::string> files = getFileListOfDirectory(testPath.c_str());

    std::cout << "Found " << files.size() << " test files." << std::endl;
    for (std::vector<std::string>::const_iterator it = files.begin(); it != files.end(); ++it) {
        const std::string& file = *it;

        if (file.find(".json") == std::string::npos)
            continue;

        std::vector<SM83TestCase> tests = parse_sm83_test(file);
        std::cout << "Loaded " << tests.size() << " tests." << std::endl;
        
        if (tests.empty()) {
            std::cout << "  Test " << file << " returned empty test cases. Skipping." << std::endl;
            continue;
        }
        
        failedTestsCount += run_sm83_test_cases(tests);
    }

    std::cout << "========= TESTING COMPLETED =========" << std::endl;
    std::cout << "Failed tests: " << std::dec << failedTestsCount << "!" << std::endl;
}

// ******************************
// ******************************
// ******************************
