/**
 * "Серводвигатель" версия 3: работа через специальные макросы для PWM.
 * размер компилированного скетча = 1022байт. SRAM=4байта
 *
 * Аппаратное, плавное управление углом поворота (ШИМ - широтно-импульсная модуляция, PWM).
 * Используем макросы, прямой работы с регистрами таймеров. Задействованы все каналы 16-и битных
 * таймеров для проверки работоспособности:
 * Timer1 -- pin12(T1outB), pin11(T1outA),
 * Timer3 -- pin5(T3outA), pin2(T3outB), pin3(T3outC)
 * Timer4 -- pin6(T4outA), pin7(t4outB), pin8(T4outC)
 * Timer5 -- pin46(T5outA), pin45(T5outB), pin55(T5outC)
 * 
 * Поведение всех каналов идентично:
 * При включении серводвигатель устанавливается в среднее положение на 2 секунды, после чего
 * перемещается в положение 0 и пошагово поворачивается до положения 180 градусов. Отсюда, пошагово
 * движется обратно к положению 0 градусов.
 *
 * Примечание:
 * Положения и шаг поворота задаются в "тиках" таймера, управляющего требуемой PWM-ножкой.
 *
 * Если нужно поворачивать в угловых единицах (градусах), то используйте функцию map() из
 * стандартной библиотеки. (Не подключается в этом режиме).
 *
 * Для работы можно использовать любую ножку PWM управления от 16-и битных таймеров.
 *
 * В примере показана одновременная установка всех PWM-ножек таймера для подключения
 * серводвигателей.
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

#define _ARHAT_    1
#include "arhat.h"

#define deg0            150     // положение 0 градусов для моей сервы SG-90
#define deg180          600     // положение 180 градусов для неё же.
#define degStep          12     // смещать будем по столько за 1 шаг. (примерно 4.5грд.) у меня менее 6 тиков серва практически не поворачивается...

void blink13(uint8_t wait)      // моргалка встроенным светодиодов для диагностики "код - работает"
{
  digitalWrite(pinLed, HIGH);
  delay(wait);
  digitalWrite(pinLed, LOW);
  delay(wait);
}

//
// Установка таймеров и каналов через макросы режима.
//
void setup() {
  // Установка режима "servo" для таймеров и его канала A в режим "servo":
  pwmSetServo(11);              // timer1 channel A
  pwmSetServo(5);               // timer3 channel A
  pwmSetServo(6);               // timer4 channel A
  pwmSetServo(46);              // timer5 channel A
  
  // Включаем остальные каналы таймеров дополнением (или!) через регистр управления:
  timerControl(1,A) |= pwmPinMode(12, PWM_NORMAL);
  timerControl(3,A) |= pwmPinMode(2, PWM_NORMAL);
  timerControl(3,A) |= pwmPinMode(3, PWM_NORMAL);
  timerControl(4,A) |= pwmPinMode(7, PWM_NORMAL);
  timerControl(4,A) |= pwmPinMode(8, PWM_NORMAL);
  timerControl(5,A) |= pwmPinMode(44, PWM_NORMAL);
  timerControl(5,A) |= pwmPinMode(45, PWM_NORMAL);

  // == pinLed == 13!!! Контрольный светодиод "на выход"
  pinModeOut(pinLed);

  // Устанавливаем ножки всех доступных каналов PWM как выход.
  pinModeOut(pin2);
  pinModeOut(pin3);
  pinModeOut(pin5);
  pinModeOut(pin6);
  pinModeOut(pin7);
  pinModeOut(pin8);
  pinModeOut(pin11);
  pinModeOut(pin12);
  pinModeOut(pin44);
  pinModeOut(pin45);
  pinModeOut(pin46);

  // ставим каждый канал в среднее положение:
  int middle = (deg180-deg0)/2+deg0;
  pwmWrite(2, middle);
  pwmWrite(3, middle);
  pwmWrite(5, middle);
  pwmWrite(6, middle);
  pwmWrite(7, middle);
  pwmWrite(8, middle);
  pwmWrite(11, middle);
  pwmWrite(12, middle);
  pwmWrite(44, middle);
  pwmWrite(45, middle);
  pwmWrite(46, middle);
  
  // моргаем светодиодом для контроля и ждем:
  blink13(150);
  delay(1700);
}

void loop() {
  uint16_t    i;
  
  for( i=deg0; i<=deg180; i+=degStep )    // крутим все сервы одновременно от 0 градусов до 180 с шагом.
  {
    pwmWrite(2, i);
    pwmWrite(3, i);
    pwmWrite(5, i);
    pwmWrite(6, i);
    pwmWrite(7, i);
    pwmWrite(8, i);
    pwmWrite(11, i);
    pwmWrite(12, i);
    pwmWrite(44, i);
    pwmWrite(45, i);
    pwmWrite(46, i);

      blink13(150);                       // ждем пока доедет, заодно моргаем моргалкой
  }
  
  for( i=deg180; i>=deg0; i-=degStep )    // а теперь обратно от 180градусов до 0.
  {
    pwmWrite(2, i);
    pwmWrite(3, i);
    pwmWrite(5, i);
    pwmWrite(6, i);
    pwmWrite(7, i);
    pwmWrite(8, i);
    pwmWrite(11, i);
    pwmWrite(12, i);
    pwmWrite(44, i);
    pwmWrite(45, i);
    pwmWrite(46, i);

      blink13(150);                       // ждем пока доедет, заодно моргаем моргалкой
  }
}
 
 
