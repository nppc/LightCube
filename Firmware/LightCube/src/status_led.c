/*
 * statusLed.c
 *
 *  Created on: Oct 5, 2025
 *      Author: Pavel
 */

#include "main.h"
#include "status_led.h"
#include "button.h"

uint8_t init_blink_count = 0;
uint16_t init_blink_timer = 0;

uint16_t poweroff_timer = 0;
bit poweroff_active = 0;

LedCommand led_cmd;

void update_status_led(LedCommand cmd) {
    static uint8_t init_blink_count = 0;
    static uint16_t init_blink_timer = 0;
    static uint16_t poweroff_timer = 0;
    static bit poweroff_active = 0;

    switch (cmd) {
        case LED_CMD_INIT:
            if (init_blink_timer == 0) {
                if (init_blink_count < 11) {
                    PIN_LED = !PIN_LED;
                    init_blink_timer = (PIN_LED == 0) ? 10 : 40;
                    init_blink_count++;
                } else {
                    PIN_LED = 1;
                    led_cmd = LED_CMD_NONE;
                }
            } else {
                init_blink_timer--;
            }
            break;

        case LED_CMD_BUTTON_PRESS:
            PIN_LED = 0;  // LED ON
            break;

        case LED_CMD_POWEROFF:
            if (!poweroff_active) {
                poweroff_timer = 0;
                poweroff_active = 1;
                PIN_LED = 0;  // LED ON
            } else {
                poweroff_timer++;
                if (poweroff_timer >= BUTTON_LONG_PRESS_TIME) {
                    PIN_LED = 1;  // LED OFF
                    poweroff_active = 0;
                    led_cmd = LED_CMD_NONE;
                    // Signal that power-off should begin
                    poweroff_trigger = 1;
                }
            }
            break;

        case LED_CMD_SHORTPRESS:
            PIN_LED = 1;  // LED OFF
            led_cmd = LED_CMD_NONE;
            break;

        case LED_CMD_NONE:
        default:
            PIN_LED = 1;  // LED OFF
            break;
    }
}
