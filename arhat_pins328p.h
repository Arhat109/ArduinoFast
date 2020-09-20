/**
 * pins definition for  for use in macros "Arhat.h"
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
#ifdef __AVR_ATmega328P__

#define ARDUINO_MEGA_PINS           17
#define NUM_DIGITAL_PINS            ARDUINO_MEGA_PINS
#define MAX_ANALOG_INPUTS           6
#define START_ANALOG_PIN_NUMBER     ARDUINO_MEGA_PINS
#define analogInputToDigitalPin(p)  ((p < MAX_ANALOG_INPUTS) ? (p) + START_ANALOG_PIN_NUMBER : -1)
#define digitalPinHasPWM(p)         ((p) == 3 || (p) == 5) || (p) == 6 || (p) == 9 || (p)==10 ||(p)==11)

/** pin number at Arduino board              */
/** second and other function on this Arduino pin in comments @see below */
#define pinLed	13	// PB 5 ** chip19 + SCK + PCINT5 ** !!! INTERNAL LED! Can't be input pin!!! **

//                         reg ** chip_pin + functions
#define pin0	0	// PD 0 ** chip2 + USART0_RX + PCINT16 **
#define pin1	1	// PD 1 ** chip3 + USART0_TX + PCINT17 **
#define pin2	2	// PD 2 ** chip4 + INT0 + PCINT18 **
#define pin3	3	// PD 3 ** chip5 + PWM3 + INT1 + OC2B + PCINT19 **
#define pin4	4	// PD 4 ** chip6 + T0 + USART0_Xck + PCINT20 **
#define pin5	5	// PD 5 ** chip11 + PWM5 + T1 + OC0B + PCINT21 **
#define pin6	6	// PD 6 ** chip12 + PWM6 + AIN0 + OC0A + PCINT22 **
#define pin7	7	// PD 7 ** chip13 + AIN1 + PCINT23 **
#define pin8	8	// PB 0 ** chip14 + ICP1 + CLK0 + PCINT0 **
#define pin9	9	// PB 1 ** chip15 + PWM9 + OC1A + PCINT1 **
#define pin10	10	// PB 2 ** chip16 + PWM10 + SS + OC1B + PCINT2 **
#define pin11	11	// PB 3 ** chip17 + PWM11 + MOSI + OC2A + PCINT3 **
#define pin12	12	// PB 4 ** chip18 + MISO + PCINT4 **
#define pin13	13	// PB 5 ** chip19 + SCK + PCINT5 **
#define pin14	14	// PB 6 ** chip9  + XTAL1 + PCINT6 **
#define pin15	15	// PB 7 ** chip10 + XTAL2 + PCINT7 **
#define pin16	16	// PC 6 ** chip1  + RESET   + PCINT14 **
#define pin17	17	// PC 0 ** chip23 + Analog0 + PCINT8 **
#define pin18	18	// PC 1 ** chip24 + Analog1 + PCINT9 **
#define pin19	19	// PC 2 ** chip25 + Analog2 + PCINT10 **
#define pin20	20	// PC 3 ** chip26 + Analog3 + PCINT11 **
#define pin21	21	// PC 4 ** chip27 + Analog4 + PCINT12 **
#define pin22	22	// PC 5 ** chip28 + Analog5 + PCINT13 **

// local analog pin numbers
#define Analog0		0
#define Analog1		1
#define Analog2		2
#define Analog3		3
#define Analog4		4
#define Analog5		5

// input pin for: "GND-pin" analog read
// p:[0..15]
#define admux1Channel(src,pin,adlar)  \
{                                     \
  ADMUX = (src)|((pin)&7)|(adlar);    \
  ADCSRB |= ((pin)&8);                \
  DIDR0 |= ((pin)&7);                 \
}

