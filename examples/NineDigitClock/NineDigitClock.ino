/*
    Demo for 9-Digit 7-Segment display on 74HC595 shift registers
    with real time clock module DS1302

    Copyright (C) 2021 Alexey Silichenko (a.silichenko@gmail.com)
  
    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
    USA
 */

#include <ShiftRegDisplay.h>
#include <SevenSegmentFonts.h>
using namespace sevenSeg;

#define DISP_DAT_PIN   8   // 14 (DS)
#define DISP_LATCH_PIN 10  // 12 (ST_CP) + 13 (OE)
#define DISP_CLK_PIN   12  // 11 (SH_CP)

ShiftRegDisplay disp(DISP_DAT_PIN, DISP_LATCH_PIN, DISP_CLK_PIN);

#include <stdio.h>
#include <DS1302.h>

#define TIME_CLK_PIN  2
#define TIME_DAT_PIN  3
#define TIME_RST_PIN  4
DS1302 clock(TIME_RST_PIN, TIME_DAT_PIN, TIME_CLK_PIN);

void setup() {
}

byte data[ShiftRegDisplay::MAX_LEN] = {0};
void loop() {
  static long timer;
  if (millis() - timer > 500) {
    timer = millis();
    receiveData();
  }
  
  disp.showData(data);
}

#define TWICE_A_SEC  (millis() / 500 % 2)
void receiveData() {
  Time t = clock.getTime();

  byte d[ShiftRegDisplay::MAX_LEN] = {
    FONT_NUMBER[t.date / 10], FONT_NUMBER[t.date % 10] | DOT,
    FONT_NUMBER[t.dow],
    FONT_O_SMALL,
    FONT_NUMBER[t.hour / 10], FONT_NUMBER[t.hour % 10],
    (TWICE_A_SEC ? DASH : 0x00),    
    FONT_NUMBER[t.min / 10], FONT_NUMBER[t.min % 10]
  };

  memcpy(data, d, sizeof d);
}
