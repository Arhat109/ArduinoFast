/**
 * Main header file for small sketchs by Arduino IDE
 * version 1.1 for ATmega2560, Atmega328p CPU
 *
 * Библиотека для уменьшения размеров скетчей и улучшения их работы
 *
 * Подключение библиотеки:
 * 1. ПЕРЕД подключением этой библиотеки можно, но не обязательно указать режим работы в виде определения константы ARHAT_MODE:
 *    Если надо, то это пишется первой строкой скетча:
 *    #define ARHAT_MODE 1 // режим совместимости с Wiring. Все типовые функции работы с пинами будут из него.
 *    #define ARHAT_MODE 2 // режим имитации команд Wiring. Все типовые функции с пинами заменяются макросами отсюда.
 * 2. Команду #include "arhat.h" надо писать второй в скетче.
 * Примечания:
 *  а) Определять ARHAT_MODE - необязательно. Если его нет, по умолчанию будет режим 2
 *  б) В режиме "2" все номера пинов нельзя брать из переменных! Только константные значения. Иначе будет ошибка компиляции скетча.
 *  d) В режиме "2" не определена функция pulseIn()! Вместо неё есть замер длительностей по прерываниям PCINT2 для Mega2560 в tsc.h
 *
 * Примеры подключения:
 * 1. Режим 2 по умолчанию: первая строка скетча:
 * #include "arhat.h"
 *
 * 2. Режим совместимости с Wiring (первые 2 строки скетча):
 * #define ARHAT_MODE 1
 * #include "arhat.h"
 *
 * @author Arhat109-20150604(started). arhat109@mail.ru
 * @license:
 *   1. This is a free software for any using and distributing without any warranties.
 *   2. You should keep author tag with any changes. May be with adding.
 *   Это свободное ПО для любого использования без каких-либо гарантий и претензий.
 *   Требуется сохранять тег @author при любых изменениях. Можете дописать свой.
 *
 * This is free software, not any pay. But you may donate some money to phone +7-951-388-2793
 * Бесплатно. Но автор принимает пожертвования на тел. +7-951-388-2793.
 *
 * Thanks:
 *  More parts was taked from this authors:
 *  Благодарности авторам, работы которых были активно использованы тут:
 *
 * authors Arduino.h, avr/io.h and other distribs files.
 * authors this document: http://www.nongnu.org/avr-libc/user-manual/index.html
 * leshak, gregoryl  -- @see https://bitbucket.org/alxarduino/leshakutils
 * autors Cyberlib.h -- @see http://www.cyber-place.ru/showthread.php?p=3789#post3789
 *
 * Кратко "как пользоваться" смотреть в комментариях к каждому определению тут.
 * v1.0 changes: #define _ARHAT_ 1 is deprecated and not use more.
 * Изменения: макрос _ARHAT_ определять больше не надо. Режим совместимости с Wiring не поддерживается.
 */

#ifndef _ARHAT_H_
#define _ARHAT_H_

// Schema all default includes for this file. Simple search if need
// Схема всех подключаемых хидеров. Для справки, дабы проще искать
#include <avr/pgmspace.h>
/* pgmspace.h  are defining macros for use programm memory for data storage. Autoincluding:
  <inttypes.h> -- constants for print any integer formats
    <stdint.h> -- .. .. redefining standart int types and max int constants
  <stddef.h>   -- standart definitions
  <avr/io.h>   -- io.h auto including:
    <avr/sfr_defs.h>   -- "Special Function Register" _SFR_xxx()
      <inttypes.h>
        <stdint.h>
    <avr/io***.h>      -- special defines for the AVR-processor: ramend, fuse ... etc.
      <avr/io***.h>    -- .. may be additional defines (x[A..L],n[0..7]): DDRxn,DDxn, PORTxn,Pxn, PINx,PINxn, .. see datasheet terms.
    <avr/portpins.h>   -- additional pin primitives: DDn,PORTn,PINn and redefines above.
    <avr/common.h>     -- additional SP,SREG,IND,X,Y,Z,RAMPZ .. etc. defines.
      <avr/sfr_defs.h>
        <inttypes.h>
          <stdint.h>
    <avr/version.h>    -- only version for avr-gcc compiler
    <avr/fuse.h>       -- only typedef for fuse structs
    <avr/lock.h>       -- only lockmem registers and bits
*/
#include <avr/interrupt.h>      // sei(),cli(),ISR() and so on. Including <avr/io.h> too.
#include <avr/eeprom.h>         // read/write eeprom. Including <avr/io.h>, <avr/stddefs.h>, <avr/sdtint.h>
#include <avr/wdt.h>            // watchdog functions

