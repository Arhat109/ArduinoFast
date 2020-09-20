/**
 * pins definition for ATmega2560 for use in macros "Arhat.h"
 *
 * Description macros, consists 2 parts
 * Part One:
 * 0. global max constants and convert macros.
 * 1. pinXX    -- macros for pin numbers as on Arduino board and additions numbers if it need
 * 2. AnalogXX -- macros for local analog pin numbers from 0 always
 * 3. RESET,XTAL,USART0_RX,..etc. -- special names for Arduino board pin numbers for further simlper using
 * 4. timer, adc,..so on special macros it use common pin numbers for converting pin to timer and etc.
 * 5. special devices constants
 * PART
 * Regular definition for each pin whoose may be use as digital pin to convert into PORT and BIT standard macros from io.h.
 *
 * @author Arhat109-20150604. arhat109@mail.ru
 * @license:
 *   1. This is a free software for any using and distributing without any warranties.
 *   2. You should keep author tag with any changes. May be with adding.
 */
#ifdef __AVR_ATmega2560__

#include <stdint.h>

// PART ONE:

// ----------------------------------------------------------------------------------------------------------------- //
// Количество цифровых и пр. контактов платы БЕЗ аналоговых входов (они на платах как правило нумерованы отдельно!   //
// Общая нумерация аналоговых входов идет ПОСЛЕ цифровых входов платы                                                //
// ----------------------------------------------------------------------------------------------------------------- //
#define ARDUINO_MEGA_PINS           70
#define NUM_DIGITAL_PINS            54
#define MAX_ANALOG_INPUTS           16
#define START_ANALOG_PIN_NUMBER     NUM_DIGITAL_PINS
#define analogInputToDigitalPin(p)  ((p < MAX_ANALOG_INPUTS) ? (p) + START_ANALOG_PIN_NUMBER : -1)
#define digitalPinHasPWM(p)         (((p) >= 2 && (p) <= 13) || ((p) >= 44 && (p)<= 46))

// ----------------------------------------------------------------------------------------------------------------- //
// pin number at Arduino Mega board                                                                                  //
// second and other function on this Arduino pin in comments @see below                                              //
// ----------------------------------------------------------------------------------------------------------------- //
// Макроопределения констант - номеров контактов платы в разъемах. Традиционно нумерация начинается с нуля.          //
// Аналоговые пины имеют нумерацию как продолжение за последним, 54-м номером на плате.                              //
// Здесь же даны макроопределения по альтернативным функциям контактов с переводом названия в общий номер контакта   //
// К каждому контакту платы дан комментарий по его порту и биту и альтернативным функциям контакта                   //
//                                                                                                                   //
// pinLed -- ВНИМАТЕЛЬНО! Этот контакт платы нельзя использовать как вход! На нем запаян диагностический светодиод   //
// ----------------------------------------------------------------------------------------------------------------- //

#define pinLed	13	// PB 7 ** pin13 + PWM13 + T0outA + T1outC + PC_INT_7 !!! INTERNAL LED! Can't be input pin!!! **

#define pin0	0	// PE 0 ** pin0 + USART0_RX + PC_INT_8 **
#define pin1	1	// PE 1 ** pin1 + USART0_TX **
#define pin2	2	// PE 4 ** pin2 + PWM2 + T3outB + INT_4 **
#define pin3	3	// PE 5 ** pin3 + PWM3 + T3outC + INT_5 **
#define pin4	4	// PG 5 ** pin4 + PWM4 + T0outB **
#define pin5	5	// PE 3 ** pin5 + PWM5 + T3outA + AIN1 **
#define pin6	6	// PH 3 ** pin6 + PWM6 + T4outA **
#define pin7	7	// PH 4 ** pin7 + PWM7 + T4outB **
#define pin8	8	// PH 5 ** pin8 + PWM8 + T4outC **
#define pin9	9	// PH 6 ** pin9 + PWM9 + T2outB **
#define pin10	10	// PB 4 ** pin10 + PWM10 + T2outA + PC_INT_4 **
#define pin11	11	// PB 5 ** pin11 + PWM11 + T1outA + PC_INT_5 **
#define pin12	12	// PB 6 ** pin12 + PWM12 + T1outB + PC_INT_6 **
#define pin13	13	// PB 7 ** pin13 + PWM13 + T0outA + T1outC + PC_INT_7 !!! INTERNAL LED! Can't be input pin!!! **
#define pin14	14	// PJ 1 ** pin14 + USART3_TX + PC_INT_10 **
#define pin15	15	// PJ 0 ** pin15 + USART3_RX + PC_INT_9 **
#define pin16	16	// PH 1 ** pin16 + USART2_TX **
#define pin17	17	// PH 0 ** pin17 + USART2_RX **
#define pin18	18	// PD 3 ** pin18 + USART1_TX + INT_3 **
#define pin19	19	// PD 2 ** pin19 + USART1_RX + INT_2 **
#define pin20	20	// PD 1 ** pin20 + I2C_SDA + INT_1 **
#define pin21	21	// PD 0 ** pin21 + I2C_SCL + INT_0 **
#define pin22	22	// PA 0 ** pin22 (D22) + BUS_AD0 **
#define pin23	23	// PA 1 ** pin23 (D23) + BUS_AD1 **
#define pin24	24	// PA 2 ** pin24 (D24) + BUS_AD2 **
#define pin25	25	// PA 3 ** pin25 (D25) + BUS_AD3 **
#define pin26	26	// PA 4 ** pin26 (D26) + BUS_AD4 **
#define pin27	27	// PA 5 ** pin27 (D27) + BUS_AD5 **
#define pin28	28	// PA 6 ** pin28 (D28) + BUS_AD6 **
#define pin29	29	// PA 7 ** pin29 (D29) + BUS_AD7 **
#define pin30	30	// PC 7 ** pin30 (D30) + BUS_A15 **
#define pin31	31	// PC 6 ** pin31 (D31) + BUS_A14 **
#define pin32	32	// PC 5 ** pin32 (D32) + BUS_A13 **
#define pin33	33	// PC 4 ** pin33 (D33) + BUS_A12 **
#define pin34	34	// PC 3 ** pin34 (D34) + BUS_A11 **
#define pin35	35	// PC 2 ** pin35 (D35) + BUS_A10 **
#define pin36	36	// PC 1 ** pin36 (D36) + BUS_A9 **
#define pin37	37	// PC 0 ** pin37 (D37) + BUS_A8 **
#define pin38	38	// PD 7 ** pin38 (D38) + T0_IN **
#define pin39	39	// PG 2 ** pin39 (D39) + BUS_ALE **
#define pin40	40	// PG 1 ** pin40 (D40) + BUS_RD **
#define pin41	41	// PG 0 ** pin41 (D41) + BUS_WR **
#define pin42	42	// PL 7 ** pin42 (D42) not other use **
#define pin43	43	// PL 6 ** pin43 (D43) not other use **
#define pin44	44	// PL 5 ** pin44 (D44) + PWM44 + T5outC **
#define pin45	45	// PL 4 ** pin45 (D45) + PWM45 + T5outB **
#define pin46	46	// PL 3 ** pin46 (D46) + PWM46 + T5outA **
#define pin47	47	// PL 2 ** pin47 (D47) + T5_IN **
#define pin48	48	// PL 1 ** pin48 (D48) + T5_ICP **
#define pin49	49	// PL 0 ** pin49 (D49) + T4_ICP **
#define pin50	50	// PB 3 ** pin50 (D50) + SPI_MISO + PC_INT_3 **
#define pin51	51	// PB 2 ** pin51 (D51) + SPI_MOSI + PC_INT_2 **
#define pin52	52	// PB 1 ** pin52 (D52) + SPI_SCK + PC_INT_1 **
#define pin53	53	// PB 0 ** pin53 (D53) + SPI_SS + PC_INT_0 **
#define pin54	54	// PF 0 ** Analog0 **
#define pin55	55	// PF 1 ** Analog1 **
#define pin56	56	// PF 2 ** Analog2 **
#define pin57	57	// PF 3 ** Analog3 **
#define pin58	58	// PF 4 ** Analog4 + JTAG_TCK **
#define pin59	59	// PF 5 ** Analog5 + JTAG_TMS **
#define pin60	60	// PF 6 ** Analog6 + JTAG_TDO **
#define pin61	61	// PF 7 ** Analog7 + JTAG_TDI **
#define pin62	62	// PK 0 ** Analog8 + PC_INT_16 **
#define pin63	63	// PK 1 ** Analog9 + PC_INT_17 **
#define pin64	64	// PK 2 ** Analog10 + PC_INT_18 **
#define pin65	65	// PK 3 ** Analog11 + PC_INT_19 **
#define pin66	66	// PK 4 ** Analog12 + PC_INT_20 **
#define pin67	67	// PK 5 ** Analog13 + PC_INT_21 **
#define pin68	68	// PK 6 ** Analog14 + PC_INT_22 **
#define pin69	69	// PK 7 ** Analog15 + PC_INT_23 **

