#include "test/sm83_tests.h"

#include "lib/jsmn.h"

// ******************************
// ******************************
// ******************************


void run_sm83_tests() {
    std::string path = "test";
    
    std::vector<std::string> files = getFileListOfDirectory(path.c_str());

    for (int i = 0; i < files.size(); i++) {
        std::string file = files[i];
        
        std::cout << file << std::endl;
    }

    // jsmn_parser p;
    // jsmntok_t t[0xFFFFF];

    // jsmn_init(&p);
    // int r = jsmn_parse(&p, test.c_str(), test.length(), t, 128); // "s" is the char array holding the json content

    // std::cout << r << std::endl;

    // delete t;
}

// ******************************
// ******************************
// ******************************