// ============= main defines constants for Arduino ============ //
// Основные константы для упрощения работы, совместимости скетчей и просто "на память"
#define SET_MASK_0              (uint8_t)1
#define SET_MASK_1              (uint8_t)2
#define SET_MASK_2              (uint8_t)4
#define SET_MASK_3              (uint8_t)8
#define SET_MASK_4              (uint8_t)16
#define SET_MASK_5              (uint8_t)32
#define SET_MASK_6              (uint8_t)64
#define SET_MASK_7              (uint8_t)128

#define CLR_MASK_0              (uint8_t)254
#define CLR_MASK_1              (uint8_t)253
#define CLR_MASK_2              (uint8_t)251
#define CLR_MASK_3              (uint8_t)247
#define CLR_MASK_4              (uint8_t)239
#define CLR_MASK_5              (uint8_t)223
#define CLR_MASK_6              (uint8_t)191
#define CLR_MASK_7              (uint8_t)127

#define B00000001               SET_MASK_0
#define B00000010               SET_MASK_1
#define B00000100               SET_MASK_2
#define B00001000               SET_MASK_3
#define B00010000               SET_MASK_4
#define B00100000               SET_MASK_5
#define B01000000               SET_MASK_6
#define B10000000               SET_MASK_7

#define B11111110               CLR_MASK_0
#define B11111101               CLR_MASK_1
#define B11111011               CLR_MASK_2
#define B11110111               CLR_MASK_3
#define B11101111               CLR_MASK_4
#define B11011111               CLR_MASK_5
#define B10111111               CLR_MASK_6
#define B01111111               CLR_MASK_7

#define HIGH         0x1
#define LOW          0x0

#define INPUT        0x0
#define OUTPUT       0x1
#define INPUT_PULLUP 0x2

#define SERIAL       0x0
#define DISPLAY      0x1

#define LSBFIRST     0
#define MSBFIRST     1

#define PI           3.1415926535897932384626433832795
#define Pi           3.1415926535897932384626433832795
#define pi           3.1415926535897932384626433832795

#define HALF_PI      1.5707963267948966192313216916398
#define TWO_PI       6.283185307179586476925286766559
#define DEG_TO_RAD   0.017453292519943295769236907684886
#define RAD_TO_DEG  57.295779513082320876798154814105
#define EULER        2.718281828459045235360287471352

// sound speed as 33500 sm./sec., 2-way: microsecs. to santimeters!
// пересчет звука в расстояние: можно делить, а можно умножить и поделить сдвигом
#define SND_DIV_SM   59.701492537       // t divide to this to sm
#define SND_MUL_MM   343                // (t*343)>>11! (/2048) from microseconds to mm!

#define NOP __asm__ __volatile__ ("nop\n\t")
#define nop __asm__ __volatile__ ("nop\n\t")
#define Nop __asm__ __volatile__ ("nop\n\t")

#define CharToDec(c)            ((c)-48)
#define DecToChar(d)            ((d)+48)

// ============= specific definitions for smaller code ============= //
// below you can add file description for your board too.            //
// This section must be above private and public common pins macros! //
// ================================================================= //

// Mega2560 only. Add other version Arduino before error section
// Описание ножек Мега2560. Добавлять распиновку плат тут "по образцу"
#if defined(__AVR_ATmega2560__) || defined(__AVR_ATmega2561__)
// special macros for each pin Arduino Mega board
#  include "arhat_pins2560.h"
#elif defined(__AVR_ATmega88P__) || defined(__AVR_ATmega88P__) || defined(__AVR_ATmega168P__) || defined(__AVR_ATmega328P__)
// special macros for UNO at Atmega328p and may be some else board at this CPU
#  include "arhat_pins328p.h"
#else
#  error "*** ERROR! Unknown processor type! Add your pins file into arhat.h before use it ***"
#endif

/* ============= private level 2. NOT USE IT in your sketches !!! ============= */
/* ПРИВАТНАЯ СЕКЦИЯ! НЕ ИСПОЛЬЗОВАТЬ ЭТИ МАКРОСЫ В СКЕТЧАХ. Ну или только сознательно */
#define _d_in(p)        (D##p##_In)
#define _d_out(p)       (D##p##_Out)
#define _d_high(p)      (D##p##_High)
#define _d_low(p)       (D##p##_Low)
#define _d_inv(p)       (D##p##_Inv)
#define _d_read(p)      (D##p##_Read)

#define _pin(p)         (pin##p)

#define pinDirReg(p)    (DREG##p)       // get DDRx  direction register macros for pin
#define pinOutReg(p)    (OREG##p)       // get PORTx output register macros for pin
#define pinInReg(p)     (IREG##p)       // get PINx  input register macros for pin
#define pinSetMask(p)   (BSET##p)       // get bit mask to set pin into HIGH
#define pinClearMask(p) (BCLR##p)       // get bit mask to LOW pin

#define _pwmGetTimer(p)         getTimer##p
#define _pwmGetChannel(p)       getTimerChannel##p

#define _timerCount(t)          (TCNT##t)
#define _timerControl(t,r)      (TCCR##t##r)
#define _timerCompare(t,r)      (OCR##t##r)
#define _timerCapture(t)        (ICR##t)
#define _timerIMask(t,v,b)      ((b)? (TIMSK##t |= (TIF_##v)) : (TIMSK##t &= ~(TIF_##v)))
#define _timerIFlag(t,v)        (TIFR##t & (TIF_##v))
#define _ISRtimer(t,v)          (TIMER##t##_##v##_vect)
#define _prescalerMode(pr)      (TCLK_##pr)

#define __pwmMaskMode0(t,c)       (0)
#define __pwmMaskMode1(t,c)       (1<<COM##t##c##0)
#define __pwmMaskMode2(t,c)       (1<<COM##t##c##1)
#define __pwmMaskMode3(t,c)       ((1<<COM##t##c##1)|(1<<COM##t##c##0))

#define _pwmMaskMode0(t,c)        __pwmMaskMode0(t,c)
#define _pwmMaskMode1(t,c)        __pwmMaskMode1(t,c)
#define _pwmMaskMode2(t,c)        __pwmMaskMode2(t,c)
#define _pwmMaskMode3(t,c)        __pwmMaskMode3(t,c)

#define _pwmPinMask(t,c,m)      (_pwmMaskMode##m(t,c))

#define _pwmSet(p)              (setPWM##p)
#define _pwmOff(p)              (offPWM##p)
#define _pwmWrite(p,v)          (outPWM##p(v))

#define _analogPin(p)           (Analog##p)
#define _admuxSrc(s)            (ADC_SRC_##s)

#define _ISRusart(t,v)          (USART##t##_##v##_vect)

// ========================================================================== //
// Public section: macros for use with constants pin numbers only!            //
// ========================================================================== //
// may use with standard macros for registers and bits names from <avr/io.h>  //
// МАКРОСЫ ДЛЯ ИСПОЛЬЗОВАНИЯ -- ТУТ. Публичная секция. Номер пина - константа //

// Classic bit operation from wiring and some other libs
// Классика битовых операций. Дубликаты из разных мест:
#define cbi(sfr, bit)                  (_SFR_BYTE(sfr) &= ~_BV(bit))
#define sbi(sfr, bit)                  (_SFR_BYTE(sfr) |= _BV(bit))
#define bitRead(value, bit)            (((value) >> (bit)) & 0x01)
#define bitSet(value, bit)             ((value) |= (_BV(bit)))
#define bitClear(value, bit)           ((value) &= ~(_BV(bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

