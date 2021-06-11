# Библиотека ShiftRegDisplay для Arduino

Библиотека для Ардуино, которая помогает использовать 74HC595 сдвиговые регистры для вывода информации на 9-разрядный дисплей 7-сегментных индикаторов.

## 9-разрядный дисплей:
<p align="center">
  <img width="460" height="300" src="https://github.com/asilichenko/ShiftRegDisplay/blob/main/docs/img/9_digit_display.jpg">
</p>

## Распиновка 74HC595:
<p align="center">
  <img width="460" height="300" src="https://github.com/asilichenko/ShiftRegDisplay/blob/main/docs/img/74HC595.jpg">
</p>

Функционально 74HC595 состоит из: собственно, сдвигового регистра SH (от shift) и регистра хранения ST (от storage).

<p align="center">
  <img width="460" height="300" src="https://github.com/asilichenko/ShiftRegDisplay/blob/main/docs/img/74hc595_functional.png">
</p>

Данные в SH регистр вносятся последовательно - бит за битом, по фронту сигнала SH_CP. В ST регистр данные попадают по фронту сигнала ST_CP.

На выводы Q0-Q7 подаются данные из ST регистра, вне зависимости от того, что находится в данный момент в SH регистре. Сигнал OE служит выключателем подачи сигнала из ST регистра на выводы Q0-Q7: низкий уровень сигнала - данные выводятся, высокий - выводы переходят в Z-состояние (грубо говоря, электрически изолированы).

На вывод Q7S (или Q7') всегда подается сигнал из 7-го бита SH регистра. Он служит для передачи данных следующему регистру, но его можно использовать и с целью вывода дополнительного бита. Для этого потребуется:
- ввести первые 8 битов в SH регистр по тактовому сигналу SH_CP
- переместить данные в ST регистр по фронту тактового сигнала ST_CP
- ввести новые 8 бит в SH регистр, где 7й бит будет соответствовать 9му.

Изучить более детально особенности сдвигового регистра 74HC595 можно в даташите: https://github.com/asilichenko/ShiftRegDisplay/blob/main/docs/pdf/74HC_HCT595.pdf

Данная библиотека позволяет упростить работу со сдвиговыми регистрами, для отображения информации на 9-разрядном 7-сегментном дисплее. Дисплей необходимо собрать по следующей схеме:

<p align="center">
  <img width="460" height="300" src="https://github.com/asilichenko/ShiftRegDisplay/blob/main/docs/img/proteus.jpg">
</p>

Файл для симуляции в Proteus: https://github.com/asilichenko/ShiftRegDisplay/blob/main/simulation/proteus/NineDigitDisplay.pdsprj

Вход DS регистра U1 подключен непосредственно к Ардуино. Он принимает данные и передает следующему регистру U2. Таким образом, вход DS второго регистра U2 подключен к выводу Q7S первого регистра.

Первый регистр U1 служит для вывода позиции текущего символа, а второй - собственно, для вывода символа.

Для обеспечения возможности управления позиционными выводами индикатора, входы регистров ST_CP (тактирующий ST) и OE (разрешение вывода) объединены.

## Физически, соединение регистров и Ардуино выглядит следующим образом
<p align="center">
  <img width="460" height="300" src="https://github.com/asilichenko/ShiftRegDisplay/blob/main/docs/img/fritzing.jpg">
</p>

## Библиотека позволяет:
- выводить на дисплей до 9 символов с выравниванием по любому краю
- выводить одиночный символ в определенной позиции
- выводить данные на дисплей в течение указанной длительности в мс
- программно переопределять соответствие выводов и сегментов индикатора
- выводит предопределенные символы: 16-ричные цифры, знак минуса, маленькая "о"
- определать собственный шрифт, который не зависит от конкретного соответствия выводов сегментам
- использовать индикаторы как с общим катодом, так и с общим анодом (в сборке, конечно, индикаторы должны быть однотипные)
