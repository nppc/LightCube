/*
 * pwm.h
 *
 *  Created on: Oct 5, 2025
 *      Author: Pavel
 */

#ifndef SRC_PWM_H_
#define SRC_PWM_H_

#define FADE_STEPS 200

extern void start_poweroff_sequence(void);
extern bit process_fadeout(void);

#endif /* SRC_PWM_H_ */
