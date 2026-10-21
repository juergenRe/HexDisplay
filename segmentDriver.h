/* 
 * File:   segmentDriver.h
 * Author: Juergen
 *
 * Created on April 9, 2026, 11:13 AM
 */

#ifndef SEGMENTDRIVER_H
#define	SEGMENTDRIVER_H

#ifdef	__cplusplus
extern "C" {
#endif

// Port definitions
#define AxMask 0x06    // Mask for anode decoder: PA1, PA2
#define DxMask 0xF0    // mask for cathode data bits: PA7..PA4

#define AxShift 1       // how many bits to shift left
#define DxShift 4       // how many bits to shift left
   
// This definition is due to wiring of the decoder
#define selDigit2 1     // bit number to distinguish between segment displays
#define selHalfNibble 2 // bit number to distinguish between anodes
    
// define input configurations here
#define CFG_STD 0           // standard configuration corresponding to schematics
#define CFG_ProgCount 1     // bits as used for program coutner schematics


void driver(void);
void readDataVal(void);
uint8_t readCfgStd(uint8_t inB, uint8_t inC);
uint8_t readCfgPC(uint8_t inB, uint8_t inC);
void setAnode(void);

#ifdef	__cplusplus
}
#endif

#endif	/* SEGMENTDRIVER_H */

