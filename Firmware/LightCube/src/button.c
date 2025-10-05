/*
 * button.c
 *
 *  Created on: Oct 5, 2025
 *      Author: Pavel
 */

#include "main.h"
#include "button.h"
#include "status_led.h"

ButtonState button_state = BUTTON_IDLE;
uint8_t debounce_counter = 0;
uint16_t press_duration = 0;

void process_button(void) {
    switch (button_state) {
        case BUTTON_IDLE:
            if (PIN_BUT == 1) {
                button_state = BUTTON_DEBOUNCE;
                debounce_counter = BUTTON_DEBOUNCE_TIME;
            }
            break;

        case BUTTON_DEBOUNCE:
            if (debounce_counter > 0) {
                debounce_counter--;
            } else {
                if (PIN_BUT == 1) {
                    button_state = BUTTON_PRESSED;
                    press_duration = 0;
                    led_cmd = LED_CMD_BUTTON_PRESS;  // LED ON
                } else {
                    button_state = BUTTON_IDLE;
                }
            }
            break;

        case BUTTON_PRESSED:
            if (PIN_BUT == 1) {
                if (press_duration < BUTTON_LONG_PRESS_TIME) {
                    press_duration++;
                } else {
                    // Long press confirmed
                    led_cmd = LED_CMD_POWEROFF;  // LED OFF after 1.5s
                    poweroff_trigger = 1;        // Signal to start power-off routine
                    button_state = BUTTON_RELEASED;
                }
            } else {
                // Released before long press
                led_cmd = LED_CMD_SHORTPRESS;
                button_state = BUTTON_IDLE;
            }
            break;

        case BUTTON_RELEASED:
            if (PIN_BUT == 0) {
                button_state = BUTTON_IDLE;
            }
            break;
    }
}

