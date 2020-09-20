/**
 * "Тест работы главного таймера времени".
 *
 * Этот тест создавался как контрольный для проверки функций, замещающих типовой файл wiring.c
 * Отличия:
 * 1. Упрощена процедура обработки прерывания от таймера0. Переписана в ассемблер.
 * Это сокращает размер, укоряет её работу (разгружает процессор от фоновой задачи)
 * и уменьшает занимаемый объем оперативной памяти с 9 до 4 байт.
 * Проверка работы процедуры прерывания выполнена в первой части.
 *
 * 2. Добавлена функция консистентного чтения (без ошибок), счетчика вызова процедуры прерываний.
 * Его просто не было.
 *
 * 3. Функция micros() переписана в ассемблер. Уменьшен размер, увеличена скорость. Количество
 * микросекунд теперь уточнено НА МОМЕНТ возврата из этой функции. Проверка работы micros()
 * выполнена во второй части теста.
 *
 * 4. Третья часть содержит проверку работы стандартной функции delay(). Тут проверяются 2 разные
 * реализации этой функции в зависимости от режима компиляции:
 * а) режим совместимости. Проверяется аналог стандартной функции, принимающей 4-х длинное целое
 * значение задержки в миллисекундах (может задерживать работу до 49,7 дней!)
 * б) режим минимальной компиляции: типовая функция delay() в нем ПЕРЕИМЕНОВАНА, так что принимает
 * только 2-х байтовое целое число миллисекунд (только до 65.5сек!). Зато этот режим экономит
 * около 6 байт на каждый вызов delay().
 *
 * @author Arhat109 arhat109@mail.ru, +7-(951)-388-2793
 * 
 * Лицензия:
 * 1. Полностью свободное и бесплатное программное обеспечение. В том числе и от претензий.
 * 2. Вы вправе использовать его на свои нужды произвольным образом и на свой риск.
 * 3. Вы не вправе удалять из него строку с тегом @author или изменять её.
 * 4. Изменяя этот файл, Вы вправе дописать свои авторские данные и/или пояснения.
 * 
 * Если Вам это оказалось полезным, то Вы можете по-достоинству оценить мой труд
 * "на свое усмотрение" (напр. кинуть денег на телефон "сколько не жалко")
 */

#define _ARHAT_ 1
#include "arhat.h"

#define testPin     13

//
// test working time interrupt and its overflow count only:
// +1000 timer0_overflow_count == 1024 milli seconds = 1.024sec!
//
static unsigned long curCount=0UL;
void testOvfCount( uint16_t onTicks, uint16_t offTicks )
{
  curCount = getOvfCount();                       // store start value
  digitalWrite(testPin, HIGH);                    // set LED to ON
  while( getOvfCount() - curCount < onTicks );    // wait for ON delay

  curCount = getOvfCount();
  digitalWrite(testPin, LOW);
  while( getOvfCount() - curCount < offTicks );
}

// quickly blinks 3 times for next test and pause 0.5 sec.
void testBlink3()
{
    testOvfCount(150,150);      // blink1
    testOvfCount(150,150);      // blink2
    testOvfCount(150,500);      // blink3 and pause after
}

//
// test working microseconds getter
//
static unsigned long    curMicros = 0UL;
void testMicros(unsigned long ticks)
{
   curMicros = micros();                        // store start value
   digitalWrite(testPin, HIGH);                 // set LED to ON
   while( micros() - curMicros < ticks );       // wait for delay

   curMicros = micros();
   digitalWrite(testPin, LOW);
   while( micros() - curMicros < ticks );
}

//
// test delay() waiting in milliseconds
//
void testDelay( uint16_t waitON, uint16_t waitOFF)
{
    digitalWrite(testPin, HIGH);
    delay(waitON);

    digitalWrite(testPin, LOW);
    delay(waitOFF);
}

void setup() {
  pinMode(testPin, OUTPUT);
}

void loop() {

uint8_t    i;

  testBlink3();

  // 1. test interrupt only: 10 times about 0.9994 sec. ON/OFF
  for(i=10; i>0; i--)  testOvfCount(976, 976);
  testBlink3();

  // 2. test micros(): 10 times each 0.5 seconds ON/OFF
  for(i=10; i>0; i--)  testMicros(500000);
  testBlink3();

  // 3. test delay16(): 10 times each 1 sec ON and 0.5 sec OFF
  for(i=10; i>0; i--)  testDelay(1000, 500);
  testBlink3();
}
