#include <system.h>
#include <fsl_common.h>
#include <fsl_iomuxc.h>
#include <MCIMX6Y2.h>
#include "gpio.h"

typedef struct {
    pin_name_t pin_name;
    GPIO_Type* port;
    ze_u8_t pin;
} pin_map_t;

const pin_map_t pin_map[] = {
    {.pin_name = LED0, .port = GPIO1, .pin = 3},
    {.pin_name = BEEP, .port = GPIO5, .pin = 1},
};

const pin_map_t* imx6ul_find_gpio(pin_name_t pin_name)
{
    for (ze_u8_t i = 0; i < ARRAY_SIZE(pin_map); i++)
    {
        if (pin_map[i].pin_name == pin_name)
            return pin_map + i;
    }
    return NULL;
}

void imx6ul_gpio_write(gpio_chip_t* chip, pin_name_t pin_name, pin_level_t level)
{
    const pin_map_t* map = imx6ul_find_gpio(pin_name);

    ze_u32_t value = map->port->DR;
    value &= ~(1 << map->pin);
    value |= ((level == PIN_LEVEL_HIGH ? 1 : 0) << map->pin);
    map->port->DR = value;
}

pin_level_t imx6ul_gpio_read(gpio_chip_t* chip, pin_name_t pin_name)
{
    const pin_map_t* map = imx6ul_find_gpio(pin_name);
    return map->port->DR & (1 << map->pin) ? PIN_LEVEL_HIGH : PIN_LEVEL_LOW;
}

void imx6ul_gpio_write_direction(gpio_chip_t* chip, pin_name_t pin_name, pin_dir_t dir)
{
    const pin_map_t* map = imx6ul_find_gpio(pin_name);
    ze_u32_t value = map->port->GDIR;
    value &= ~(1 << map->pin);
    value |= ((dir == PIN_DIR_INPUT ? 0 : 1) << map->pin);

    map->port->GDIR = value;
}

pin_level_t imx6ul_gpio_read_direction(gpio_chip_t* chip,  pin_name_t pin_name)
{
    const pin_map_t* map = imx6ul_find_gpio(pin_name);
    return map->port->GDIR & (1 << map->pin) ? PIN_DIR_OUTPUT : PIN_DIR_INPUT;
}


const gpio_chip_operations_t imx6ul_gpio_ops = {
    .write = imx6ul_gpio_write,
    .read = imx6ul_gpio_read,
    .write_direction = imx6ul_gpio_write_direction,
    .read_direction = imx6ul_gpio_read_direction,
};

void gpio_hw_init(gpio_chip_t* chip)
{

    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO03_GPIO1_IO03, 0x0);
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO03_GPIO1_IO03, 0X10B0);

    IOMUXC_SetPinMux(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01, 0);
    IOMUXC_SetPinConfig(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01, 0X10B0);

    gpio_chip_init(chip, &imx6ul_gpio_ops);
}