// for PCINT0 redefine data
#define PCINT0_DDR              DDRB
#define PCINT0_PORT             PORTB
#define PCINT0_PIN              PINB
#define PCINT0_pin2number(p)    ((p)-8) // p=[8,9,10,11,12,13,14,15]

// for PCINT1 redefine data
#define PCINT1_DDR              DDRC
#define PCINT1_PORT             PORTC
#define PCINT1_PIN              PINC
#define PCINT1_pin2number(p)    ((p)==16? 6 :(p)-START_ANALOG_PIN_NUMBER) // p=[17,18,19,20,21,22,16,-] .. 7 only!

// for PCINT2 redefine data
#define PCINT2_DDR              DDRD
#define PCINT2_PORT             PORTD
#define PCINT2_PIN              PIND
#define PCINT2_pin2number(p)    (p) // p=[0,1,2,3,4,5,6,7]

// converter pin to pcint level number 0,1,2
#define pin2pcintLevel(p)       ((p)<8? 2 : ((p)<16? 0 : 1))

// special pin names and its numbers for special functions:
#define RESET	16

#define XTAL1	14
#define XTAL2	15
#define ADC6	6	// ADC6 pin are presents only for TQFP chip! Not pin - local analog number!
#define ADC7	7	// ADC7 pin are presents only for TQFP chip! Not pin - local analog number!

#define USART0_RX	0
#define USART0_TX	1
#define USART0_CLK	4

#define SPI_MISO	12
#define SPI_MOSI	11
#define SPI_SCK		13
#define SPI_SS		10

#define AIN0		6
#define AIN1		7

#define INT_0		2
#define INT_1		3

#define PC_INT_0	8
#define PC_INT_1	9
#define PC_INT_2	10
#define PC_INT_3	11
#define PC_INT_4	12
#define PC_INT_5	13
#define PC_INT_6	14
#define PC_INT_7	15
#define PC_INT_8	START_ANALOG_PIN_NUMBER+0
#define PC_INT_9	START_ANALOG_PIN_NUMBER+1
#define PC_INT_10	START_ANALOG_PIN_NUMBER+2
#define PC_INT_11	START_ANALOG_PIN_NUMBER+3
#define PC_INT_12	START_ANALOG_PIN_NUMBER+4
#define PC_INT_13	START_ANALOG_PIN_NUMBER+5
#define PC_INT_14	START_ANALOG_PIN_NUMBER+6
#define PC_INT_16	0
#define PC_INT_17	1
#define PC_INT_18	2
#define PC_INT_19	3
#define PC_INT_20	4
#define PC_INT_21	5
#define PC_INT_22	6
#define PC_INT_23	7

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

// macros by pin numbers for timer functions
#define getTimer3       2       // T2 channel B
#define getTimer5       0       // T0 channel B
#define getTimer6       0       // T0 channel A
#define getTimer9       1       // 16-bit, T1 channel A
#define getTimer10      1       // 16-bit, T1 channel B
#define getTimer11      2       // T2 channel A

#define getTimerChannel3        B       // T2 channel B
#define getTimerChannel5        B       // T0 channel B
#define getTimerChannel6        A       // T0 channel A
#define getTimerChannel9        A       // 16-bit, T1 channel A
#define getTimerChannel10       B       // 16-bit, T1 channel B
#define getTimerChannel11       A       // T2 channel A

#define setPWM3         { TCCR2A |= (SET_MASK_5+3); TCCR3B |= 3; }
#define setPWM5         { TCCR0A |= (SET_MASK_5+3); TCCR3B |= 3; }
#define setPWM6         { TCCR0A |= (SET_MASK_7+3); TCCR4B |= 3; }
#define setPWM9         { TCCR1A |= (SET_MASK_7+1); TCCR2B |= 3; } /* 16-bit: mode 8-bit compatible! */
#define setPWM10        { TCCR1A |= (SET_MASK_5+1); TCCR2B |= 3; } /* 16-bit: mode 8-bit compatible! */
#define setPWM11        { TCCR2A |= (SET_MASK_7+3); TCCR1B |= 3; }

