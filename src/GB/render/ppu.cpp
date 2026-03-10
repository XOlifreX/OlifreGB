#include "GB/render/ppu.h"

// *****

PPU::PPU(Bus* bus) {
    this->bus = bus;

    HardwareRegisterState* temp = this->bus->getHRStateRef();
    this->lcdState = &temp->LcdState;

    this->state.mode = PPU_Mode2;
    
    this->state.modeState.mode2.step = 0;
    this->state.modeState.mode2.currSpriteIndex = 0;
}
PPU::~PPU() {}

// *****

// Mode 2: OAM Scan
// Goes over all 40 sprites in the OAM RAM and checks which ones need to be rendered on the current scanline
// Lasts 80 dots, so 1 sprite per 2 dots. Thus, this process is divided in 2 steps.
void PPU::execMode2() {
    // Start Mode 2 (OAM Scan) in a clean state
    if (this->lcdState->ly == 0x00) {
        this->spriteBuffer.clear();
        this->state.modeState.mode2.step = 0;
        this->state.modeState.mode2.currSpriteIndex = 0;
    }

    if (this->spriteBuffer.size() >= 10)
        return;
    
    // Step 1: Get Nth sprite data
    if (!this->state.modeState.mode2.step) {
        this->state.modeState.mode2.step++;
        
        ObjectInfo sprite;
        sprite.yPos  = this->bus->readMemoryU8(OAM_RANGE_FROM + (4 * this->state.modeState.mode2.currSpriteIndex));
        sprite.xPos  = this->bus->readMemoryU8(OAM_RANGE_FROM + (4 * this->state.modeState.mode2.currSpriteIndex) + 1);
        sprite.index = this->bus->readMemoryU8(OAM_RANGE_FROM + (4 * this->state.modeState.mode2.currSpriteIndex) + 2);
        sprite.flags = this->bus->readMemoryU8(OAM_RANGE_FROM + (4 * this->state.modeState.mode2.currSpriteIndex) + 3);
 
        this->state.modeState.mode2.currSprite = sprite;
    }
    else {
        // Step 2: Check if sprite needs to be used during rendering for this scanline

        // Is sprite 8x16 of 8x8
        bool isTallSprite = this->lcdState->ObjSize;

        u8 yPosMin = this->state.modeState.mode2.currSprite.yPos;
        u8 yPosMax = this->state.modeState.mode2.currSprite.yPos + (8 * (isTallSprite + 1));
        u8 internalYPos = this->lcdState->ly + 16;

        // Is the sprite in current Y pos range
        if (internalYPos >= yPosMin && internalYPos < yPosMax) {
            // Push to sprite buffer if OK
            this->spriteBuffer.push_back(this->state.modeState.mode2.currSprite);
        }

        this->state.modeState.mode2.step = 0;
        this->state.modeState.mode2.currSpriteIndex++;
    }
}

void PPU::execMode3() {

}

void PPU::execMode0() {

}

void PPU::execMode1() {

}

void PPU::tryModeChange() {
    switch (this->state.mode) {
        case PPU_Mode2:
            if (this->state.currModeDotCount >= MODE2_MAX_DOT_COUNT) {
                this->state.mode = PPU_Mode3;
                this->state.currModeEstimatedTotalDotCount = MODE3_MIN_DOT_COUNT;
                this->state.currModeDotCount = 0;
                this->state.earlyModeExit = false;
            }
            break;
        case PPU_Mode3:
            if (this->state.currModeDotCount <= MODE3_MIN_DOT_COUNT && (
                    this->state.currModeDotCount >= MODE3_MAX_DOT_COUNT ||
                    this->state.earlyModeExit
                )
            ) {
                this->state.mode = PPU_Mode0;
                this->state.currModeEstimatedTotalDotCount = SCANLINE_MAX_DOT_COUNT - this->state.currScanLineDotCount;
                this->state.currModeDotCount = 0;
                this->state.earlyModeExit = false;
            }
            break;
        case PPU_Mode0:
            if (this->state.currScanLineDotCount >= SCANLINE_MAX_DOT_COUNT) {
                this->state.mode = PPU_Mode2;
                this->state.currModeEstimatedTotalDotCount = MODE2_MAX_DOT_COUNT;
                this->state.currModeDotCount = 0;
                this->state.currScanLineDotCount = 0;
                this->state.earlyModeExit = false;
                
                this->lcdState->memory->writeMemoryU8(LCD_STATUS_LY, this->lcdState->ly + 1);
            }
        case PPU_Mode1:
            if (this->state.currScanLineDotCount >= SCANLINE_MAX_DOT_COUNT) {
                this->state.currModeDotCount = 0;
                this->state.currScanLineDotCount = 0;
                this->state.earlyModeExit = false;
                this->state.currModeEstimatedTotalDotCount = SCANLINE_MAX_DOT_COUNT;

                this->lcdState->memory->writeMemoryU8(LCD_STATUS_LY, this->lcdState->ly + 1);
            }
    }

    // If we are going to enter a new line scan of index 143, Mode 1 has to start instead of Mode 2.
    if (this->state.mode == PPU_Mode2 &&
        this->lcdState->ly == (LY_MODE_1 - 1) && 
        this->state.currModeDotCount == 0
    ) {
        this->state.mode = PPU_Mode1;
    }

    // If we are at the last dot of the scanline 153, a frame has ended and Mode 2 has to start on scaneline 0
    if (this->state.mode == PPU_Mode1 &&
        this->lcdState->ly == LY_LAST_INDEX && 
        this->state.currScanLineDotCount == SCANLINE_MAX_DOT_COUNT
    ) {
        this->state.mode = PPU_Mode2;
        this->state.currModeDotCount = 0;
        this->state.currScanLineDotCount = 0;
        this->state.currFrameDotCount = 0;
    }
}

// *****

// Do one dot execution
void PPU::execDot() {
    switch (this->state.mode) {
        case PPU_Mode2:
            this->execMode2();
            break;
        case PPU_Mode3:
            this->execMode3();
            break;
        case PPU_Mode1:
            this->execMode1();
            break;
        default: // PPU_Mode0
            this->execMode0();
    }

    this->state.currModeDotCount++;
    this->state.currScanLineDotCount++;
    this->state.currFrameDotCount++;

    this->tryModeChange();
}