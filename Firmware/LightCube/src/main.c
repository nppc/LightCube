//#pragma src
//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include "main.h"
#include "InitDevice.h"
#include "candle.h"

//volatile uint16_t tmp_millis;
//volatile uint16_t butcntr;
//volatile bit delay_on;
volatile U16_U8 pwm_channels[4];

bit effect_trigger = 0;
uint8_t ambient_level = 9; // Default to max brightness


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


  { // INIT LED Sequence
    uint8_t i;
    for(i=0;i<3;i++){
      PIN_LED = 0;
      delay_ms(200);
      PIN_LED = 1;
      delay_ms(200);
     }
  }

  rand_set(getRAW_Ambient()); // set initial seed for rand

  PIN_BUT = 1;

//  setAmbientLevel(7);
  candle_init();


  while(1){
      uint16_t ambient = getRAW_Ambient();

      if(effect_trigger){
          effect_trigger = 0;
          //Efect4_routine();
          candle_tick();
      }


      if(PIN_BUT){
          uint8_t i;
          bit shutdown = 1;
          PIN_LED = 0;
          delay_ms(200);
          for(i=0;i<12;i++){
              delay_ms(100);
              if(!PIN_BUT) {
                  shutdown = 0;
                  break;
              }
          }
          PIN_LED = 1;
          if(shutdown){
              set_pwm(0, 0);
              set_pwm(1, 0);
              set_pwm(2, 0);
              set_pwm(3, 0);
              while(PIN_BUT);
              delay_ms(300);
              PIN_BUT = 0;
              //PCON1 = PCON1_PINRETAIN__RETAIN;
              REG0CN = REG0CN_STOPCF__SHUTDOWN;
              PCON0 = PCON0_STOP__STOP;
          }
      }

  }

}
