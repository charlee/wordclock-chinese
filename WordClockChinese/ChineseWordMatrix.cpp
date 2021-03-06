/**
 * Chinese word mapping to the LED matrix
 */

#include <Arduino.h>
#include <TimeLib.h>
#include "ChineseWordMatrix.h"


/*

十一二三月  四五六七月   60 -> 69
八九月二三  十一二三日   59 <- 50
二十四五六  日七八九日   40 -> 49
早晚上中下  午十一二点   39 <- 30
两三四五点  六七八九点   20 -> 29
二三十零一  二分三四分   19 <- 10
四五十五六  分七八九分    0 ->  9

*/


const uint8_t cw_minutes[60][4] = {

  {99, 99, 99, 99},     // 00
  {16, 15, 13, 99},     // 01
  {16, 14, 13, 99},     // 02
  {16, 12, 10, 99},     // 03
  {16, 11, 10, 99},     // 04
  {16,  3,  5, 99},     // 05
  {16,  4,  5, 99},     // 06
  {16,  6,  9, 99},     // 07
  {16,  7,  9, 99},     // 08
  {16,  8,  9, 99},     // 09

  {17, 13, 99, 99},     // 10
  {17, 15, 13, 99},     // 11
  {17, 14, 13, 99},     // 12
  {17, 12, 10, 99},     // 13
  {17, 11, 10, 99},     // 14
  { 2,  3,  5, 99},     // 15
  { 2,  4,  5, 99},     // 16
  { 2,  6,  9, 99},     // 17
  { 2,  7,  9, 99},     // 18
  { 2,  8,  9, 99},     // 19

  {19, 17, 13, 99},     // 20
  {19, 17, 15, 13},     // 21
  {19, 17, 14, 13},     // 22
  {19, 17, 12, 10},     // 23
  {19, 17, 11, 10},     // 24
  {19, 17,  3,  5},     // 25
  {19, 17,  4,  5},     // 26
  {19, 17,  6,  9},     // 27
  {19, 17,  7,  9},     // 28
  {19, 17,  8,  9},     // 29

  {18, 17, 13, 99},     // 30
  {18, 17, 15, 13},     // 31
  {18, 17, 14, 13},     // 32
  {18, 17, 12, 10},     // 33
  {18, 17, 11, 10},     // 34
  {18, 17,  3,  5},     // 35
  {18, 17,  4,  5},     // 36
  {18, 17,  6,  9},     // 37
  {18, 17,  7,  9},     // 38
  {18, 17,  8,  9},     // 39

  { 0,  2, 13, 99},     // 40
  { 0,  2, 15, 13},     // 41
  { 0,  2, 14, 13},     // 42
  { 0,  2, 12, 10},     // 43
  { 0,  2, 11, 10},     // 44
  { 0,  2,  3,  5},     // 45
  { 0,  2,  4,  5},     // 46
  { 0,  2,  6,  9},     // 47
  { 0,  2,  7,  9},     // 48
  { 0,  2,  8,  9},     // 49

  { 1,  2, 13, 99},     // 50
  { 1,  2, 15, 13},     // 51
  { 1,  2, 14, 13},     // 52
  { 1,  2, 12, 10},     // 53
  { 1,  2, 11, 10},     // 54
  { 1,  2,  3,  5},     // 55
  { 1,  2,  4,  5},     // 56
  { 1,  2,  6,  9},     // 57
  { 1,  2,  7,  9},     // 58
  { 1,  2,  8,  9},     // 59
};



/*

十一二三月  四五六七月   60 -> 69
八九月二三  十一二三日   59 <- 50
二十四五六  日七八九日   40 -> 49
早晚上中下  午十一二点   39 <- 30
两三四五点  六七八九点   20 -> 29
二三十零一  二分三四分   19 <- 10
四五十五六  分七八九分    0 ->  9

*/

