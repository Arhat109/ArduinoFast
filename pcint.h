/**
 * Определения и реализация с применением конечных автоматов для измерения длительностей сигналов и/или подсчета импульсов
 * по фронту/спаду на пинах прерывания PCINT 0..2.
 *
 * Подключаются, только если до вызова #include "pcint.h" определено количество пинов прерывания: MAX_PULSES
 * и определен используемый уровень прерываний 0,1,2 - реализация TEMPLATE на С, иначе в скетчи будут вставляться
 * процедуры обработки прерываний - принудительно.
 *
 * Доступные прерывания в Ардуино Мега 2560:
 * PC_INT0[0..7] отключает SPI:SS(53),SPI:SCK(52),SPI:MOSI(51),SPI:MISO(50),pwm10(T2outA),pwm11(T1outA),pwm12(T1outB),
 *                         (pwm13 - нельзя использовать! Только на выход!)
 * PC_INT1[8..10] отключает USART0:RX(0), USART3:RX(15), USART3:TX(14) -- не реализовано для Мега2560 из-за разных регистров данных
 * PC_INT2[16..23] (Analog8..Analog15)
 * .. остальные ножки прерываний контроллера ATmega2560 в Ардуино - отсутствуют.
 *
 * Реализован "интерфейс" из ООП: методы обработки прерываний могут разрабатываться и расширяться без
 * существенных изменений кода. Есть 2 метода:
 *   pcint_micros()  -- измеряет длительность импульса или до таймаута
 *   pcint_encoder() -- подсчитывает прерывания по фронту/спаду/оба до таймаута или до запрета извне
 *
 * @example Примеры подключения:
 * 1. Подключение 1 узв. датчика для замеров расстояний (длительности импульса) на прерывание PCINT2:
 * #define PCINT       2
 * #define MAX_PULSES2 1
 * include "pcint.h"
 *
 * 2. Подключение 4 энкодеров для подсчета импульсов на прерывание PCINT0:
 * #define PCINT       0
 * #define MAX_PULSES0 4
 * #include "pcint.h"
 *
 * 3. Одновременное использование прерываний в скетче уровня 0 (8шт) и 1(2шт) (подключаем дважды! и имеем 2 обработчика в скетче):
 * #define PCINT       0
 * #define MAX_PULSES0 8
 * #include "pcint.h"
 *
 * #define PCINT       1
 * #define MAX_PULSES1 2
 * #include "pcint.h"
 *
 * Примечания:
 * 1. Номер уровня прерывания PCINT - только константа #define! изменяет результирующий код обработчиков и функций
 * 2. Уровень прерываний 1 для Ардуино Мега 2560 - не реализован: их всего 3 из 8 и они из разных регистров.
 * 3. Файл tsc.h подключается автоматически
 * 4. При подключении файла #include "hcsr04.h" этот файл подключается автоматически, но все предопределения должны
 *    выполняться также в скетче ПЕРЕД включением.
 *
 * @author Arhat109-20151125. arhat109@mail.ru
 * @license:
 *   1. This is a free software for any using and distributing without any warranties.
 *   2. You should keep author tag with any changes. May be with adding.
 *   Это свободное ПО для любого использования без каких-либо гарантий и претензий.
 *   Требуется сохранять тег @author при любых изменениях. Можете дописать свой.
 *
 * This is free software, not any pay. But you may donate some money to phone +7-951-388-2793
 * Бесплатно. Но автор принимает пожертвования на тел. +7-951-388-2793.
 *
 */
#if defined(PCINT) && ( (PCINT==0 && !defined(PCINT_0))||(PCINT==1 && !defined(PCINT_1))||(PCINT==2 && !defined(PCINT_2)) )

#if PCINT==0

#if !defined(MAX_PULSES0)
#error "*** pcint.h::ERROR! not defined how much pins will be used for pcint level 0"
#endif
#define PCINT_0 1

#elif PCINT==1

#if !defined(MAX_PULSES1)
#error "*** pcint.h::ERROR! not defined how much pins will be used for pcint level 1"
#endif
#define PCINT_1 1

#elif PCINT==2

#if !defined(MAX_PULSES2)
#error "*** pcint.h::ERROR! not defined how much pins will be used for pcint level 2"
#endif
#define PCINT_2 1

#endif

#include "tsc.h"                        // требуется для обработки таймаутов

#if PCINT==0

uint8_t          pcint0old = 0;         // состояние пинов прерываний "предыдущее"
uint8_t          pcint0numbers[8];      // текущие номера КА из pulses[], измеряющие на пинах 62..69 = 8шт!
Pulse            pulses0[MAX_PULSES0];  // данные КА измерения длительностей и таймаутов

