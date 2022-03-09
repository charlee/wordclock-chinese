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
    { CHSV(150, 255, 160), CHSV(255, 255, 160) },   // 0: dark blue
    { CHSV(150, 255,  96), CHSV(200, 255, 120) },   // 1: 
    { CHSV(150, 255,  96), CHSV(200, 255, 120) },   // 2: 
    { CHSV(160, 255,  96), CHSV(210, 255, 120) },   // 3: 
    { CHSV(160, 255,  96), CHSV(210, 255, 120) },   // 4
    { CHSV(210, 187, 160), CHSV(210,  48, 255) },   // 5
    { CHSV(210, 187, 160), CHSV(210,  48, 255) },   // 6
    { CHSV(224, 255, 120), CHSV(180, 255, 120) },   // 7
    { CHSV(180, 255, 120), CHSV( 88, 255, 120) },   // 8
    { CHSV(180, 255, 120), CHSV( 88, 255, 120) },   // 9
    { CHSV(105, 255, 120), CHSV( 46, 255, 120) },   // 10
    { CHSV( 35, 255, 120), CHSV(255, 255, 120) },   // 11
    { CHSV( 35, 255, 120), CHSV(255, 255, 120) },   // 12
    { CHSV(  0, 255, 120), CHSV(255, 255, 120) },   // 13
    { CHSV(  0, 255, 120), CHSV(255, 255, 120) },   // 14
    { CHSV(  0, 255, 224), CHSV(255, 255, 224) },   // 15
    { CHSV(  0, 255, 224), CHSV(255, 255, 224) },   // 16
    { CHSV(130, 255, 224), CHSV( 50, 255, 224) },   // 17
    { CHSV(130, 255, 194), CHSV(  0, 255, 140) },   // 18
    { CHSV( 60, 255, 194), CHSV(  0, 255, 120) },   // 19
    { CHSV( 60, 255, 194), CHSV(  0, 255, 120) },   // 20
    { CHSV(  0, 180, 165), CHSV(  0,  55, 255) },   // 21
    { CHSV(  0, 180, 165), CHSV(  0,  55, 255) },   // 22
    { CHSV(  0,   0, 255), CHSV(194, 255, 160) },   // 23
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

private:
  void dump(unsigned long epoch);
};

#endif
