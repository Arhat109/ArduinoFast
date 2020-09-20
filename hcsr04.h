/**
 * Пример библиотечного конечного автомата для ультразвукового датчика расстояний HCSR04
 *
 * Для использования надо определить одну из констант MAX_PULSES{0,1,2} -- сколько всего подключено устройств
 * и к каким прерываниям PCINT0..2, и, только затем, определить пины Ардуино, к которым подключен датчик
 * И после этого добавить в скетч #include "hcsr04.h", который создаст методы конечного автомата
 * с названиями дополненными номером пина, например: startTrig1() -- запуск начала измерения расстояния.
 * Если датчиков несколько, то можно вставлять файл последовательно несколько раз, переопределяя используемые пины
 * , например:
 *
 * #define PCINT        0       // этот датчик обслуживается этим уровнем прерываний
 * #define MAX_PULSES0  1       // и всего будет занято 1 нога прерываний уровня 0
 * #define trigPin     14       // trig первого датчика подключено к этой ноге Ардуино Мега2560
 * #define echoPin     10       // echo первого датчика подключено к PCINT0, сигнал 4 (pwm10)
 * #include "hcsr04.h"
 *
 * #define PCINT        2       // а теперь разворачиваем код для обработки на PCINT2
 * #define MAX_PULSES2  2       // тут у нас 2 прерывания в обработке
 * #define trigPin     15       // trig второго датчика подключен сюда
 * #define echoPin     63       // echo второго датчика подключен сюда, к PCINT2, сигнал 1 (Analog9)
 * #include "hcsr04.h"
 *
 * В результате, появятся функции:
 * extern "C" {
 *   void     startTrig14(void) -- запуск сигнала начала измерения и включение ожидания длительности импульса по прерыванию
 *   void     startTrig15(void) -- она же для второго датчика
 *
 * Pulses     pulses0[MAX_PULSES0] -- и структура данных КА для вычисления длительностей в мксек и отработки таймаутов измерений.
 * Pulses     pulses2[MAX_PULSES2] -- .. согласно количеству подключенных уровней и используемых ног у них.
 * }
 * Далее в скетче можно руками распределить номера структур в массивах на соотв. им датчики функцией pcint{0..2}_init();
 *
 * ПРИМЕЧАНИЕ: Если пины датчика НЕ определены или не определено MAX_PULSES{0..2} до #include "hcsr04.h", то будет ошибка компиляции:
 * *** ERROR! {MAX_PULSES,trigPin,echoPin} is not defined ***
 *
 * @examples TSC_Pulsein.ino
 */

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(trigPin)
#  error *** ERROR! trigPin is not defined before include hcsr04.h ***
#elif !defined(echoPin)
#  error *** ERROR! echoPin is not defined before include hcsr04.h ***
#endif

#include "pcint.h"

#define _START_TRIG(p)  startTrig##p (void *_tsc)
#define START_TRIG(p)  _START_TRIG(p)

#define HCSR04_START           4        // номер статуса КА для запуска замеров (вручную)
#define HCSR04_MAX_DISTANCE 5000        // предельно измеряемое расстояние.

// реализация функции вкоючается только один раз!
#ifndef GET_DISTANCE
#  define GET_DISTANCE 1
/**
 * Вычисляет расстояние по замеру длительности в миллиметрах!
 */
uint16_t getDistance( volatile Pulse *ptr)
{
  if(ptr->state != PULSE_OK) return 0;

  return (uint16_t)((((uint32_t)ptr->res) * 343UL) >> 11);
}
#endif

/**
 * определяет startTrig..()
 *
 * Запуск начала замера для узв. датчика HCSR04
 * Прием и замер длительности сигнала echo на одном из (PCINT2) [62..69] силами КА "Pulse"
 * Пока для HC-SR04: макс. дальность = 5м или 29800мксек. = 29
 * пауза на прием около 4мксек = 0,335 * 4 = 1,34мм
 */
void START_TRIG(trigPin)
{
  pinOutLow(trigPin);                           // ногу trigPin в 0,
  delayMicro8(11);                              // inline! ждем 2мксек: 2/0.1875 = 10.67
  pinOutHigh(trigPin);                          // подаем импульс длительностью 10мксек
  delayMicro8(53);                              // inline! остаток задержки в 10мксек: 10/0.1875 = 53.33
  pinOutLow(trigPin);                           // выключаем trigPin

// ~4мксек настраиваем прерывания и таймаут.
#if defined(PCINT) && PCINT==0
  pcint0_start( pcint0_init(PULSE_ID, echoPin, PULSE_BUSY, pcint_micros, 35) );
#elif defined(PCINT) && PCINT==1
  pcint1_start( pcint1_init(PULSE_ID, echoPin, PULSE_BUSY, pcint_micros, 35) );
#elif defined(PCINT) && PCINT==2
  pcint2_start( pcint2_init(PULSE_ID, echoPin, PULSE_BUSY, pcint_micros, 35) );
#endif
}

#ifdef __cplusplus
}
#endif