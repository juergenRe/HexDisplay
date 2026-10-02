/*
 Driver function to be called cyclic for driving 7 Segment display
 */
#include "mcc_generated_files/system/pins.h"

#include "segmentDriver.h"


#define MAX_ADDR 3
uint8_t actDataVal = 0x00;      // 8 bit value to be displayed
uint8_t actAddress = 0;         // addresses the common anodes (A0, A1))

uint8_t outSegment[] = {
    0x3f, 0x06, 0x5b, 0x8f, 0x66, 0x6d, 0x7d, 0x07, 
    0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71
};


// switch to next anode
void setAnode(void){
    if(actAddress > MAX_ADDR)
        actAddress = 0;
    PORTA_OUTCLR = AxMask;
    PORTA_OUTSET = (actAddress << AxShift) & AxMask;
    actAddress++;
}

void setSegments(void){
    uint8_t inVal = actDataVal;
    // get data nibble according to anode address
    if(actAddress & 0x02)
        inVal = inVal >> 4;
    inVal &= 0x0f;
    
    uint8_t segVal = outSegment[inVal];
    if(actAddress & 0x01)
        segVal = (segVal >> 4);
    segVal &= 0x0f;
    PORTA_OUTCLR = DxMask;
    PORTA_OUTSET = (segVal << DxShift) & DxMask;
}

// display current Byte on display if enabled
void driver(void){
    if(Enable_GetValue() == 0) {
        DEna_SetHigh();      // disable display
        return;
    }
    DEna_SetLow();
    setSegments();
    setAnode();
}

// read data from bus and reorder it
void readDataVal(void){
    uint8_t inData = 0;
    uint8_t inPortB = VPORTB.IN;
    
    if(Latch_GetValue() != 0) {
        inData |= inPortB & 0x01;           // Bit 0
        inData |= (VPORTC.IN & 0x3) << 1;   // Bit 1,2
        inData |= (inPortB & 0x10) >> 1;    // Bit 3
        inData |= (inPortB & 0x0E) << 3;    // Bits 4, 5, 6
        inData |= (inPortB & 0x20) << 2;    // Bit 7
        actDataVal = inData;
        
        /* Debug input conversion only
        uint8_t segVal = actDataVal >> 4;
        PORTA_OUTCLR = DxMask;
        PORTA_OUTSET = (segVal << DxShift) & DxMask;
        */
    }
}

