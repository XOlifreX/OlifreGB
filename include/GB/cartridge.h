#pragma once
#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <iostream>
#include <fstream>
#include "utils.h"

class Cartridge {
private:
    bool  initialized;
    char* data;

    int   entrypoint;
    char* nLogo;
    char* title;
    char* mCode;
    char  gbcFlag;
    short licenseCode;
    char  sgbFlag;
    char  type;
    int   romSize;
    int   ramSize;
    char  destinationCode;
    char  oldLicenseCode;
    char  romVersion;
    char  checksum;
    short gChecksum;

    void loadCartridge(char* path);
public:
    Cartridge(char* path);
    ~Cartridge();

    void printCartridgeData();

    char readByte(int address);
    void writeByte(int address, char value);
};

#endif // CARTRIDGE_H