#ifndef __CHINESE_WORD_MATRIX_H__
#define __CHINESE_WORD_MATRIX_H__

typedef struct time_leds {
  byte month[3];
  byte day[4];
  byte hour[5];
  byte minute[4];
} TimeLEDs;


int getLEDsByEpoch(unsigned long epoch, uint8_t* leds);

#endif