/*
  drmLib.h - Utility Library for drm 
  To use put #include <drmLib.h> in your source code
  Created by drm 20151213
  V1.0 --> First with EEPROM access and start print
  V2.0 --> adding RTC access
  V2.1 --> ifdef(ing) for M0 cases
  V2.2 --> more on SAM serialno
  V2.3 --> adding message types (for radio RH_RFMESH)
*/
#ifndef drmLib_h
#define drmLib_h
#define drmLibVer "drmLib V2.2 -- 20160902"


#if !defined(ARDUINO_ARCH_SAM) && !defined(ARDUINO_ARCH_SAMD) && !defined(ESP8266) && !defined(ARDUINO_ARCH_STM32F2)
  #include <avr/sleep.h> // AVR sleep modes (power saving)
  #include <avr/power.h> // AVR power states
  #include <avr/wdt.h>   // AVR watch dog timer
  #include <util/delay.h>
  #include <EEPROM.h>    // AVR on chip EEPROM 
#endif

#ifdef ESP8266
  #include <EEPROM.h>    // AVR on chip EEPROM 
#endif


#include "Arduino.h"
#include <Wire.h>      // I2C and SPI
#include <SPI.h>
#include <TM1637Display.h> // 4 digit 7 seg display

// Doug's Data structures, constants and enums
#define ER_BADID -20 // bad ID on requested operation
#define ER_BADOPEN -21 // error opening file
#define ER_UNEXPFIO -22 // unexpected result with file IO
#define ST_AOK 0	// Everything is good
#define ST_NOERR 1	// No error occured
#define ST_NOOP 2	// Nothing happened
#define ER_ERR -1 // generic error
#define ER_UNK -1001 // unknown error 

// Logic constants
#define FALSE 1!=1
#define TRUE 1==1

// LED pin
#define LED LED_BUILTIN

#define MAX_LINE 180    // Max line buffer length
#define NUMRTCREGS 19   // numbmer of registers on the DS3231 RTC
#define BAT_AVG_CNT 10  // numbers of times to average battery V
#define SAMM0_BATT A7 // GPIO #9 A7 is battery voltage divider level

/* Define the message types used for radio messages (and serial)
 */
#define ty_M 0
#define ty_DHT_F 1
#define ty_DHT_C 2
#define ty_DATE 10
#define ty_TIME 11
#define ty_DATETIME 12
#define ty_ALARM 50
#define ty_DIAG 200
// Extended message types
#define ty_LONG 255
#define ty_CONT 256
#define ty_IMAGE 1001
#define ty_SOUND 1002
#define ty_VIDEO 1003

/* Can't do the struct thing in Arduino for some reason
 *
enum rtc_type 
{
	DS3231,
	OTHER
}
 */

/*
typedef struct parseTime {
  unsigned long lsec;
  long tempf; // F temperature * 100 (poor mans float)
  int int_year;
  byte seconds;
  byte minutes;
  byte hours;
  byte dow;
  byte dom;
  byte month;
  byte year;
  byte csr;
  byte sr;
};
struct parseTime time_struct[1];
 */

// Routines in this Library
int drmBcd2Dec(int inbyte);
unsigned short drmSerialNo();
char * drmSAMSerialNo(char *outbuf, int buflen); // New 20160902
void drmStartPrint(const char *drmversion);
void drmPrtLead0(long in, int places);
void printTime(unsigned long milli_time);

/* Save the RTC for later
int initRTC(rtc_type type);
struct parseTime readRTC(rtc_type type);
void readClock(byte *readBytes);
struct parseTime decodeTime(byte *readBytes);
*/

#endif
