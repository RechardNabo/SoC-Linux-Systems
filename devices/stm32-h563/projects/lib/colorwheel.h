/* colorwheel.h — hue-to-RGB conversion for the rainbow demo.
 * Pure function: hue 0-767 across three 256-step transitions R->G->B->R. */
#ifndef COLORWHEEL_H
#define COLORWHEEL_H
#include <stdint.h>

#define COLORWHEEL_STEPS 768U

void colorwheel_rgb(uint16_t hue, uint8_t *r, uint8_t *g, uint8_t *b);

#endif