// Alternate names for pins by spec. functions:

#define pwm2	2
#define pwm3	3
#define pwm4	4
#define pwm5	5
#define pwm6	6
#define pwm7	7
#define pwm8	8
#define pwm9	9
#define pwm10	10
#define pwm11	11
#define pwm12	12
#define pwm13	13	// using as timer 0 channel A only! You must to use psevdoname T1C for timer 1 channel C on pin 13!

#define Analog0		START_ANALOG_PIN_NUMBER + 0
#define Analog1		START_ANALOG_PIN_NUMBER + 1
#define Analog2		START_ANALOG_PIN_NUMBER + 2
#define Analog3		START_ANALOG_PIN_NUMBER + 3
#define Analog4		START_ANALOG_PIN_NUMBER + 4
#define Analog5		START_ANALOG_PIN_NUMBER + 5
#define Analog6		START_ANALOG_PIN_NUMBER + 6
#define Analog7		START_ANALOG_PIN_NUMBER + 7
#define Analog8		START_ANALOG_PIN_NUMBER + 8
#define Analog9		START_ANALOG_PIN_NUMBER + 9
#define Analog10	START_ANALOG_PIN_NUMBER + 10
#define Analog11	START_ANALOG_PIN_NUMBER + 11
#define Analog12	START_ANALOG_PIN_NUMBER + 12
#define Analog13	START_ANALOG_PIN_NUMBER + 13
#define Analog14	START_ANALOG_PIN_NUMBER + 14
#define Analog15	START_ANALOG_PIN_NUMBER + 15

// input pin for: "GND-pin" analog read
// p:[0..15]
#define admux1Channel(src,pin,adlar)  \
{                                     \
  ADMUX = (src)|((pin)&7)|(adlar);    \
  ADCSRB |= ((pin)&8);                \
  if((pin)&8) { DIDR2 |= ((pin)&7); } \
  else        { DIDR0 |= ((pin)&7); } \
}

// input for differential "neg-poz" pin read
// neg:[1,2|9,10], poz:[0..7|8..15]
#define admux2Channel(src,neg,poz,adlar)                 \
{                                                        \
  ADMUX = ((src)|(16+(((neg-1)&1)<<3)+(poz)&7)|(adlar)); \
  ADCSRB |= ((poz)&8);                                   \
  if((poz)&8) { DIDR2 |= ((poz)&7); }                    \
  else        { DIDR0 |= ((poz)&7); }                    \
}

// differential and gain "neg-poz" read
// neg:[0,2|8,10], poz:[0..3|8..11], g:[GAIN_10,GAIN_200], adlar:[ADC_LEFT|ADC_RIGHT]
#define admux2Gain(src,neg,poz,g,adlar)                              \
{                                                                    \
  ADMUX = ((src)|(8+(((neg)&2)<<1)|(((g)&1)<<1)|((poz)&1))|(adlar)); \
  ADCSRB |= ((poz)&8);                                               \
  if((poz)&8) { DIDR2 |= ((poz)&7); }                                \
  else        { DIDR0 |= ((poz)&7); }                                \
}

#define INT_0           21
#define INT_1           20
#define INT_2           19
#define INT_3           18
#define INT_4           2
#define INT_5           3

#define PC_INT_0        53
#define PC_INT_1        52
#define PC_INT_2        51
#define PC_INT_3        50
#define PC_INT_4        10
#define PC_INT_5        11
#define PC_INT_6        12
#define PC_INT_7        13

#define PC_INT_8        0
#define PC_INT_9        15
#define PC_INT_10       14
/**
 * You may define it if your board have this pins!
#define PC_INT_11
#define PC_INT_12
#define PC_INT_13
#define PC_INT_14
#define PC_INT_15
*/

#define PC_INT_16       62
#define PC_INT_17       63
#define PC_INT_18       64
#define PC_INT_19       65
#define PC_INT_20       66
#define PC_INT_21       67
#define PC_INT_22       68
#define PC_INT_23       69

// for PCINT0 redefine data
#define PCINT0_DDR              DDRB
#define PCINT0_PORT             PORTB
#define PCINT0_PIN              PINB
#define PCINT0_pin2number(p)    ((p)<50?(p)-6:53-(p))     // p=[53,52,51,50,10,11,12,(13)] pin13 only OUT! Not PCINT!

// for PCINT1 has not redefine data!!! More pin hasn't Arduino Mega board .. sorry

// for PCINT2 redefine data
#define PCINT2_DDR              DDRK
#define PCINT2_PORT             PORTK
#define PCINT2_PIN              PINK
#define PCINT2_pin2number(p)    ((p) - (START_ANALOG_PIN_NUMBER + 8)) // p=[62,63,64,65,66,67,68,69]]

#define PCINT_pin2level(p)      ((p)<50? 0 : ((p)<62? 0 : 2))

#define BUS_AD0		22
#define BUS_AD1		23
#define BUS_AD2		24
#define BUS_AD3		25
#define BUS_AD4		26
#define BUS_AD5		27
#define BUS_AD6		28
#define BUS_AD7		29
#define BUS_A8		37
#define BUS_A9		36
#define BUS_A10		35
#define BUS_A11		34
#define BUS_A12		33
#define BUS_A13		32
#define BUS_A14		31
#define BUS_A15		30
#define BUS_ALE		39
#define BUS_RD		40
#define BUS_WR		41

#define USART0_RX	0
#define USART0_TX	1
#define USART1_RX	19
#define USART1_TX	18
#define USART2_RX	17
#define USART2_TX	16
#define USART3_RX	15
#define USART3_TX	14
#define I2C_SDA		20
#define I2C_SCL		21
#define SPI_MISO	50
#define SPI_MOSI	51
#define SPI_SCK		52
#define SPI_SS		53
#define JTAG_TDI	61
#define JTAG_TDO	60
#define JTAG_TMS	59
#define JTAG_TCK	58

#define AIN1		5

// ============= special defines for ATmega constants ============ //
// timer interrupt names and flag bits
#define TIF_OVF                 (uint8_t)1
#define TIF_COMPA               (uint8_t)2
#define TIF_COMPB               (uint8_t)4
#define TIF_COMPC               (uint8_t)8
#define TIF_CAPT                (uint8_t)32

#define CHANGE 1
#define FALLING 2
#define RISING 3

// timer prescaler (CS) constants
#define TCLK_0          0       // timer is stopped.
#define TCLK_1          1
#define TCLK_8          2
#define TCLK_64         3
#define TCLK_256        4
#define TCLK_1024       5
#define TCLK_IN_EDGE    6
#define TLCK_IN_FRONT   7

#define PWM_DISABLE     0       // pwm pin out modes
#define PWM_TOGGLE      1
#define PWM_NORMAL      2
#define PWM_INVERSE     3

// timer specific macroses
#define getTimer2       3       // T3 channel B
#define getTimer3       3       // T3 channel C
#define getTimer4       0       // 8 bit, T0 channel B
#define getTimer5       3       // T3 channel A
#define getTimer6       4       // T4 channel A
#define getTimer7       4       // T4 channel B
#define getTimer8       4       // T4 channel C
#define getTimer9       2       // 8 bit, T2 channel B
#define getTimer10      2       // 8 bit, T2 channel A
#define getTimer11      1       // T1 channel A
#define getTimer12      1       // T1 channel B
#define getTimer13      0       // 8 bit, T0 channel A + 16bit T1 channel C
#define getTimer44      5       // T5 channel C
#define getTimer45      5       // T5 channel B
#define getTimer46      5       // T5 channel A
#define getTimerT1C     1       // special!!! for T1 channel C - 16bit !!!

#define getTimerChannel2        B       // T3 channel B
#define getTimerChannel3        C       // T3 channel C
#define getTimerChannel4        B       // 8 bit, T0 channel B
#define getTimerChannel5        A       // T3 channel A
#define getTimerChannel6        A       // T4 channel A
#define getTimerChannel7        B       // T4 channel B
#define getTimerChannel8        C       // T4 channel C
#define getTimerChannel9        B       // 8 bit, T2 channel B
#define getTimerChannel10       A       // 8 bit, T2 channel A
#define getTimerChannel11       A       // T1 channel A
#define getTimerChannel12       B       // T1 channel B
#define getTimerChannel13       A       // 8 bit, T0 channel A + 16bit T1 channel C
#define getTimerChannel44       C       // T5 channel C
#define getTimerChannel45       B       // T5 channel B
#define getTimerChannel46       A       // T5 channel A
#define getTimerChannelT1C      C       // special!!! for T1 channel C - 16bit !!!

