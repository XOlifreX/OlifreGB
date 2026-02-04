#pragma once
#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <map>
#include <algorithm>

#include "global.h"
#include "utils.h"

#include "GB/memory/memory.h"

#define ROM_RANGE_FROM 0x0000
#define ROM_RANGE_TO 0x3FFF

#define ROM_RANGE_BANKN_FROM 0x4000
#define ROM_RANGE_BANKN_TO 0x7FFF

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
    u32 size;
    u16 banks;
};

class Cartridge: public Memory {
private:
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
    Cartridge();
    Cartridge(const char* path);
    ~Cartridge();

    void printCartridgeData();

    u8 readMemoryU8(u16 address);
    void writeMemoryU8(u16 address, u8 data);

    u8* getROMBank(u8 bank);
};

#endif // CARTRIDGE_H