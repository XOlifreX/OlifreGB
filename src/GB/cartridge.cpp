#include "GB/cartridge.h"

// ******************************

const char* publisherNames[] = {
    "None",
    "Nintendo Research & Development 1",
    "Capcom",
    "EA (Electronic Arts)",
    "Hudson Soft",
    "B-AI",
    "KSS",
    "Planning Office WADA",
    "PCM Complete",
    "San-X",
    "Kemco",
    "SETA Corporation",
    "Viacom",
    "Nintendo",
    "Bandai",
    "Ocean Software/Acclaim Entertainment",
    "Konami",
    "HectorSoft",
    "Taito",
    "Hudson Soft",
    "Banpresto",
    "Ubi Soft",
    "Atlus",
    "Malibu Interactive",
    "Angel",
    "Bullet-Proof Software",
    "Irem",
    "Absolute",
    "Acclaim Entertainment",
    "Activision",
    "Sammy USA Corporation",
    "Konami",
    "Hi Tech Expressions",
    "LJN",
    "Matchbox",
    "Mattel",
    "Milton Bradley Company",
    "Titus Interactive",
    "Virgin Games Ltd.",
    "Lucasfilm Games",
    "Ocean Software",
    "Infogrames",
    "Interplay Entertainment",
    "Broderbund",
    "Sculptured Software",
    "The Sales Curve Limited",
    "THQ",
    "Accolade",
    "Misawa Entertainment",
    "lozc",
    "Tokuma Shoten",
    "Tsukuda Original",
    "Chunsoft Co.",
    "Video System",
    "Ocean Software/Acclaim Entertainment",
    "Varie",
    "Yonezawa/s’pal",
    "Kaneko",
    "Pack-In-Video",
    "Bottom Up",
    "Konami (Yu-Gi-Oh!)",
    "MTO",
    "Kodansha",
    "Unknown"
};

const char* ramSizeNames[] = {
    "0",
    "-",
    "8 KiB",
    "32 KiB",
    "128 KiB",
    "64 KiB"
};

// ******************************
// ******************************
// ******************************

