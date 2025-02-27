/*
 * main.c
 *
 *  Created on: 18.01.2016
 *      Author: christofpfannenmuller
 */
#include "test.h"
#include <util/delay.h>
#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>

#include "light_ws2812.h"
//Icludes von DS1307
#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "uart/uart.h"
#define UART_BAUD_RATE 2400
#include "ds1307/ds1307.h"

#define t_alarm 		//TODO: Einf�gen der Pins f�r die Taster
#define t_up
#define t_down
#define t_snooze
#define t_mode
#define V_ON_B 30  		//Wert f�r LED on 0...255
#define V_ON_G 30  		//Wert f�r LED on 0...255
#define V_ON_R 30  		//Wert f�r LED on 0...255

struct cRGB matrix[111];//eines l�nger als eigentlich damit besser beleuchtet bei letzter
uint8_t frontplatte = 0; //Art der Frontplatte; 0:Standartfrontplatte; 1:Bin�re Frontplatte; 2:Englische Frontplatte; ...
uint8_t matrix_on = 1; //TODO: evlt mit anderen zu einer Statusvariable zusammenf�gen

uint16_t year = 2016;
uint8_t month = 1;
uint8_t day = 0;
uint8_t hour = 1;//aktueller hourwert  1...12
uint8_t minute = 0;//aktueller minutewert  0...59
uint8_t second = 0;

ISR(INT1_vect)
    {
    //TODO: weiter int Vektoren einf�gen; auch f�r PCint
    }

void setalarm(void)
    {
    //get alarm time from user

    //send alarm time to RTC
    }

void all_on(uint8_t prozent_rot, uint8_t prozent_blau, uint8_t prozent_gruen)
    {
    PORTC &= ~(1 << 1);
    while (0)
	{
	for (uint8_t i = 0; i <= 110; i++)
	    {
	    matrix[i].r = prozent_rot;
	    matrix[i].g = prozent_gruen;
	    matrix[i].b = prozent_blau;
	    }
	ws2812_setleds(matrix, 110);
	_delay_ms(1000);
	_delay_ms(1000);
	_delay_ms(1000);
	_delay_ms(1000);
	_delay_ms(1000);
	}
    }
void lauflicht(void)
    {
    PORTC &= ~(1 << 1);
    uint8_t i = 0;
    uint8_t j = 37;
    uint8_t k = 73;
    while (1)
	{
	matrix[i].r = 30;
	matrix[j].g = 30;
	matrix[k].b = 30;
	ws2812_setleds(matrix, 110);
	matrix[i].r = 0;
	matrix[j].g = 0;
	matrix[k].b = 0;
	i++;
	j++;
	k++;
	if (i >= 110)
	    {
	    i = 0;
	    }
	if (j >= 110)
	    {
	    j = 0;
	    }
	if (k >= 110)
	    {
	    k = 0;
	    }
	_delay_ms(100);

	}
    }

void settime(void)
    {

    //get time from user

    //send time to RTC
    ds1307_setdate(year, month, day, hour, minute, 0);

    }

