/*
    ShiftRegDisplay.cpp - Library implementation for 9 digit 7 segment display on 74HC595 shift registers.

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

#include "ShiftRegDisplay.h"

ShiftRegDisplay::ShiftRegDisplay(byte dataPin, byte latchPin, byte clockPin, byte bitOrder, indicatorType iType) {
  this->_dataPin = dataPin;
  this->_latchPin = latchPin;
  this->_clockPin = clockPin;
  this->_bitOrder = bitOrder;
  this->_iType = iType;
  this-> Q7S_BIT = bit((LSBFIRST == this->_bitOrder) ? 0 : 7);
	
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
}

void ShiftRegDisplay::showDataMillis(long duration, const byte data[], byte len, alignMode align) {
  for(long t = millis(); millis() - t < duration;) this->showData(data, len, align);
}

void ShiftRegDisplay::showData(const byte data[], byte len, alignMode align) {
  if(len > MAX_LEN) len = MAX_LEN;
  for(byte i = 0; i < len; i++) {
    byte pos = ShiftRegDisplay::UPPER_POS == align ? (i + MAX_LEN - len) : i;
    this->showSymbol(data[i], pos);
  }
}

void ShiftRegDisplay::showSymbolMillis(long duration, byte symbol, byte pos) {
  for(long t = millis(); millis() - t < duration;) this->showSymbol(symbol, pos);
}

void ShiftRegDisplay::showSymbol(byte symbol, byte pos) {
  if(LSBFIRST == this->_bitOrder) pos = ((0 == pos) ? this->MAX_LEN : pos) - 1;
	
  // загрузить данные в SH регистр
  this->_sendData(symbol, bit(pos));

  // загрузить данные из SH регистров в ST регистры
  digitalWrite(this->_latchPin, LOW);  // подготовка к переносу данных в ST регистр (происходит по фронту сигнала: LOW -> HIGH)
  digitalWrite(this->_latchPin, HIGH); // вывести данные в ST регистр, переход в Z-состояние (отключить отображение)

  // очистить SH регистр символа и выставить состояние отображения 9-го разряда
  const bool IS_Q7S_DIGIT = (this->MAX_LEN - 1 == pos);
  this->_sendData(0x00, IS_Q7S_DIGIT ? this->Q7S_BIT : 0x00);  
    
  digitalWrite(this->_latchPin, LOW);  // снять Z-состояние (отобразить текущий символ)
    
  delay(1); // минимальная задержка, чтобы символ успел отобразится. Значение задержки > 2мс приводит к заметному мерцанию

  digitalWrite(this->_latchPin, HIGH); // перевести в Z-состояние (убрать отображение), чтобы все разряды горели равномерно 
}

void ShiftRegDisplay::_sendData(byte symbol, byte pos) {
  if(ShiftRegDisplay::COMMON_CATHODE == _iType) pos = ~pos; else symbol = ~symbol;
  shiftOut(this->_dataPin, this->_clockPin, this->_bitOrder, symbol);
  shiftOut(this->_dataPin, this->_clockPin, this->_bitOrder, pos);
}
