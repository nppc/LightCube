/*
 * status_led.h
 *
 *  Created on: Oct 5, 2025
 *      Author: Pavel
 */

#ifndef SRC_STATUS_LED_H_
#define SRC_STATUS_LED_H_


typedef enum {
    LED_CMD_NONE,
    LED_CMD_INIT,
    LED_CMD_BUTTON_PRESS,
    LED_CMD_POWEROFF,
    LED_CMD_SHORTPRESS
} LedCommand;

extern LedCommand led_cmd;


extern void update_status_led(LedCommand cmd);

#endif /* SRC_STATUS_LED_H_ */
