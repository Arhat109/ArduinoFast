/**
 * Simple function for calc time and delays.
 * 
 * use timer0 as default and prescaler 1/64 for each 4 microseconds with 16Mhz CLK.
 * By default timer0 is overflowing each 256 ticks at 1024 microseconds.
 * 
 * For use other timer you need predefine all constants in block TIME_DEFAULT
 * and recompile this file.
 * 
 * For simple use, you may rename this file to wiring.c and replace it.
 * 
 * @author Arhat109: arhat109@mail.ru
 * 
 * license agreement:
 * You use this software on own your risks. No claims will be accepted.
 * You may use this file any way, but cannot change
 * or delete tag @author above (you may append your tag @author) and must keeping this rows:
 * 
 * This is free software, not any pay. But you may donate some money to phone +7-951-388-2793
 */

#define ARHAT_C 1           // need for includes interrupt function in this file only.
#include "arhat.h"

/**
 * Volatile read count TOV interrupt
 * 24 bytes, 19 cycles (1.1875mcsec.)
 */
uint32_t getOvfCount()
{
  uint8_t       _sreg = SREG;
  uint32_t      _count;
  
  cli();
  _count = timer0_overflow_count;
  SREG = _sreg;
  
  return _count;
}

/**
 * Return microseconds 0..up to 1 hours 11.4 minutes are identical with wiring.c
 * "C" code = 76 bytes, "Asm" = 56 bytes and 42 cycles.
 */
uint32_t time_micros()             // return in r22..r25
{
/*
 * register struct{ uint8_t timer, uint24_t micro } retVal; -- can't compile right!
 * retVal must be in r22,r23,r24,r25 registers for right return avr-gcc convention!
 *
    uint8_t     oldSREG = SREG;         // r27
    uint8_t     timer, tov;             // r22, r26
    uint32_t    micro;                  // r23,r24,r25

    // read all into local: volatile!
    cli();
      micro = timer0_overflow_count;		// not use h-byte!
      timer = timerCount(TIME_DEFAULT);
//      tov = timerIFlag(TIME_DEFAULT,OVF);	// bit0! =={0,1} only!
      if ( timerIFlag(TIME_DEFAULT,OVF) && (timer<255) ){ micro++; }
    SREG = oldSREG;

    // this is a precompiler #IF because is constants:
    if( TIME_TICK_MCS>1 ) {
      return (((micro<<8)+timer)<<TIME_SHIFT)+3;	// +3 microsec. fot this routine
    } else {
      return (((micro<<8)+timer)>>TIME_SHIFT)+3;
    }
*/
  asm volatile (
    "  push r26                 ;1\n\t"
    "  in r26,__SREG__          ;1 oldSREG = SREG\n\t"
    "  cli                      ;1\n\t"
    "  in r22,0x26              ;1 timer = timerCount(TIME_DEFAULT)\n\t"
    "  lds r23,timer0_overflow_count        ;3 micro = (uint24_t)timer0_overflow_count;\n\t"
    "  lds r24,timer0_overflow_count+1      ;3\n\t"
    "  lds r25,timer0_overflow_count+2      ;3 now: {r22..25}=(micro<<8)+timer!\n\t"
    "  sbis 0x15,0              ;1/2 TOV==1? ->PС+1\n\t"
    "   rjmp .skip1\n\t"
    "  cpi  r22,lo8(-1)         ;1 ?!? timer == 255?\n\t"
    "  breq .skip1\n\t"
    "    sec                    ;1 set carry flag\n\t"
    "    adc   r23,__zero_reg__ ;1 micro++\n\t"
    "    adc   r24,__zero_reg__ ;1\n\t"
    "    adc   r25,__zero_reg__ ;1\n\t"
    ".skip1:\n\t"
    "  out __SREG__,r26         ;1 SREG = oldSREG, tmp_reg not use!\n\t"

    "  ldi  r26,2               ;3 load TIME_SHIFT counter\n\t"
    ".shift1: \n\t"
  ::);
  if( TIME_TICK_MCS>1 ) {
    asm volatile (
      "  lsl r22                ;1*2 retVal<<TIME_SHIFT\n\t"
      "  rol r23                ;1*2\n\t"
      "  rol r24                ;1*2\n\t"
      "  rol r25                ;1*2\n\t"
    ::);
  } else {
    asm volatile (
      "  lsr r22                ;1*2 retVal>>TIME_SHIFT\n\t"
      "  ror r23                ;1*2\n\t"
      "  ror r24                ;1*2\n\t"
      "  ror r25                ;1*2\n\t"
    ::);
  }
  asm volatile (
    "  dec r26                  ;1*2 TIME_SHIFT counter--\n\t"
    "  brne .shift1             ;1+2\n\t"
//    "  subi r22,-2              ;1 retVal += 2[.25] mcsec for this routine\n\t"
//    "  sbci r23,-1              ;1\n\t"
//    "  sbci r24,-1              ;1\n\t"
//    "  sbci r25,-1              ;1\n\t"
    "  pop  r26                 ;1\n\t"
  ::);
}

/**
 * Return current time into milliseconds upto 49.7 days
 * corrected for timer counter current value and fract data
 * 102 bytes, long time: use udiv libc function!
 */
uint32_t time_millis()
{
    uint16_t    timer;
    uint8_t     oldSREG = SREG, tov=0;

    cli();
      timer = timerCount(TIME_DEFAULT);
      if ( timerIFlag(TIME_DEFAULT,OVF) ){ tov++; }
    SREG = oldSREG;

    timer = (TIME_TICK_MCS>1 ? timer<<TIME_SHIFT : timer>>TIME_SHIFT);
    return (timer0_overflow_count * TIME_MCS2MS)+tov+(timer>1000? 1 : 0);
}

