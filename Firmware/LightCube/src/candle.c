#include "main.h"
#define NUM_LEDS           4
#define BRIGHTNESS_LEVEL   75
#define STARTUP_STEP       1
#define FLICKER_PROB       8 // Controls probability of starting a flicker event.
#define GLOW_EVENT_PROB    16 // Controls probability of starting a glow event.
#define GLOW_RANGE         25

/* Ensure brightness curve index never exceeds MAX_STEPS */
#if (BRIGHTNESS_LEVEL + GLOW_RANGE + 8) >= MAX_STEPS
  #error "Configuration error: BRIGHTNESS_LEVEL + GLOW_RANGE + max flicker offset exceeds MAX_STEPS"
#endif


typedef struct {
    unsigned char current_level;
    unsigned char flicker_timer;
    char flicker_delta;
    char glow_timer;   /* signed: >0 up, <0 down, 0 = idle */
} LEDState;

static LEDState leds[NUM_LEDS];
static bit startup_done;

void candle_init(void)
{
    unsigned char i;
    for (i = 0; i < NUM_LEDS; ++i) {
        leds[i].current_level = 0;
        leds[i].flicker_timer = 0;
        leds[i].flicker_delta = 0;
        leds[i].glow_timer = 0;
        set_pwm(i, 0, 1);
    }
    startup_done = 0;
}

void candle_tick(void)
{
    unsigned char i, idx;
    for (i = 0; i < NUM_LEDS; ++i) {
        LEDState *led = &leds[i];
        char offset = 0;

        if (!startup_done) {
            if (led->current_level < BRIGHTNESS_LEVEL) {
                led->current_level += STARTUP_STEP;
                if (led->current_level > BRIGHTNESS_LEVEL)
                    led->current_level = BRIGHTNESS_LEVEL;
            }
        } else if (led->flicker_timer) {
            led->flicker_timer--;
            offset = (led->flicker_timer < led->flicker_delta) ?
                        led->flicker_timer :
                        (2 * led->flicker_delta - led->flicker_timer);
        } else if ((rand() & 0xFF) < FLICKER_PROB) {
            led->flicker_delta = (char)((rand() & 7) + 1);
            led->flicker_timer = (unsigned char)(led->flicker_delta << 1);
        } else if (led->glow_timer) {
            if (led->glow_timer > 0) {
                led->glow_timer--;
                if (led->current_level < BRIGHTNESS_LEVEL + GLOW_RANGE)
                    led->current_level++;
                else
                    led->glow_timer = -(led->glow_timer); /* flip direction */
            } else {
                led->glow_timer++;
                if (led->current_level > BRIGHTNESS_LEVEL - GLOW_RANGE)
                    led->current_level--;
                else
                    led->glow_timer = -(led->glow_timer); /* flip direction */
            }
        } else if ((rand() & 0xFF) < GLOW_EVENT_PROB) {
            /* pick direction by sign */
            char t = (char)(30 + (rand() & 0x1F));
            led->glow_timer = (rand() & 1) ? t : -t;
        }

        idx = led->current_level + offset;
        if (idx >= MAX_STEPS) idx = MAX_STEPS - 1;
        set_pwm(i, brightness_curve[idx], 1);
    }

    if (!startup_done) {
        startup_done = 1;
        for (i = 0; i < NUM_LEDS; ++i)
            if (leds[i].current_level < BRIGHTNESS_LEVEL)
                startup_done = 0;
    }
}
