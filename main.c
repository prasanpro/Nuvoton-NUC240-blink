/**************************************************************************//**
 * @file     main.c
 * @version  V2.00
 * $Revision: 7 $
 * $Date: 15/04/10 5:51p $
 * @brief    Show how to set GPIO pin mode and use pin data input/output control.
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <stdio.h>
#include "NUC200Series.h"

#define PLL_CLOCK           50000000


void SYS_Init(void)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init System Clock                                                                                       */
    /*---------------------------------------------------------------------------------------------------------*/

    /* Enable Internal RC 22.1184MHz clock */
    CLK_EnableXtalRC(CLK_PWRCON_OSC22M_EN_Msk);

    /* Waiting for Internal RC clock ready */
    CLK_WaitClockReady(CLK_CLKSTATUS_OSC22M_STB_Msk);

    /* Switch HCLK clock source to Internal RC and HCLK source divide 1 */
    CLK_SetHCLK(CLK_CLKSEL0_HCLK_S_HIRC, CLK_CLKDIV_HCLK(1));

    /* Enable external XTAL 12MHz clock */
    CLK_EnableXtalRC(CLK_PWRCON_XTL12M_EN_Msk);

    /* Waiting for external XTAL clock ready */
    CLK_WaitClockReady(CLK_CLKSTATUS_XTL12M_STB_Msk);

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(PLL_CLOCK);

    /* Enable UART module clock */
    CLK_EnableModuleClock(UART0_MODULE);

    /* Select UART module clock source */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART_S_HXT, CLK_CLKDIV_UART(1));

     
    /* Enable Timer 0 module clock */
    CLK_EnableModuleClock(TMR1_MODULE);

    /* Select Timer 0 module clock source */
    CLK_SetModuleClock(TMR1_MODULE,CLK_CLKSEL1_TMR1_S_HIRC, NULL);

    /* Configure PA 1 as Output mode  */
     PA->PMD = (PA->PMD & (~GPIO_PMD_PMD1_Msk)) | (GPIO_PMD_OUTPUT << GPIO_PMD_PMD1_Pos);
}


/*---------------------------------------------------------------------------------------------------------*/
/* MAIN function                                                                                           */
/*---------------------------------------------------------------------------------------------------------*/
int main(void)
{
 

    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Init System, peripheral clock and multi-function I/O */
    SYS_Init();

    /* Lock protected registers */
    SYS_LockReg();
  
   
while(1){
 
   TIMER_Delay(TIMER1, 100000000);      //100ms * 1000 = 1second
   PA1 = 1;
   TIMER_Delay(TIMER1, 100000000);      //100ms * 1000 = 1second
   PA1 = 0;
}
}






