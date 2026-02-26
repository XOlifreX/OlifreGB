#include "GB/memory/registers/lcd.h"

// *****

LCD::LCD(LcdState* state) : Memory(LCD_RANGE_FROM, LCD_RANGE_TO) {
    this->state = state;
    this->state->memory = this;
}

LCD::~LCD() {}

// *****

u32 LCD::translateAddress(u32 address) {
    return LCD_IS_IN_REGION(address) ? (address - LCD_RANGE_FROM) : address;
}

void LCD::handleLCDCWrite(u8 value) {
    // LCD & PPU Enable
    if ((value >> 7) & 0x01) {
        
    }
}

// *****

u8 LCD::readMemoryU8(u32 address) {
    if (!this->isAddressInRange(address)) {
        std::cerr << "Out of bounds LCD READ:" << std::endl;
        std::cerr << "Address:  0x" << std::hex << address << std::endl;

        exit(1);
    }

    u32 location = this->translateAddress(address);
    return this->data[location];
}

void LCD::writeMemoryU8(u32 address, u8 value) {
    if (!this->isAddressInRange(address)) {
        std::cerr << "Out of bounds LCD WRITE:" << std::endl;
        std::cerr << "Address:  0x" << std::hex << address << std::endl;

        exit(1);
    }

    switch (address) {
        case LCD_RANGE_FROM:
            break;
        case LCD_RANGE_TO:
            break;
        case LCD_CONTROL_LCDC:
            break;
        case LCD_STATUS_STAT:
            break;
        case LCD_BACKGROUND_SCY:
            break;
        case LCD_BACKGROUND_SCX:
            break;
        case LCD_STATUS_LY:
            break;
        case LCD_STATUS_LYC:
            break;
        case LCD_OAM_DMA:
            break;
        case LCD_PALLET_BGP:
            break;
        case LCD_PALLET_OBP0:
            break;
        case LCD_PALLET_OBP1:
            break;
        case LCD_SCROLLING_WY:
            break;
        case LCD_SCROLLING_WX:
            break;
        case LCD_PALLET_BCPS:
            break;
        case LCD_PALLET_BCPD:
            break;
        case LCD_PALLET_OCPS:
            break;
        case LCD_PALLET_OCPD:
            break;
    }
    
    u32 location = this->translateAddress(address);
    this->data[location] = value;
}

bool LCD::isAddressInRange(u32 address) {
    return LCD_IS_IN_REGION(address);
}