#define offPWM3         { TCCR2A &= (CLR_MASK_5 & CLR_MASK_4); }
#define offPWM5         { TCCR0A &= (CLR_MASK_5 & CLR_MASK_4); }
#define offPWM6         { TCCR0A &= (CLR_MASK_7 & CLR_MASK_6); }
#define offPWM9         { TCCR1A &= (CLR_MASK_7 & CLR_MASK_6); }
#define offPWM10        { TCCR1A &= (CLR_MASK_5 & CLR_MASK_4); }
#define offPWM11        { TCCR2A &= (CLR_MASK_7 & CLR_MASK_6); }

#define outPWM3(v)	{ OCR2B = (unsigned char)(v); }
#define outPWM5(v)	{ OCR0B = (unsigned char)(v); }
#define outPWM6(v)	{ OCR0A = (unsigned char)(v); }
#define outPWM9(v)	{ OCR1AH = (unsigned char)(v>>8); OCR1AL = (unsigned char)(v); }
#define outPWM10(v)	{ OCR1BH = (unsigned char)(v>>8); OCR1BL = (unsigned char)(v); }
#define outPWM11(v)	{ OCR2A = (unsigned char)(v); }

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

// ************ All special macros by pin numbers ************ //
// PD 0 ** chip2 + USART0_RX + PCINT16 **
#define D0_In		DDRD  &= CLR_MASK_0
#define D0_Out		DDRD  |= SET_MASK_0
#define D0_High		PORTD |= SET_MASK_0
#define D0_Low		PORTD &= CLR_MASK_0
#define D0_Inv		PORTD ^= SET_MASK_0
#define D0_Read		(PIND & SET_MASK_0)
#define DREG0		DDRD
#define OREG0		PORTD
#define IREG0		PIND
#define BSET0		SET_MASK_0
#define BCLR0		CLR_MASK_0

// PD 1 ** chip3 + USART0_TX + PCINT17 **
#define D1_In		DDRD  &= CLR_MASK_1
#define D1_Out		DDRD  |= SET_MASK_1
#define D1_High		PORTD |= SET_MASK_1
#define D1_Low		PORTD &= CLR_MASK_1
#define D1_Inv		PORTD ^= SET_MASK_1
#define D1_Read		((PIND & SET_MASK_1)>>1)
#define DREG1		DDRD
#define OREG1		PORTD
#define IREG1		PIND
#define BSET1		SET_MASK_1
#define BCLR1		CLR_MASK_1

// PD 2 ** chip4 + INT0 + PCINT18 **
#define D2_In		DDRD  &= CLR_MASK_2
#define D2_Out		DDRD  |= SET_MASK_2
#define D2_High		PORTD |= SET_MASK_2
#define D2_Low		PORTD &= CLR_MASK_2
#define D2_Inv		PORTD ^= SET_MASK_2
#define D2_Read		((PIND & SET_MASK_2)>>2)
#define DREG2		DDRD
#define OREG2		PORTD
#define IREG2		PIND
#define BSET2		SET_MASK_2
#define BCLR2		CLR_MASK_2

// PD 3 ** chip5 + PWM3 + INT1 + OC2B + PCINT19 **
#define D3_In		DDRD  &= CLR_MASK_3
#define D3_Out		DDRD  |= SET_MASK_3
#define D3_High		PORTD |= SET_MASK_3
#define D3_Low		PORTD &= CLR_MASK_3
#define D3_Inv		PORTD ^= SET_MASK_3
#define D3_Read		((PIND & SET_MASK_3)>>3)
#define DREG3		DDRD
#define OREG3		PORTD
#define IREG3		PIND
#define BSET3		SET_MASK_3
#define BCLR3		CLR_MASK_3