const uint8_t cw_hours[24][5] = {

  {38, 37, 33, 31, 30},   // 00
  {38, 37, 32, 30, 99},   // 01
  {38, 37, 20, 24, 99},   // 02
  {38, 37, 21, 24, 99},   // 03
  {39, 37, 22, 24, 99},   // 04
  {39, 37, 23, 24, 99},   // 05
  {39, 37, 25, 29, 99},   // 06
  {39, 37, 26, 29, 99},   // 07
  {39, 37, 27, 29, 99},   // 08
  {37, 34, 28, 29, 99},   // 09
  {37, 34, 33, 30, 99},   // 10
  {37, 34, 33, 32, 30},   // 11

  {36, 34, 33, 31, 30},   // 12
  {35, 34, 32, 30, 99},   // 13
  {35, 34, 20, 24, 99},   // 14
  {35, 34, 21, 24, 99},   // 15
  {35, 34, 22, 24, 99},   // 16
  {35, 34, 23, 24, 99},   // 17
  {38, 37, 25, 29, 99},   // 18
  {38, 37, 26, 29, 99},   // 19
  {38, 37, 27, 29, 99},   // 20
  {38, 37, 28, 29, 99},   // 21
  {38, 37, 33, 30, 99},   // 22
  {38, 37, 33, 32, 30},   // 23
};


/*

十一二三月  四五六七月   60 -> 69
八九月二三  十一二三日   59 <- 50
二十四五六  日七八九日   40 -> 49
早晚上中下  午十一二点   39 <- 30
两三四五点  六七八九点   20 -> 29
二三十零一  二分三四分   19 <- 10
四五十五六  分七八九分    0 ->  9

*/

const uint8_t cw_days[32][4] = {

  {99, 99, 99, 99},       // -
  {53, 50, 99, 99},       //  1
  {52, 50, 99, 99},       //  2
  {51, 50, 99, 99},       //  3
  {42, 45, 99, 99},       //  4
  {43, 45, 99, 99},       //  5
  {44, 45, 99, 99},       //  6
  {46, 49, 99, 99},       //  7
  {47, 49, 99, 99},       //  8
  {48, 49, 99, 99},       //  9

  {54, 50, 99, 99},       // 10
  {54, 53, 50, 99},       // 11
  {54, 52, 50, 99},       // 12
  {54, 51, 50, 99},       // 13
  {41, 42, 45, 99},       // 14
  {41, 43, 45, 99},       // 15
  {41, 44, 45, 99},       // 16
  {41, 46, 49, 99},       // 17
  {41, 47, 49, 99},       // 18
  {41, 48, 49, 99},       // 19

  {56, 54, 50, 99},       // 20
  {56, 54, 53, 50},       // 21
  {56, 54, 52, 50},       // 22
  {56, 54, 51, 50},       // 23
  {40, 41, 42, 45},       // 24
  {40, 41, 43, 45},       // 25
  {40, 41, 44, 45},       // 26
  {40, 41, 46, 49},       // 27
  {40, 41, 47, 49},       // 28
  {40, 41, 48, 49},       // 29

  {55, 54, 50, 99},       // 30
  {55, 54, 53, 50},       // 31
};

/*

十一二三月  四五六七月   60 -> 69
八九月二三  十一二三日   59 <- 50
二十四五六  日七八九日   40 -> 49
早晚上中下  午十一二点   39 <- 30
两三四五点  六七八九点   20 -> 29
二三十零一  二分三四分   19 <- 10
四五十五六  分七八九分    0 ->  9

*/
const uint8_t cw_months[13][3] = {
  {99, 99, 99},       // -
  {61, 64, 99},       //  1
  {62, 64, 99},       //  2
  {63, 64, 99},       //  3
  {65, 69, 99},       //  4
  {66, 69, 99},       //  5
  {67, 69, 99},       //  6
  {68, 69, 99},       //  7
  {59, 57, 99},       //  8
  {58, 57, 99},       //  9
  {60, 64, 99},       // 10
  {60, 61, 64},       // 11
  {60, 62, 64},       // 11
};

/**
 * epoch is with offset
 */
int getLEDsByEpoch(unsigned long epoch, uint8_t* led_pos) {

  int i, count, t;

  t = month(epoch);
  count = 0;
  for (i = 0; i < 3; i++) {
    if (cw_months[t][i] == 99) break;
    led_pos[count] = cw_months[t][i];
    count++;
  }

  t = day(epoch);
  for (i = 0; i < 4; i++) {
    if (cw_days[t][i] == 99) break;
    led_pos[count] = cw_days[t][i];
    count++;
  }

  t = hour(epoch);
  for (i = 0; i < 5; i++) {
    if (cw_hours[t][i] == 99) break;
    led_pos[count] = cw_hours[t][i];
    count++;
  }

  t = minute(epoch);
  for (i = 0; i < 4; i++) {
    if (cw_minutes[t][i] == 99) break;
    led_pos[count] = cw_minutes[t][i];
    count++;
  }

  return count;
}