Cartridge::Cartridge(const char* path) {
    this->initialized = false;

    this->cartridgeTypes[0x00] = "ROM ONLY";
    this->cartridgeTypes[0x01] = "MBC1";
    this->cartridgeTypes[0x02] = "MBC1+RAM";
    this->cartridgeTypes[0x03] = "MBC1+RAM+BATTERY";
    this->cartridgeTypes[0x05] = "MBC2";
    this->cartridgeTypes[0x06] = "MBC2+BATTERY";
    this->cartridgeTypes[0x08] = "ROM+RAM 9";
    this->cartridgeTypes[0x09] = "ROM+RAM+BATTERY 9";
    this->cartridgeTypes[0x0B] = "MMM01";
    this->cartridgeTypes[0x0C] = "MMM01+RAM";
    this->cartridgeTypes[0x0D] = "MMM01+RAM+BATTERY";
    this->cartridgeTypes[0x0F] = "MBC3+TIMER+BATTERY";
    this->cartridgeTypes[0x10] = "MBC3+TIMER+RAM+BATTERY 10";
    this->cartridgeTypes[0x11] = "MBC3";
    this->cartridgeTypes[0x12] = "MBC3+RAM 10";
    this->cartridgeTypes[0x13] = "MBC3+RAM+BATTERY 10";
    this->cartridgeTypes[0x19] = "MBC5";
    this->cartridgeTypes[0x1A] = "MBC5+RAM";
    this->cartridgeTypes[0x1B] = "MBC5+RAM+BATTERY";
    this->cartridgeTypes[0x1C] = "MBC5+RUMBLE";
    this->cartridgeTypes[0x1D] = "MBC5+RUMBLE+RAM";
    this->cartridgeTypes[0x1E] = "MBC5+RUMBLE+RAM+BATTERY";
    this->cartridgeTypes[0x20] = "MBC6";
    this->cartridgeTypes[0x22] = "MBC7+SENSOR+RUMBLE+RAM+BATTERY";
    this->cartridgeTypes[0xFC] = "POCKET CAMERA";
    this->cartridgeTypes[0xFD] = "BANDAI TAMA5";
    this->cartridgeTypes[0xFE] = "HuC3";
    this->cartridgeTypes[0xFF] = "HuC1+RAM+BATTERY";


    RomSizeInfo info;
    info.name = "32 KiB";
    info.banks = 2;
    info.size = 32768;
    this->ROMSizes[0x00] = info;
    info.name = "64 KiB";
    info.banks = 4;
    info.size = 65536;
    this->ROMSizes[0x01] = info;
    info.name = "128 KiB";
    info.banks = 8;
    info.size = 131072;
    this->ROMSizes[0x02] = info;
    info.name = "256 KiB";
    info.banks = 16;
    info.size = 262144;
    this->ROMSizes[0x03] = info;
    info.name = "512 KiB";
    info.banks = 32;
    info.size = 524288;
    this->ROMSizes[0x04] = info;
    info.name = "1 MiB";
    info.banks = 64;
    info.size = 1048576;
    this->ROMSizes[0x05] = info;
    info.name = "2 MiB";
    info.banks = 128;
    info.size = 2097152;
    this->ROMSizes[0x06] = info;
    info.name = "4 MiB";
    info.banks = 256;
    info.size = 4194304;
    this->ROMSizes[0x07] = info;
    info.name = "8 MiB";
    info.banks = 512;
    info.size = 8388608;
    this->ROMSizes[0x08] = info;
    info.name = "1.1 MiB";
    info.banks = 72;
    info.size = 1153434;
    this->ROMSizes[0x52] = info;
    info.name = "1.2 MiB";
    info.banks = 80;
    info.size = 1258292;
    this->ROMSizes[0x53] = info;
    info.name = "1.5 MiB";
    info.banks = 96;
    info.size = 1572864;
    this->ROMSizes[0x54] = info;

    this->oldLicenseeCodes[0x00] = "None";
    this->oldLicenseeCodes[0x01] = "Nintendo";
    this->oldLicenseeCodes[0x08] = "Capcom";
    this->oldLicenseeCodes[0x09] = "HOT-B";
    this->oldLicenseeCodes[0x0A] = "Jaleco";
    this->oldLicenseeCodes[0x0B] = "Coconuts Japan";
    this->oldLicenseeCodes[0x0C] = "Elite Systems";
    this->oldLicenseeCodes[0x13] = "EA (Electronic Arts)";
    this->oldLicenseeCodes[0x18] = "Hudson Soft";
    this->oldLicenseeCodes[0x19] = "ITC Entertainment";
    this->oldLicenseeCodes[0x1A] = "Yanoman";
    this->oldLicenseeCodes[0x1D] = "Japan Clary";
    this->oldLicenseeCodes[0x1F] = "Virgin Games Ltd.3";
    this->oldLicenseeCodes[0x24] = "PCM Complete";
    this->oldLicenseeCodes[0x25] = "San-X";
    this->oldLicenseeCodes[0x28] = "Kemco";
    this->oldLicenseeCodes[0x29] = "SETA Corporation";
    this->oldLicenseeCodes[0x30] = "Infogrames5";
    this->oldLicenseeCodes[0x31] = "Nintendo";
    this->oldLicenseeCodes[0x32] = "Bandai";
    this->oldLicenseeCodes[0x33] = "Indicates that the New licensee code should be used instead.";
    this->oldLicenseeCodes[0x34] = "Konami";
    this->oldLicenseeCodes[0x35] = "HectorSoft";
    this->oldLicenseeCodes[0x38] = "Capcom";
    this->oldLicenseeCodes[0x39] = "Banpresto";
    this->oldLicenseeCodes[0x3C] = ".Entertainment i";
    this->oldLicenseeCodes[0x3E] = "Gremlin";
    this->oldLicenseeCodes[0x41] = "Ubi Soft1";
    this->oldLicenseeCodes[0x42] = "Atlus";
    this->oldLicenseeCodes[0x44] = "Malibu Interactive";
    this->oldLicenseeCodes[0x46] = "Angel";
    this->oldLicenseeCodes[0x47] = "Spectrum Holoby";
    this->oldLicenseeCodes[0x49] = "Irem";
    this->oldLicenseeCodes[0x4A] = "Virgin Games Ltd.3";
    this->oldLicenseeCodes[0x4D] = "Malibu Interactive";
    this->oldLicenseeCodes[0x4F] = "U.S. Gold";
    this->oldLicenseeCodes[0x50] = "Absolute";
    this->oldLicenseeCodes[0x51] = "Acclaim Entertainment";
    this->oldLicenseeCodes[0x52] = "Activision";
    this->oldLicenseeCodes[0x53] = "Sammy USA Corporation";
    this->oldLicenseeCodes[0x54] = "GameTek";
    this->oldLicenseeCodes[0x55] = "Park Place";
    this->oldLicenseeCodes[0x56] = "LJN";
    this->oldLicenseeCodes[0x57] = "Matchbox";
    this->oldLicenseeCodes[0x59] = "Milton Bradley Company";
    this->oldLicenseeCodes[0x5A] = "Mindscape";
    this->oldLicenseeCodes[0x5B] = "Romstar";
    this->oldLicenseeCodes[0x5C] = "Naxat Soft13";
    this->oldLicenseeCodes[0x5D] = "Tradewest";
    this->oldLicenseeCodes[0x60] = "Titus Interactive";
    this->oldLicenseeCodes[0x61] = "Virgin Games Ltd.3";
    this->oldLicenseeCodes[0x67] = "Ocean Software";
    this->oldLicenseeCodes[0x69] = "EA (Electronic Arts)";
    this->oldLicenseeCodes[0x6E] = "Elite Systems";
    this->oldLicenseeCodes[0x6F] = "Electro Brain";
    this->oldLicenseeCodes[0x70] = "Infogrames5";
    this->oldLicenseeCodes[0x71] = "Interplay Entertainment";
    this->oldLicenseeCodes[0x72] = "Broderbund";
    this->oldLicenseeCodes[0x73] = "Sculptured Software6";
    this->oldLicenseeCodes[0x75] = "The Sales Curve Limited7";
    this->oldLicenseeCodes[0x78] = "THQ";
    this->oldLicenseeCodes[0x79] = "Accolade";
    this->oldLicenseeCodes[0x7A] = "Triffix Entertainment";
    this->oldLicenseeCodes[0x7C] = "Microprose";
    this->oldLicenseeCodes[0x7F] = "Kemco";
    this->oldLicenseeCodes[0x80] = "Misawa Entertainment";
    this->oldLicenseeCodes[0x83] = "Lozc";
    this->oldLicenseeCodes[0x86] = "Tokuma Shoten";
    this->oldLicenseeCodes[0x8B] = "Bullet-Proof Software2";
    this->oldLicenseeCodes[0x8C] = "Vic Tokai";
    this->oldLicenseeCodes[0x8E] = "Ape";
    this->oldLicenseeCodes[0x8F] = "I’Max";
    this->oldLicenseeCodes[0x91] = "Chunsoft Co.8";
    this->oldLicenseeCodes[0x92] = "Video System";
    this->oldLicenseeCodes[0x93] = "Tsubaraya Productions";
    this->oldLicenseeCodes[0x95] = "Varie";
    this->oldLicenseeCodes[0x96] = "Yonezawa/S’Pal";
    this->oldLicenseeCodes[0x97] = "Kemco";
    this->oldLicenseeCodes[0x99] = "Arc";
    this->oldLicenseeCodes[0x9A] = "Nihon Bussan";
    this->oldLicenseeCodes[0x9B] = "Tecmo";
    this->oldLicenseeCodes[0x9C] = "Imagineer";
    this->oldLicenseeCodes[0x9D] = "Banpresto";
    this->oldLicenseeCodes[0x9F] = "Nova";
    this->oldLicenseeCodes[0xA1] = "Hori Electric";
    this->oldLicenseeCodes[0xA2] = "Bandai";
    this->oldLicenseeCodes[0xA4] = "Konami";
    this->oldLicenseeCodes[0xA6] = "Kawada";
    this->oldLicenseeCodes[0xA7] = "Takara";

    if (path == NULL) {
        this->data = (char*)malloc(sizeof(u8) * 0x4000);
        this->romSize = 0x06;
        return;
    }

    this->loadCartridge(path);
}