// for users cyberlib.h
// Совместимость с Cyberlib.h:
#define D_In(p)         (_d_in(p))
#define D_Out(p)        (_d_out(p))
#define D_High(p)       (_d_high(p))
#define D_Low(p)        (_d_low(p))
#define D_Inv(p)        (_d_inv(p))
#define D_Read(p)       (_d_read(p))

// defaults timer0 timers functions and interrupts such in wiring
// Константы настройки таймера 0 совместимые с wiring: таймер работает по 4мксек.
#ifndef TIME_DEFAULT                    /* all defaults for F_CPU=16Mhz ONLY! */
#  define TIME_DEFAULT             0
#  define TIME_MAX_COUNTER       256    /* max conter+1                                               */
#  define TIME_PRESCALLER         64
#  define TIME_MODE                3    /* WGM10 = 1, WGM00 = 1 fast-PWM mode for timer0              */
#  define TIME_TICK_MCS            4    /* 1 tick by prescaler:[0.25, 0.5, 4, 16, 64] in microseconds */
#  define TIME_SHIFT               2    /* From prescaller: 1=>4, 8=>1, 64=>2, 256=>4, 1024=>6        */
#  define TIME_MCS2MS      1024/1000    /* ==[16,128,1024,4096,16384]/1000 by prescaler               */
#  define TIME_ISR               OVF    /* what interrupt name using for this timer                   */
#endif

/* =========== Pin works. Работа с цифровыми входами и выходами 1 командой ============= */

// setup(): set pin to out. Настройка пина на вывод (и только):
#define pinModeOut(p)   (pinDirReg(p) |= pinSetMask(p))

// setup(): set pin to input. Настройка пина на ввод (и только):
#define pinModeIn(p)    (pinDirReg(p) &= pinClearMask(p))

// loop(): out 1 (HIGH) to pin. Установка на выводе лог.1:
#define pinOutHigh(p)   (pinOutReg(p) |= pinSetMask(p))

// loop(): out 0 (LOW) to pin. Установка на выводе лог.0:
#define pinOutLow(p)    (pinOutReg(p) &= pinClearMask(p))

// loop(): @see digitalWrite(). Для замены (ниже) этой функции на 1 команду:
#define pinOut(p,v)     ((v)? pinOutHigh(p) : pinOutLow(p))

// loop(): @see digitalRead(). Для замены (ниже) этой функции на 1 команду:
#define pinRead(p)      (D_Read(p))

// Setup(): Set pin to input with pullup resistor. Пин на ввод с подтяжкой к +5В:
#define pinModePullIn(p) (pinModeOut(p), pinOutHigh(p), pinModeIn(p))

/* =========== Timer and PWM works. Работа с таймерами и ШИМ 1 командой ============= */

// This and further: T1C is special name for 13 pin when you want it use as Timer1 channel C!
// Тут и далее: T1C - "спецномер" (не макрос!) пина для использования канала С таймера 1 на 13 ноге платы!
// @see arhat_pins2560.h
// Impotant: Not replace macros in it orders! Не переставлять определения макросов, их порядок - важен!

// get timer number by PWM pin. Номер пина(p) - в номер таймера(t). Пин p:[2..13,44,45,46, T1C]
#define pwmGetTimer(p)          _pwmGetTimer(p)

// get timer channel letter by PWM pin. Получить букву канала таймера по его номеру. Пин p:[2..13,44,45,46, T1C]
#define pwmGetChannel(p)        _pwmGetChannel(p)

// get/set TCNT register 8/16bit t:[0,2,[1,3,4,5]]. Работа с регистром текущего счета: [8[16]] битовые
#define timerCount(t)           _timerCount(t)

