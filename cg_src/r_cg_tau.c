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
* File Name    : r_cg_tau.c
* Version      : Code Generator for RL78/R7F0C8021 V1.03.00.03 [07 Aug 2014]
* Device(s)    : R7F0C8021
* Tool-Chain   : CA78K0R
* Description  : This file implements device driver for TAU module.
* Creation Date: 28/10/2014
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
#include "r_cg_tau.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* For TAU0_ch0 pulse measurement */
extern volatile uint32_t g_tau0_ch0_width;
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_TAU0_Create
* Description  : This function initializes the TAU0 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TAU0_Create(void)
{
    TAU0EN = 1U;    /* supplies input clock */
    TPS0 = _03_TAU_CKM0_FCLK_3 | _00_TAU_CKM1_FCLK_0;
    /* Stop all channels */
    TTH0 =_02_TAU_CH1_H8_STOP_TRG_ON;
    TT0 = _01_TAU_CH0_STOP_TRG_ON | _02_TAU_CH1_STOP_TRG_ON;
    /* Mask channel 0 interrupt */
    TMMK00 = 1U;    /* disable INTTM00 interrupt */
    TMIF00 = 0U;    /* clear INTTM00 interrupt flag */
    /* Mask channel 1 interrupt */
    TMMK01 = 1U;    /* disable INTTM01 interrupt */
    TMIF01 = 0U;    /* clear INTTM01 interrupt flag */
    /* Mask channel 1 higher 8 bits interrupt */
    TMMK01H = 1U;    /* disable INTTM01H interrupt */
    TMIF01H = 0U;    /* clear INTTM01H interrupt flag */
    /* Set INTTM00 low priority */
    TMPR100 = 1U;
    TMPR000 = 1U;
    /* Set INTTM01 low priority */
    TMPR101 = 1U;
    TMPR001 = 1U;
    /* Channel 0 is used to measure input pulse low-/high-width */
    TMR00H = _80_TAU_CLOCK_SELECT_CKM1 | _00_TAU_CLOCK_MODE_CKS | _00_TAU_COMBINATION_SLAVE | _02_TAU_TRIGGER_TIMN_BOTH;
    TMR00L = _80_TAU_TIMN_EDGE_BOTH_LOW | _0C_TAU_MODE_HIGHLOW_MEASURE;
    TO0 &= (uint8_t)~_01_TAU_CH0_OUTPUT_VALUE_1;
    TOE0 &= (uint8_t)~_01_TAU_CH0_OUTPUT_ENABLE;
    NFEN1 &= (uint8_t)~_01_TAU_CH0_NOISE_ON;    /* disable using noise filter of TI00 pin input signal */
    /* Channel 1 used as interval timer */
    TMR01H = _00_TAU_CLOCK_SELECT_CKM0 | _00_TAU_CLOCK_MODE_CKS | _00_TAU_16BITS_MODE | _00_TAU_TRIGGER_SOFTWARE;
    TMR01L = _00_TAU_MODE_INTERVAL_TIMER | _00_TAU_START_INT_UNUSED;
    /* Consecutive reading from the TDR0nH and TDR0nL registers and consecutive writing to the TDR0nH and TDR0nL
    registers must be performed in the state where an interrupt is disabled by the DI instruction. */
    TDR01H = _F4_TAU_TDR01H_VALUE;
    TDR01L = _23_TAU_TDR01L_VALUE;
    TOM0 &= (uint8_t)~_02_TAU_CH1_OUTPUT_COMBIN;
    TOL0 &= (uint8_t)~_02_TAU_CH1_OUTPUT_LEVEL_L;
    TO0 &= (uint8_t)~_02_TAU_CH1_OUTPUT_VALUE_1;
    TOE0 &= (uint8_t)~_02_TAU_CH1_OUTPUT_ENABLE;
}
/***********************************************************************************************************************
* Function Name: R_TAU0_Channel0_Start
* Description  : This function starts TAU0 channel 0 counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TAU0_Channel0_Start(void)
{
    TMIF00 = 0U;    /* clear INTTM00 interrupt flag */
    TMMK00 = 0U;    /* enable INTTM00 interrupt */
    TS0 |= _01_TAU_CH0_START_TRG_ON;
}
/***********************************************************************************************************************
* Function Name: R_TAU0_Channel0_Stop
* Description  : This function stops TAU0 channel 0 counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TAU0_Channel0_Stop(void)
{
    TT0 |= _01_TAU_CH0_STOP_TRG_ON;
    /* Mask channel 0 interrupt */
    TMMK00 = 1U;    /* disable INTTM00 interrupt */
    TMIF00 = 0U;    /* clear INTTM00 interrupt flag */
}
/***********************************************************************************************************************
* Function Name: R_TAU0_Channel0_Get_PulseWidth
* Description  : This function measures TAU0 channel 0 input pulse width.
* Arguments    : width -
*                    the address where to write the input pulse width
* Return Value : None
***********************************************************************************************************************/
void R_TAU0_Channel0_Get_PulseWidth(uint32_t * const width)
{
    /* For channel 0 pulse measurement */
    *width = g_tau0_ch0_width;
}
/***********************************************************************************************************************
* Function Name: R_TAU0_Channel1_Start
* Description  : This function starts TAU0 channel 1 counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TAU0_Channel1_Start(void)
{
    TMIF01 = 0U;    /* clear INTTM01 interrupt flag */
    TMMK01 = 0U;    /* enable INTTM01 interrupt */
    TS0 |= _02_TAU_CH1_START_TRG_ON;
}
/***********************************************************************************************************************
* Function Name: R_TAU0_Channel1_Stop
* Description  : This function stops TAU0 channel 1 counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TAU0_Channel1_Stop(void)
{
    TT0 |= _02_TAU_CH1_STOP_TRG_ON;
    /* Mask channel 1 interrupt */
    TMMK01 = 1U;    /* disable INTTM01 interrupt */
    TMIF01 = 0U;    /* clear INTTM01 interrupt flag */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
