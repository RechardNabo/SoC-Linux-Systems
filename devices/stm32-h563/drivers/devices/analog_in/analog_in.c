/* analog_in.c — see analog_in.h. */
#include "analog_in.h"
#include "../../peripherals/adc/stm_adc.h"

analog_in_status_t analog_in_init(analog_in_t *dev, const analog_in_config_t *config)
{
    if (dev == 0 || config == 0 || config->scale_den == 0)
        return ANALOG_IN_STATUS_INVALID_CONFIG;
    if (config->adc_channel > STM_ADC_MAX_CHANNEL) return ANALOG_IN_STATUS_INVALID_CONFIG;
    dev->cfg = *config;
    return ANALOG_IN_STATUS_OK;
}

int32_t analog_in_scale(uint16_t raw, const analog_in_config_t *cfg)
{
    /* 64-bit intermediate — same overflow lesson as the PIC32 clock math */
    return (int32_t)(((int64_t)raw * cfg->scale_num) / cfg->scale_den) + cfg->offset;
}

analog_in_status_t analog_in_read_raw(analog_in_t *dev, uint16_t *raw_out)
{
    if (dev == 0 || raw_out == 0) return ANALOG_IN_STATUS_INVALID_CONFIG;
    if (stm_adc_read_channel(dev->cfg.adc_channel, raw_out) != STM_ADC_STATUS_OK)
        return ANALOG_IN_STATUS_READ_FAULT;
    return ANALOG_IN_STATUS_OK;
}

analog_in_status_t analog_in_read_scaled(analog_in_t *dev, int32_t *eng_out)
{
    uint16_t raw;
    analog_in_status_t st = analog_in_read_raw(dev, &raw);
    if (st != ANALOG_IN_STATUS_OK) return st;
    *eng_out = analog_in_scale(raw, &dev->cfg);
    return ANALOG_IN_STATUS_OK;
}
