#include "main.h"

#define TICKS_PER_MS  (PCA_FREQ / 1000) // Number of PCA ticks per millisecond
void delay_ms(uint16_t ms)
{
    uint16_t start, elapsed;

    while (ms > 0) {
        start = PCA0L;
        start |= ((uint16_t)PCA0H << 8);

        do {
            uint16_t now = PCA0L;
            now |= ((uint16_t)PCA0H << 8);

            // Handle counter wrap-around
            elapsed = now - start;
        } while (elapsed < TICKS_PER_MS);

        ms--;
    }
}

void set_pwm(uint8_t ch, uint16_t val){
  IE_EA = 0;
  pwm_channels[ch].u16 = val;
  IE_EA = 1;
  switch (ch) {
//    case 0:
    case 1:
      SFRPAGE = 0x10;
      if(val==0) PWMCFG2 &= ~(PWMCFG2_CH0EN__BMASK);
      PWMCPUDL0 = pwm_channels[ch].u8[1];
      PWMCPUDH0 = pwm_channels[ch].u8[0];
      if(val!=0) PWMCFG2 |= PWMCFG2_CH0EN__ENABLE;
      SFRPAGE = 0x00;
      break;
    case 2:
      SFRPAGE = 0x10;
      if(val==0) PWMCFG2 &= ~(PWMCFG2_CH1EN__BMASK);
      PWMCPUDL1 = pwm_channels[ch].u8[1];
      PWMCPUDH1 = pwm_channels[ch].u8[0];
      if(val!=0) PWMCFG2 |= PWMCFG2_CH1EN__ENABLE;
      SFRPAGE = 0x00;
      break;
    case 3:
      SFRPAGE = 0x10;
      if(val==0) PWMCFG2 &= ~(PWMCFG2_CH2EN__BMASK);
      PWMCPUDL2 = pwm_channels[ch].u8[1];
      PWMCPUDH2 = pwm_channels[ch].u8[0];
      if(val!=0) PWMCFG2 |= PWMCFG2_CH2EN__ENABLE;
      SFRPAGE = 0x00;
      break;
  }
}

static uint16_t seed;
void rand_set(uint16_t seedval){
  seed = seedval;
}

//LCG pseudo random number generator
uint16_t rand(void) {
    seed = (seed * 2053 + 13849) & 0xFFFF;
    return seed;
}

uint16_t getRAW_Ambient(void) {
    uint16_t adcraw; // raw data from ADC
    ADC0CN0_ADBUSY = 1; // start the conversion (32 times 10 bit)
    while(!ADC0CN0_ADINT);
    adcraw = ADC0;
    ADC0CN0_ADINT = 0;
    return adcraw;;
}

// Gamma-corrected brightness curve (64 steps, gamma = 2.2)
const uint16_t code brightness_curve[MAX_STEPS] = {
        0,     2,     7,    17,    33,    53,    79,   112,
      150,   194,   244,   301,   365,   435,   512,   596,
      687,   785,   891,  1003,  1123,  1250,  1385,  1527,
     1677,  1835,  2000,  2173,  2354,  2543,  2740,  2945,
     3158,  3379,  3609,  3846,  4092,  4347,  4609,  4880,
     5160,  5448,  5745,  6050,  6364,  6686,  7017,  7357,
     7706,  8064,  8430,  8806,  9190,  9583,  9986, 10397,
    10817, 11247, 11685, 12133, 12590, 13057, 13532, 14017,
    14511, 15015, 15528, 16050, 16582, 17123, 17673, 18234,
    18803, 19383, 19972, 20570, 21178, 21796, 22424, 23061,
    23708, 24365, 25032, 25709, 26395, 27091, 27797, 28513,
    29239, 29975, 30721, 31477, 32243, 33019, 33805, 34602,
    35408, 36225, 37051, 37888, 38735, 39592, 40460, 41338,
    42226, 43124, 44033, 44952, 45881, 46821, 47772, 48732,
    49703, 50685, 51677, 52679, 53692, 54716, 55750, 56795,
    57850, 58916, 59992, 61080, 62177, 63286, 64405, 65535
};

// Gamma-corrected ambient brightness scale (10 levels)
const uint16_t code ambient_scale[10] = {
    0, 521, 2395, 5845, 11007, 17983, 26857, 37701, 50575, 65535
};


void setAmbientLevel(uint8_t level) {
    if (level > 9) level = 9;
    ambient_level = level;
}