// PD 4 ** chip6 + T0 + USART0_Xck + PCINT20 **
#define D4_In		DDRD  &= CLR_MASK_4
#define D4_Out		DDRD  |= SET_MASK_4
#define D4_High		PORTD |= SET_MASK_4
#define D4_Low		PORTD &= CLR_MASK_4
#define D4_Inv		PORTD ^= SET_MASK_4
#define D4_Read		((PIND & SET_MASK_4)>>4)
#define DREG4		DDRD
#define OREG4		PORTD
#define IREG4		PIND
#define BSET4		SET_MASK_4
#define BCLR4		CLR_MASK_4

// PD 5 ** chip11 + PWM5 + T1 + OC0B + PCINT21 **
#define D5_In		DDRD  &= CLR_MASK_5
#define D5_Out		DDRD  |= SET_MASK_5
#define D5_High		PORTD |= SET_MASK_5
#define D5_Low		PORTD &= CLR_MASK_5
#define D5_Inv		PORTD ^= SET_MASK_5
#define D5_Read		((PIND & SET_MASK_5)>>5)
#define DREG5		DDRD
#define OREG5		PORTD
#define IREG5		PIND
#define BSET5		SET_MASK_5
#define BCLR5		CLR_MASK_5

// PD 6 ** chip12 + PWM6 + AIN0 + OC0A + PCINT22 **
#define D6_In		DDRD  &= CLR_MASK_6
#define D6_Out		DDRD  |= SET_MASK_6
#define D6_High		PORTD |= SET_MASK_6
#define D6_Low		PORTD &= CLR_MASK_6
#define D6_Inv		PORTD ^= SET_MASK_6
#define D6_Read		((PIND & SET_MASK_6)>>6)
#define DREG6		DDRD
#define OREG6		PORTD
#define IREG6		PIND
#define BSET6		SET_MASK_6
#define BCLR6		CLR_MASK_6

// PD 7 ** chip13 + AIN1 + PCINT23 **
#define D7_In		DDRD  &= CLR_MASK_7
#define D7_Out		DDRD  |= SET_MASK_7
#define D7_High		PORTD |= SET_MASK_7
#define D7_Low		PORTD &= CLR_MASK_7
#define D7_Inv		PORTD ^= SET_MASK_7
#define D7_Read		((PIND & SET_MASK_7)>>7)
#define DREG7		DDRD
#define OREG7		PORTD
#define IREG7		PIND
#define BSET7		SET_MASK_7
#define BCLR7		CLR_MASK_7

// PB 0 ** chip14 + ICP1 + CLK0 + PCINT0 **
#define D8_In		DDRB  &= CLR_MASK_0
#define D8_Out		DDRB  |= SET_MASK_0
#define D8_High		PORTB |= SET_MASK_0
#define D8_Low		PORTB &= CLR_MASK_0
#define D8_Inv		PORTB ^= SET_MASK_0
#define D8_Read		(PINB & SET_MASK_0)
#define DREG8		DDRB
#define OREG8		PORTB
#define IREG8		PINB
#define BSET8		SET_MASK_0
#define BCLR8		CLR_MASK_0

// PB 1 ** chip15 + PWM9 + OC1A + PCINT1 **
#define D9_In		DDRB  &= CLR_MASK_1
#define D9_Out		DDRB  |= SET_MASK_1
#define D9_High		PORTB |= SET_MASK_1
#define D9_Low		PORTB &= CLR_MASK_1
#define D9_Inv		PORTB ^= SET_MASK_1
#define D9_Read		((PINB & SET_MASK_1)>>1)
#define DREG9		DDRB
#define OREG9		PORTB
#define IREG9		PINB
#define BSET9		SET_MASK_1
#define BCLR9		CLR_MASK_1