Cartridge::~Cartridge() {
    delete this->data;
}

// I HATE THIS
PublisherKey Cartridge::getPublisherKey(const char* key) {
    if (std::strcmp(key, "") == 0) return None;
    if (std::strcmp(key, "01") == 0) return NintendoRD1;
    if (std::strcmp(key, "08") == 0) return Capcom;
    if (std::strcmp(key, "13") == 0) return EA;
    if (std::strcmp(key, "18") == 0) return HudsonSoft1;
    if (std::strcmp(key, "19") == 0) return B_AI;
    if (std::strcmp(key, "20") == 0) return KSS;
    if (std::strcmp(key, "22") == 0) return PlanningOfficeWADA;
    if (std::strcmp(key, "24") == 0) return PCMComplete;
    if (std::strcmp(key, "25") == 0) return San_X;
    if (std::strcmp(key, "28") == 0) return Kemco;
    if (std::strcmp(key, "29") == 0) return SETACorporation;
    if (std::strcmp(key, "30") == 0) return Viacom;
    if (std::strcmp(key, "31") == 0) return Nintendo;
    if (std::strcmp(key, "32") == 0) return Bandai;
    if (std::strcmp(key, "33") == 0) return OceanAcclaim;
    if (std::strcmp(key, "34") == 0) return Konami1;
    if (std::strcmp(key, "35") == 0) return HectorSoft;
    if (std::strcmp(key, "37") == 0) return Taito;
    if (std::strcmp(key, "38") == 0) return HudsonSoft2;
    if (std::strcmp(key, "39") == 0) return Banpresto;
    if (std::strcmp(key, "41") == 0) return UbiSoft1;
    if (std::strcmp(key, "42") == 0) return Atlus;
    if (std::strcmp(key, "44") == 0) return MalibuInteractive;
    if (std::strcmp(key, "46") == 0) return Angel;
    if (std::strcmp(key, "47") == 0) return BulletProofSoftware;
    if (std::strcmp(key, "49") == 0) return Irem;
    if (std::strcmp(key, "50") == 0) return Absolute;
    if (std::strcmp(key, "51") == 0) return AcclaimEntertainment;
    if (std::strcmp(key, "52") == 0) return Activision;
    if (std::strcmp(key, "53") == 0) return SammyUSA;
    if (std::strcmp(key, "54") == 0) return Konami2;
    if (std::strcmp(key, "55") == 0) return HiTechExpressions;
    if (std::strcmp(key, "56") == 0) return LJN;
    if (std::strcmp(key, "57") == 0) return Matchbox;
    if (std::strcmp(key, "58") == 0) return Mattel;
    if (std::strcmp(key, "59") == 0) return MiltonBradleyCompany;
    if (std::strcmp(key, "60") == 0) return TitusInteractive;
    if (std::strcmp(key, "61") == 0) return VirginGames;
    if (std::strcmp(key, "64") == 0) return LucasfilmGames;
    if (std::strcmp(key, "67") == 0) return OceanSoftware;
    if (std::strcmp(key, "69") == 0) return EA;
    if (std::strcmp(key, "70") == 0) return Infogrames;
    if (std::strcmp(key, "71") == 0) return InterplayEntertainment;
    if (std::strcmp(key, "72") == 0) return Broderbund;
    if (std::strcmp(key, "73") == 0) return SculpturedSoftware;
    if (std::strcmp(key, "75") == 0) return TheSalesCurve;
    if (std::strcmp(key, "78") == 0) return THQ;
    if (std::strcmp(key, "79") == 0) return Accolade;
    if (std::strcmp(key, "80") == 0) return MisawaEntertainment;
    if (std::strcmp(key, "83") == 0) return lozc;
    if (std::strcmp(key, "86") == 0) return TokumaShoten;
    if (std::strcmp(key, "87") == 0) return TsukudaOriginal;
    if (std::strcmp(key, "91") == 0) return Chunsoft;
    if (std::strcmp(key, "92") == 0) return VideoSystem;
    if (std::strcmp(key, "93") == 0) return OceanAcclaim2;
    if (std::strcmp(key, "95") == 0) return Varie;
    if (std::strcmp(key, "96") == 0) return YonezawaSpal;
    if (std::strcmp(key, "97") == 0) return Kaneko;
    if (std::strcmp(key, "99") == 0) return PackInVideo;
    if (std::strcmp(key, "9H") == 0) return BottomUp;
    if (std::strcmp(key, "A4") == 0) return KonamiYuGiOh;
    if (std::strcmp(key, "BL") == 0) return MTO;
    if (std::strcmp(key, "DK") == 0) return Kodansha;
    return UNKNOWN;
}