#define setPWM2         { TCCR3A |=  33; TCCR3B |= 3; } /* A: COM32B=normal, mode 8-bit; B: prescaler=64 */
#define setPWM3         { TCCR3A |=   9; TCCR3B |= 3; } /* A: COM32C=normal, mode 8-bit; B: prescaler=64 */
#define setPWM4         { TCCR0A |=  32; }              /* A: COM02B=normal, not set: use for time functions! */
#define setPWM5         { TCCR3A |= 129; TCCR3B |= 3; } /* A: COM32A=normal, mode 8-bit; B: prescaler=64 */
#define setPWM6         { TCCR4A |= 129; TCCR4B |= 3; } /* A: COM42A=normal, mode 8-bit; B: prescaler=64 */
#define setPWM7         { TCCR4A |=  33; TCCR4B |= 3; } /* A: COM42B=normal, mode 8-bit; B: prescaler=64 */
#define setPWM8         { TCCR4A |=   9; TCCR4B |= 3; } /* A: COM42C=normal, mode 8-bit; B: prescaler=64 */
#define setPWM9         { TCCR2A |=  35; TCCR2B |= 3; } /* A: COM22B=normal, fastPWM; B: prescaler=64 */
#define setPWM10        { TCCR2A |= 131; TCCR2B |= 3; } /* A: COM22A=normal, fastPWM; B: prescaler=64 */
#define setPWM11        { TCCR1A |= 129; TCCR1B |= 3; } /* A: COM12A=normal, mode 8-bit; B: prescaler=64 */
#define setPWM12        { TCCR1A |=  33; TCCR1B |= 3; } /* A: COM12B=normal, mode 8-bit; B: prescaler=64 */
#define setPWM13        { TCCR0A |= 128; }		/* A: COM02A=normal, not set other!  */
#define setPWM44        { TCCR5A |=   9; TCCR5B |= 3; } /* A: COM52C=normal, mode 8-bit; B: prescaler=64 */
#define setPWM45        { TCCR5A |=  33; TCCR5B |= 3; } /* A: COM52B=normal, mode 8-bit; B: prescaler=64 */
#define setPWM46        { TCCR5A |= 128; TCCR5B |= 3; } /* A: COM52A=normal, mode 8-bit; B: prescaler=64 */
#define setPWMT1C       { TCCR1A |=   9; TCCR1B |= 3; } /* A: COM12C=normal, mode 8-bit; B: prescaler=64 */

#define offPWM2         { TCCR3A &= (CLR_MASK_5 & CLR_MASK_4); } /* A: COM32B=normal, mode 8-bit; B: prescaler=64 */
#define offPWM3         { TCCR3A &= (CLR_MASK_3 & CLR_MASK_2); } /* A: COM32C=normal, mode 8-bit; B: prescaler=64 */
#define offPWM4         { TCCR0A &= (CLR_MASK_5 & CLR_MASK_4); } /* A: COM02B=normal, not off: use for time functions! */
#define offPWM5         { TCCR3A &= (CLR_MASK_7 & CLR_MASK_6); } /* A: COM32A=normal, mode 8-bit; B: prescaler=64 */
#define offPWM6         { TCCR4A &= (CLR_MASK_7 & CLR_MASK_6); } /* A: COM42A=normal, mode 8-bit; B: prescaler=64 */
#define offPWM7         { TCCR4A &= (CLR_MASK_5 & CLR_MASK_4); } /* A: COM42B=normal, mode 8-bit; B: prescaler=64 */
#define offPWM8         { TCCR4A &= (CLR_MASK_3 & CLR_MASK_2); } /* A: COM42C=normal, mode 8-bit; B: prescaler=64 */
#define offPWM9         { TCCR2A &= (CLR_MASK_5 & CLR_MASK_4); } /* A: COM22B=normal, fastPWM; B: prescaler=64 */
#define offPWM10        { TCCR2A &= (CLR_MASK_7 & CLR_MASK_6); } /* A: COM22A=normal, fastPWM; B: prescaler=64 */
#define offPWM11        { TCCR1A &= (CLR_MASK_7 & CLR_MASK_6); } /* A: COM12A=normal, mode 8-bit; B: prescaler=64 */
#define offPWM12        { TCCR1A &= (CLR_MASK_5 & CLR_MASK_4); } /* A: COM12B=normal, mode 8-bit; B: prescaler=64 */
#define offPWM13        { TCCR0A &= (CLR_MASK_7 & CLR_MASK_6); } /* A: COM02A=normal, not off other!  */
#define offPWM44        { TCCR5A &= (CLR_MASK_3 & CLR_MASK_2); } /* A: COM52C=normal, mode 8-bit; B: prescaler=64 */
#define offPWM45        { TCCR5A &= (CLR_MASK_5 & CLR_MASK_4); } /* A: COM52B=normal, mode 8-bit; B: prescaler=64 */
#define offPWM46        { TCCR5A &= (CLR_MASK_7 & CLR_MASK_6); } /* A: COM52A=normal, mode 8-bit; B: prescaler=64 */
#define offPWMT1C       { TCCR1A &= (CLR_MASK_3 & CLR_MASK_2); } /* A: COM12C=normal, mode 8-bit; B: prescaler=64 */

#define outPWM2(v)	{ OCR3BH = (unsigned char)(v>>8); OCR3BL = (unsigned char)(v); }
#define outPWM3(v)	{ OCR3CH = (unsigned char)(v>>8); OCR3CL = (unsigned char)(v); }
#define outPWM4(v)	{ OCR0B = (unsigned char)(v); } /*8 bit */
#define outPWM5(v)	{ OCR3AH = (unsigned char)(v>>8); OCR3AL = (unsigned char)(v); }
#define outPWM6(v)	{ OCR4AH = (unsigned char)(v>>8); OCR4AL = (unsigned char)(v); }
#define outPWM7(v)	{ OCR4BH = (unsigned char)(v>>8); OCR4BL = (unsigned char)(v); }
#define outPWM8(v)	{ OCR4CH = (unsigned char)(v>>8); OCR4CL = (unsigned char)(v); }
#define outPWM9(v)	{ OCR2B = (unsigned char)(v); } /*8 bit */
#define outPWM10(v)	{ OCR2A = (unsigned char)(v); } /*8 bit */
#define outPWM11(v)	{ OCR1AH = (unsigned char)(v>>8); OCR1AL = (unsigned char)(v); }
#define outPWM12(v)	{ OCR1BH = (unsigned char)(v>>8); OCR1BL = (unsigned char)(v); }
#define outPWM13(v)	{ OCR0A = (unsigned char)(v); } /*8 bit */
#define outPWM44(v)	{ OCR5CH = (unsigned char)(v>>8); OCR5CL = (unsigned char)(v); }
#define outPWM45(v)	{ OCR5BH = (unsigned char)(v>>8); OCR5BL = (unsigned char)(v); }
#define outPWM46(v)	{ OCR5AH = (unsigned char)(v>>8); OCR5AL = (unsigned char)(v); }
#define outPWM99(v)	{ OCR1CH = (unsigned char)(v>>8); OCR1CL = (unsigned char)(v); }

// ============= ADC constants ============ //
// base example voltage source
#define ADC_SRC_AREF              0
#define ADC_SRC_AVCC             64
#define ADC_SRC_110             128
#define ADC_SRC_256             192

// adlar direction
#define ADC_LEFT                32
#define ADC_RIGHT                0

// gain selection
#define GAIN_10                  0
#define GAIN_200                 1

// PART TWO:

// ************ All special macros by pin numbers ************ //
// SPECIAL VIRTUAL PIN13 (T1C) for Timer1 channel C using:
#define DREGT1C         DDRB
#define OREGT1C         PORTB
#define IREGT1C         PINB
#define BSETT1C         SET_MASK_7
#define BCLRT1C         CLR_MASK_7

// PE 0 ** pin0 + USART0_RX + PC_INT_8 **
#define D0_In		DDRE  &= CLR_MASK_0
#define D0_Out		DDRE  |= SET_MASK_0
#define D0_High		PORTE |= SET_MASK_0
#define D0_Low		PORTE &= CLR_MASK_0
#define D0_Inv		PORTE ^= SET_MASK_0
#define D0_Read		(PINE & SET_MASK_0)
#define DREG0		DDRE
#define OREG0		PORTE
#define IREG0		PINE
#define BSET0		SET_MASK_0
#define BCLR0		CLR_MASK_0

// PE 1 ** pin1 + USART0_TX **
#define D1_In		DDRE  &= CLR_MASK_1
#define D1_Out		DDRE  |= SET_MASK_1
#define D1_High		PORTE |= SET_MASK_1
#define D1_Low		PORTE &= CLR_MASK_1
#define D1_Inv		PORTE ^= SET_MASK_1
#define D1_Read		((PINE & SET_MASK_1)>>1)
#define DREG1		DDRE
#define OREG1		PORTE
#define IREG1		PINE
#define BSET1		SET_MASK_1
#define BCLR1		CLR_MASK_1

