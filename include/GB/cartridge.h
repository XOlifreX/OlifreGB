#pragma once
#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <map>

#include "global.h"
#include "utils.h"

enum PublisherKey {
    None = 0,
    NintendoRD1,
    Capcom,
    EA,
    HudsonSoft1,
    B_AI,
    KSS,
    PlanningOfficeWADA,
    PCMComplete,
    San_X,
    Kemco,
    SETACorporation,
    Viacom,
    Nintendo,
    Bandai,
    OceanAcclaim,
    Konami1,
    HectorSoft,
    Taito,
    HudsonSoft2,
    Banpresto,
    UbiSoft1,
    Atlus,
    MalibuInteractive,
    Angel,
    BulletProofSoftware,
    Irem,
    Absolute,
    AcclaimEntertainment,
    Activision,
    SammyUSA,
    Konami2,
    HiTechExpressions,
    LJN,
    Matchbox,
    Mattel,
    MiltonBradleyCompany,
    TitusInteractive,
    VirginGames,
    LucasfilmGames,
    OceanSoftware,
    Infogrames,
    InterplayEntertainment,
    Broderbund,
    SculpturedSoftware,
    TheSalesCurve,
    THQ,
    Accolade,
    MisawaEntertainment,
    lozc,
    TokumaShoten,
    TsukudaOriginal,
    Chunsoft,
    VideoSystem,
    OceanAcclaim2,
    Varie,
    YonezawaSpal,
    Kaneko,
    PackInVideo,
    BottomUp,
    KonamiYuGiOh,
    MTO,
    Kodansha,
    UNKNOWN
};

extern const char* publisherNames[];
extern const char* ramSizeNames[];

struct RomSizeInfo {
    const char* name;
    u16 size;
};

class Cartridge {
private:
    bool  initialized;
    char* data;

    int   entrypoint;
    char* nLogo;
    char* title;
    char* mCode;
    char  gbcFlag;
    char* licenseCode;
    char  sgbFlag;
    char  type;
    int   romSize;
    int   ramSize;
    char  destinationCode;
    char  oldLicenseCode;
    char  romVersion;
    char  checksum;
    short gChecksum;

    std::map<int, const char*> cartridgeTypes;
    std::map<int, RomSizeInfo> ROMSizes;
    std::map<int, const char*> oldLicenseeCodes;

    PublisherKey getPublisherKey(const char* key);
    void loadCartridge(const char* path);
public:
    Cartridge(const char* path);
    ~Cartridge();

    void printCartridgeData();

    char readByte(int address);
    void writeByte(int address, char value);
};

#endif // CARTRIDGE_H