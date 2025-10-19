/*
 * pwm.c
 *
 *  Created on: Oct 5, 2025
 *      Author: Pavel
 */

#include "main.h"
#include "pwm.h"

uint16_t pwm_fade_step[NUM_LEDS];      // Calculated step per channel
//bit fading_active = 0;                     // Flag to indicate fading is in progress


void start_poweroff_sequence(void) {
    uint8_t i;
    for (i = 0; i < NUM_LEDS; i++) {
        uint16_t current_pwm = pwm_channels[i].u16;  // Read current value
        pwm_fade_step[i] = current_pwm / FADE_STEPS;
        if (pwm_fade_step[i] == 0 && current_pwm > 0) {
            pwm_fade_step[i] = 1;  // Ensure minimum step
        }
    }
}


bit process_fadeout(void) {

    bit all_zero = 1;
    uint8_t i;
    for (i = 0; i < NUM_LEDS; i++) {
        uint16_t current_pwm = pwm_channels[i].u16;  // Read current value

        if (current_pwm > 0) {
            uint16_t new_pwm = (current_pwm > pwm_fade_step[i])
                               ? (current_pwm - pwm_fade_step[i])
                               : 0;
            set_pwm(i, new_pwm, 0);  // Update via setter
        }

        if (pwm_channels[i].u16 > 0) {
            all_zero = 0;
        }
    }

    if (all_zero) {
        return 1;  // Fade-out complete
    }

    return 0;  // Still fading
}
