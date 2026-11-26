#include "buzzer_passive_app.h"

static const uint32_t scale_notes[SCALE_NOTE_COUNT] = {
    262U, 294U, 330U, 349U, 392U, 440U, 494U,
    523U, 587U, 659U, 698U, 784U, 880U, 988U, 1047U
};

const uint32_t *buzzer_passive_app_scale(void) { return scale_notes; }

void buzzer_passive_app_init(buzzer_passive_app_t *app, uint8_t channel, uint32_t clk_hz)
{
    buzzer_init(&app->device, STM_TIM3, channel, clk_hz);
    sequencer_init(&app->scale, scale_notes, SCALE_NOTE_COUNT);
}

void buzzer_passive_app_step(buzzer_passive_app_t *app)
{
    buzzer_tone(&app->device, sequencer_next(&app->scale));
}

uint8_t buzzer_passive_app_position(const buzzer_passive_app_t *app)
{
    return sequencer_position(&app->scale);
}
