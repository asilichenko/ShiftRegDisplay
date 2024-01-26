/*
    Demo for 9-Digit 7-Segment display on 74HC595 shift registers.

    Copyright (C) 2021-2024 Oleksii Sylichenko (a.silichenko@gmail.com)

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

namespace sevenSeg {
  const byte FONT_S = FONT_NUMBER[5];
  const byte FONT_T = _F|_E|_D|_G;
  const byte FONT_A = FONT_NUMBER[0xA];
  const byte FONT_R = _G|_E;
}

#define DAT_PIN   8   // 14 (DS)
#define LATCH_PIN 10  // 12 (ST_CP) + 13 (OE)
#define CLK_PIN   12  // 11 (SH_CP)

ShiftRegDisplay disp(DAT_PIN, LATCH_PIN, CLK_PIN);
ShiftRegDisplay dispLsb(DAT_PIN, LATCH_PIN, CLK_PIN, LSBFIRST);

const byte START[9] = {FONT_S, FONT_T, FONT_A, FONT_R, FONT_T};

byte data[9] = {FONT_NUMBER[1], FONT_NUMBER[2], FONT_NUMBER[3], FONT_NUMBER[4], 
                FONT_NUMBER[5], FONT_NUMBER[6], FONT_NUMBER[7], FONT_NUMBER[8], FONT_NUMBER[9]};

byte time[9] = {FONT_NUMBER[0], FONT_NUMBER[8]|DOT, FONT_NUMBER[2], FONT_O_SMALL, FONT_NUMBER[0], 
                FONT_NUMBER[4], DASH, FONT_NUMBER[2], FONT_NUMBER[0]};

void setup() {
  disp.showDataMillis(1000, START);
}

#define ONCE_A_SEC (millis() / 1000)

void loop() {
  long state = ONCE_A_SEC % 6;
  switch (state) {
    case 0: disp.showData(data); break;
    case 1: disp.showData(data, 4); break;
    case 2: disp.showData(data, 5, ShiftRegDisplay::UPPER_POS); break;
    case 3: 
      time[6] = ((millis() % 1000) > 500) ? DASH : 0x00;
      disp.showData(time);
      break;
    case 4:
      for(byte pos = 0; pos < 9; pos++) {
        for(byte seg = 0; seg < 8; seg++) disp.showSymbolMillis(100, bit(seg), pos);
      }
      break;
    case 5:
      for(byte pos = 0; pos < 9; pos++) {
        for(byte seg = 0; seg < 8; seg++) dispLsb.showSymbolMillis(100, bit(seg), pos);
      }
      break;
  } 
}