// PE 4 ** pin2 + PWM2 + T3outB + INT_4 **
#define D2_In		DDRE  &= CLR_MASK_4
#define D2_Out		DDRE  |= SET_MASK_4
#define D2_High		PORTE |= SET_MASK_4
#define D2_Low		PORTE &= CLR_MASK_4
#define D2_Inv		PORTE ^= SET_MASK_4
#define D2_Read		((PINE & SET_MASK_4)>>4)
#define DREG2		DDRE
#define OREG2		PORTE
#define IREG2		PINE
#define BSET2		SET_MASK_4
#define BCLR2		CLR_MASK_4

// PE 5 ** pin3 + PWM3 + T3outC + INT_5 **
#define D3_In		DDRE  &= CLR_MASK_5
#define D3_Out		DDRE  |= SET_MASK_5
#define D3_High		PORTE |= SET_MASK_5
#define D3_Low		PORTE &= CLR_MASK_5
#define D3_Inv		PORTE ^= SET_MASK_5
#define D3_Read		((PINE & SET_MASK_5)>>5)
#define DREG3		DDRE
#define OREG3		PORTE
#define IREG3		PINE
#define BSET3		SET_MASK_5
#define BCLR3		CLR_MASK_5

// PG 5 ** pin4 + PWM4 + T0outB **
#define D4_In		DDRG  &= CLR_MASK_5
#define D4_Out		DDRG  |= SET_MASK_5
#define D4_High		PORTG |= SET_MASK_5
#define D4_Low		PORTG &= CLR_MASK_5
#define D4_Inv		PORTG ^= SET_MASK_5
#define D4_Read		((PING & SET_MASK_5)>>5)
#define DREG4		DDRG
#define OREG4		PORTG
#define IREG4		PING
#define BSET4		SET_MASK_5
#define BCLR4		CLR_MASK_5

// PE 3 ** pin5 + PWM5 + T3outA + AIN1 **
#define D5_In		DDRE  &= CLR_MASK_3
#define D5_Out		DDRE  |= SET_MASK_3
#define D5_High		PORTE |= SET_MASK_3
#define D5_Low		PORTE &= CLR_MASK_3
#define D5_Inv		PORTE ^= SET_MASK_3
#define D5_Read		((PINE & SET_MASK_3)>>3)
#define DREG5		DDRE
#define OREG5		PORTE
#define IREG5		PINE
#define BSET5		SET_MASK_3
#define BCLR5		CLR_MASK_3

// PH 3 ** pin6 + PWM6 + T4outA **
#define D6_In		DDRH  &= CLR_MASK_3
#define D6_Out		DDRH  |= SET_MASK_3
#define D6_High		PORTH |= SET_MASK_3
#define D6_Low		PORTH &= CLR_MASK_3
#define D6_Inv		PORTH ^= SET_MASK_3
#define D6_Read		((PINH & SET_MASK_3)>>3)
#define DREG6		DDRH
#define OREG6		PORTH
#define IREG6		PINH
#define BSET6		SET_MASK_3
#define BCLR6		CLR_MASK_3

// PH 4 ** pin7 + PWM7 + T4outB **
#define D7_In		DDRH  &= CLR_MASK_4
#define D7_Out		DDRH  |= SET_MASK_4
#define D7_High		PORTH |= SET_MASK_4
#define D7_Low		PORTH &= CLR_MASK_4
#define D7_Inv		PORTH ^= SET_MASK_4
#define D7_Read		((PINH & SET_MASK_4)>>4)
#define DREG7		DDRH
#define OREG7		PORTH
#define IREG7		PINH
#define BSET7		SET_MASK_4
#define BCLR7		CLR_MASK_4

// PH 5 ** pin8 + PWM8 + T4outC **
#define D8_In		DDRH  &= CLR_MASK_5
#define D8_Out		DDRH  |= SET_MASK_5
#define D8_High		PORTH |= SET_MASK_5
#define D8_Low		PORTH &= CLR_MASK_5
#define D8_Inv		PORTH ^= SET_MASK_5
#define D8_Read		((PINH & SET_MASK_5)>>5)
#define DREG8		DDRH
#define OREG8		PORTH
#define IREG8		PINH
#define BSET8		SET_MASK_5
#define BCLR8		CLR_MASK_5

// PH 6 ** pin9 + PWM9 + T2outB **
#define D9_In		DDRH  &= CLR_MASK_6
#define D9_Out		DDRH  |= SET_MASK_6
#define D9_High		PORTH |= SET_MASK_6
#define D9_Low		PORTH &= CLR_MASK_6
#define D9_Inv		PORTH ^= SET_MASK_6
#define D9_Read		((PINH & SET_MASK_6)>>6)
#define DREG9		DDRH
#define OREG9		PORTH
#define IREG9		PINH
#define BSET9		SET_MASK_6
#define BCLR9		CLR_MASK_6

// PB 4 ** pin10 + PWM10 + T2outA + PC_INT_4 **
#define D10_In		DDRB  &= CLR_MASK_4
#define D10_Out		DDRB  |= SET_MASK_4
#define D10_High	PORTB |= SET_MASK_4
#define D10_Low		PORTB &= CLR_MASK_4
#define D10_Inv		PORTB ^= SET_MASK_4
#define D10_Read	((PINB & SET_MASK_4)>>4)
#define DREG10		DDRB
#define OREG10		PORTB
#define IREG10		PINB
#define BSET10		SET_MASK_4
#define BCLR10		CLR_MASK_4

// PB 5 ** pin11 + PWM11 + T1outA + PC_INT_5 **
#define D11_In		DDRB  &= CLR_MASK_5
#define D11_Out		DDRB  |= SET_MASK_5
#define D11_High	PORTB |= SET_MASK_5
#define D11_Low		PORTB &= CLR_MASK_5
#define D11_Inv		PORTB ^= SET_MASK_5
#define D11_Read	((PINB & SET_MASK_5)>>5)
#define DREG11		DDRB
#define OREG11		PORTB
#define IREG11		PINB
#define BSET11		SET_MASK_5
#define BCLR11		CLR_MASK_5

// PB 6 ** pin12 + PWM12 + T1outB + PC_INT_6 **
#define D12_In		DDRB  &= CLR_MASK_6
#define D12_Out		DDRB  |= SET_MASK_6
#define D12_High	PORTB |= SET_MASK_6
#define D12_Low		PORTB &= CLR_MASK_6
#define D12_Inv		PORTB ^= SET_MASK_6
#define D12_Read	((PINB & SET_MASK_6)>>6)
#define DREG12		DDRB
#define OREG12		PORTB
#define IREG12		PINB
#define BSET12		SET_MASK_6
#define BCLR12		CLR_MASK_6

// PB 7 ** pin13 + PWM13 + T0outA + T1outC + PC_INT_7 !!! INTERNAL LED! Can't be input pin!!! **
//#define D13_In	DDRB  &= CLR_MASK_7
#define D13_Out		DDRB  |= SET_MASK_7
#define D13_High	PORTB |= SET_MASK_7
#define D13_Low		PORTB &= CLR_MASK_7
#define D13_Inv		PORTB ^= SET_MASK_7
#define D13_Read	*** ERROR! You can't read 13 pin in Arduino Mega!
#define DREG13		DDRB
#define OREG13		PORTB
#define IREG13		*** ERROR! You can't read 13 pin in Arduino Mega!
#define BSET13		SET_MASK_7
#define BCLR13		CLR_MASK_7

// PJ 1 ** pin14 + USART3_TX + PC_INT_10 **
#define D14_In		DDRJ  &= CLR_MASK_1
#define D14_Out		DDRJ  |= SET_MASK_1
#define D14_High	PORTJ |= SET_MASK_1
#define D14_Low		PORTJ &= CLR_MASK_1
#define D14_Inv		PORTJ ^= SET_MASK_1
#define D14_Read	((PINJ & SET_MASK_1)>>1)
#define DREG14		DDRJ
#define OREG14		PORTJ
#define IREG14		PINJ
#define BSET14		SET_MASK_1
#define BCLR14		CLR_MASK_1

// PJ 0 ** pin15 + USART3_RX + PC_INT_9 **
#define D15_In		DDRJ  &= CLR_MASK_0
#define D15_Out		DDRJ  |= SET_MASK_0
#define D15_High	PORTJ |= SET_MASK_0
#define D15_Low		PORTJ &= CLR_MASK_0
#define D15_Inv		PORTJ ^= SET_MASK_0
#define D15_Read	(PINJ & SET_MASK_0)
#define DREG15		DDRJ
#define OREG15		PORTJ
#define IREG15		PINJ
#define BSET15		SET_MASK_0
#define BCLR15		CLR_MASK_0

// PH 1 ** pin16 + USART2_TX **
#define D16_In		DDRH  &= CLR_MASK_1
#define D16_Out		DDRH  |= SET_MASK_1
#define D16_High	PORTH |= SET_MASK_1
#define D16_Low		PORTH &= CLR_MASK_1
#define D16_Inv		PORTH ^= SET_MASK_1
#define D16_Read	((PINH & SET_MASK_1)>>1)
#define DREG16		DDRH
#define OREG16		PORTH
#define IREG16		PINH
#define BSET16		SET_MASK_1
#define BCLR16		CLR_MASK_1

