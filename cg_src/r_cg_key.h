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
* File Name    : r_cg_key.h
* Version      : Code Generator for RL78/R7F0C8021 V1.03.00.03 [07 Aug 2014]
* Device(s)    : R7F0C8021
* Tool-Chain   : CA78K0R
* Description  : This file implements device driver for KEY module.
* Creation Date: 17/11/2014
***********************************************************************************************************************/
#ifndef KEY_H
#define KEY_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    Key Interrupt Control Register (KRCTL)
*/
/* Key interrupt flag control (KRMD) */
#define _00_KR_FLAG_UNUSED              (0x00U)   /* unuse key interrupt flag */
#define _80_KR_FLAG_USED                (0x80U)   /* use key interrupt flag */
/* Key interrupt edge detection control (KREG) */
#define _00_KR_EDGE_FALLING             (0x00U)   /* falling edge */
#define _01_KR_EDGE_RISING              (0x01U)   /* rising edge */

/*
    Key Return Mode Register (KRM)
*/
/* Key interrupt mode control (KRM0) */
#define _00_KR0_SIGNAL_DETECT_OFF       (0x00U) /* not detect KR0 signal */
#define _01_KR0_SIGNAL_DETECT_ON        (0x01U) /* detect KR0 signal */
/* Key interrupt mode control (KRM1) */
#define _00_KR1_SIGNAL_DETECT_OFF       (0x00U) /* not detect KR1 signal */
#define _02_KR1_SIGNAL_DETECT_ON        (0x02U) /* detect KR1 signal */
/* Key interrupt mode control (KRM2) */
#define _00_KR2_SIGNAL_DETECT_OFF       (0x00U) /* not detect KR2 signal */
#define _04_KR2_SIGNAL_DETECT_ON        (0x04U) /* detect KR2 signal */
/* Key interrupt mode control (KRM3) */
#define _00_KR3_SIGNAL_DETECT_OFF       (0x00U) /* not detect KR3 signal */
#define _08_KR3_SIGNAL_DETECT_ON        (0x08U) /* detect KR3 signal */
/* Key interrupt mode control (KRM4) */
#define _00_KR4_SIGNAL_DETECT_OFF       (0x00U) /* not detect KR4 signal */
#define _10_KR4_SIGNAL_DETECT_ON        (0x10U) /* detect KR4 signal */
/* Key interrupt mode control (KRM5) */
#define _00_KR5_SIGNAL_DETECT_OFF       (0x00U) /* not detect KR5 signal */
#define _20_KR5_SIGNAL_DETECT_ON        (0x20U) /* detect KR5 signal */

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define KEY_WAITTIME                    (1U)   /* change the waiting time according to the system */ 

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void R_KEY_Create(void);
void R_KEY_Start(void);
void R_KEY_Stop(void);

/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif