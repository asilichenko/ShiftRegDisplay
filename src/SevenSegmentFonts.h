/*
    SevenSegmentFonts.h - Fonts definition for 7-Segment display.

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
#pragma once

namespace sevenSeg {

#ifndef CUSTOM_FONT_BIT_MAPPING
  /*
    Names of segments:
     -- A --
    |       |
    F       B
     -- G --
    E       C
    |       |
     -- D --  .DP
  */
#ifdef FONT_BIT_MAPPING_REVERSED
  const byte _A  bit(7);
  const byte _B  bit(6);
  const byte _C  bit(5);
  const byte _D  bit(4);
  const byte _E  bit(3);
  const byte _F  bit(2);
  const byte _G  bit(1);
  const byte _DP bit(0);
#else
  const byte _A  bit(0);
  const byte _B  bit(1);
  const byte _C  bit(2);
  const byte _D  bit(3);
  const byte _E  bit(4);
  const byte _F  bit(5);
  const byte _G  bit(6);
  const byte _DP bit(7);
#endif // FONT_BIT_MAPPING_REVERSED
#endif // CUSTOM_FONT_BIT_MAPPING

#define CLEAR_BITS(val, ex)   (val ^ ex)

  const byte DOT = _DP;
  const byte FULL_DIGIT = 0xFF;
  const byte DIGIT = CLEAR_BITS(FULL_DIGIT, _DP);
  const byte DASH = _G;

  const byte FONT_NUMBER[16] = {
    CLEAR_BITS(DIGIT, DASH),    // 0
    _B|_C,                      // 1 
    CLEAR_BITS(DIGIT, (_F|_C)), // 2 
    CLEAR_BITS(DIGIT, (_F|_E)), // 3 
    _B|_C|_F|_G,                // 4 
    CLEAR_BITS(DIGIT, (_B|_E)), // 5 
    CLEAR_BITS(DIGIT, _B),      // 6 
    _A|_B|_C,                   // 7 
    DIGIT,                      // 8
    CLEAR_BITS(DIGIT, _E),      // 9
    CLEAR_BITS(DIGIT, _D),      // A
    CLEAR_BITS(DIGIT, (_A|_B)), // b
    _A|_D|_E|_F,                // C
    CLEAR_BITS(DIGIT, (_A|_F)), // d
    CLEAR_BITS(DIGIT, (_B|_C)), // E
    _A|_E|_F|_G                 // F
  };

  const byte FONT_O_SMALL = _G|_C|_D|_E;
}
