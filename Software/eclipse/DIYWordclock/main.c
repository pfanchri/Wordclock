/*
 * main.c
 *
 *  Created on: 18.01.2016
 *      Author: christofpfannenmuller
 */
#include <util/delay.h>
#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>

#include "light_ws2812.h"
#include "i2c_master.h"

#define t_alarm //TODO: Einf�gen der Pins f�r die Taster
#define t_up
#define t_down
#define t_snooze
#define t_mode



struct cRGB matrix[110];
uint8_t stunden==1; //1...12
uint8_t minuten==0; //0...59
uint8_t frontplatte=0; //Art der Frontplatte; 0:Standartfrontplatte; 1:Bin�re Frontplatte; 2:Englische Frontplatte; ...

void setalarm(void){
	//get alarm time from user


	//send alarm time to RTC
}

void settime(void){

	//get time from user


	//send time to RTC

}

void showtime(uint8_t hours_to_show, uint8_t minutes_to_show){
	if(frontplatte==0){

	}else if(frontplatte==1){
		//Zeitanzeige f�r Bin�re Frontplatte
	}else if(frontplatte==2){
		//Zeitanzeige f�r Englische Frontplatte
	}
}

void change_frontplatte(uint8_t new_frontplatte){
	frontplatte=new_frontplatte;
}

int main(void){
	//itialisierung


	settime();//get time from user


	//


	while(1){//Dauerablauf



	}
}
