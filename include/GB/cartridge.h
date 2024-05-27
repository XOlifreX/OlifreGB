#pragma once
#include <iostream>

class Cartridge {
private:
    bool initialized;
    char* data;
    int size;

public:
    Cartridge();
    ~Cartridge();

    void setCartridge(char* data, int size);

    char readByte(int address);
    void writeByte(int address, char value);
};