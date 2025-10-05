#include <SI_EFM8BB50_Register_Enums.h>                  // SFR declarations
#include <SI_EFM8BB50_Defs.h>
#include <stdint.h>

#ifndef MAIN_H_
#define MAIN_H_

#define SYSCLK        49000000UL        // Define your system clock here (SYSCLK)
#define PCA_CLK_DIV   1                // Typically, PCA is clocked at SYSCLK/1
#define PCA_FREQ      (SYSCLK / PCA_CLK_DIV)


#define NUM_LEDS 4
#define MAX_STEPS 128
#define PWM_MAX 65535


// LED states
typedef enum
  {
    IDLE,
    FADING_IN,
    FADING_OUT
  } LedState;


/***** COMPILATION VARIANTS *****/
//#define RC_MOVINGAVERAGE


// Structure for accessing 16bit number by 2 8 bit (back and forth)
// Usage:
// U16_U8 ptr;
// ptr.u8[0] = high;
// ptr.u8[1] = low;
// ptr.u16 = 16bit;
typedef union
   {
   unsigned short u16;
   unsigned char u8[2];
   } U16_U8;

extern bit effect_trigger;
extern bit poweroff_trigger;

extern void delay_ms(uint16_t ms);

extern void set_pwm(uint8_t ch, uint16_t val);

extern uint16_t getRAW_Ambient(void);

extern void rand_set(uint16_t seedval);
extern uint16_t rand(void);

extern void setAmbientLevel(uint8_t level);

extern uint8_t ambient_level;

const uint16_t code brightness_curve[];
const uint16_t code ambient_scale[];

SI_SBIT(PIN_BUT, SFR_P0, 6);
SI_SBIT(PIN_LED, SFR_P0, 3);

//SI_SBIT(PSWREG_C, SFR_PSW, 7); // CARRY FLAG for direct access

extern U16_U8 pwm_channels[];

#endif /* MAIN_H_ */