// get/set control registers:    p:[0,2,[1,3,4,5]], r:[A,B[,C]]. Чтение/Установка регистра ШИМ таймера и канала соответсвенно:
#define timerControl(t,r)       _timerControl(t,r)

// get/set compare registers:    p:[0,2,[1,3,4,5]], r:[A,B[,C]]. Регистр сравнения счетчика:
#define timerCompare(t,r)       _timerCompare(t,r)

// get/set capture registers:    p:[1,3,4,5]. Регистр захвата. Присутствует только у 16-и разрядных счетчиков!
#define timerCapture(t)         _timerCapture(t)

// timer mask register for interrupt t:[0,2[,1,3,4,5]] v:[OVF,COMPA,COMPB[,COMPC,CAPT]], b:[0,1] -- clear/set
// Работа с разрешением прерывания счетчика: таймер, имя_прерывания и запретить/разрешить.
#define timerIMask(t,v,b)       _timerIMask(t,v,b)

// get interrupt flag t:[0,2[,1,3,4,5]] v:[OVF,COMPA,COMPB[,COMPC,CAPT]]. Читать флаг состояния прерывания таймера:
#define timerIFlag(t,v)         _timerIFlag(t,v)

// make interrupt vector name t:[0,2[,1,3,4,5]] v:[OVF,COMPA,COMPB[,COMPC,CAPT]].
// Это если забылось как оно пишется в interrupt.h
#define ISRtimer(t,v)           _ISRtimer(t,v)

// return mode for prescaler by devider 64 --> 3. Удобства для. Перевод коэффициента делителя в код режима прескалера:
#define prescalerMode(pr)       _prescalerMode(pr)

// get mask PWM mode only to pin p:[2..13,44,45,46,T1C], m[PWM_DISABLE,PWM_TOGGLE,PWM_NORMAL,PWM_INVERSE]
// получить выражение для режима ШИМ заданной ноги для дальнейшего использования где-либо (вспомогательный макрос)
#define pwmPinMode(p,m)         _pwmPinMask(pwmGetTimer(p), pwmGetChannel(p),m)

// to setup() set pin to PWM mode: 8bit timer - fastPWM, 16bit timer - mode-8bit and prescaler 1/64
// @param p:[2..13,44,45,46,T1C]
// Настроить ногу и её таймер на типовой ШИМ: делитель 1/64 (такт=4мксек), режим "8-битного fastPWM" для 8/16 таймеров.
#define pwmSet(p)               { pinModeOut(p); _pwmSet(p); }

// stop pin to PWM mode p:[2..13,44,45,46,T1C].
// Выключить ногу из ШИМ. Нога остается "на вывод". Весь таймер - не отключаем:
#define pwmOff(p)               _pwmOff(p)

// analogWrite(): out PWM p:[2..13,44,45,46,T1C], v:[0..255] with 250kHz. Аналог этой функции 1-й командой.
#define pwmWrite(p,v)           _pwmWrite(p,v)

// v.1 set 16bit timer (only t:[1,3,4,5]) to PWM special for servo motors:
//     1/64 FAST-pwm mode with ICP, 50hz (20msec) and set to pwmOut PWM pin,
// Установка 16битного таймера и его каналов в типовой ШИМ для серво моторов. Ноги на вывод устанавливать отдельно!
//
// @example: set timer5 to pwmServo and use 2 servo at pins 44,46:
//   timerSetServo(5, pwmPinMode(44, PWM_NORMAL)|pwmPinMode(46, PWM_NORMAL))
//   ** set pins 44,46 to OUTPUT manually!
#define timerSetServo(t,pwmPinMask)                               \
{                                                                 \
  timerControl(t, A) = (1<<WGM11)|(pwmPinMask);                   \
  timerControl(t, B) = (1<<WGM13)|(1<<WGM12)|(1<<CS11)|(1<<CS10); \
  timerCapture(t) = 4999;                                         \
}