// PH 0 ** pin17 + USART2_RX **
#define D17_In		DDRH  &= CLR_MASK_0
#define D17_Out		DDRH  |= SET_MASK_0
#define D17_High	PORTH |= SET_MASK_0
#define D17_Low		PORTH &= CLR_MASK_0
#define D17_Inv		PORTH ^= SET_MASK_0
#define D17_Read	(PINH & SET_MASK_0)
#define DREG17		DDRH
#define OREG17		PORTH
#define IREG17		PINH
#define BSET17		SET_MASK_0
#define BCLR17		CLR_MASK_0

// PD 3 ** pin18 + USART1_TX + INT_3 **
#define D18_In		DDRD  &= CLR_MASK_3
#define D18_Out		DDRD  |= SET_MASK_3
#define D18_High	PORTD |= SET_MASK_3
#define D18_Low		PORTD &= CLR_MASK_3
#define D18_Inv		PORTD ^= SET_MASK_3
#define D18_Read	((PIND & SET_MASK_3)>>3)
#define DREG18		DDRD
#define OREG18		PORTD
#define IREG18		PIND
#define BSET18		SET_MASK_3
#define BCLR18		CLR_MASK_3

// PD 2 ** pin19 + USART1_RX + INT_2 **
#define D19_In		DDRD  &= CLR_MASK_2
#define D19_Out		DDRD  |= SET_MASK_2
#define D19_High	PORTD |= SET_MASK_2
#define D19_Low		PORTD &= CLR_MASK_2
#define D19_Inv		PORTD ^= SET_MASK_2
#define D19_Read	((PIND & SET_MASK_2)>>2)
#define DREG19		DDRD
#define OREG19		PORTD
#define IREG19		PIND
#define BSET19		SET_MASK_2
#define BCLR19		CLR_MASK_2

// PD 1 ** pin20 + I2C_SDA + INT_1 **
#define D20_In		DDRD  &= CLR_MASK_1
#define D20_Out		DDRD  |= SET_MASK_1
#define D20_High	PORTD |= SET_MASK_1
#define D20_Low		PORTD &= CLR_MASK_1
#define D20_Inv		PORTD ^= SET_MASK_1
#define D20_Read	((PIND & SET_MASK_1)>>1)
#define DREG20		DDRD
#define OREG20		PORTD
#define IREG20		PIND
#define BSET20		SET_MASK_1
#define BCLR20		CLR_MASK_1

// PD 0 ** pin21 + I2C_SCL + INT_0 **
#define D21_In		DDRD  &= CLR_MASK_0
#define D21_Out		DDRD  |= SET_MASK_0
#define D21_High	PORTD |= SET_MASK_0
#define D21_Low		PORTD &= CLR_MASK_0
#define D21_Inv		PORTD ^= SET_MASK_0
#define D21_Read	(PIND & SET_MASK_0)
#define DREG21		DDRD
#define OREG21		PORTD
#define IREG21		PIND
#define BSET21		SET_MASK_0
#define BCLR21		CLR_MASK_0

// PA 0 ** pin22 (D22) + BUS_AD0 **
#define D22_In		DDRA  &= CLR_MASK_0
#define D22_Out		DDRA  |= SET_MASK_0
#define D22_High	PORTA |= SET_MASK_0
#define D22_Low		PORTA &= CLR_MASK_0
#define D22_Inv		PORTA ^= SET_MASK_0
#define D22_Read	(PINA & SET_MASK_0)
#define DREG22		DDRA
#define OREG22		PORTA
#define IREG22		PINA
#define BSET22		SET_MASK_0
#define BCLR22		CLR_MASK_0

// PA 1 ** pin23 (D23) + BUS_AD1 **
#define D23_In		DDRA  &= CLR_MASK_1
#define D23_Out		DDRA  |= SET_MASK_1
#define D23_High	PORTA |= SET_MASK_1
#define D23_Low		PORTA &= CLR_MASK_1
#define D23_Inv		PORTA ^= SET_MASK_1
#define D23_Read	((PINA & SET_MASK_1)>>1)
#define DREG23		DDRA
#define OREG23		PORTA
#define IREG23		PINA
#define BSET23		SET_MASK_1
#define BCLR23		CLR_MASK_1

// PA 2 ** pin24 (D24) + BUS_AD2 **
#define D24_In		DDRA  &= CLR_MASK_2
#define D24_Out		DDRA  |= SET_MASK_2
#define D24_High	PORTA |= SET_MASK_2
#define D24_Low		PORTA &= CLR_MASK_2
#define D24_Inv		PORTA ^= SET_MASK_2
#define D24_Read	((PINA & SET_MASK_2)>>2)
#define DREG24		DDRA
#define OREG24		PORTA
#define IREG24		PINA
#define BSET24		SET_MASK_2
#define BCLR24		CLR_MASK_2

// PA 3 ** pin25 (D25) + BUS_AD3 **
#define D25_In		DDRA  &= CLR_MASK_3
#define D25_Out		DDRA  |= SET_MASK_3
#define D25_High	PORTA |= SET_MASK_3
#define D25_Low		PORTA &= CLR_MASK_3
#define D25_Inv		PORTA ^= SET_MASK_3
#define D25_Read	((PINA & SET_MASK_3)>>3)
#define DREG25		DDRA
#define OREG25		PORTA
#define IREG25		PINA
#define BSET25		SET_MASK_3
#define BCLR25		CLR_MASK_3

// PA 4 ** pin26 (D26) + BUS_AD4 **
#define D26_In		DDRA  &= CLR_MASK_4
#define D26_Out		DDRA  |= SET_MASK_4
#define D26_High	PORTA |= SET_MASK_4
#define D26_Low		PORTA &= CLR_MASK_4
#define D26_Inv		PORTA ^= SET_MASK_4
#define D26_Read	((PINA & SET_MASK_4)>>4)
#define DREG26		DDRA
#define OREG26		PORTA
#define IREG26		PINA
#define BSET26		SET_MASK_4
#define BCLR26		CLR_MASK_4

// PA 5 ** pin27 (D27) + BUS_AD5 **
#define D27_In		DDRA  &= CLR_MASK_5
#define D27_Out		DDRA  |= SET_MASK_5
#define D27_High	PORTA |= SET_MASK_5
#define D27_Low		PORTA &= CLR_MASK_5
#define D27_Inv		PORTA ^= SET_MASK_5
#define D27_Read	((PINA & SET_MASK_5)>>5)
#define DREG27		DDRA
#define OREG27		PORTA
#define IREG27		PINA
#define BSET27		SET_MASK_5
#define BCLR27		CLR_MASK_5

// PA 6 ** pin28 (D28) + BUS_AD6 **
#define D28_In		DDRA  &= CLR_MASK_6
#define D28_Out		DDRA  |= SET_MASK_6
#define D28_High	PORTA |= SET_MASK_6
#define D28_Low		PORTA &= CLR_MASK_6
#define D28_Inv		PORTA ^= SET_MASK_6
#define D28_Read	((PINA & SET_MASK_6)>>6)
#define DREG28		DDRA
#define OREG28		PORTA
#define IREG28		PINA
#define BSET28		SET_MASK_6
#define BCLR28		CLR_MASK_6

// PA 7 ** pin29 (D29) + BUS_AD7 **
#define D29_In		DDRA  &= CLR_MASK_7
#define D29_Out		DDRA  |= SET_MASK_7
#define D29_High	PORTA |= SET_MASK_7
#define D29_Low		PORTA &= CLR_MASK_7
#define D29_Inv		PORTA ^= SET_MASK_7
#define D29_Read	((PINA & SET_MASK_7)>>7)
#define DREG29		DDRA
#define OREG29		PORTA
#define IREG29		PINA
#define BSET29		SET_MASK_7
#define BCLR29		CLR_MASK_7

// PC 7 ** pin30 (D30) + BUS_A15 **
#define D30_In		DDRC  &= CLR_MASK_7
#define D30_Out		DDRC  |= SET_MASK_7
#define D30_High	PORTC |= SET_MASK_7
#define D30_Low		PORTC &= CLR_MASK_7
#define D30_Inv		PORTC ^= SET_MASK_7
#define D30_Read	((PINC & SET_MASK_7)>>7)
#define DREG30		DDRC
#define OREG30		PORTC
#define IREG30		PINC
#define BSET30		SET_MASK_7
#define BCLR30		CLR_MASK_7

// PC 6 ** pin31 (D31) + BUS_A14 **
#define D31_In		DDRC  &= CLR_MASK_6
#define D31_Out		DDRC  |= SET_MASK_6
#define D31_High	PORTC |= SET_MASK_6
#define D31_Low		PORTC &= CLR_MASK_6
#define D31_Inv		PORTC ^= SET_MASK_6
#define D31_Read	((PINC & SET_MASK_6)>>6)
#define DREG31		DDRC
#define OREG31		PORTC
#define IREG31		PINC
#define BSET31		SET_MASK_6
#define BCLR31		CLR_MASK_6