void showtime(uint8_t hours_to_show, uint8_t minutes_to_show)
    {

    //beginn der Frontplattenansteuerung
    if (frontplatte == 0)
	{
	//Zeitanzeige f�r Standart Frontplatte
	//Minutenleds
	PORTB |= (1 << PB5);
	PORTB |= (1 << PB4);
	PORTB |= (1 << PB3);
	PORTB |= (1 << PB1);		//alle Minutenleds off
	switch (minutes_to_show % 5)
	    {		//setzen entsprechende Minuten auf GND = anschalten
	case 1:
	    PORTB &= ~(1 << PB4);
	    break;
	case 2:
	    PORTB &= ~(1 << PB4) ^ (1 << PB3);
	    break;
	case 3:
	    PORTB &= ~(1 << PB4) ^ (1 << PB3) ^ (1 << PB1);
	    break;
	case 4:
	    PORTB &= ~(1 << PB4) ^ (1 << PB3) ^ (1 << PB1) ^ (1 << PB5);
	    break;
	    }

	//Leeren des Arrays
	for (uint8_t i = 0; i < 111; i++)
	    {
	    matrix[i].r = 0;
	    matrix[i].g = 0;
	    matrix[i].b = 0;
	    }
	PORTC &= ~(1 << 1);				//Mosfet anschalten
	ws2812_setleds(matrix, 111);
	/*

	 //Ansteuerung der Matrix

	 Vorlage:
	 es ist ein uhr
	 es ist f�nf nach eins
	 es ist zehn nach eins
	 es ist viertel zwei
	 es ist zehn vor halb zwei
	 es ist f�nf vor halb zwei
	 es ist halb zwei
	 es ist f�nf nach halb zwei
	 es ist zehn nach halb zwei
	 es ist dreiviertel zwei
	 es ist zehn vor zwei
	 es ist f�nf vor zwei
	 */

	//ES IST anschalten
	matrix[0].r = V_ON_R;
	matrix[0].g = V_ON_G;
	matrix[0].b = V_ON_B;
	matrix[1].r = V_ON_R;
	matrix[1].g = V_ON_G;
	matrix[1].b = V_ON_B;
	matrix[3].r = V_ON_R;
	matrix[3].g = V_ON_G;
	matrix[3].b = V_ON_B;
	matrix[4].r = V_ON_R;
	matrix[4].g = V_ON_G;
	matrix[4].b = V_ON_B;//TODO: ES IST darf nur dann angezeigt werden wenn es das auch soll
	matrix[5].r = V_ON_R;
	matrix[5].g = V_ON_G;
	matrix[5].b = V_ON_B;

	//TODO: Anpassen an die aktuellen Ports
	//Minuten anschalten

	switch (((int) (minutes_to_show / 5)) * 5)
	    {
	case 0:	//x Uhr
	    matrix[107].r = V_ON_R;
	    matrix[107].g = V_ON_G;
	    matrix[107].b = V_ON_B;
	    matrix[108].r = V_ON_R;
	    matrix[108].g = V_ON_G;
	    matrix[108].b = V_ON_B;
	    matrix[109].r = V_ON_R;
	    matrix[109].g = V_ON_G;
	    matrix[109].b = V_ON_B;
	    break;

	case 5:	//5 nach x
	    matrix[7].r = V_ON_R;
	    matrix[7].g = V_ON_G;
	    matrix[7].b = V_ON_B;
	    matrix[8].r = V_ON_R;
	    matrix[8].g = V_ON_G;
	    matrix[8].b = V_ON_B;
	    matrix[9].r = V_ON_R;
	    matrix[9].g = V_ON_G;
	    matrix[9].b = V_ON_B;
	    matrix[10].r = V_ON_R;
	    matrix[10].g = V_ON_G;
	    matrix[10].b = V_ON_B;
	    matrix[40].r = V_ON_R;
	    matrix[40].g = V_ON_G;
	    matrix[40].b = V_ON_B;
	    matrix[41].r = V_ON_R;
	    matrix[41].g = V_ON_G;
	    matrix[41].b = V_ON_B;
	    matrix[42].r = V_ON_R;
	    matrix[42].g = V_ON_G;
	    matrix[42].b = V_ON_B;
	    matrix[43].r = V_ON_R;
	    matrix[43].g = V_ON_G;
	    matrix[43].b = V_ON_B;
	    break;

	case 10:	//10 nach x
	    matrix[11].r = V_ON_R;
	    matrix[11].g = V_ON_G;
	    matrix[11].b = V_ON_B;
	    matrix[12].r = V_ON_R;
	    matrix[12].g = V_ON_G;
	    matrix[12].b = V_ON_B;
	    matrix[13].r = V_ON_R;
	    matrix[13].g = V_ON_G;
	    matrix[13].b = V_ON_B;
	    matrix[14].r = V_ON_R;
	    matrix[14].g = V_ON_G;
	    matrix[14].b = V_ON_B;
	    matrix[40].r = V_ON_R;
	    matrix[40].g = V_ON_G;
	    matrix[40].b = V_ON_B;
	    matrix[41].r = V_ON_R;
	    matrix[41].g = V_ON_G;
	    matrix[41].b = V_ON_B;
	    matrix[42].r = V_ON_R;
	    matrix[42].g = V_ON_G;
	    matrix[42].b = V_ON_B;
	    matrix[43].r = V_ON_R;
	    matrix[43].g = V_ON_G;
	    matrix[43].b = V_ON_B;
	    break;

	case 15: //viertel x+1
	    matrix[26].r = V_ON_R;
	    matrix[26].g = V_ON_G;
	    matrix[26].b = V_ON_B;
	    matrix[27].r = V_ON_R;
	    matrix[27].g = V_ON_G;
	    matrix[27].b = V_ON_B;
	    matrix[28].r = V_ON_R;
	    matrix[28].g = V_ON_G;
	    matrix[28].b = V_ON_B;
	    matrix[29].r = V_ON_R;
	    matrix[29].g = V_ON_G;
	    matrix[29].b = V_ON_B;
	    matrix[30].r = V_ON_R;
	    matrix[30].g = V_ON_G;
	    matrix[30].b = V_ON_B;
	    matrix[31].r = V_ON_R;
	    matrix[31].g = V_ON_G;
	    matrix[31].b = V_ON_B;
	    hours_to_show++;
	    break;

	case 20: //zehn vor halb x+1
	    matrix[11].r = V_ON_R;
	    matrix[11].g = V_ON_G;
	    matrix[11].b = V_ON_B;
	    matrix[12].r = V_ON_R;
	    matrix[12].g = V_ON_G;
	    matrix[12].b = V_ON_B;
	    matrix[13].r = V_ON_R;
	    matrix[13].g = V_ON_G;
	    matrix[13].b = V_ON_B;
	    matrix[14].r = V_ON_R;
	    matrix[14].g = V_ON_G;
	    matrix[14].b = V_ON_B;
	    matrix[33].r = V_ON_R;
	    matrix[33].g = V_ON_G;
	    matrix[33].b = V_ON_B;
	    matrix[34].r = V_ON_R;
	    matrix[34].g = V_ON_G;
	    matrix[34].b = V_ON_B;
	    matrix[35].r = V_ON_R;
	    matrix[35].g = V_ON_G;
	    matrix[35].b = V_ON_B;
	    matrix[44].r = V_ON_R;
	    matrix[44].g = V_ON_G;
	    matrix[44].b = V_ON_B;
	    matrix[45].r = V_ON_R;
	    matrix[45].g = V_ON_G;
	    matrix[45].b = V_ON_B;
	    matrix[46].r = V_ON_R;
	    matrix[46].g = V_ON_G;
	    matrix[46].b = V_ON_B;
	    matrix[47].r = V_ON_R;
	    matrix[47].g = V_ON_G;
	    matrix[47].b = V_ON_B;
	    hours_to_show++;
	    break;

	case 25: //f�nf vor halb x+1
	    matrix[7].r = V_ON_R;
	    matrix[7].g = V_ON_G;
	    matrix[7].b = V_ON_B;
	    matrix[8].r = V_ON_R;
	    matrix[8].g = V_ON_G;
	    matrix[8].b = V_ON_B;
	    matrix[9].r = V_ON_R;
	    matrix[9].g = V_ON_G;
	    matrix[9].b = V_ON_B;
	    matrix[10].r = V_ON_R;
	    matrix[10].g = V_ON_G;
	    matrix[10].b = V_ON_B;
	    matrix[33].r = V_ON_R;
	    matrix[33].g = V_ON_G;
	    matrix[33].b = V_ON_B;
	    matrix[34].r = V_ON_R;
	    matrix[34].g = V_ON_G;
	    matrix[34].b = V_ON_B;
	    matrix[35].r = V_ON_R;
	    matrix[35].g = V_ON_G;
	    matrix[35].b = V_ON_B;
	    matrix[44].r = V_ON_R;
	    matrix[44].g = V_ON_G;
	    matrix[44].b = V_ON_B;
	    matrix[45].r = V_ON_R;
	    matrix[45].g = V_ON_G;
	    matrix[45].b = V_ON_B;
	    matrix[46].r = V_ON_R;
	    matrix[46].g = V_ON_G;
	    matrix[46].b = V_ON_B;
	    matrix[47].r = V_ON_R;
	    matrix[47].g = V_ON_G;
	    matrix[47].b = V_ON_B;
	    hours_to_show++;
	    break;

	case 30: //halb x+1
	    matrix[44].r = V_ON_R;
	    matrix[44].g = V_ON_G;
	    matrix[44].b = V_ON_B;
	    matrix[45].r = V_ON_R;
	    matrix[45].g = V_ON_G;
	    matrix[45].b = V_ON_B;
	    matrix[46].r = V_ON_R;
	    matrix[46].g = V_ON_G;
	    matrix[46].b = V_ON_B;
	    matrix[47].r = V_ON_R;
	    matrix[47].g = V_ON_G;
	    matrix[47].b = V_ON_B;
	    hours_to_show++;
	    break;

	case 35: //f�nf nach halb x+1
	    matrix[7].r = V_ON_R;
	    matrix[7].g = V_ON_G;
	    matrix[7].b = V_ON_B;
	    matrix[8].r = V_ON_R;
	    matrix[8].g = V_ON_G;
	    matrix[8].b = V_ON_B;
	    matrix[9].r = V_ON_R;
	    matrix[9].g = V_ON_G;
	    matrix[9].b = V_ON_B;
	    matrix[10].r = V_ON_R;
	    matrix[10].g = V_ON_G;
	    matrix[10].b = V_ON_B;
	    matrix[40].r = V_ON_R;
	    matrix[40].g = V_ON_G;
	    matrix[40].b = V_ON_B;
	    matrix[41].r = V_ON_R;
	    matrix[41].g = V_ON_G;
	    matrix[41].b = V_ON_B;
	    matrix[42].r = V_ON_R;
	    matrix[42].g = V_ON_G;
	    matrix[42].b = V_ON_B;
	    matrix[43].r = V_ON_R;
	    matrix[43].g = V_ON_G;
	    matrix[43].b = V_ON_B;
	    matrix[44].r = V_ON_R;
	    matrix[44].g = V_ON_G;
	    matrix[44].b = V_ON_B;
	    matrix[45].r = V_ON_R;
	    matrix[45].g = V_ON_G;
	    matrix[45].b = V_ON_B;
	    matrix[46].r = V_ON_R;
	    matrix[46].g = V_ON_G;
	    matrix[46].b = V_ON_B;
	    matrix[47].r = V_ON_R;
	    matrix[47].g = V_ON_G;
	    matrix[47].b = V_ON_B;
	    hours_to_show++;
	    break;

	case 40: //zehn nach halb x+1
	    matrix[11].r = V_ON_R;
	    matrix[11].g = V_ON_G;
	    matrix[11].b = V_ON_B;
	    matrix[12].r = V_ON_R;
	    matrix[12].g = V_ON_G;
	    matrix[12].b = V_ON_B;
	    matrix[13].r = V_ON_R;
	    matrix[13].g = V_ON_G;
	    matrix[13].b = V_ON_B;
	    matrix[14].r = V_ON_R;
	    matrix[14].g = V_ON_G;
	    matrix[14].b = V_ON_B;
	    matrix[40].r = V_ON_R;
	    matrix[40].g = V_ON_G;
	    matrix[40].b = V_ON_B;
	    matrix[41].r = V_ON_R;
	    matrix[41].g = V_ON_G;
	    matrix[41].b = V_ON_B;
	    matrix[42].r = V_ON_R;
	    matrix[42].g = V_ON_G;
	    matrix[42].b = V_ON_B;
	    matrix[43].r = V_ON_R;
	    matrix[43].g = V_ON_G;
	    matrix[43].b = V_ON_B;
	    matrix[44].r = V_ON_R;
	    matrix[44].g = V_ON_G;
	    matrix[44].b = V_ON_B;
	    matrix[45].r = V_ON_R;
	    matrix[45].g = V_ON_G;
	    matrix[45].b = V_ON_B;
	    matrix[46].r = V_ON_R;
	    matrix[46].g = V_ON_G;
	    matrix[46].b = V_ON_B;
	    matrix[47].r = V_ON_R;
	    matrix[47].g = V_ON_G;
	    matrix[47].b = V_ON_B;
	    hours_to_show++;
	    break;

	case 45: //dreiviertel x+1
	    matrix[22].r = V_ON_R;
	    matrix[22].g = V_ON_G;
	    matrix[22].b = V_ON_B;
	    matrix[23].r = V_ON_R;
	    matrix[23].g = V_ON_G;
	    matrix[23].b = V_ON_B;
	    matrix[24].r = V_ON_R;
	    matrix[24].g = V_ON_G;
	    matrix[24].b = V_ON_B;
	    matrix[25].r = V_ON_R;
	    matrix[25].g = V_ON_G;
	    matrix[25].b = V_ON_B;
	    matrix[26].r = V_ON_R;
	    matrix[26].g = V_ON_G;
	    matrix[26].b = V_ON_B;
	    matrix[27].r = V_ON_R;
	    matrix[27].g = V_ON_G;
	    matrix[27].b = V_ON_B;
	    matrix[28].r = V_ON_R;
	    matrix[28].g = V_ON_G;
	    matrix[28].b = V_ON_B;
	    matrix[29].r = V_ON_R;
	    matrix[29].g = V_ON_G;
	    matrix[29].b = V_ON_B;
	    matrix[30].r = V_ON_R;
	    matrix[30].g = V_ON_G;
	    matrix[30].b = V_ON_B;
	    matrix[31].r = V_ON_R;
	    matrix[31].g = V_ON_G;
	    matrix[31].b = V_ON_B;
	    hours_to_show++;
	    break;

	case 50: //zehn vor x+1
	    matrix[11].r = V_ON_R;
	    matrix[11].g = V_ON_G;
	    matrix[11].b = V_ON_B;
	    matrix[12].r = V_ON_R;
	    matrix[12].g = V_ON_G;
	    matrix[12].b = V_ON_B;
	    matrix[13].r = V_ON_R;
	    matrix[13].g = V_ON_G;
	    matrix[13].b = V_ON_B;
	    matrix[14].r = V_ON_R;
	    matrix[14].g = V_ON_G;
	    matrix[14].b = V_ON_B;
	    matrix[33].r = V_ON_R;
	    matrix[33].g = V_ON_G;
	    matrix[33].b = V_ON_B;
	    matrix[34].r = V_ON_R;
	    matrix[34].g = V_ON_G;
	    matrix[34].b = V_ON_B;
	    matrix[35].r = V_ON_R;
	    matrix[35].g = V_ON_G;
	    matrix[35].b = V_ON_B;
	    hours_to_show++;
	    break;

	case 55: //f�nf vor x+1
	    matrix[7].r = V_ON_R;
	    matrix[7].g = V_ON_G;
	    matrix[7].b = V_ON_B;
	    matrix[8].r = V_ON_R;
	    matrix[8].g = V_ON_G;
	    matrix[8].b = V_ON_B;
	    matrix[9].r = V_ON_R;
	    matrix[9].g = V_ON_G;
	    matrix[9].b = V_ON_B;
	    matrix[10].r = V_ON_R;
	    matrix[10].g = V_ON_G;
	    matrix[10].b = V_ON_B;
	    matrix[33].r = V_ON_R;
	    matrix[33].g = V_ON_G;
	    matrix[33].b = V_ON_B;
	    matrix[34].r = V_ON_R;
	    matrix[34].g = V_ON_G;
	    matrix[34].b = V_ON_B;
	    matrix[35].r = V_ON_R;
	    matrix[35].g = V_ON_G;
	    matrix[35].b = V_ON_B;
	    hours_to_show++;
	    break;

	    }

	if (hours_to_show >= 13)
	    {
	    hours_to_show = 1;
	    }
	switch (hours_to_show)
	    {
	case 1: //EINS
	    matrix[55].r = V_ON_R;
	    matrix[55].g = V_ON_G;
	    matrix[55].b = V_ON_B;
	    matrix[56].r = V_ON_R;
	    matrix[56].g = V_ON_G;
	    matrix[56].b = V_ON_B;
	    matrix[57].r = V_ON_R;
	    matrix[57].g = V_ON_G;
	    matrix[57].b = V_ON_B;
	    matrix[58].r = V_ON_R;
	    matrix[58].g = V_ON_G;
	    matrix[58].b = V_ON_B;
	    break;
	case 2: //ZWEI
	    matrix[62].r = V_ON_R;
	    matrix[62].g = V_ON_G;
	    matrix[62].b = V_ON_B;
	    matrix[63].r = V_ON_R;
	    matrix[63].g = V_ON_G;
	    matrix[63].b = V_ON_B;
	    matrix[64].r = V_ON_R;
	    matrix[64].g = V_ON_G;
	    matrix[64].b = V_ON_B;
	    matrix[65].r = V_ON_R;
	    matrix[65].g = V_ON_G;
	    matrix[65].b = V_ON_B;
	    break;
	case 3: //DREI
	    matrix[66].r = V_ON_R;
	    matrix[66].g = V_ON_G;
	    matrix[66].b = V_ON_B;
	    matrix[67].r = V_ON_R;
	    matrix[67].g = V_ON_G;
	    matrix[67].b = V_ON_B;
	    matrix[68].r = V_ON_R;
	    matrix[68].g = V_ON_G;
	    matrix[68].b = V_ON_B;
	    matrix[69].r = V_ON_R;
	    matrix[69].g = V_ON_G;
	    matrix[69].b = V_ON_B;
	    break;
	case 4: //VIER
	    matrix[73].r = V_ON_R;
	    matrix[73].g = V_ON_G;
	    matrix[73].b = V_ON_B;
	    matrix[74].r = V_ON_R;
	    matrix[74].g = V_ON_G;
	    matrix[74].b = V_ON_B;
	    matrix[75].r = V_ON_R;
	    matrix[75].g = V_ON_G;
	    matrix[75].b = V_ON_B;
	    matrix[76].r = V_ON_R;
	    matrix[76].g = V_ON_G;
	    matrix[76].b = V_ON_B;
	    break;
	case 5: //F�NF
	    matrix[51].r = V_ON_R;
	    matrix[51].g = V_ON_G;
	    matrix[51].b = V_ON_B;
	    matrix[52].r = V_ON_R;
	    matrix[52].g = V_ON_G;
	    matrix[52].b = V_ON_B;
	    matrix[53].r = V_ON_R;
	    matrix[53].g = V_ON_G;
	    matrix[53].b = V_ON_B;
	    matrix[54].r = V_ON_R;
	    matrix[54].g = V_ON_G;
	    matrix[54].b = V_ON_B;
	    break;
	case 6: //SECHS
	    matrix[77].r = V_ON_R;
	    matrix[77].g = V_ON_G;
	    matrix[77].b = V_ON_B;
	    matrix[78].r = V_ON_R;
	    matrix[78].g = V_ON_G;
	    matrix[78].b = V_ON_B;
	    matrix[79].r = V_ON_R;
	    matrix[79].g = V_ON_G;
	    matrix[79].b = V_ON_B;
	    matrix[80].r = V_ON_R;
	    matrix[80].g = V_ON_G;
	    matrix[80].b = V_ON_B;
	    matrix[81].r = V_ON_R;
	    matrix[81].g = V_ON_G;
	    matrix[81].b = V_ON_B;
	    break;
	case 7: //SIEBEN
	    matrix[88].r = V_ON_R;
	    matrix[88].g = V_ON_G;
	    matrix[88].b = V_ON_B;
	    matrix[89].r = V_ON_R;
	    matrix[89].g = V_ON_G;
	    matrix[89].b = V_ON_B;
	    matrix[90].r = V_ON_R;
	    matrix[90].g = V_ON_G;
	    matrix[90].b = V_ON_B;
	    matrix[91].r = V_ON_R;
	    matrix[91].g = V_ON_G;
	    matrix[91].b = V_ON_B;
	    matrix[92].r = V_ON_R;
	    matrix[92].g = V_ON_G;
	    matrix[92].b = V_ON_B;
	    matrix[93].r = V_ON_R;
	    matrix[93].g = V_ON_G;
	    matrix[93].b = V_ON_B;
	    break;
	case 8: //ACHT
	    matrix[84].r = V_ON_R;
	    matrix[84].g = V_ON_G;
	    matrix[84].b = V_ON_B;
	    matrix[85].r = V_ON_R;
	    matrix[85].g = V_ON_G;
	    matrix[85].b = V_ON_B;
	    matrix[86].r = V_ON_R;
	    matrix[86].g = V_ON_G;
	    matrix[86].b = V_ON_B;
	    matrix[87].r = V_ON_R;
	    matrix[87].g = V_ON_G;
	    matrix[87].b = V_ON_B;
	    break;
	case 9: //NEUN
	    matrix[102].r = V_ON_R;
	    matrix[102].g = V_ON_G;
	    matrix[102].b = V_ON_B;
	    matrix[103].r = V_ON_R;
	    matrix[103].g = V_ON_G;
	    matrix[103].b = V_ON_B;
	    matrix[104].r = V_ON_R;
	    matrix[104].g = V_ON_G;
	    matrix[104].b = V_ON_B;
	    matrix[105].r = V_ON_R;
	    matrix[105].g = V_ON_G;
	    matrix[105].b = V_ON_B;
	    break;
	case 10: //ZEHN
	    matrix[99].r = V_ON_R;
	    matrix[99].g = V_ON_G;
	    matrix[99].b = V_ON_B;
	    matrix[100].r = V_ON_R;
	    matrix[100].g = V_ON_G;
	    matrix[100].b = V_ON_B;
	    matrix[101].r = V_ON_R;
	    matrix[101].g = V_ON_G;
	    matrix[101].b = V_ON_B;
	    matrix[102].r = V_ON_R;
	    matrix[102].g = V_ON_G;
	    matrix[102].b = V_ON_B;
	    break;
	case 11: //ELF
	    matrix[49].r = V_ON_R;
	    matrix[49].g = V_ON_G;
	    matrix[49].b = V_ON_B;
	    matrix[50].r = V_ON_R;
	    matrix[50].g = V_ON_G;
	    matrix[50].b = V_ON_B;
	    matrix[51].r = V_ON_R;
	    matrix[51].g = V_ON_G;
	    matrix[51].b = V_ON_B;
	    break;
	case 12: //ZW�LF
	    matrix[94].r = V_ON_R;
	    matrix[94].g = V_ON_G;
	    matrix[94].b = V_ON_B;
	    matrix[95].r = V_ON_R;
	    matrix[95].g = V_ON_G;
	    matrix[95].b = V_ON_B;
	    matrix[96].r = V_ON_R;
	    matrix[96].g = V_ON_G;
	    matrix[96].b = V_ON_B;
	    matrix[97].r = V_ON_R;
	    matrix[97].g = V_ON_G;
	    matrix[97].b = V_ON_B;
	    matrix[98].r = V_ON_R;
	    matrix[98].g = V_ON_G;
	    matrix[98].b = V_ON_B;
	    break;
	    }
	//Sonderf�lle:
	if (hours_to_show == 1 && minutes_to_show < 5) //S von einS ausschalten bei "ein Uhr"
	    {
	    matrix[58].r = 0;
	    matrix[58].g = 0;
	    matrix[58].b = 0;
	    }
	}
    else if (frontplatte == 1)
	{
	//Zeitanzeige f�r Bin�re Frontplatte
	}
    else if (frontplatte == 2)
	{
	//Zeitanzeige f�r Englische Frontplatte
	}
    //Ende der Frontplattenansteuerung

    if (matrix_on)
	{
	PORTC &= ~(1 << 1);				//Mosfet anschalten
	ws2812_setleds(matrix, 111);
	}
    else
	{
	PORTC |= (1 << 1);				//Mosfet ausschalten
	}
    }

