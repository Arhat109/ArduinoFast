/**
 * "КА мотор".
 * размер компилированного скетча = 896байт., SRAM = 28байт.
 *
 * Автоматное управление двумя маршевыми моторами, подключенными через шилд L298N
 * Каждый мотор управляется из своей таблицы переходов, хотя тут они полностью одинаковы.
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
#include "tsc.h"

// ============= Blink13 ============= //

#define BLINK13_ON   150          // Включен 0.15сек
#define BLINK13_OFF  850          // Выключен 0.85сек. Период = 1сек.

// .. Таблица переходов КА (нумерация с 0!):
const TSC_Step PROGMEM        tblBlink13[2] = {
/* { command, timeout,  next} */
   { to_on, BLINK13_ON,   1 }      // "выключен": включить, перейти к состоянию "включен" с задержкой
  ,{ to_off, BLINK13_OFF, 0 }      // "включен": всё наоборот, выключаем, переходим к пред. состоянию.
};

// .. Методы, исполняемые при изменении состояния КА:
void to_on(void *_ctrl) { digitalWrite(pinLed, HIGH); }     // .. включаем светодиод
void to_off(void *_ctrl){ digitalWrite(pinLed, LOW); }      // .. выключаем светодиод

TSC_Control     blink13;     // тут будем хранить текущие данные этого КА

// ============ Motors ============ //
#define moto1f  14
#define moto1b  15
#define moto1s   4

#define moto2f  16
#define moto2b  17
#define moto2s   9

#define WAIT_FORWARD    500
#define WAIT_BACK       500
#define WAIT_OP         100

TSC_Control     moto1;                  // тут будем хранить текущее состояние КА
TSC_Control     moto2;                  // тут будем хранить текущее состояние КА

// .. Методы, исполняемые при изменении состояния КА:
void empty() { return; }             // пропуск действия

void moto1Forward(void *_ctrl)
{
  pinOutLow(moto1b);
  pinOutHigh(moto1f);
  pinOutHigh(moto1s);
}
void moto1Back(void *_ctrl)
{
  pinOutLow(moto1f);
  pinOutHigh(moto1b);
  pinOutHigh(moto1s);
}
void moto1Stop(void *_ctrl)
{
  pinOutLow(moto1s);
}
void moto2Forward(void *_ctrl)
{
  pinOutLow(moto2b);
  pinOutHigh(moto2f);
  pinOutHigh(moto2s);
}
void moto2Back(void *_ctrl)
{
  pinOutLow(moto2f);
  pinOutHigh(moto2b);
  pinOutHigh(moto2s);
}
void moto2Stop(void *_ctrl)
{
  pinOutLow(moto2s);
}

const TSC_Step PROGMEM        tblMoto1[] = {
/* {   command,     timeout,   next} */
   { moto1Forward, WAIT_OP,      1 }    // 0: "вперед": запуск мотора.
  ,{ moto1Stop,    WAIT_FORWARD, 2 }    // 1: Пустое действие, едем вперед.
  ,{ moto1Back,    WAIT_OP,      3 }    // 2: "назад": запуск мотора.
  ,{ moto1Stop,    WAIT_BACK,    0 }    // 3: Пустое действие, едем назад.
};

const TSC_Step PROGMEM        tblMoto2[] = {
/* {   command,     timeout,   next} */
   { moto2Forward, WAIT_OP,      1 }    // 0: "вперед": запуск мотора.
  ,{ moto2Stop,    WAIT_FORWARD, 2 }    // 1: Пустое действие, едем вперед.
  ,{ moto2Back,    WAIT_OP,      3 }    // 2: "назад": запуск мотора.
  ,{ moto2Stop,    WAIT_BACK,    0 }    // 3: Пустое действие, едем назад.
};

// *********** начальные установки: **************** //
void setup()
{
  pinModeOut(pinLed);                   // == pinLed == 13!!! Контрольный светодиод тоже на вывод
  pinModeOut(moto1f);
  pinModeOut(moto1b);
  pinModeOut(moto1s);
  pinModeOut(moto2f);
  pinModeOut(moto2b);
  pinModeOut(moto2s);

  tsc_init(&blink13, tblBlink13, 0);    // добавляем КА "Blink" и задаем его начальное состояние
  tsc_init(&moto1,   tblMoto1,   0);    // добавляем КА "Servo" и задаем его начальное состояние
  tsc_init(&moto2,   tblMoto2,   0);    // добавляем КА "Servo" и задаем его начальное состояние
}

// *********** повторяем это: ************************//
void loop()
{
  int i=0;
  
  for(i=0; i<10; i++){
    tsc_step( &blink13 );                 // запускаем КА Blink13 на 1 шаг
    tsc_step( &moto1);                    // запускаем КА Servo на 1 шаг
    tsc_step( &moto2);                    // запускаем КА Servo на 1 шаг
  }
}