void Cartridge::loadCartridge(const char* path) {
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    if (!file) {
        std::cerr << "Error: Could not find rom file " << path << std::endl;
        exit(1);
    }

    int size = (int)file.tellg();
    file.seekg(0, std::ios::beg);

    char* buffer = new char[size];

    if (!file.read(buffer, size)) {
        std::cerr << "Error: Could not read rom file " << path << std::endl;
        delete[] buffer;
        
        exit(1);
    }

    file.close();

    this->entrypoint = charsToInt(buffer, size, 0x100);
    this->nLogo = spliceChars(buffer, size, 0x104, 0x2F);
    this->title = spliceChars(buffer, size, 0x134, 0xF);
    this->mCode = spliceChars(buffer, size, 0x13F, 0x4);
    this->gbcFlag = buffer[0x143];
    this->licenseCode = spliceChars(buffer, size, 0x144, 0x2);
    this->sgbFlag = buffer[0x146];
    this->type = buffer[0x147];
    this->romSize = buffer[0x148];
    this->ramSize = buffer[0x149];
    this->destinationCode = buffer[0x14A];
    this->oldLicenseCode = buffer[0x14B];
    this->romVersion = buffer[0x14C];
    this->checksum = buffer[0x14D];
    this->gChecksum = charsToShort(buffer, size, 0x14E);

    this->data = buffer;
}

