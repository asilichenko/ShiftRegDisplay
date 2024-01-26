/*
    ShiftRegDisplay.h - Library for 9 digit 7 segment display on 74HC595 shift registers.

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

#pragma once
#include <Arduino.h>

class ShiftRegDisplay {

  public:

  static const byte MAX_LEN = 9;

  enum alignMode {
    LOWER_POS, UPPER_POS
  };
  
  enum indicatorType {
    COMMON_CATHODE, COMMON_ANODE
  };

  /**
   * dataPin  - connected to DS (14) pin of 74HC595
   * latchPin - connected to ST_CP (12) and OE (13) pins of 74HC595
   * clockPin - connected to SH_CP (11) pin of 74HC595
   * bitOrder - either MSBFIRST or LSBFIRST
   */
  ShiftRegDisplay(byte dataPin, byte latchPin, byte clockPin, 
                  byte bitOrder = MSBFIRST, indicatorType iType = COMMON_CATHODE);
  
  /**
   * Display an array of symbols to the display
   *
   * data - symbols array (size from 0 to 9)
   * len - how many symbols from the array must be displayed (0-9)
   * align - if number of symbols is less than 9, then align to the edge (LOWER_POS или UPPER_POS)
   */
  void showData(const byte data[], byte len = MAX_LEN, alignMode align = LOWER_POS);

  /**
   * Display `data` within `duration` milliseconds
   */
  void showDataMillis(long duration, const byte data[], byte len = MAX_LEN, alignMode align = LOWER_POS);
  
  /**
   * Display a symbols in specific position
   *
   * symbol - Bit representation of the character on the display
   * pos - indicator position (0-9)
   */
  void showSymbol(byte symbol, byte pos);

  /**
   * Display a symbol on the position `pos` within `duration` milliseconds
   */
  void showSymbolMillis(long duration, byte symbol, byte pos);

  private:
  byte _dataPin;
  byte _latchPin;
  byte _clockPin;
  byte _bitOrder;
  indicatorType _iType;
  byte Q7S_BIT;
  void _sendData(byte symbol, byte pos);
};
