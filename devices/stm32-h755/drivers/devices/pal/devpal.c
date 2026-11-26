/* devpal.c — see devpal.h. */
#include "devpal.h"

bool devpal_pin_input(uint8_t pinid)
{
    return stm_gpio_set_input(DEVPAL_PORT_OF(pinid), DEVPAL_PINNO_OF(pinid)) == STM_GPIO_STATUS_OK;
}

bool devpal_pin_output(uint8_t pinid)
{
    return stm_gpio_set_output(DEVPAL_PORT_OF(pinid), DEVPAL_PINNO_OF(pinid)) == STM_GPIO_STATUS_OK;
}

void devpal_pin_write(uint8_t pinid, bool high)
{
    stm_gpio_write(DEVPAL_PORT_OF(pinid), DEVPAL_PINNO_OF(pinid), high);
}

bool devpal_pin_read(uint8_t pinid)
{
    return stm_gpio_read(DEVPAL_PORT_OF(pinid), DEVPAL_PINNO_OF(pinid));
}
