#include <system.h>
#include <fsl_common.h>
#include <fsl_iomuxc.h>
#include <MCIMX6Y2.h>
#include "clock.h"


static void system_clock_init(void)
{
    // switch pll1_sw_clk to step clock
    CCM->CCSR &= ~(1 << 8);
    CCM->CCSR |= (1 << 2);
    
    CCM_ANALOG->PLL_ARM &= ~0x7f;
    CCM_ANALOG->PLL_ARM |= 88;
    CCM_ANALOG->PLL_ARM |= (1 << 13);
    
    ze_u32_t value = CCM->CACRR;
    value &= ~07;
    value |= 0x01;
    CCM->CACRR = value;

    CCM->CCSR &= ~(1 << 2);

    // PLL2 PDF0 352MHz
    CCM_ANALOG->PFD_528 &= ~0x3F;
    CCM_ANALOG->PFD_528 |= 27;
    CCM_ANALOG->PFD_528 &= ~(1 << 7);

    // PLL2 PFD1 594MHz
    CCM_ANALOG->PFD_528 &= ~(0X3F << 8);
    CCM_ANALOG->PFD_528 |= (16 << 8);
    CCM_ANALOG->PFD_528 &= ~(1 << 15);
    // PLL2 PFD2 400MHz
    CCM_ANALOG->PFD_528 &= ~(0X3F << 16);
    CCM_ANALOG->PFD_528 |= (24 << 16);
    CCM_ANALOG->PFD_528 &= ~(1 << 23);
    // PLL2 PFD3 297MHz
    CCM_ANALOG->PFD_528 &= ~(0X3F << 24);
    CCM_ANALOG->PFD_528 |= (32 << 24);
    CCM_ANALOG->PFD_528 &= ~(1 << 31);
    // PLL3 PFD0 720MHz
    CCM_ANALOG->PFD_480 &= ~0x3F;
    CCM_ANALOG->PFD_480 |= 12;
    CCM_ANALOG->PFD_480 &= ~(1 << 7);
    // PLL3 PFD1 540MHz
    CCM_ANALOG->PFD_480 &= ~(0x3F << 8);
    CCM_ANALOG->PFD_480 |= (16 << 8);
    CCM_ANALOG->PFD_480 &= ~(1 << 15);
    // PLL3 PFD2 508.2MHz
    CCM_ANALOG->PFD_480 &= ~(0x3F << 16);
    CCM_ANALOG->PFD_480 |= (17 << 16);
    CCM_ANALOG->PFD_480 &= ~(1 << 23);
    // PLL3 PFD3 454.7MHz
    CCM_ANALOG->PFD_480 &= ~(0x3F << 24);
    CCM_ANALOG->PFD_480 |= (19 << 24);
    CCM_ANALOG->PFD_480 &= ~(1 << 31);


    // Set AHB clock 132MHz
    CCM->CBCMR &= ~(0x03 << 18);
    CCM->CBCMR |= (0x01 << 18);

    CCM->CBCDR &= ~(1 << 25);
    while (CCM->CDHIPR & (1 << 5));


    CCM->CBCDR &= ~(3 << 8);
    CCM->CBCDR |= 1 << 8;

    CCM->CSCMR1 &= ~(1 << 6);
    CCM->CSCMR1 &= ~(7 << 0);
}

static void periph_clock_enable(void)
{
    CCM->CCGR0 = 0xFFFFFFFF;
    CCM->CCGR1 = 0xFFFFFFFF;
    CCM->CCGR2 = 0xFFFFFFFF;
    CCM->CCGR3 = 0xFFFFFFFF;
    CCM->CCGR4 = 0xFFFFFFFF;
    CCM->CCGR5 = 0xFFFFFFFF;
    CCM->CCGR6 = 0xFFFFFFFF;
}

void clock_init(void)
{
    system_clock_init();
    periph_clock_enable();
}