// PB 2 ** chip16 + PWM10 + SS + OC1B + PCINT2 **
#define D10_In		DDRB  &= CLR_MASK_2
#define D10_Out		DDRB  |= SET_MASK_2
#define D10_High	PORTB |= SET_MASK_2
#define D10_Low		PORTB &= CLR_MASK_2
#define D10_Inv		PORTB ^= SET_MASK_2
#define D10_Read	((PINB & SET_MASK_2)>>2)
#define DREG10		DDRB
#define OREG10		PORTB
#define IREG10		PINB
#define BSET10		SET_MASK_2
#define BCLR10		CLR_MASK_2

// PB 3 ** chip17 + PWM11 + MOSI + OC2A + PCINT3 **
#define D11_In		DDRB  &= CLR_MASK_3
#define D11_Out		DDRB  |= SET_MASK_3
#define D11_High	PORTB |= SET_MASK_3
#define D11_Low		PORTB &= CLR_MASK_3
#define D11_Inv		PORTB ^= SET_MASK_3
#define D11_Read	((PINB & SET_MASK_3)>>3)
#define DREG11		DDRB
#define OREG11		PORTB
#define IREG11		PINB
#define BSET11		SET_MASK_3
#define BCLR11		CLR_MASK_3

// PB 4 ** chip18 + MISO + PCINT4 **
#define D12_In		DDRB  &= CLR_MASK_4
#define D12_Out		DDRB  |= SET_MASK_4
#define D12_High	PORTB |= SET_MASK_4
#define D12_Low		PORTB &= CLR_MASK_4
#define D12_Inv		PORTB ^= SET_MASK_4
#define D12_Read	((PINB & SET_MASK_4)>>4)
#define DREG12		DDRB
#define OREG12		PORTB
#define IREG12		PINB
#define BSET12		SET_MASK_4
#define BCLR12		CLR_MASK_4

// PB 5 ** chip19 + SCK + PCINT5 **
#define D13_In		DDRB  &= CLR_MASK_5
#define D13_Out		DDRB  |= SET_MASK_5
#define D13_High	PORTB |= SET_MASK_5
#define D13_Low		PORTB &= CLR_MASK_5
#define D13_Inv		PORTB ^= SET_MASK_5
#define D13_Read	((PINB & SET_MASK_5)>>5)
#define DREG13		DDRB
#define OREG13		PORTB
#define IREG13		PINB
#define BSET13		SET_MASK_5
#define BCLR13		CLR_MASK_5

// PB 6 ** chip9  + XTAL1 + PCINT6 **
#define D14_In		DDRB  &= CLR_MASK_6
#define D14_Out		DDRB  |= SET_MASK_6
#define D14_High	PORTB |= SET_MASK_6
#define D14_Low		PORTB &= CLR_MASK_6
#define D14_Inv		PORTB ^= SET_MASK_6
#define D14_Read	((PINB & SET_MASK_6)>>6)
#define DREG14		DDRB
#define OREG14		PORTB
#define IREG14		PINB
#define BSET14		SET_MASK_6
#define BCLR14		CLR_MASK_6

// PB 7 ** chip10 + XTAL2 + PCINT7 **
#define D15_In		DDRB  &= CLR_MASK_7
#define D15_Out		DDRB  |= SET_MASK_7
#define D15_High	PORTB |= SET_MASK_7
#define D15_Low		PORTB &= CLR_MASK_7
#define D15_Inv		PORTB ^= SET_MASK_7
#define D15_Read	((PINB & SET_MASK_7)>>7)
#define DREG15		DDRB
#define OREG15		PORTB
#define IREG15		PINB
#define BSET15		SET_MASK_7
#define BCLR15		CLR_MASK_7

// PC 6 ** chip1  + RESET   + PCINT14 **
#define D16_In		DDRC  &= CLR_MASK_6
#define D16_Out		DDRC  |= SET_MASK_6
#define D16_High	PORTC |= SET_MASK_6
#define D16_Low		PORTC &= CLR_MASK_6
#define D16_Inv		PORTC ^= SET_MASK_6
#define D16_Read	((PINC & SET_MASK_6)>>6)
#define DREG16		DDRC
#define OREG16		PORTC
#define IREG16		PINC
#define BSET16		SET_MASK_6
#define BCLR16		CLR_MASK_6

