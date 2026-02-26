#pragma once
#ifndef LCD_H
#define LCD_H

#include "GB/memory/memory.h"

#define LCD_RANGE_FROM      0xFF40
#define LCD_RANGE_TO        0xFF6B

#define LCD_CONTROL_LCDC    0xFF40 // LCD Control
#define LCD_STATUS_STAT     0xFF41 // LCD Status
#define LCD_BACKGROUND_SCY  0xFF42 // BG viewporty Y-Pos
#define LCD_BACKGROUND_SCX  0xFF43 // BG viewporty X-Pos
#define LCD_STATUS_LY       0xFF44 // LCD Y coordinate (read-only)
#define LCD_STATUS_LYC      0xFF45 // LY Compare
#define LCD_OAM_DMA         0xFF46 // OAM DMA Source address & start
#define LCD_PALLET_BGP      0xFF47 // BG palette data
#define LCD_PALLET_OBP0     0xFF48 // OBJ palette 0
#define LCD_PALLET_OBP1     0xFF49 // OBJ palette 1
#define LCD_SCROLLING_WY    0xFF4A // Window Y-Pos
#define LCD_SCROLLING_WX    0xFF4B // Window X-Pos +7

#define LCD_PALLET_BCPS     0xFF68 // BGPI - BG color palette specs / index
#define LCD_PALLET_BCPD     0xFF69 // BGPD - BG color palette data
#define LCD_PALLET_OCPS     0xFF6A // OBPI - OBJ color palette specs / index
#define LCD_PALLET_OCPD     0xFF6B // OBPD - OBJ color palette data

#define LCD_IS_IN_REGION(ADDRESS) \
    (ADDRESS >= LCD_CONTROL_LCDC && ADDRESS <= LCD_SCROLLING_WX) || \
    (ADDRESS >= LCD_PALLET_BCPS && ADDRESS <= LCD_PALLET_OCPD)


enum InterruptTypes {
    Intr_None = 0x00,
    Intr_VBlank = 0x40,
    Intr_STAT = 0x48,
    Intr_Timer = 0x50,
    Intr_Serial = 0x58,
    Intr_Joypad = 0x60
};

class LCD;

struct LcdState {
    // 0xFF40: LCDC
    union {
        u8 LcdEnable : 1;
        u8 WindowTileMapArea : 1;
        u8 WindowEnable : 1;
        u8 VRAMAddressingMode : 1; // BG and Window tile data area
        u8 BGTileMapArea : 1;
        u8 ObjSize : 1;
        u8 ObjEnable : 1;
        u8 VRAMEnable : 1; // BG and Window enable/priority

        u8 lcdc;
    };
    
    // 0xFF41: STAT
    union {
        u8 __statUnused : 1;
        u8 LycIntSelect : 1;
        u8 Mode2IntSelect : 1;
        u8 Mode1IntSelect : 1;
        u8 Mode0IntSelect : 1;
        u8 LycIsSameAsLy : 1;
        u8 PpuMode : 2;

        u8 stat;
    };

    // 0xFF42: SCY
    u8 scy;

    // 0xFF43: SCX
    u8 scx;

    // 0xFF44: LY
    u8 ly;

    // 0xFF45: LYC
    u8 lyc;

    // 0xFF46: DMA
    u8 dma;
    
    // 0xFF47: BGP
    union {
        u8 Id3 : 2;
        u8 Id2 : 2;
        u8 Id1 : 2;
        u8 Id0 : 2;
        
        u8 bgp;
    };

    // 0xFF48: OBP0
    u8 obp0;

    // 0xFF49: OBP1
    u8 obp1;

    // 0xFF4A: WY
    u8 wy;

    // 0xFF4B: WX
    u8 wx;
    
    // **********

    LCD* memory;
};

class LCD : public Memory {
private:
    LcdState* state;

    u32 translateAddress(u32 address);
    
    void handleLCDCWrite(u8 value);
public:
    LCD(LcdState* state);
    ~LCD();

    u8 readMemoryU8(u32 address);
    void writeMemoryU8(u32 address, u8 data);
    
    bool isAddressInRange(u32 address);
};

#endif // LCD_H