// v.2: set to servoMode too for one servo drive by PWM pin number p:[2,3,5,6,7,8,11,12,44,45,46,T1C]
//      Установка одной ноги на ШИМ и её таймера в типовой режим сервоШИМа: 50Гц.
// Для последующего канала этого же таймера достаточно вызвать pwmSet(p).
//
// example set 45 pin to use servo (only one for timer!): pwmSetServo(45);
//     set pin to OUTPUT manually! Ногу на вывод - самостоятельно!
#define pwmSetServo(p1)                                                         \
{                                                                               \
  timerControl(pwmGetTimer(p1), A) = (1<<WGM11)|(pwmPinMode(p1, PWM_NORMAL));   \
  timerControl(pwmGetTimer(p1), B) = (1<<WGM13)|(1<<WGM12)|(1<<CS11)|(1<<CS10); \
  timerCapture(pwmGetTimer(p1)) = 4999;                                         \
}

// ============ ADC macros ============ //

// select base voltage example s:[AREF,AVCC,110,256]. Получить маску опорного напряжения (надо далее):
#define admuxSrc(s)     _admuxSrc(s)

// enable ADC to work and set 16Mhz/128 adc clk (125kHz). Включение АЦП отдельной командой:
#define adcOn()         ADCSRA |= (128|7)

// disable work ADC. Выключение АЦП. Нормально - выключен, ибо "жрет" - много:
#define adcOff()        { ADCSRA &= ~ADEN; }

/*
 * Moved into arhat_pinsXXX.h!
 *
// input pin for: "GND-pin" analog read
// p:[0..15]
admux1Channel(src,pin,adlar)
// input for differential "neg-poz" pin read
// neg:[1,2|9,10], poz:[0..7|8..15]
admux2Channel(src,neg,poz,adlar)                 \
// differential and gain "neg-poz" read
// neg:[0,2|8,10], poz:[0..3|8..11], g:[GAIN_10,GAIN_200], adlar:[ADC_LEFT|ADC_RIGHT]
admux2Gain(src,neg,poz,g,adlar)                              \
*/

//
// examples for set ADC registers:
// ===============================
// admux1Channel(admuxSrc(110), analog5, ADC_RIGHT);                 -- поставить АЦП в режим сравнения с опорным в 1.1в, читать 5 вход, значения 0..1023
// admux2Channel(admuxSrc(AREF),analog10, analog11, ADC_LEFT);       -- сравнивать с AREF, дифференциальный режим 10,11, значения домножать на 64.
// admux2Gain(admuxSrc(AVCC), analog0, analog1, GAIN_200, ADC_LEFT); -- сравнивать с Vсс, предусилитель 200х, дифф. режим 0,1; домножать на 64.
//

// ============= wait without delay ============ //
// Простейший конечный автомат сначала исполняющий действие command и
// затем ожидающий его повторения через interval тиков таймера по 1 миллисекунде.
// В качестве команды может быть последовательность команд через ; или прямой вызов функции!
// интервалы можно задавать константно и переменными (выражениями).
// Например (исполнение через 1 сек):
//
// everyMillis(1000,
// {
//   pinOut(pinLed, 1-digitalRead(pinLed));
//   analogWrite(pwm12, analogRead(pin54)>>4);
// });
//
// или так: everyMillis(1000, blink() );
//
// @param void (*)(void) action;
// @param uint32_t       interval; [milliseconds]
//
#define everyMillis(interval, action) \
{                                     \
  static unsigned long t = 0UL;       \
  if( millis() - t > (interval) )     \
  {                                   \
    { action; }                       \
    t = millis();                     \
  }                                   \
}

// Его аналог. Дешевле и шустрее, но "тики" по 1024мксек!
// интервалы желательно пересчитывать в тики вручную на калькуляторе, округлять и подставлять куда надо
#define everyOVF(interval, action)     \
{                                      \
  static unsigned long t = 0UL;        \
  if( getOvfCount() - t > (interval) ) \
  {                                    \
    { action; }                        \
    t = getOvfCount();                 \
  }                                    \
}