/**
 * identical with wiring.c
 * @deprecated: big parameter (uint32_t) @see time_delay16()
 */
void time_delay(uint32_t interval)
{
    uint16_t start = (uint16_t)micros();

    while (interval > 0) {
      if (((uint16_t)micros() - start) >= 1000) {
        interval--;
        start += 1000;
      }
    }
}

/**
 * for smaller parameter size: only 65535 milli seconds
 * 52 bytes.
 */
void time_delay16(uint16_t interval)
{
    uint16_t start = (uint16_t)micros();

    while (interval > 0) {
      if (((uint16_t)micros() - start) >= 1000) {
        interval--;
        start += 1000;
      }
    }
}

/**
 * (re)start timer for time functions
 * @see TIME_DEFAULT define section
 * 26 bytes
 */
void time_init()
{
    sei();
    timerControl(TIME_DEFAULT, A) |= TIME_MODE;
    timerControl(TIME_DEFAULT, B) |= prescalerMode(TIME_PRESCALLER);
    timerIMask(TIME_DEFAULT, OVF, 1);
}

/**
 * Simple function for calc time and delays
 * 
 * @author Arhat109: arhat109@mail.ru
 */

/** Input multiplexer channels (@deprecated: not need more!) */
#define ADMUX_0		0	/* from Analog0 */
#define ADMUX_1		1	/* from Analog1 */
#define ADMUX_2		2	/* from Analog2 */
#define ADMUX_3		3	/* from Analog3 */
#define ADMUX_4		4	/* from Analog4 */
#define ADMUX_5		5	/* from Analog5 */
#define ADMUX_6		6	/* from Analog6 */
#define ADMUX_7		7	/* from Analog7 */
#define ADMUX_8		32	/* from Analog8 */
#define ADMUX_9		33	/* from Analog9 */
#define ADMUX_10	34	/* from Analog10 */
#define ADMUX_11	35	/* from Analog11 */
#define ADMUX_12	36	/* from Analog12 */
#define ADMUX_13	37	/* from Analog13 */
#define ADMUX_14	38	/* from Analog14 */
#define ADMUX_15	39	/* from Analog15 */
#define ADMUX_M10_a0a0		8
#define ADMUX_M10_a0a1		9
#define ADMUX_M200_a0a0		10
#define ADMUX_M200_a0a1		11
#define ADMUX_M10_a2a2		12
#define ADMUX_M10_a2a3		13
#define ADMUX_M200_a2a2		14
#define ADMUX_M200_a2a3		15
#define ADMUX_M10_a8a8		40
#define ADMUX_M10_a8a9		41
#define ADMUX_M200_a8a8		42
#define ADMUX_M200_a8a9		43
#define ADMUX_M10_a10a10	44
#define ADMUX_M10_a10a11	45
#define ADMUX_M200_a10a10	46
#define ADMUX_M200_a10a11	47
#define ADMUX_M1_a1a0		16
#define ADMUX_M1_a1a1		17
#define ADMUX_M1_a1a2		18
#define ADMUX_M1_a1a3		19
#define ADMUX_M1_a1a4		20
#define ADMUX_M1_a1a5		21
#define ADMUX_M1_a1a6		22
#define ADMUX_M1_a1a7		23
#define ADMUX_M1_a2a0		24
#define ADMUX_M1_a2a1		25
#define ADMUX_M1_a2a2		26
#define ADMUX_M1_a2a3		27
#define ADMUX_M1_a2a4		28
#define ADMUX_M1_a2a5		29
#define ADMUX_M1_a9a8		48
#define ADMUX_M1_a9a9		49
#define ADMUX_M1_a9a10		50
#define ADMUX_M1_a9a11		51
#define ADMUX_M1_a9a12		52
#define ADMUX_M1_a9a13		53
#define ADMUX_M1_a9a14		54
#define ADMUX_M1_a9a15		55
#define ADMUX_M1_a10a8		56
#define ADMUX_M1_a10a9		57
#define ADMUX_M1_a10a10		58
#define ADMUX_M1_a10a11		59
#define ADMUX_M1_a10a12		60
#define ADMUX_M1_a10a13		61

/**
 * AnalogRead
 * ==========
 * 1. ADC clock [50..200]kHz. for F_CPU = 16Mhz ADC prescaler = 160(opt.): ADPS2:0 = 111 = F_CPU/128
 * 2. set in default mode: 1 channel, ADLAR=right,src=AVCC
 * 
 * 3. !!! before use it must be adcOn() with delay=108micros !!!
 */
uint16_t adc_read(uint8_t anPin)
{
//  uint8_t    oreg, anh;

  admux1Channel(admuxSrc(AVCC), anPin, ADC_RIGHT);      // set registers: ADMUX, ADCSRB
  ADCSRA |= _BV(ADSC);                                  // start analog read
  while (ADCSRA & (1 << ADSC));                         // wait as ADC is done

//  oreg = SREG;
//  cli();
//    anPin = ADCL;
//    anh = ADCH;
//  SREG = oreg;
//  return (ADCH<<8) + ADCL;
  asm volatile (
    "in  __tmp_reg__, __SREG__\n\t"
    "cli\n\t"
    "lds r24,120    ; retL = ADCL\n\t"
    "lds r25,121    ; retH = ADCH\n\t"
    "out __SREG__,__tmp_reg__\n\t"
  ::);
}
