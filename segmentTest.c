/*
 * File:   segmentTest.c
 * Author: Juergen
 *
 * Created on 21. Oktober 2026, 15:15
 */

#include "mcc_generated_files/system/pins.h"
#include "segmentDriver.h"

#define MainPeriod 200      // Base tick is 2.5ms --> 1s
uint16_t actCnt = 0;

uint8_t iAnode = 0;
uint8_t iCath = 0;
uint8_t offCnt = 0;


// test states:
// 0: Init
// 1: next iCath/iAnode/all on
// 2: all off via Ena

uint8_t iState = 0;

// testing procedure for HW functions
// it runs with reduced speed and drives one segment after the other 
// to be able to identify any HW related problems on the segment driver
void segmentTest(void){
    if(actCnt++ >= MainPeriod){
        actCnt = 0;
        
        switch(iState){
            case 0: // Init variables
                iAnode = 0;
                iCath = 0x08;
                offCnt = 0;
                DEna_SetLow();
                iState++;
                break;
            case 1:
                iCath = iCath >> 1;
                if(iCath == 0){
                    iCath = 0x08;
                    iAnode++;
                    if(iAnode > 3){
                        iAnode = 0;
                        iCath = 0x0f;
                        iState++;
                    }
                }
                break;
            case 2:
                iAnode++;
                if(iAnode > 3){
                    DEna_SetHigh();
                    iState++;
                }
                break;
            case 3:
                offCnt++;
                if(offCnt>3)
                    iState = 0;
                break;
            default:
                ;
        }
        PORTA_OUTCLR = DxMask;
        PORTA_OUTSET = (iCath << DxShift) & DxMask;
        PORTA_OUTCLR = AxMask;
        PORTA_OUTSET = (iAnode << AxShift) & AxMask;
    }
}

