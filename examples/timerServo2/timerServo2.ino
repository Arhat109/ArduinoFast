/**
 * "Серводвигатель" версия 2: напрямую через таймеры с макросами упрощающими работу с битовыми масками.
 * размер компилированного скетча = 958байт. SRAM=4байта
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
  // прямая установка режима "servo" для таймеров и всех его каналов в режим "servo":
  // !!! У таймера 1 нормально доступны только 2 канала! Канал С тут занят под светодиод!
  // светодиод и канал таймера совмещены в Ардуино - АППАРАТНО!
  timerSetServo(1, pwmPinMode(11, PWM_NORMAL)|pwmPinMode(12,PWM_NORMAL));
  timerSetServo(3, pwmPinMode(2, PWM_NORMAL)|pwmPinMode(3,PWM_NORMAL)|pwmPinMode(5,PWM_NORMAL));
  timerSetServo(4, pwmPinMode(6, PWM_NORMAL)|pwmPinMode(7,PWM_NORMAL)|pwmPinMode(8,PWM_NORMAL));
  timerSetServo(5, pwmPinMode(44, PWM_NORMAL)|pwmPinMode(45,PWM_NORMAL)|pwmPinMode(46,PWM_NORMAL));

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
  timerCompare(1, A) = middle;
  timerCompare(1, B) = middle;
  timerCompare(3, A) = middle;
  timerCompare(3, B) = middle;
  timerCompare(3, C) = middle;
  timerCompare(4, A) = middle;
  timerCompare(4, B) = middle;
  timerCompare(4, C) = middle;
  timerCompare(5, A) = middle;
  timerCompare(5, B) = middle;
  timerCompare(5, C) = middle;
  
  // моргаем светодиодом для контроля и ждем:
  blink13(150);
  delay(1700);
}

void loop() {
  uint16_t    i;
  
  for( i=deg0; i<=deg180; i+=degStep )    // крутим все сервы одновременно от 0 градусов до 180 с шагом.
  {
      timerCompare(1, A) = i;
      timerCompare(1, B) = i;
      timerCompare(3, A) = i;
      timerCompare(3, B) = i;
      timerCompare(3, C) = i;
      timerCompare(4, A) = i;
      timerCompare(4, B) = i;
      timerCompare(4, C) = i;
      timerCompare(5, A) = i;
      timerCompare(5, B) = i;
      timerCompare(5, C) = i;

      blink13(150);                       // ждем пока доедет, заодно моргаем моргалкой
  }
  
  for( i=deg180; i>=deg0; i-=degStep )    // а теперь обратно от 180градусов до 0.
  {
      timerCompare(1, A) = i;
      timerCompare(1, B) = i;
      timerCompare(3, A) = i;
      timerCompare(3, B) = i;
      timerCompare(3, C) = i;
      timerCompare(4, A) = i;
      timerCompare(4, B) = i;
      timerCompare(4, C) = i;
      timerCompare(5, A) = i;
      timerCompare(5, B) = i;
      timerCompare(5, C) = i;

      blink13(150);                       // ждем пока доедет, заодно моргаем моргалкой
  }
}
 