uint8_t  pcint0_init(uint8_t pulseID, uint8_t pin, uint8_t state, PcintMethod method, TSC_Time timeout);
void     pcint0_start(uint8_t intNumber);
TSC_Time pulseIn0(uint8_t pulseId, void (*action)(void));

#elif PCINT==1

uint8_t          pcint1old = 0;         // состояние пинов прерываний "предыдущее"
uint8_t          pcint1numbers[8];      // текущие номера КА из pulses[], измеряющие на пинах 62..69 = 8шт!
Pulse            pulses1[MAX_PULSES1];  // данные КА измерения длительностей и таймаутов

uint8_t  pcint1_init(uint8_t pulseID, uint8_t pin, uint8_t state, PcintMethod method, TSC_Time timeout);
void     pcint1_start(uint8_t intNumber);
TSC_Time pulseIn1(uint8_t pulseId, void (*action)(void));

#elif PCINT==2

uint8_t          pcint2old = 0;         // состояние пинов прерываний "предыдущее"
uint8_t          pcint2numbers[8];      // текущие номера КА из pulses[], измеряющие на пинах 62..69 = 8шт!
Pulse            pulses2[MAX_PULSES2];  // данные КА измерения длительностей и таймаутов

uint8_t  pcint2_init(uint8_t pulseID, uint8_t pin, uint8_t state, PcintMethod method, TSC_Time timeout);
void     pcint2_start(uint8_t intNumber);
TSC_Time pulseIn2(uint8_t pulseId, void (*action)(void));

#endif // PCINT

// template генерация названий функций для текущего уровня прерываний PCINT:
#define __pcint_init(p)         uint8_t pcint##p##_init ( \
  uint8_t pulseID, uint8_t pin, uint8_t state,            \
  PcintMethod method, TSC_Time timeout                    \
)
#define _pcint_init(p)          __pcint_init(p)

#define __pcint_start(p)        void pcint##p##_start (uint8_t intNumber)
#define _pcint_start(pcint)     __pcint_start(pcint)

#define __pulsein(p)            TSC_Time pulseIn##p (uint8_t pulseId, void (*action)(void))
#define _pulsein(p)             __pulsein(p)

/**
 * Замена типовой pulseIn(). В отличии от типовой - замеряет длительность сигнала по прерыванию.
 * Структура pulsesX[p] должна быть настроена на обработку ЗАРАНЕЕ.
 * Позволяет исполнять функцию без параметров, пока идет замер.
 *
 * template: TSC_Time pulseIn{0,1,2}(uint8_t pulseId, void (*action)(void))
 * calls:
 *   pulseIn0(pulseId, callback);       // for PCINT0 level
 *   pulseIn1(pulseId, callback);
 *   pulseIn2(pulseId, callback);
 */
_pulsein(PCINT)
{
#if PCINT==0
    pcint0_start(pulses0[pulseId].pin & 0x3f);
#elif PCINT==1
    pcint1_start(pulses1[pulseId].pin & 0x3f);
#elif PCINT==2
    pcint2_start(pulses2[pulseId].pin & 0x3f);
#endif
    while(
           (PCINT_pulses(PCINT)[pulseId].state == PULSE_BUSY)
        || (PCINT_pulses(PCINT)[pulseId].state == PULSE_SECOND)
        || !(tsc_getTime() - PCINT_pulses(PCINT)[pulseId].ctrl.started_at > PCINT_pulses(PCINT)[pulseId].ctrl.timeout)
    ){
        action();
    }
    return (PCINT_pulses(PCINT)[pulseId].state == PULSE_OK? PCINT_pulses(PCINT)[pulseId].res : 0);
}

/**
 * Настройка структуры замера на работу что и как измерять динамически. До вызова pcintX_start()!
 * Предпочтительнее статическая настройка в setup():
 *
 * @example для PCINT2, номер в структурах замера 1:
 * pulses2[1] = {{0, 28, pcint_timeout}, 0, pcint_micros, PULSE_BUSY, Analog8};
 * , что означает, данные КА:
 * {"0 мсек - начни сразу как сможешь", ждать <28*1024мксек, функция_таймаута}, res=0, "замер длительности", "занят", "на 8 аналоговом входе"
 *
 * @return uint8_t pcint_number -- номер вектора прерываний в уровне [0..7]
 *
 * template: uint8_t pcint{0|1|2}_init(
 *     uint8_t pulseID, uint8_t pin, uint8_t state,
 *     PcintMethod method, TSC_Time timeout
 * )
 * calls:
 *   pcint0_init(pulseID, pin, state, method, timeout);
 *   pcint1_init(pulseID, pin, state, method, timeout);
 *   pcint2_init(pulseID, pin, state, method, timeout);
 */