// ============= Макросы для микросекундных задержек  ============== //
// Взято из .../avr/include/utils -- микросекундные задержки циклами //
// ================================================================= //
/**
 * INLINE: 8-bit counter (up to 256*3 F_CPU) 16Mhz:[0.1875 .. 48] mcsec.
 * Короткие задержки по 3 цикла ЦПУ (кратно 187.5 нсек)
 */
#define delayMicro8(__count)    \
  __asm__ __volatile__ (        \
    "L_%=: " "dec %0"    "\n\t" \
             "brne L_%=" "\n\t" \
            : /* no outputs */  \
            : "r" (__count)     \
        )

/**
 * INLINE: 16-bit counter: up to 65535*4 F_CPU for 16Mhz:[0.25 .. 16383.75] mcsec.
 * Короткие задержки по 4 цикла ЦПУ (кратно 250 нсек)
 */
#define delayMicro16(__count) \
  __asm__ __volatile__ (      \
    "1: sbiw %0,1 \n\t"       \
       "brne 1b\n\t"          \
       :: "r" (__count)       \
        )

// ============= COMMON LIBRARY: functions from *.c files only ============= //
#ifdef __cplusplus
extern "C" {
#endif

#define min(a,b)                ((a)<(b)?(a):(b))
#define max(a,b)                ((a)>(b)?(a):(b))
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define radians(deg)            ((deg)*DEG_TO_RAD)
#define degrees(rad)            ((rad)*RAD_TO_DEG)
#define sq(x)                   ((x)*(x))

// @see in this below or wiring.c by ARHAT_MODE:
extern volatile uint32_t timer0_overflow_count;

// @see arhat.c

void          time_init(void);                  // init timer with TIME_DEFAULT section in arhat_time.c
uint32_t      time_micros(void);                // microseconds upto 1.19 hour
uint32_t      time_millis(void);                // milliseconds upto 49.7 days
void          time_delay(unsigned long);        // delay in milliseconds upto 49.7 days
void          time_delay16(uint16_t);           // delay in milliseconds upto 65.5 sec. only
uint32_t      getOvfCount(void);		        // cli() .. {sei()} getter.

uint16_t      adc_read(uint8_t);                // ADC read analog pin with waiting to ready. Not by interrupt! for interrupt reading @see tsc.h

// ============ standart sketches defines ============= //
void setup(void);
void loop(void);

#ifdef __cplusplus
} // extern "C"
#endif

#if defined(ARHAT_MODE) && (ARHAT_MODE == 1)
// ================================================================================================================== //
//                         РЕЖИМ совместимости с Wiring, но без подключения самого Wiring:                            //
// ------------------------------------------------------------------------------------------------------------------ //
// Возможность работы с цифровыми пинами, номера которых хранятся в памяти, через вызовы функций Wiring               //
// ================================================================================================================== //

#include "Arduino.h"

#elif !defined(ARHAT_MODE) || (ARHAT_MODE == 2)

// ================================================================================================================== //
//                      РЕЖИМ оптимизации типовых скетчей, написанных с использованием Wiring:                        //
// ------------------------------------------------------------------------------------------------------------------ //
// замена типовых функций на макросы. Номера пинов платы - только через числовые константы. НЕ в памяти!              //
// ================================================================================================================== //

// Blocking. Not used standart Arduino.h header!
// Режим минимизации кода через константные номера пинов: отключаем хидер Arduino.h и переопределяем типовые функции в макросы
#define Arduino_h       1

// redefining all typical wiring functions and so on into this macros:
#define pinMode(p,m)            ((m)==OUTPUT? pinModeOut(p) : ((m)==INPUT? pinModeIn(p) : (pinModePullIn(p))))
#define digitalRead(p)          (pinRead(p))
#define digitalWrite(p,v)       ((v)? pinOutHigh(p) : pinOutLow(p))
#define turnOffPWM(t)           (pwmOff(p))
#define analogRead(p)           (adc_read(p))
#define analogWrite(p,v)        (pwmWrite(p,v))

