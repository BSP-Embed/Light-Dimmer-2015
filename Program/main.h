#ifndef MAIN_H
#define MAIN_H

#include <htc.h>
#include "delay.h"
#include "lcd.h"

//DEFINE CONSTANT
#define _XTAL_FREQ	16000000
#define PRESSED         0
#define HIGH            1
#define LOW             0
#define TRUE            1

//DEFINE CONFIGURATION MACROS
__CONFIG (0x2F0A);


//DEFINE TYPES
typedef unsigned char int8u;
typedef signed char int8s;
typedef unsigned short int16u;

//PORT/PIN DEFINITION
#define LOAD_PIN        RB1
#define START_SW        RD0
#define SPEED_SW        RD1

//MACROS
#define ppt_off()   SD_PIN = LOW; PPTLED_PIN = LOW
#define ppt_on()    SD_PIN = HIGH; PPTLED_PIN = HIGH

#define LoadOn()    LOAD_PIN = HIGH
#define LoadOff()   LOAD_PIN = LOW

#define ind_batt(x) BLED_PIN = x



//FUNCTION PROTOTYPES
void init           (void);
void disp_title     (void);
void init_pwm       (void);
void update_dtcyc   (int8s duty_cycle);
void tmr1init       (void);
void initGPIO       (void);
void update_param   (void);
void meas_sp_param  (void);
void meas_batt_param(void);
void cal_gain       (int16u curr_watts);

#endif