void change_frontplatte(uint8_t new_frontplatte)
    {
    frontplatte = new_frontplatte;
    }

void init(void)
    {
    //in outputs intit
    //minutenleds + alarmLed
    //setze bit 1 =Ausgang
    DDRB |= (1 << 1);
    DDRB |= (1 << 3);
    DDRB |= (1 << 4);
    DDRB |= (1 << 5);
    DDRC |= (1 << 3);	//AlarmLED
    // setze pin auf vdd = LED aus
    PORTB |= (1 << 1);
    PORTB |= (1 << 3);
    PORTB |= (1 << 4);
    PORTB |= (1 << 5);
    PORTC |= (1 << 3);		//AlarmLED

    //Buzzer als Ausgang setzen und auf +5V schalten = ausgeschaltet
    DDRB |= (1 << 2);
    PORTB |= (1 << 2);
    //Mosfet als Ausgang und ausschalten
    DDRC |= (1 << 1);
    PORTC |= (1 << 1);

    //Matrix leeren
    PORTC &= ~(1 << 1);					//Mosfet anschalten
    for (uint8_t i = 0; i <= 111; i++)
	{
	matrix[i].r = 0;
	matrix[i].g = 0;//TODO: evtl den gesamten BLock nach vorne verschieben
	matrix[i].b = 0; //War geplant damit am anfang erst einmal dunkel
	}
    ws2812_setleds(matrix, 111);
    PORTC |= (1 << 1);
    //init ds1307
    ds1307_init();
    }

int main(void)
    {
    //itialisierung
    init();

    //settime();//get time from user
    //setalarm();



	//get date
	ds1307_getdate(&year, &month, &day, &hour, &minute, &second);


	_delay_ms(1000);
	_delay_ms(1000);//hier war ich -----------
	_delay_ms(1000);
	while (1)
	    {
	    }



    while (1)
	{	//Dauerablauf

	showtime(hour, minute);

	//Uhrzeit erh�hen testweise
	_delay_ms(1000);
	minute++;
	if (minute >= 60)
	    {
	    minute = 0;
	    hour++;
	    }
	if (hour >= 13)
	    {
	    hour = 1;
	    }
	//ende Uhrzeit Testweise erh�hen

	}
    }
