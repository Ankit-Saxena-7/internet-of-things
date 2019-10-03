
< Back to Libraries
Selected library
ADAFRUIT_MPR1210.0.2
Adafruit MPR121 12-Key Capacitive Touch Sensor Breakout library for Particle devices
Files
Adafruit_MPR121.cpp
Adafruit_MPR121.h
Examples
MPR121_ISR.ino
MPR121_Test.ino
Adafruit_MPR121.cppAdafruit_MPR121.h

1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
32
33
34
35
36
37
38
39
40
41
42
43
44
/***************************************************
  This is a library for the MPR121 12-Channel Capacitive Sensor
  Designed specifically to work with the MPR121 breakout from Adafruit
  ----> https://www.adafruit.com/products/1982
  These sensors use I2C to communicate, 2+ pins are required to
  interface
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!
  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/
#ifndef ADAFRUIT_MPR121_H
#define ADAFRUIT_MPR121_H

#if defined(PARTICLE)
#include "Particle.h"
#undef _BV
#define _BV(_b)   (0x01 << _b)
#else
#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
#include <Wire.h>
#endif
// The default I2C address
#define MPR121_I2CADDR_DEFAULT 0x5A
#define MPR121_TOUCHSTATUS_L 0x00
#define MPR121_TOUCHSTATUS_H 0x01
#define MPR121_FILTDATA_0L  0x04
#define MPR121_FILTDATA_0H  0x05
#define MPR121_BASELINE_0   0x1E
#define MPR121_MHDR         0x2B
#define MPR121_NHDR         0x2C
#define MPR121_NCLR         0x2D
#define MPR121_FDLR         0x2E
#define MPR121_MHDF         0x2F
Please enter the title to create your first app. R2-D2  v1.4.0 