// PC 5 ** pin32 (D32) + BUS_A13 **
#define D32_In		DDRC  &= CLR_MASK_5
#define D32_Out		DDRC  |= SET_MASK_5
#define D32_High	PORTC |= SET_MASK_5
#define D32_Low		PORTC &= CLR_MASK_5
#define D32_Inv		PORTC ^= SET_MASK_5
#define D32_Read	((PINC & SET_MASK_5)>>5)
#define DREG32		DDRC
#define OREG32		PORTC
#define IREG32		PINC
#define BSET32		SET_MASK_5
#define BCLR32		CLR_MASK_5

// PC 4 ** pin33 (D33) + BUS_A12 **
#define D33_In		DDRC  &= CLR_MASK_4
#define D33_Out		DDRC  |= SET_MASK_4
#define D33_High	PORTC |= SET_MASK_4
#define D33_Low		PORTC &= CLR_MASK_4
#define D33_Inv		PORTC ^= SET_MASK_4
#define D33_Read	((PINC & SET_MASK_4)>>4)
#define DREG33		DDRC
#define OREG33		PORTC
#define IREG33		PINC
#define BSET33		SET_MASK_4
#define BCLR33		CLR_MASK_4

// PC 3 ** pin34 (D34) + BUS_A11 **
#define D34_In		DDRC  &= CLR_MASK_3
#define D34_Out		DDRC  |= SET_MASK_3
#define D34_High	PORTC |= SET_MASK_3
#define D34_Low		PORTC &= CLR_MASK_3
#define D34_Inv		PORTC ^= SET_MASK_3
#define D34_Read	((PINC & SET_MASK_3)>>3)
#define DREG34		DDRC
#define OREG34		PORTC
#define IREG34		PINC
#define BSET34		SET_MASK_3
#define BCLR34		CLR_MASK_3

// PC 2 ** pin35 (D35) + BUS_A10 **
#define D35_In		DDRC  &= CLR_MASK_2
#define D35_Out		DDRC  |= SET_MASK_2
#define D35_High	PORTC |= SET_MASK_2
#define D35_Low		PORTC &= CLR_MASK_2
#define D35_Inv		PORTC ^= SET_MASK_2
#define D35_Read	((PINC & SET_MASK_2)>>2)
#define DREG35		DDRC
#define OREG35		PORTC
#define IREG35		PINC
#define BSET35		SET_MASK_2
#define BCLR35		CLR_MASK_2

// PC 1 ** pin36 (D36) + BUS_A9 **
#define D36_In		DDRC  &= CLR_MASK_1
#define D36_Out		DDRC  |= SET_MASK_1
#define D36_High	PORTC |= SET_MASK_1
#define D36_Low		PORTC &= CLR_MASK_1
#define D36_Inv		PORTC ^= SET_MASK_1
#define D36_Read	((PINC & SET_MASK_1)>>1)
#define DREG36		DDRC
#define OREG36		PORTC
#define IREG36		PINC
#define BSET36		SET_MASK_1
#define BCLR36		CLR_MASK_1

// PC 0 ** pin37 (D37) + BUS_A8 **
#define D37_In		DDRC  &= CLR_MASK_0
#define D37_Out		DDRC  |= SET_MASK_0
#define D37_High	PORTC |= SET_MASK_0
#define D37_Low		PORTC &= CLR_MASK_0
#define D37_Inv		PORTC ^= SET_MASK_0
#define D37_Read	(PINC & SET_MASK_0)
#define DREG37		DDRC
#define OREG37		PORTC
#define IREG37		PINC
#define BSET37		SET_MASK_0
#define BCLR37		CLR_MASK_0

// PD 7 ** pin38 (D38) + T0_IN **
#define D38_In		DDRD  &= CLR_MASK_7
#define D38_Out		DDRD  |= SET_MASK_7
#define D38_High	PORTD |= SET_MASK_7
#define D38_Low		PORTD &= CLR_MASK_7
#define D38_Inv		PORTD ^= SET_MASK_7
#define D38_Read	((PIND & SET_MASK_7)>>7)
#define DREG38		DDRD
#define OREG38		PORTD
#define IREG38		PIND
#define BSET38		SET_MASK_7
#define BCLR38		CLR_MASK_7

// PG 2 ** pin39 (D39) + BUS_ALE **
#define D39_In		DDRG  &= CLR_MASK_2
#define D39_Out		DDRG  |= SET_MASK_2
#define D39_High	PORTG |= SET_MASK_2
#define D39_Low		PORTG &= CLR_MASK_2
#define D39_Inv		PORTG ^= SET_MASK_2
#define D39_Read	((PING & SET_MASK_2)>>2)
#define DREG39		DDRG
#define OREG39		PORTG
#define IREG39		PING
#define BSET39		SET_MASK_2
#define BCLR39		CLR_MASK_2

// PG 1 ** pin40 (D40) + BUS_RD **
#define D40_In		DDRG  &= CLR_MASK_1
#define D40_Out		DDRG  |= SET_MASK_1
#define D40_High	PORTG |= SET_MASK_1
#define D40_Low		PORTG &= CLR_MASK_1
#define D40_Inv		PORTG ^= SET_MASK_1
#define D40_Read	((PING & SET_MASK_1)>>1)
#define DREG40		DDRG
#define OREG40		PORTG
#define IREG40		PING
#define BSET40		SET_MASK_1
#define BCLR40		CLR_MASK_1

// PG 0 ** pin41 (D41) + BUS_WR **
#define D41_In		DDRG  &= CLR_MASK_0
#define D41_Out		DDRG  |= SET_MASK_0
#define D41_High	PORTG |= SET_MASK_0
#define D41_Low		PORTG &= CLR_MASK_0
#define D41_Inv		PORTG ^= SET_MASK_0
#define D41_Read	(PING &  SET_MASK_0)
#define DREG41		DDRG
#define OREG41		PORTG
#define IREG41		PING
#define BSET41		SET_MASK_0
#define BCLR41		CLR_MASK_0

// PL 7 ** pin42 (D42) not other use **
#define D42_In		DDRL  &= CLR_MASK_7
#define D42_Out		DDRL  |= SET_MASK_7
#define D42_High	PORTL |= SET_MASK_7
#define D42_Low		PORTL &= CLR_MASK_7
#define D42_Inv		PORTL ^= SET_MASK_7
#define D42_Read	((PINL & SET_MASK_7)>>7)
#define DREG42		DDRL
#define OREG42		PORTL
#define IREG42		PINL
#define BSET42		SET_MASK_7
#define BCLR42		CLR_MASK_7

// PL 6 ** pin43 (D43) not other use **
#define D43_In		DDRL  &= CLR_MASK_6
#define D43_Out		DDRL  |= SET_MASK_6
#define D43_High	PORTL |= SET_MASK_6
#define D43_Low		PORTL &= CLR_MASK_6
#define D43_Inv		PORTL ^= SET_MASK_6
#define D43_Read	((PINL & SET_MASK_6)>>6)
#define DREG43		DDRL
#define OREG43		PORTL
#define IREG43		PINL
#define BSET43		SET_MASK_6
#define BCLR43		CLR_MASK_6

// PL 5 ** pin44 (D44) + PWM44 + T5outC **
#define D44_In		DDRL  &= CLR_MASK_5
#define D44_Out		DDRL  |= SET_MASK_5
#define D44_High	PORTL |= SET_MASK_5
#define D44_Low		PORTL &= CLR_MASK_5
#define D44_Inv		PORTL ^= SET_MASK_5
#define D44_Read	((PINL & SET_MASK_5)>>5)
#define DREG44		DDRL
#define OREG44		PORTL
#define IREG44		PINL
#define BSET44		SET_MASK_5
#define BCLR44		CLR_MASK_5

// PL 4 ** pin45 (D45) + PWM45 + T5outB **
#define D45_In		DDRL  &= CLR_MASK_4
#define D45_Out		DDRL  |= SET_MASK_4
#define D45_High	PORTL |= SET_MASK_4
#define D45_Low		PORTL &= CLR_MASK_4
#define D45_Inv		PORTL ^= SET_MASK_4
#define D45_Read	((PINL & SET_MASK_4)>>4)
#define DREG45		DDRL
#define OREG45		PORTL
#define IREG45		PINL
#define BSET45		SET_MASK_4
#define BCLR45		CLR_MASK_4

// PL 3 ** pin46 (D46) + PWM46 + T5outA **
#define D46_In		DDRL  &= CLR_MASK_3
#define D46_Out		DDRL  |= SET_MASK_3
#define D46_High	PORTL |= SET_MASK_3
#define D46_Low		PORTL &= CLR_MASK_3
#define D46_Inv		PORTL ^= SET_MASK_3
#define D46_Read	((PINL & SET_MASK_3)>>3)
#define DREG46		DDRL
#define OREG46		PORTL
#define IREG46		PINL
#define BSET46		SET_MASK_3
#define BCLR46		CLR_MASK_3

