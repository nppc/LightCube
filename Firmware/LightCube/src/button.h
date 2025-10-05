/*
 * button.h
 *
 *  Created on: Oct 5, 2025
 *      Author: Pavel
 */

#ifndef SRC_BUTTON_H_
#define SRC_BUTTON_H_


typedef enum {
    BUTTON_IDLE,
    BUTTON_DEBOUNCE,
    BUTTON_PRESSED,
    BUTTON_RELEASED
} ButtonState;


#define BUTTON_DEBOUNCE_TIME 6     // 60ms
#define BUTTON_LONG_PRESS_TIME 150 // 1.5s

extern void process_button(void);

#endif /* SRC_BUTTON_H_ */
