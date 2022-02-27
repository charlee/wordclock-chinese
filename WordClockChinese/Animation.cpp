#include <TimeLib.h>
#include <stdlib.h>
#include "Animation.h"
#include "ChineseWordMatrix.h"

#include "config.h"


Gradient::Gradient(int count, int stockId) {
  m_startColor = m_stockGradients[stockId][0];
  m_endColor = m_stockGradients[stockId][1];
  m_count = count;

  m_dh = (m_endColor.h - m_startColor.h) * 10 / (m_count - 1);
  m_ds = (m_endColor.s - m_startColor.s) * 10 / (m_count - 1);
  m_dv = (m_endColor.v - m_startColor.v) * 10 / (m_count - 1);
}

void Gradient::getColor(int pos, CHSV& color) {
  color.h = m_startColor.h + (m_dh * pos / 10);
  color.s = m_startColor.s + (m_ds * pos / 10);
  color.v = m_startColor.v + (m_dv * pos / 10);
}


void Animation::createAnimation(unsigned long epoch) {

  int i;
  int count;
  uint8_t led_pos[16];

  int sec = second(epoch);

  Gradient *pGradient;

  // clear all
  for (i = 0; i < NUM_LEDS; i++) {
    m_fromColors[i].setHSV(0, 0, 0);
    m_toColors[i].setHSV(0, 0, 0);
    m_animationTypes[i] = ANIMATION_STATIC;
  }

  if (sec == 0) {
    // switch time display animation
    unsigned long oldEpoch = epoch - 2000;
    count = getLEDsByEpoch(oldEpoch, &(led_pos[0]));

    pGradient = new Gradient(count, hour(oldEpoch));

    for (i = 0; i < count; i++) {
      pGradient->getColor(i, m_fromColors[led_pos[i]]);
      m_animationTypes[led_pos[i]] = ANIMATION_FADE;
    }

    delete pGradient;

    count = getLEDsByEpoch(epoch, &(led_pos[0]));
    for (i = 0; i < count; i++) {
      pGradient->getColor(i, m_toColors[led_pos[i]]);
      m_animationTypes[led_pos[i]] = ANIMATION_FADE;
    }

    delete pGradient;

  } else {
    // blink last digit animation
    count = getLEDsByEpoch(epoch, &(led_pos[0]));

    // create gradient based on current hour
    pGradient = new Gradient(count, hour(epoch));

    for (i = 0; i < count; i++) {
      pGradient->getColor(i, m_fromColors[led_pos[i]]);
      m_animationTypes[led_pos[i]] = (i == count - 1) ? ANIMATION_BLINK : ANIMATION_STATIC;
    }

    delete pGradient;
  }

}


CHSV Animation::getColor(int pos, int decisec) {

  if (m_animationTypes[pos] == ANIMATION_BLINK) {
    int ratio = (abs((decisec* 2) - 9) + 10) / 2;
    return CHSV(m_fromColors[pos].h, m_fromColors[pos].s, m_fromColors[pos].v * ratio / 10);
  } else if (m_animationTypes[pos] == ANIMATION_FADE) {
    return CHSV(
      m_fromColors[pos].h * (10 - decisec) + m_toColors[pos].h * decisec,
      m_fromColors[pos].s * (10 - decisec) + m_toColors[pos].s * decisec,
      m_fromColors[pos].v * (10 - decisec) + m_toColors[pos].v * decisec
    );
  } else {
    return m_fromColors[pos];
  }
}