#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#define ANIMATION_STATIC 0
#define ANIMATION_BLINK  1
#define ANIMATION_FADE   2

#include "config.h"
#include <FastLED.h>


class Gradient {


private:
  const CHSV m_stockGradients[24][2] = {
    { CHSV(224, 187, 255), CHSV(0, 187, 255) },
    { CHSV(224, 187, 255), CHSV(0, 187, 255) },
    { CHSV(224, 187, 255), CHSV(0, 187, 255) },
    { CHSV(224, 187, 255), CHSV(0, 187, 255) },
    { CHSV(224, 187, 255), CHSV(0, 187, 255) },
    { CHSV(224, 187, 255), CHSV(0, 187, 255) },
    { CHSV(224, 187, 255), CHSV(0, 187, 255) },
    { CHSV(224, 187, 255), CHSV(0, 187, 255) },
    { CHSV(224, 187, 255), CHSV(0, 187, 255) },
    { CHSV(224, 187, 255), CHSV(0, 187, 255) },
    { CHSV(224, 187, 255), CHSV(0, 187, 255) },
    { CHSV(224, 187, 255), CHSV(0, 187, 255) },
    { CHSV(224, 187, 255), CHSV(0, 187, 255) },
    { CHSV(224, 187, 255), CHSV(0, 187, 255) },
    { CHSV(224, 187, 255), CHSV(0, 187, 255) },
    { CHSV(224, 187, 255), CHSV(0, 187, 255) },
    { CHSV(224, 187, 255), CHSV(0, 187, 255) },
    { CHSV(224, 187, 255), CHSV(0, 187, 255) },
    { CHSV(224, 187, 255), CHSV(0, 187, 255) },
    { CHSV(224, 187, 255), CHSV(0, 187, 255) },
    { CHSV(224, 187, 255), CHSV(0, 187, 255) },
    { CHSV(224, 187, 255), CHSV(0, 187, 255) },
    { CHSV(224, 187, 255), CHSV(0, 187, 255) },
    { CHSV(224, 187, 255), CHSV(0, 187, 255) }
  };

  int m_count;

  CHSV m_startColor;
  CHSV m_endColor;

  int m_dh;
  int m_ds;
  int m_dv;

public:
  Gradient(int count, int stockId);
  void getColor(int pos, CHSV& color);
};


class Animation {
private:
  CHSV m_fromColors[NUM_LEDS];
  CHSV m_toColors[NUM_LEDS];
  uint8_t m_animationTypes[NUM_LEDS];

public:
  void createAnimation(unsigned long epoch);

  int getCount();

  CHSV getColor(int pos, int decisec);
};

#endif
