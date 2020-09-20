/**
 * "Сердечко". Вариант 3 КА (RGB) на базе макроса everyOVF().
 * размер скетча при компиляции 1136 байт. SRAM = 53байт.
 *
 * Аппаратное, плавное управление яркостью каналов RGB светодиода (ШИМ - широтно-импульсная модуляция, PWM)
 * Изменяем яркость за счет изменения ширины (длительности) импульса (1) и его паузы (0) при одной и той же
 * тактовой частоте следования импульсов (тут стандартно 16МГц/64/256=976Гц.)
 *
 * "Сердечный ритм" задается последовательностью предельных значений яркости (массив starts)
 * и набором шагов (скорости) изменения яркости (ширины импульсов). На каждой стадии цикла
 * из массива starts[] выбираются 2 соседних элемента для определения "начала" и "конца" стадии.
 *
 * Дополнительно подключаем КА "контрольный светодиод", который будет моргать по секундно.
 * 
 * Примечание:
 * поскольку чиселки небольшие, то крайние значения надо выбирать так, чтобы добавляя или убавляя
 * шаг не выйти через переполнение (<256). В противном случае, получится не то что вы ожидали увидеть.
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

#include "arhat.h"

#define pinRed          pin9    // нога со светодиодом R для плавного управления яркостью
#define pinGreen        pin4    // нога со светодиодом G для плавного управления яркостью
#define pinBlue         pin10   // нога со светодиодом B для плавного управления яркостью

#define WAIT_STEP       29      // тиков, 30 миллисекунд на 1 шаг изменения яркости
#define WAIT_CYCLE      156     // .., 160 миллисекунд паузы между повторением

#define WAIT_ON         98      // .., 100 мсек интервал включение контрольного светодиода (pinLed = 13)
#define WAIT_OFF        878     // .., 900 мсек интервал выключения контрольного светодиода

// Текущие данные всех КА объявляем статически. Они не должны меняться между вызовами функции КА:
// начальные значение устанавливаем в setup() чтобы компилятор не создавал доп. код по переносу данных
// из программной памяти flash в оперативную sram

// ======== КА blink: моргалка контрольным светодиодом ========= //
uint32_t blinkWait;             // текущий интервал ожидания. WAIT_ON или WAIT_OFF могут отличаться!
uint8_t  blinkState;            // текущее состояние светодиода. НЕЛЬЗЯ прочитать через digitalRead() !!!

// ======== КА heart: сердечко ========= //

// пределы яркости: каждая пара соседних чисел: "от".."до"
// сначала плавно растим яркость от 10 до 240, затем гасим от 240 до 20,
// снова увеличиваем от 20 до 230 и потом уменьшаем от 230 до 10
// ... и далее "по кругу". Конец всегда должен быть равен началу.
uint8_t starts[] = {10,230,20,220,10};

// скорость изменения яркости: шагов меньше на один чем пределов!
#define MAX_STEPS   4
uint8_t steps[] = {20,15,15,10};

// Счетчики стадии сердечка, текущая яркость и текущее время ожидания
uint32_t  heartWait[3];
uint8_t  heartState[3];
uint8_t  heartLight[3];

// Пример единой функции действий для 3-х КА в виде "функции переходов" между его состояниями
void doHeart(uint8_t tscNum)
{
  uint8_t curMax  = starts[heartState[tscNum]];
  uint8_t nextMax = starts[heartState[tscNum] + 1];

  if( nextMax > curMax ){                               // яркость - увеличиваем?
    heartLight[tscNum] += steps[heartState[tscNum]];
    if( heartLight[tscNum] >= nextMax ){                // . дошли до максиума яркости стадии?
      ++heartState[tscNum];                             // .. переходим на след. стадию.
    }
  } else {
    heartLight[tscNum] -= steps[heartState[tscNum]];
    if( heartLight[tscNum] <= nextMax ){                // . уменьшаем текущую яркость. Миниум?
      ++heartState[tscNum];                             // .. переходим на след. стадию.
    }
  }
  heartWait[tscNum] = WAIT_STEP;                        // интервал ожидания следующего шага КА
  if( heartState[tscNum] >= MAX_STEPS ){
    heartState[tscNum] = 0;                             // стадии кончились? Всё с начала.
    heartWait[tscNum] = WAIT_CYCLE + 250*tscNum;        // но ожидание начала у каждого КА - своё
  };

  // поскольку библиотека работает только с константами, то изменяем ШИМ (яркость) так:
  {
    uint8_t curLight = heartLight[tscNum];

    if( tscNum == 0 ){ analogWrite(pinRed,   curLight); return; }
    if( tscNum == 1 ){ analogWrite(pinGreen, curLight); return; }
    if( tscNum == 2 ){ analogWrite(pinBlue,  curLight); return; }
  }
}

// ======== Остаток типового скетча: настройки в setup() и повтор действий КА в loop()
void setup() {
  pinMode(pinLed, OUTPUT);      // контрольная 13 нога (встроенный светодиод)

  pwmSet(pinRed);               // включаем 4-ю ногу в режим ШИМ (PWM) и на выход
  pwmSet(pinBlue);              // включаем 10-ю ногу в режим ШИМ (PWM) и на выход
  pwmSet(pinGreen);             // включаем 9-ю ногу в режим ШИМ (PWM) и на выход

  // начальные установки КА: всё в нули, поставят сами при первом вызове
  blinkWait = blinkState = 0;

  heartWait[0] = 0; heartState[0] = 0; heartLight[0] = steps[0];
  heartWait[1] = 0; heartState[1] = 0; heartLight[1] = steps[0];
  heartWait[2] = 0; heartState[2] = 0; heartLight[2] = steps[0];
}

void loop() {
  // пример КА, реализуемый непосредственно внутри вызова макроса:
  everyOVF(blinkWait,
  {
    if( blinkState == 0 ) { blinkState = 1; blinkWait = WAIT_ON; }
    else                  { blinkState = 0; blinkWait = WAIT_OFF; }
    digitalWrite(pinLed, blinkState);
  });

  // отдельную функцию КА прописываем как вызов прямо в параметрах, ибо подстановка текста "как есть":
  everyOVF(heartWait[0], doHeart(0) );
  everyOVF(heartWait[1], doHeart(1) );
  everyOVF(heartWait[2], doHeart(2) );
}