#include "test/sm83_tests.h"
#include "lib/jsmn.h"

// Helper to read file content
static std::string readFile(const std::string& path) {
    std::ifstream t(path);
    if (!t.is_open()) return "";
    std::stringstream buffer;
    buffer << t.rdbuf();
    return buffer.str();
}

// Helper to extract string from token
static std::string get_token_string(const std::string& json, const jsmntok_t& token) {
    if (token.type == JSMN_STRING || token.type == JSMN_PRIMITIVE) {
        return json.substr(token.start, token.end - token.start);
    }
    return "";
}

static u8 parse_u8(const std::string& json, const jsmntok_t& token) {
    try {
        return (u8)std::strtoul(get_token_string(json, token).c_str(), NULL, 10);
    } catch (...) {
        return 0;
    }
}

static u16 parse_u16(const std::string& json, const jsmntok_t& token) {
    try {
        return (u16)std::strtoul(get_token_string(json, token).c_str(), NULL, 10);
    } catch (...) {
        return 0;
    }
}

static void parse_ram(const std::string& json, const jsmntok_t* tokens, int& current, std::vector<SM83RamEntry>& ram) {
    // Current is at "ram" VALUE which is ARRAY
    int size = tokens[current].size;
    current++; // Skip ARRAY token
    
    for(int i=0; i<size; i++) {
        // Each element is ARRAY [addr, val]
        // Current is at sub-array
        int entrySize = tokens[current].size; // Should be 2
        current++; // Skip sub-array token
        
        // Element 0: address
        u16 addr = parse_u16(json, tokens[current]);
        current++;
        
        // Element 1: value
        u8 val = parse_u8(json, tokens[current]);
        current++;
        
        SM83RamEntry entry;
        entry.address = addr;
        entry.value = val;
        ram.push_back(entry);
    }
}

static void parse_registers(const std::string& json, const jsmntok_t* tokens, int& current, SM83TestCaseRegisters& regs) {
    // Current is at OBJECT (initial or final)
    int size = tokens[current].size;
    current++; // Skip OBJECT
    
    for(int i=0; i<size; i++) {
        // Key
        std::string key = get_token_string(json, tokens[current]);
        current++;
        
        // Value
        if (key == "ram") {
            parse_ram(json, tokens, current, regs.ram);
        } else {
            // Register fields
            if (key == "a") regs.a = parse_u8(json, tokens[current]);
            else if (key == "b") regs.b = parse_u8(json, tokens[current]);
            else if (key == "c") regs.c = parse_u8(json, tokens[current]);
            else if (key == "d") regs.d = parse_u8(json, tokens[current]);
            else if (key == "e") regs.e = parse_u8(json, tokens[current]);
            else if (key == "f") regs.f = parse_u8(json, tokens[current]);
            else if (key == "h") regs.h = parse_u8(json, tokens[current]);
            else if (key == "l") regs.l = parse_u8(json, tokens[current]);
            else if (key == "pc") regs.pc = parse_u16(json, tokens[current]);
            else if (key == "sp") regs.sp = parse_u16(json, tokens[current]);
            else {
                // If unknown key in registers, skip it (primitive assumed)
                current++;
            }
        }
    }
}

static void parse_cycles(const std::string& json, const jsmntok_t* tokens, int& current, std::vector<SM83CycleEntry>& cycles) {
    // Current is at "cycles" value (ARRAY)
    int size = tokens[current].size;
    current++;
    
    for (int i=0; i<size; i++) {
        // Check for null entry
        if (tokens[current].type == JSMN_PRIMITIVE && get_token_string(json, tokens[current]) == "null") {
            SM83CycleEntry entry;
            entry.is_null = true;
            cycles.push_back(entry);
            current++;
            continue;
        }

        // Each element is ARRAY [addr, val, type]
        // current is sub-array
        int entrySize = tokens[current].size;
        current++; // skip sub-array
        
        SM83CycleEntry entry;
        entry.is_null = false;
        
        // 0: addr
        entry.address = parse_u16(json, tokens[current]);
        current++;
        
        // 1: val
        entry.value = parse_u8(json, tokens[current]);
        current++;
        
        // 2: type
        entry.type = get_token_string(json, tokens[current]);
        current++;
        
        cycles.push_back(entry);
    }
}

static SM83TestCase parse_test_case(const std::string& json, const jsmntok_t* tokens, int& current) {
    SM83TestCase test;
    // Current is OBJECT
    int size = tokens[current].size;
    current++;
    
    for(int i=0; i<size; i++) {
        std::string key = get_token_string(json, tokens[current]);
        current++;
        
        if (key == "name") {
            test.name = get_token_string(json, tokens[current]);
            current++;
        } else if (key == "initial") {
            parse_registers(json, tokens, current, test.initial);
        } else if (key == "final") {
            parse_registers(json, tokens, current, test.final);
        } else if (key == "cycles") {
            parse_cycles(json, tokens, current, test.cycles);
        } else {
            // Unknown key at top level
            current++; 
        }
    }
    return test;
}

static std::vector<SM83TestCase> parse_json_content(const std::string& json) {
    jsmn_parser p;
    jsmn_init(&p);
    
    int token_count = jsmn_parse(&p, json.c_str(), json.length(), NULL, 0);
    if (token_count < 0) {
        std::cout << "Failed to parse JSON: " << token_count << std::endl;
        return {};
    }
    
    std::vector<jsmntok_t> tokens(token_count);
    jsmn_init(&p);
    jsmn_parse(&p, json.c_str(), json.length(), &tokens[0], token_count);
    
    std::vector<SM83TestCase> tests;
    int current = 0;
    
    // Root should be ARRAY
    if (tokens[current].type != JSMN_ARRAY) {
        std::cout << "Root element is not an array" << std::endl;
        return {};
    }
    
    int num_tests = tokens[current].size;
    current++;
    
    for(int i=0; i<num_tests; i++) {
        tests.push_back(parse_test_case(json, &tokens[0], current));
    }
    
    return tests;
}


void run_sm83_tests() {
    std::string testPath = "test";
    
    // Get list of JSON files
    std::vector<std::string> files = getFileListOfDirectory(testPath.c_str());
    std::cout << "Found " << files.size() << " test files." << std::endl;

    for (std::vector<std::string>::const_iterator it = files.begin(); it != files.end(); ++it) {
        const std::string& file = *it;
        // Only process .json files
        if (file.find(".json") == std::string::npos) continue;

        std::string fullPath = testPath + "/" + file;
        std::string content = readFile(fullPath);
        
        if (content.empty()) {
            std::cout << "Failed to read file: " << fullPath << std::endl;
            continue;
        }

        std::cout << "Parsing " << file << "... ";
        std::vector<SM83TestCase> tests = parse_json_content(content);
        std::cout << "Loaded " << tests.size() << " tests." << std::endl;
        
        if (!tests.empty()) {
            // Optional: Print first test name to verify
            // std::cout << "  First test: " << tests[0].name << std::endl;
        }
        
        // TODO: Run the tests here
    }
}
