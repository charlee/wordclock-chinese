Chinese Word Clock
======================

[中文版](#汉字文字钟)

Inspired by the famous [Word Clock](https://www.instructables.com/Wordclock/),
this project created a word clock that consists of Chinese characters.
Driven by an ESP8266, this clock synchronize time from NTP servers automatically.

## Hardware

The clock itself is a 7x10 LED matrix consists of 70 WS2812b RGB LEDs,
cut from an LED strip. The microcontroller is an ESP8266 DevKit,
which provides Micro-USB interface used to power the ESP8266 and the LEDs.

### Power

WS2812b RGB consumes a lot of power. When displaying white color in full brightness,
it consumes about 60mA at 5V (20mA per R, G, B color). 
In the worst case, there are 16 LEDs being turned on (e.g. "十二月二十四日晚上十一点五十六分"),
which consumes 60mA * 16 = 960mA. 

Also, according to [the datasheet of ESP8266](https://www.espressif.com/sites/default/files/documentation/0a-esp8266ex_datasheet_en.pdf), it consumes about 170mA when using WiFi.

So the total current is about 1.2A. Therefore, a USB power adapter at least 1.5A is required.

Also note that 1.2A goes way beyond the 500mA limit that computer USB ports could provide.
When debugging / developing programs on the computer, make sure to use a small brightness.



## Development

The program is written with Arduino. 

The whole program consists of the following parts:

- `ChineseWordMatrix.*`: convert timestamps to LED indicies.
- `EEPROMConfig。*`, `ESP8266AutoConfig.*`, `WiFiConfig.*`: provides the WiFi management functionality.
- `Animation.*`: implements the fade in/fade out/breathing animations.



汉字文字钟
============

本项目是一个汉字版本的文字钟，通过钟面上的汉字来显示时间。创意来自[Word Clock](https://www.instructables.com/Wordclock/)。
微控制器为ESP8266，因此设备支持WiFi，并且可以自动从NTP服务器同步时间。

## 硬件

钟面本身由70个 WS2812b RGB LED组成。LED来自一条RGB LED灯带。微控制器为一块ESP8266开发板，
可以通过Micro-USB为ESP8266和LED供电。

### 电源

WS2812b RGB LED本身会消耗很大电力。在以最大亮度显示白色时，一颗RGB大约产生60mA的电流（红黄蓝每种颜色各20mA）。
在最坏的情况下，会有16个LED同时亮起（例如“十二月十二四日晚上十一点五十六分”），此时产生的电流为 60mA * 16 = 960mA。

另外，根据[ESP8266的数据手册](https://www.espressif.com/sites/default/files/documentation/0a-esp8266ex_datasheet_en.pdf)，在使用WiFi时，
ESP8266会产生大约170mA的电流。

总电流约为1.2A。因此，需要使用至少1.5A的USB适配器来供电。

另外，1.2A已远远超过了电脑的USB接口能提供的500mA限制。因此在开发或调试时，务必将brightness设为一个较小的值。


## 开发

程序基于Arduino。

整个程序由以下模块组成：

- `ChineseWordMatrix.*`：负责将时间戳转换成LED的序号。
- `EEPROMConfig。*`, `ESP8266AutoConfig.*`, `WiFiConfig.*`：负责WiFi管理和配置。
- `Animation.*`：用于产生渐入/渐出和呼吸效果的动画。

