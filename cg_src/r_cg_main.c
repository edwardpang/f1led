/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIESREGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2012, 2014 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_main.c
* Version      : Code Generator for RL78/R7F0C8021 V1.03.00.03 [07 Aug 2014]
* Device(s)    : R7F0C8021
* Tool-Chain   : CA78K0R
* Description  : This file implements main function.
* Creation Date: 26/10/2014
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_port.h"
#include "r_cg_tau.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
#define TIME_PERIOD_100MS			1
#define TIME_PERIOD_1S				10
#define TIME_PERIOD_CALIBRATION		(10 * TIME_PERIOD_1S)
#define TIME_PERIOD_LED_BLINK		(5 * TIME_PERIOD_100MS)

typedef enum {
	APP_STATE_INIT = 0,
	APP_STATE_PRE_CALIBRATION,
	APP_STATE_CALIBRATION,
	APP_STATE_POST_CALIBRATION,
	APP_STATE_MODE_1,
	APP_STATE_MODE_2,
	APP_STATE_NUM
} eAppState;

eAppState state;

boolean ledOnOff;
boolean tickFlag;
short tickCnt;

/*
Test with blue colour Throttle Generator.
When display shows 2200, throttle variable = 44xxx
When display shows 1500, throttle variable = 30xxx
When display shows 800, throttle variable = 16xxx
 */
#define THROTTLE_READING_MIN	16000
#define THROTTLE_READING_MAX	45000

unsigned short u16Throttle;
unsigned short u16ThrottleMiddle;
unsigned short u16ThrottleUpperBound;
unsigned short u16ThrottleLowerBound;

void tickCntUpdate (void) {
	if (tickFlag) {
		tickCnt ++;
		tickFlag = 0;
	}
}

void tickCntClear (void) {
	tickCnt = 0;
}

void LedOn ( ) {
	P0 = _00_Pn0_OUTPUT_0 | _00_Pn1_OUTPUT_0 | _00_Pn2_OUTPUT_0 | _00_Pn3_OUTPUT_0 | _00_Pn4_OUTPUT_0;
	ledOnOff = true;
}

void LedOff ( ) {
	P0 = _01_Pn0_OUTPUT_1 | _02_Pn1_OUTPUT_1 | _04_Pn2_OUTPUT_1 | _08_Pn3_OUTPUT_1 | _10_Pn4_OUTPUT_1;
	ledOnOff = false;
}

void LedInit ( ) {
	LedOff ( );
	ledOnOff = false;
}

void LedToggle ( ) {
	if (ledOnOff)
		LedOff ( );
	else
		LedOn ( );
}

/* End user code. Do not edit comment generated here */

void R_MAIN_UserInit(void);
/***********************************************************************************************************************
* Function Name: main
* Description  : This function implements main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void main(void)
{
    R_MAIN_UserInit();
    /* Start user code. Do not edit comment generated here */
    while (1U) {
		tickCntUpdate ( );
		switch (state) {
			case APP_STATE_INIT:
				// Init Global Variable
				tickFlag = false;
				tickCntClear ( );
				u16Throttle = 0;
				
				// Init LED
				LedInit ( );
				LedOn ( );

				// Start Timer
				R_TAU0_Channel0_Start ( );
				R_TAU0_Channel1_Start ( );
				state = APP_STATE_PRE_CALIBRATION;
				break;

			case APP_STATE_PRE_CALIBRATION:
				// Make Sure Throttle is connected
				if (u16Throttle > THROTTLE_READING_MIN) {
					state = APP_STATE_CALIBRATION;
					LedOff ( );
					tickCntClear ( );
				}
				break;
				
			case APP_STATE_CALIBRATION:
				if (tickCnt == TIME_PERIOD_CALIBRATION) {
					tickCntClear ( );
					state = APP_STATE_POST_CALIBRATION;
				}
				break;
				
			case APP_STATE_POST_CALIBRATION:
				state = APP_STATE_MODE_1;
				break;
				
			case APP_STATE_MODE_1:
				if (tickCnt == TIME_PERIOD_LED_BLINK) {
					tickCntClear ( );
					LedToggle ( );
				}
				break;
				
			case APP_STATE_MODE_2:
				break;
		}
    }
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: R_MAIN_UserInit
* Description  : This function adds user code before implementing main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MAIN_UserInit(void)
{
    /* Start user code. Do not edit comment generated here */
    EI();
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
