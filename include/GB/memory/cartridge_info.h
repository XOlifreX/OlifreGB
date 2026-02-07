#pragma once
#ifndef CARTRIDGE_INFO_H
#define CARTRIDGE_INFO_H

#include <map>
#include <vector>
#include <cstring>
#include <string>

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

struct RomSizeInfo {
    const char* name;
    u32 size;
    u16 banks;
};

struct RomInfo {
    u32         entrypoint;
    std::string nLogo;
    std::string title;
    std::string mCode;
    u8          gbcFlag;
    std::string licenseCode;
    u8          sgbFlag;
    u8          type;
    u32         romSize;
    u32         ramSize;
    u8          destinationCode;
    u8          oldLicenseCode;
    u8          romVersion;
    u8          checksum;
    u16         gChecksum;
};

class CartridgeInfo {
public:
    RomInfo cartInfo;

    std::vector<std::string> publisherNames;
    std::vector<std::string> ramSizeNames;

    std::map<int, std::string> cartridgeTypes;
    std::map<int, RomSizeInfo> ROMSizes;
    std::map<int, std::string> oldLicenseeCodes;

    // *****
    
    CartridgeInfo();
    
    // *****

    void setCartridgeInfo(const char* data, u32 size);
    
    PublisherKey getPublisherKey(const char* key);
    u32 getROMSize();

    void printCartridgeData();
};

#endif // CARTRIDGE_INFO_H