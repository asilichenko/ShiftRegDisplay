/*
    ShiftRegDisplay.h - Library for 9 digit 7 segment display on 74HC595 shift registers.

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
	 * dataPin - connected to DS (14) pin of 74HC595
	 * latchPin - connected to ST_CP (12) and OE (13) pins of 74HC595
	 * clockPin - connected to SH_CP (11) pin of 74HC595
	 * bitOrder - either MSBFIRST or LSBFIRST
	 */
    ShiftRegDisplay(byte dataPin, byte latchPin, byte clockPin, 
					byte bitOrder = MSBFIRST, indicatorType iType = COMMON_CATHODE);
	
	/**
	 * Вывести массив символов на индикатор
	 *
	 * data - массив символов (размер от 0 до 9)
	 * len - сколько символов из массива data необходимо вывести (0-9)
	 * align - если количество символов меньше 9, то выравнивание по краю (LOWER_POS или UPPER_POS)
	 */
    void showData(const byte data[], byte len = MAX_LEN, alignMode align = LOWER_POS);
	/**
	  * Отображать данные data в течение duration миллисекунд
	  */
	void showDataMillis(long duration, const byte data[], byte len = MAX_LEN, alignMode align = LOWER_POS);
	
	/**
	 * Вывести одиночный символ в конкретной позиции
	 *
	 * symbol - битовое представление символа на индикаторе
	 * pos - позиция индикатора (0-9)
	 */
    void showSymbol(byte symbol, byte pos);
	/**
	  * Отображать одиночный символ symbol на позиции pos в течение duration миллисекунд
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