#define digitalPinToPort(P)     (pinOutReg(P))
#define digitalPinToBitMask(P)  (pinSetMask(P))
#define digitalPinToTimer(P)    (pwmGetTimer(P))
#define analogInPinToBit(P)     (P)
#define portOutputRegister(P)   ( (volatile uint8_t *)(&pinOutReg(P) )
#define portInputRegister(P)    ( (volatile uint8_t *)(&pinInReg(P)  )
#define portModeRegister(P)     ( (volatile uint8_t *)(&pinDirReg(P) )

#define millis()                     time_millis()
#define micros()                     time_micros()
#define delay(ms)                    time_delay16(ms)           // upto 65.5 sec. only!
#define delayMicroseconds(us)        delayMicro16((us)<<2)      // for 16Mhz CPU only!

#ifdef __cplusplus

// not released yet. From Wiring for compatible:
#include <stdbool.h>
typedef bool boolean;           // need in WString.h, WCharacter.h !

#include "WCharacter.h"
#include "WString.h"
#include "HardwareSerial.h"
#include "USBAPI.h"

#if defined(HAVE_HWSERIAL0) && defined(HAVE_CDCSERIAL)
#  error "Targets with both UART0 and CDC serial not supported"
#endif

#endif // __cplusplus {compatible and not realised yet }

// definition for timer 0 OVF count interrupt included for arhat.c ONLY!
// Определение обработчика прерывания __vector_23() (timer 0 ovf count) подключается только для компиляции arhat.c
#ifdef ARHAT_C

#ifdef __cplusplus
extern "C" {
#endif

volatile uint32_t       timer0_overflow_count   = 0UL;

/**
 * Timer interrupt by Overflow Flag up each (TIMER_TICK_MCS*TIMER_MAX_COUNT) microseconds.
 *
 * Пользуемся побайтовой арифметикой: считали - добавили - сохранили.
 * Экономим регистры и 3 команды (6 байт) от "С" реализации
 * 58 bytes, 40 cycles (2.5mcsec)
 *
 * ISR(ISRtimer(TIME_DEFAULT, TIME_ISR), ISR_NAKED) после подстановок формирует это:
 *
 * void __vector_ 23(void) __attribute__ ((signal, used, externally_visible)) __attribute__((naked));
 * void __vector_ 23(void)
 */
ISR(ISRtimer(TIME_DEFAULT, TIME_ISR), ISR_NAKED)
{
//    timer0_overflow_count++;
// now run events dispatcher:
//  { uint8_t     i = eventsCount;
//    Event     * ptr = &Events[0];
//
//    while( i ){
//      if((ptr->start - (uint16_t)timer0_overflow_count) > ptr->timeout)
//      {
//        ptr->callback( ptr->data );
//      }
//      ptr++;
//      i--;
//    }
//  }
// reti;
  asm volatile(
    "    push r24\n\t"
    "    push r25\n\t"
    "    in r24,__SREG__\n\t"
    "    push r24\n\t"

    "    lds r24,timer0_overflow_count\n\t"
    "    lds r25,timer0_overflow_count+1\n\t"
    "    adiw r24,1\n\t"
    "    sts timer0_overflow_count,r24\n\t"
    "    sts timer0_overflow_count+1,r25\n\t"
    "    clr r25\n\t"
    "    lds r24,timer0_overflow_count+2\n\t"
    "    adc r24,r25\n\t"
    "    sts timer0_overflow_count+2,r24\n\t"
    "    lds r24,timer0_overflow_count+3\n\t"
    "    adc r24,r25\n\t"
    "    sts timer0_overflow_count+3,r24\n\t"
    "    pop r24\n\t"
    "    out __SREG__,r24\n\t"
    "    pop r25\n\t"
    "    pop r24\n\t"
    "    reti\n\t"
    ::
  );
}

#endif // ARHAT_C

// need redefined after all includes .cpp headers!
#define time_init()             init()

#else  // other ARHAT_MODE:
# error "*** ERROR! Unknown mode for arhat.h ***"
#endif // ARHAT_MODE

// ============= END ============ //

#endif // ifdef _ARHAT_H_
