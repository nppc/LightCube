//#pragma src
//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include "main.h"
#include "InitDevice.h"
#include "status_led.h"
#include "button.h"
#include "pwm.h"
#include "candle.h"

//volatile uint16_t tmp_millis;
//volatile uint16_t butcntr;
//volatile bit delay_on;
volatile U16_U8 pwm_channels[4];

bit effect_trigger = 0;
uint8_t ambient_level = 9; // Default to max brightness
bit poweroff_trigger = 0;  // Set to 1 when power-off should begin


//-----------------------------------------------------------------------------
// SiLabs_Startup() Routine
// ----------------------------------------------------------------------------
// This function is called immediately after reset, before the initialization
// code is run in SILABS_STARTUP.A51 (which runs before main() ). This is a
// useful place to disable the watchdog timer, which is enable by default
// and may trigger before main() in some instances.
//-----------------------------------------------------------------------------
void SiLabs_Startup(void) {
  // $[SiLabs Startup]
  // [SiLabs Startup]$
}

//-----------------------------------------------------------------------------
// main() Routine
// ----------------------------------------------------------------------------
int main(void) {
  enter_DefaultMode_from_RESET();

    SFRPAGE = 0x10;
    PWMCFG0 = PWMCFG0_PWMMODE__EDGE | PWMCFG0_PWMCLKEN__ENABLE | PWMCFG0_SYNCUPD__CH0CH1CH2;
//    PWMCFG1 = PWMCFG1_DTIEN__ENABLE |
    PWMCFG2 = PWMCFG2_CNTRZERO__ZERO;
    PWMLIML = 0xFF;
    PWMLIMH = 0xFF;
    PWMCFG1 = PWMCFG1_PWMLTSYS__GTSYSCK | PWMCFG1_PWMEN__ENABLE; // start PWM0
    SFRPAGE = 0x00;

  PCA0CN0_CR = PCA0CN0_CR__RUN; // Start PCA0 after config is done

  set_pwm(0, 0);
  set_pwm(1, 0);
  set_pwm(2, 0);
  set_pwm(3, 0);

  IE_EA = 1;

  rand_set(getRAW_Ambient()); // set initial seed for rand

  PIN_BUT = 1;

  PIN_LED = 0;
  while(PIN_BUT); // wait until button is depressed

  led_cmd = LED_CMD_INIT;

//  setAmbientLevel(7);
  candle_init();


  while(1){
      uint16_t ambient = getRAW_Ambient();

      if(effect_trigger){
          effect_trigger = 0;
          candle_tick();
          process_button();
          update_status_led(led_cmd);
      }

      if (poweroff_trigger) {
          bit fade_finished = 0;
          PIN_LED = 1;
          start_poweroff_sequence();
          while(!fade_finished){
              if(effect_trigger){
                  effect_trigger = 0;
                  fade_finished = process_fadeout();
              }
          }
          // go to powerdown
          while(PIN_BUT);
          delay_ms(100);
          PIN_BUT = 0;
          REG0CN = REG0CN_STOPCF__SHUTDOWN;
          PCON0 = PCON0_STOP__STOP;
      }

  }

}