_pcint_init(PCINT)
{
  uint8_t intNumber = PCINT_pin2number(PCINT, pin);              // макрос от уровня PCINT! ищем номер прерывания по общему номеру пина

  PCINT_numbers(PCINT)[intNumber] = pulseID;                     // сохраняем номер активной структуры
  PCINT_pulses(PCINT)[pulseID].state = state;                    // закрываем доступ "идет замер"
  PCINT_pulses(PCINT)[pulseID].pin = (PCINT<<6) | intNumber;     // пригодится для записи ошибки по таймауту
  PCINT_pulses(PCINT)[pulseID].method = method;                  // метод обработки - подсчет длительности импульса
  tsc_simple( &(PCINT_pulses(PCINT)[pulseID].ctrl), pcint_timeout, timeout);    // включаем таймаут для этого замера

  return intNumber;
}

/**
 * Запуск измерения длительности сигнала на ножке через прерывания PCINT2
 *
 * @param uint8_t  intNumber -- номер запускаемого прерывания этого уровня 0..7
 *
 * template: void pcint{0|1|2}_start(uint8_t intNumber)
 * calls:
 *   pcint0_start( intNumber );
 *   pcint1_start( intNumber );
 *   pcint2_start( intNumber );
 * or call:
 *   pcintX_start( pcintX_init(...));
 *
 * К моменту вызова структура замеров должна быть настроена на конкретную работу
 * @see pcintX_init();
 */
_pcint_start(PCINT)
{
  uint8_t       mask;

  mask = (1<<intNumber);                                         // получаем маску для битовых операций {0}1{0}

  PCINT_DDR(PCINT)  |= mask;                                     // ?надо Pullup? нога "на выход" {0}1{0}
  PCINT_PORT(PCINT) |= mask;                                     // ?надо Pullup? сброс ножки прерывания в 1 ("echo")
  mask = ~mask;                                                  // инвертируем маску для битовых операций {1}0{1}
  PCINT_old(PCINT) &= mask;                                      // бит в "было раньше" = 0
  PCINT_DDR(PCINT) &= mask;                                      // нога "на вход"

  PCINT_MSK(PCINT) |= ~mask;                                     // и только теперь разрешаем прерывание с этой ноги
  PCICR  |= (1<<PCINT);                                          // и разрешаем вектор PCINT0..2
}

/**
 * Обработчик прерывания для прерываний PCINT0..2
 *
 * При срабатывании - ищет сработавшие ножки и для каждой из них вызывает
 * свой метод замера, передавая ему предыдущее состояние пина.
 *
 * ISR( PCINT2_vect ) после подстановок формирует это:
 *
 * void __vector_ 11(void) __attribute__ ((signal, used, externally_visible));
 * void __vector_ 11(void)
 *
 * Время исполнения около 15+(15*N+8*M), где N-сработало ног, M-просмотрено бит (N+M<8!)
 * Оптимизация: шустрые ноги - размещать в начало уровня!
 */
ISR( PCINT_NAME(PCINT) )
{
  uint8_t       reg  = PCINT_PIN(PCINT);                        // Первым делом читаем ноги регистра К (Analog8..15)
  uint8_t       temp = PCINT_old(PCINT);                        // и предыдущее их состояние
  uint8_t     * ptrNumbers = PCINT_numbers(PCINT);

  PCINT_old(PCINT) = reg;                                       // сразу сохраняем новое состояние
  reg = (temp ^ reg) & PCINT_MSK(PCINT);                        // ищем разрешенные И сработавшие ножки (нормально 1шт)
  do{
    if( reg & 0x01 )                                            // Если прерывание от этого бита
    {
      Pulse * ptrPulse = PCINT_pulses(PCINT)+(*ptrNumbers);     // получаем адрес структуры замера
      ptrPulse->method(ptrPulse, temp & 0x01);                  // исполняем собственно обработчик
    }
    ptrNumbers++;                                               // следующий номер прерывания
    reg = reg >> 1;                                             // готовим следующую проверку "кто сработал"
    temp = temp >> 1;                                           // готовим его пред. состояние (raising|failing)
  }while(reg);
}

#endif // PCINT blocking for twice parsing
