#include <system.h>
#include <fsl_common.h>
#include <fsl_iomuxc.h>
#include <MCIMX6Y2.h>
#include "clock.h"

/*
static void clock_init(void)
{
    ze_u32_t reg = 0;

    if ((CCM->CCSR >> 2) & 0x01 == 0)
    {
        CCM->CCSR &= ~(1 << 8);
        CCM->CCSR |= (1 << 2);
    }

    CCM_ANALOG->PLL_ARM |= (88 | (1 << 13));
    CCM->CCSR &= ~(1 << 2);

    reg = CCM_ANALOG->PFD_528;
    reg &= ~(0x3F3F3F3F);
    reg |= 27;                  // PFD0 = 352 MHz
    reg |= 

}
*/
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

    periph_clock_enable();
}