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

enum ROMSizes {
    rom32KiB = 0x00,
    rom64KiB = 0x01,
    rom128KiB = 0x02,
    rom256KiB = 0x03,
    rom512KiB = 0x04,
    rom1MiB = 0x05,
    rom2MiB = 0x06,
    rom4MiB = 0x07,
    rom8MiB = 0x08,
    rom1_1MiB = 0x52,
    rom1_2MiB = 0x53,
    rom1_5MiB = 0x54
};

enum SRAMSizes {
    ram0KiB = 0x00,
    ramNoSRAM = 0x01,
    ram8KiB = 0x02,
    ram32KiB = 0x03,
    ram128KiB = 0x04,
    ram64KiB = 0x05
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
    u16 getROMBankCount();

    void printCartridgeData();
};

#endif // CARTRIDGE_INFO_H