// PL 2 ** pin47 (D47) + T5_IN **
#define D47_In		DDRL  &= CLR_MASK_2
#define D47_Out		DDRL  |= SET_MASK_2
#define D47_High	PORTL |= SET_MASK_2
#define D47_Low		PORTL &= CLR_MASK_2
#define D47_Inv		PORTL ^= SET_MASK_2
#define D47_Read	((PINL & SET_MASK_2)>>2)
#define DREG47		DDRL
#define OREG47		PORTL
#define IREG47		PINL
#define BSET47		SET_MASK_2
#define BCLR47		CLR_MASK_2

// PL 1 ** pin48 (D48) + T5_ICP **
#define D48_In		DDRL  &= CLR_MASK_1
#define D48_Out		DDRL  |= SET_MASK_1
#define D48_High	PORTL |= SET_MASK_1
#define D48_Low		PORTL &= CLR_MASK_1
#define D48_Inv		PORTL ^= SET_MASK_1
#define D48_Read	((PINL & SET_MASK_1)>>1)
#define DREG48		DDRL
#define OREG48		PORTL
#define IREG48		PINL
#define BSET48		SET_MASK_1
#define BCLR48		CLR_MASK_1

// PL 0 ** pin49 (D49) + T4_ICP **
#define D49_In		DDRL  &= CLR_MASK_0
#define D49_Out		DDRL  |= SET_MASK_0
#define D49_High	PORTL |= SET_MASK_0
#define D49_Low		PORTL &= CLR_MASK_0
#define D49_Inv		PORTL ^= SET_MASK_0
#define D49_Read	(PINL &  SET_MASK_0)
#define DREG49		DDRL
#define OREG49		PORTL
#define IREG49		PINL
#define BSET49		SET_MASK_0
#define BCLR49		CLR_MASK_0

// PB 3 ** pin50 (D50) + SPI_MISO + PC_INT_3 **
#define D50_In		DDRB  &= CLR_MASK_3
#define D50_Out		DDRB  |= SET_MASK_3
#define D50_High	PORTB |= SET_MASK_3
#define D50_Low		PORTB &= CLR_MASK_3
#define D50_Inv		PORTB ^= SET_MASK_3
#define D50_Read	((PINB & SET_MASK_3)>>3)
#define DREG50		DDRB
#define OREG50		PORTB
#define IREG50		PINB
#define BSET50		SET_MASK_3
#define BCLR50		CLR_MASK_3

// PB 2 ** pin51 (D51) + SPI_MOSI + PC_INT_2 **
#define D51_In		DDRB  &= CLR_MASK_2
#define D51_Out		DDRB  |= SET_MASK_2
#define D51_High	PORTB |= SET_MASK_2
#define D51_Low		PORTB &= CLR_MASK_2
#define D51_Inv		PORTB ^= SET_MASK_2
#define D51_Read	((PINB & SET_MASK_2)>>2)
#define DREG51		DDRB
#define OREG51		PORTB
#define IREG51		PINB
#define BSET51		SET_MASK_2
#define BCLR51		CLR_MASK_2

// PB 1 ** pin52 (D52) + SPI_SCK + PC_INT_1 **
#define D52_In		DDRB  &= CLR_MASK_1
#define D52_Out		DDRB  |= SET_MASK_1
#define D52_High	PORTB |= SET_MASK_1
#define D52_Low		PORTB &= CLR_MASK_1
#define D52_Inv		PORTB ^= SET_MASK_1
#define D52_Read	((PINB & SET_MASK_1)>>1)
#define DREG52		DDRB
#define OREG52		PORTB
#define IREG52		PINB
#define BSET52		SET_MASK_1
#define BCLR52		CLR_MASK_1

// PB 0 ** pin53 (D53) + SPI_SS + PC_INT_0 **
#define D53_In		DDRB  &= CLR_MASK_0
#define D53_Out		DDRB  |= SET_MASK_0
#define D53_High	PORTB |= SET_MASK_0
#define D53_Low		PORTB &= CLR_MASK_0
#define D53_Inv		PORTB ^= SET_MASK_0
#define D53_Read	(PINB &  SET_MASK_0)
#define DREG53		DDRB
#define OREG53		PORTB
#define IREG53		PINB
#define BSET53		SET_MASK_0
#define BCLR53		CLR_MASK_0

// PF 0 ** Analog0 **
#define D54_In		DDRF  &= CLR_MASK_0
#define D54_Out		DDRF  |= SET_MASK_0
#define D54_High	PORTF |= SET_MASK_0
#define D54_Low		PORTF &= CLR_MASK_0
#define D54_Inv		PORTF ^= SET_MASK_0
#define D54_Read	(PINF &  SET_MASK_0)
#define DREG54		DDRF
#define OREG54		PORTF
#define IREG54		PINF
#define BSET54		SET_MASK_0
#define BCLR54		CLR_MASK_0

// PF 1 ** Analog1 **
#define D55_In		DDRF  &= CLR_MASK_1
#define D55_Out		DDRF  |= SET_MASK_1
#define D55_High	PORTF |= SET_MASK_1
#define D55_Low		PORTF &= CLR_MASK_1
#define D55_Inv		PORTF ^= SET_MASK_1
#define D55_Read	((PINF & SET_MASK_1)>>1)
#define DREG55		DDRF
#define OREG55		PORTF
#define IREG55		PINF
#define BSET55		SET_MASK_1
#define BCLR55		CLR_MASK_1

// PF 2 ** Analog2 **
#define D56_In		DDRF  &= CLR_MASK_2
#define D56_Out		DDRF  |= SET_MASK_2
#define D56_High	PORTF |= SET_MASK_2
#define D56_Low		PORTF &= CLR_MASK_2
#define D56_Inv		PORTF ^= SET_MASK_2
#define D56_Read	((PINF & SET_MASK_2)>>2)
#define DREG56		DDRF
#define OREG56		PORTF
#define IREG56		PINF
#define BSET56		SET_MASK_2
#define BCLR56		CLR_MASK_2

// PF 3 ** Analog3 **
#define D57_In		DDRF  &= CLR_MASK_3
#define D57_Out		DDRF  |= SET_MASK_3
#define D57_High	PORTF |= SET_MASK_3
#define D57_Low		PORTF &= CLR_MASK_3
#define D57_Inv		PORTF ^= SET_MASK_3
#define D57_Read	((PINF & SET_MASK_3)>>3)
#define DREG57		DDRF
#define OREG57		PORTF
#define IREG57		PINF
#define BSET57		SET_MASK_3
#define BCLR57		CLR_MASK_3

// PF 4 ** Analog4 + JTAG_TCK **
#define D58_In		DDRF  &= CLR_MASK_4
#define D58_Out		DDRF  |= SET_MASK_4
#define D58_High	PORTF |= SET_MASK_4
#define D58_Low		PORTF &= CLR_MASK_4
#define D58_Inv		PORTF ^= SET_MASK_4
#define D58_Read	((PINF & SET_MASK_4)>>4)
#define DREG58		DDRF
#define OREG58		PORTF
#define IREG58		PINF
#define BSET58		SET_MASK_4
#define BCLR58		CLR_MASK_4

// PF 5 ** Analog5 + JTAG_TMS **
#define D59_In		DDRF  &= CLR_MASK_5
#define D59_Out		DDRF  |= SET_MASK_5
#define D59_High	PORTF |= SET_MASK_5
#define D59_Low		PORTF &= CLR_MASK_5
#define D59_Inv		PORTF ^= SET_MASK_5
#define D59_Read	((PINF & SET_MASK_5)>>5)
#define DREG59		DDRF
#define OREG59		PORTF
#define IREG59		PINF
#define BSET59		SET_MASK_5
#define BCLR59		CLR_MASK_5

// PF 6 ** Analog6 + JTAG_TDO **
#define D60_In		DDRF  &= CLR_MASK_6
#define D60_Out		DDRF  |= SET_MASK_6
#define D60_High	PORTF |= SET_MASK_6
#define D60_Low		PORTF &= CLR_MASK_6
#define D60_Inv		PORTF ^= SET_MASK_6
#define D60_Read	((PINF & SET_MASK_6)>>6)
#define DREG60		DDRF
#define OREG60		PORTF
#define IREG60		PINF
#define BSET60		SET_MASK_6
#define BCLR60		CLR_MASK_6

// PF 7 ** Analog7 + JTAG_TDI **
#define D61_In		DDRF  &= CLR_MASK_7
#define D61_Out		DDRF  |= SET_MASK_7
#define D61_High	PORTF |= SET_MASK_7
#define D61_Low		PORTF &= CLR_MASK_7
#define D61_Inv		PORTF ^= SET_MASK_7
#define D61_Read	((PINF & SET_MASK_7)>>7)
#define DREG61		DDRF
#define OREG61		PORTF
#define IREG61		PINF
#define BSET61		SET_MASK_7
#define BCLR61		CLR_MASK_7

