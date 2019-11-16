#include <fsl_common.h>
#include <fsl_iomuxc.h>
#include <MCIMX6Y2.h>
#include <system.h>
#include <chip/gpio.h>
#include "driver/gpio.h"


static gpio_chip_t imx6ul_gpio;
static gpio_t led0;
static gpio_t beep;

void clk_enable(void)
{
    CCM->CCGR0 = 0xFFFFFFFF;
    CCM->CCGR1 = 0xFFFFFFFF;
    CCM->CCGR2 = 0xFFFFFFFF;
    CCM->CCGR3 = 0xFFFFFFFF;
    CCM->CCGR4 = 0xFFFFFFFF;
    CCM->CCGR5 = 0xFFFFFFFF;
    CCM->CCGR6 = 0xFFFFFFFF;
}

void delay_short(volatile unsigned int n)
{
    while (n--);
}

void delay(volatile unsigned int n)
{
    while (n--)
    {
        delay_short(0x7ff);
    }
}

void user_driver_init(void)
{
    gpio_hw_init(&imx6ul_gpio);

    gpio_init(&led0, &imx6ul_gpio, LED0);
    gpio_init(&beep, &imx6ul_gpio, BEEP);
}

void user_application_init(void)
{

}


int main(void)
{

    clk_enable();
    user_driver_init();
    user_application_init();

    while (1)
    {
        gpio_direction_output(&led0, PIN_LEVEL_LOW);
        //gpio_direction_output(&beep, PIN_LEVEL_LOW);
        delay(500);

        gpio_direction_output(&led0, PIN_LEVEL_HIGH);
        //gpio_direction_output(&beep, PIN_LEVEL_HIGH);
        delay(500);
    }

    return 0;
}