// PC 0 ** chip23 + Analog0 + PCINT8 **
#define D17_In		DDRC  &= CLR_MASK_0
#define D17_Out		DDRC  |= SET_MASK_0
#define D17_High	PORTC |= SET_MASK_0
#define D17_Low		PORTC &= CLR_MASK_0
#define D17_Inv		PORTC ^= SET_MASK_0
#define D17_Read	(PINC & SET_MASK_0)
#define DREG17		DDRC
#define OREG17		PORTC
#define IREG17		PINC
#define BSET17		SET_MASK_0
#define BCLR17		CLR_MASK_0

// PC 1 ** chip24 + Analog1 + PCINT9 **
#define D18_In		DDRC  &= CLR_MASK_1
#define D18_Out		DDRC  |= SET_MASK_1
#define D18_High	PORTC |= SET_MASK_1
#define D18_Low		PORTC &= CLR_MASK_1
#define D18_Inv		PORTC ^= SET_MASK_1
#define D18_Read	((PINC & SET_MASK_1)>>1)
#define DREG18		DDRC
#define OREG18		PORTC
#define IREG18		PINC
#define BSET18		SET_MASK_1
#define BCLR18		CLR_MASK_1

// PC 2 ** chip25 + Analog2 + PCINT10 **
#define D19_In		DDRC  &= CLR_MASK_2
#define D19_Out		DDRC  |= SET_MASK_2
#define D19_High	PORTC |= SET_MASK_2
#define D19_Low		PORTC &= CLR_MASK_2
#define D19_Inv		PORTC ^= SET_MASK_2
#define D19_Read	((PINC & SET_MASK_2)>>2)
#define DREG19		DDRC
#define OREG19		PORTC
#define IREG19		PINC
#define BSET19		SET_MASK_2
#define BCLR19		CLR_MASK_2

// PC 3 ** chip26 + Analog3 + PCINT11 **
#define D20_In		DDRC  &= CLR_MASK_3
#define D20_Out		DDRC  |= SET_MASK_3
#define D20_High	PORTC |= SET_MASK_3
#define D20_Low		PORTC &= CLR_MASK_3
#define D20_Inv		PORTC ^= SET_MASK_3
#define D20_Read	((PINC & SET_MASK_3)>>3)
#define DREG20		DDRC
#define OREG20		PORTC
#define IREG20		PINC
#define BSET20		SET_MASK_3
#define BCLR20		CLR_MASK_3

// PC 4 ** chip27 + Analog4 + PCINT12 **
#define D21_In		DDRC  &= CLR_MASK_4
#define D21_Out		DDRC  |= SET_MASK_4
#define D21_High	PORTC |= SET_MASK_4
#define D21_Low		PORTC &= CLR_MASK_4
#define D21_Inv		PORTC ^= SET_MASK_4
#define D21_Read	((PINC & SET_MASK_4)>>4)
#define DREG21		DDRC
#define OREG21		PORTC
#define IREG21		PINC
#define BSET21		SET_MASK_4
#define BCLR21		CLR_MASK_4

// PC 5 ** chip28 + Analog5 + PCINT13 **
#define D22_In		DDRC  &= CLR_MASK_5
#define D22_Out		DDRC  |= SET_MASK_5
#define D22_High	PORTC |= SET_MASK_5
#define D22_Low		PORTC &= CLR_MASK_5
#define D22_Inv		PORTC ^= SET_MASK_5
#define D22_Read	((PINC & SET_MASK_5)>>5)
#define DREG22		DDRC
#define OREG22		PORTC
#define IREG22		PINC
#define BSET22		SET_MASK_5
#define BCLR22		CLR_MASK_5

#endif /* __AVR_ATmega328P__ */