// PK 0 ** Analog8 + PC_INT_16 **
#define D62_In		DDRK  &= CLR_MASK_0
#define D62_Out		DDRK  |= SET_MASK_0
#define D62_High	PORTK |= SET_MASK_0
#define D62_Low		PORTK &= CLR_MASK_0
#define D62_Inv		PORTK ^= SET_MASK_0
#define D62_Read	(PINK & SET_MASK_0)
#define DREG62		DDRK
#define OREG62		PORTK
#define IREG62		PINK
#define BSET62		SET_MASK_0
#define BCLR62		CLR_MASK_0

// PK 1 ** Analog9 + PC_INT_17 **
#define D63_In		DDRK  &= CLR_MASK_1
#define D63_Out		DDRK  |= SET_MASK_1
#define D63_High	PORTK |= SET_MASK_1
#define D63_Low		PORTK &= CLR_MASK_1
#define D63_Inv		PORTK ^= SET_MASK_1
#define D63_Read	((PINK & SET_MASK_1)>>1)
#define DREG63		DDRK
#define OREG63		PORTK
#define IREG63		PINK
#define BSET63		SET_MASK_1
#define BCLR63		CLR_MASK_1

// PK 2 ** Analog10 + PC_INT_18 **
#define D64_In		DDRK  &= CLR_MASK_2
#define D64_Out		DDRK  |= SET_MASK_2
#define D64_High	PORTK |= SET_MASK_2
#define D64_Low		PORTK &= CLR_MASK_2
#define D64_Inv		PORTK ^= SET_MASK_2
#define D64_Read	((PINK & SET_MASK_2)>>2)
#define DREG64		DDRK
#define OREG64		PORTK
#define IREG64		PINK
#define BSET64		SET_MASK_2
#define BCLR64		CLR_MASK_2

// PK 3 ** Analog11 + PC_INT_19 **
#define D65_In		DDRK  &= CLR_MASK_3
#define D65_Out		DDRK  |= SET_MASK_3
#define D65_High	PORTK |= SET_MASK_3
#define D65_Low		PORTK &= CLR_MASK_3
#define D65_Inv		PORTK ^= SET_MASK_3
#define D65_Read	((PINK & SET_MASK_3)>>3)
#define DREG65		DDRK
#define OREG65		PORTK
#define IREG65		PINK
#define BSET65		SET_MASK_3
#define BCLR65		CLR_MASK_3

// PK 4 ** Analog12 + PC_INT_20 **
#define D66_In		DDRK  &= CLR_MASK_4
#define D66_Out		DDRK  |= SET_MASK_4
#define D66_High	PORTK |= SET_MASK_4
#define D66_Low		PORTK &= CLR_MASK_4
#define D66_Inv		PORTK ^= SET_MASK_4
#define D66_Read	((PINK & SET_MASK_4)>>4)
#define DREG66		DDRK
#define OREG66		PORTK
#define IREG66		PINK
#define BSET66		SET_MASK_4
#define BCLR66		CLR_MASK_4

// PK 5 ** Analog13 + PC_INT_21 **
#define D67_In		DDRK  &= CLR_MASK_5
#define D67_Out		DDRK  |= SET_MASK_5
#define D67_High	PORTK |= SET_MASK_5
#define D67_Low		PORTK &= CLR_MASK_5
#define D67_Inv		PORTK ^= SET_MASK_5
#define D67_Read	((PINK & SET_MASK_5)>>5)
#define DREG67		DDRK
#define OREG67		PORTK
#define IREG67		PINK
#define BSET67		SET_MASK_5
#define BCLR67		CLR_MASK_5

// PK 6 ** Analog14 + PC_INT_22 **
#define D68_In		DDRK  &= CLR_MASK_6
#define D68_Out		DDRK  |= SET_MASK_6
#define D68_High	PORTK |= SET_MASK_6
#define D68_Low		PORTK &= CLR_MASK_6
#define D68_Inv		PORTK ^= SET_MASK_6
#define D68_Read	((PINK & SET_MASK_6)>>6)
#define DREG68		DDRK
#define OREG68		PORTK
#define IREG68		PINK
#define BSET68		SET_MASK_6
#define BCLR68		CLR_MASK_6

// PK 7 ** Analog15 + PC_INT_23 **
#define D69_In		DDRK  &= CLR_MASK_7
#define D69_Out		DDRK  |= SET_MASK_7
#define D69_High	PORTK |= SET_MASK_7
#define D69_Low		PORTK &= CLR_MASK_7
#define D69_Inv		PORTK ^= SET_MASK_7
#define D69_Read	((PINK & SET_MASK_7)>>7)
#define DREG69		DDRK
#define OREG69		PORTK
#define IREG69		PINK
#define BSET69		SET_MASK_7
#define BCLR69		CLR_MASK_7

/* ******************************************************************** */
/* not used in Arduino Mega2560 not a pin!                              */
/* If you have this pin on your board add it numbers in this correctly! */
/* ******************************************************************** */
/*
#define D_In		DDRK  &= CLR_MASK_
#define D_Out		DDRK  |= SET_MASK_
#define D_High		PORTK |= SET_MASK_
#define D_Low		PORTK &= CLR_MASK_
#define D_Inv		PORTK ^= SET_MASK_
#define D_Read		((PINK & SET_MASK_)>>)

#define pin	pinE2
#define AIN0		pinE2
#define USART0_Xck	pinE2
#define DREG		DDRE
#define OREG		PORTE
#define IREG		PINE
#define BSET		SET_MASK_2
#define BCLR		CLR_MASK_2

#define pin	pinD5
#define USART1_Xck	pinD5
#define DREG		DDRD
#define OREG		PORTD
#define IREG		PIND
#define BSET		SET_MASK_5
#define BCLR		CLR_MASK_5

#define pin	pinH2
#define USART2_Xck	pinH2
#define DREG		DDRH
#define OREG		PORTH
#define IREG		PINH
#define BSET		SET_MASK_2
#define BCLR		CLR_MASK_2

#define pin	pinJ2
#define USART3_Xck	pinJ2
#define PC_INT_11	pinJ2
#define DREG		DDRJ
#define OREG		PORTJ
#define IREG		PINJ
#define BSET		SET_MASK_2
#define BCLR		CLR_MASK_2

#define pin	pinG3
#define T2osc1		pinG3
#define DREG		DDRG
#define OREG		PORTG
#define IREG		PING
#define BSET		SET_MASK_3
#define BCLR		CLR_MASK_3

#define pin	pinG4
#define T2osc2		pinG4
#define DREG		DDRG
#define OREG		PORTG
#define IREG		PING
#define BSET		SET_MASK_4
#define BCLR		CLR_MASK_4

#define pin	pinD6
#define T1_IN	pinD6
#define DREG		DDRD
#define OREG		PORTD
#define IREG		PIND
#define BSET		SET_MASK_6
#define BCLR		CLR_MASK_6

#define pin	pinD4
#define T1_ICP	pinD4
#define DREG		DDRD
#define OREG		PORTD
#define IREG		PIND
#define BSET		SET_MASK_4
#define BCLR		CLR_MASK_4

#define pin	pinE6
#define T3_IN		pinE6
#define INT_6		pinE6
#define DREG		DDRE
#define OREG		PORTE
#define IREG		PINE
#define BSET		SET_MASK_6
#define BCLR		CLR_MASK_6

#define pin	pinE7
#define T3_ICP		pinE7
#define INT_7		pinE7
#define DREG		DDRE
#define OREG		PORTE
#define IREG		PINE
#define BSET		SET_MASK_7
#define BCLR		CLR_MASK_7

#define pin	pinH7
#define T4_IN		pinH7
#define DREG		DDRH
#define OREG		PORTH
#define IREG		PINH
#define BSET		SET_MASK_7
#define BCLR		CLR_MASK_7

#define pin	pinJ3
#define PC_INT_12	pinJ3
#define DREG		DDRJ
#define OREG		PORTJ
#define IREG		PINJ
#define BSET		SET_MASK_3
#define BCLR		CLR_MASK_3

#define pin	pinJ4
#define PC_INT_13	pinJ4
#define DREG		DDRJ
#define OREG		PORTJ
#define IREG		PINJ
#define BSET		SET_MASK_4
#define BCLR		CLR_MASK_4

#define pin	pinJ5
#define PC_INT_14	pinJ5
#define DREG		DDRJ
#define OREG		PORTJ
#define IREG		PINJ
#define BSET		SET_MASK_5
#define BCLR		CLR_MASK_5

#define pin	pinJ6
#define PC_INT_15	pinJ6
#define DREG		DDRJ
#define OREG		PORTJ
#define IREG		PINJ
#define BSET		SET_MASK_6
#define BCLR		CLR_MASK_6

#define pin	pinJ7
#define DREG		DDRJ
#define OREG		PORTJ
#define IREG		PINJ
#define BSET		SET_MASK_7
#define BCLR		CLR_MASK_7
*/

#endif /* __AVR_ATmega2560__ */
