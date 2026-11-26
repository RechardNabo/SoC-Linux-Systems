#include "colorwheel.h"

void colorwheel_rgb(uint16_t hue, uint8_t *r, uint8_t *g, uint8_t *b)
{
    const uint16_t h = hue % COLORWHEEL_STEPS;
    if (h < 256U) {
        *r = (uint8_t)(255U - h); *g = (uint8_t)h;          *b = 0U;
    } else if (h < 512U) {
        *r = 0U;                  *g = (uint8_t)(511U - h); *b = (uint8_t)(h - 256U);
    } else {
        *r = (uint8_t)(h - 512U); *g = 0U;                  *b = (uint8_t)(767U - h);
    }
}
