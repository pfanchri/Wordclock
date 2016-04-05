/*
ds1307 lib 0x01

copyright (c) Davide Gironi, 2013

Released under GPLv3.
Please refer to LICENSE file for licensing information.

References: parts of the code taken from https://github.com/adafruit/RTClib
*/


#ifndef DS1307_H
#define DS1307_H

//definitions
#define DS1307_ADDR (0x68<<1) //device address

//path to i2c fleury lib
#define DS1307_I2CFLEURYPATH "../i2chw/i2cmaster.h" //define the path to i2c fleury lib
#define DS1307_I2CINIT 1 //init i2c

//functions
extern void ds1307_init();
extern uint8_t ds1307_setdate(uint8_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second);
extern void ds1307_getdate(uint8_t *year, uint8_t *month, uint8_t *day, uint8_t *hour, uint8_t *minute, uint8_t *second);

//added for Support for ds1337
extern uint8_t ds1307_setalarm1( uint8_t dayofweek, uint8_t hour, uint8_t minute, uint8_t second);
extern void ds1307_getalarm1( uint8_t *day, uint8_t *hour, uint8_t *minute, uint8_t *second);
extern uint8_t ds1307_setalarm2( uint8_t day, uint8_t hour, uint8_t minute);
extern void ds1307_getalarm2( uint8_t *day, uint8_t *hour, uint8_t *minute);
//TODO:einstellen der anderen Register z.b.Status etc am/pm
//TODO: alarm when day fits or when day of week fits??


#endif