// ******************************
// ******************************
// ******************************


void Cartridge::printCartridgeData() {
    std::cout << "Title: " << this->title << std::endl;
    std::cout << "Manufacturer: " << this->mCode << std::endl;

    std::cout << "License code: " << publisherNames[getPublisherKey(this->licenseCode)] << std::endl;
    std::cout << "Cartridge type: " << this->cartridgeTypes[this->type] << std::endl;

    std::cout << "ROM size: " << this->ROMSizes[this->romSize].name << std::endl;
    std::cout << "RAM size: " << ramSizeNames[this->ramSize] << std::endl;

    std::cout << "Old licensee: " << this->oldLicenseeCodes[this->oldLicenseCode] << std::endl;
}

char Cartridge::readByte(u16 address) {
    int actualRomSize = this->ROMSizes[this->romSize].size;
    if (address > actualRomSize || address < 0) {
        std::cerr << "Out of bounds READ:" << std::endl;
        std::cerr << "Address:  0x" << std::hex << address << std::endl;
        std::cerr << "ROM size: 0x" << std::hex << actualRomSize;

        exit(1);
    }

    return this->data[address];
}

void Cartridge::writeByte(u16 address, u8 value) {
    int actualRomSize = this->ROMSizes[this->romSize].size;
    if (address > actualRomSize || address < 0) {
        std::cerr << "Out of bounds WRITE:" << std::endl;
        std::cerr << "Address:  0x" << std::hex << address << std::endl;
        std::cerr << "ROM size: 0x" << std::hex << actualRomSize;

        exit(1);
    }

    this->data[address] = value;
}