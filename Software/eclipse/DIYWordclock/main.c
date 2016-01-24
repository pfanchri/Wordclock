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
#define V_ON 150  //Wert f�r LED on 0...255



struct cRGB matrix[110];
uint8_t stunden=1; //aktueller Stundenwert  1...12
uint8_t minuten=0; //aktueller Minutenwert  0...59
uint8_t frontplatte=0; //Art der Frontplatte; 0:Standartfrontplatte; 1:Bin�re Frontplatte; 2:Englische Frontplatte; ...

void setalarm(void){
	//get alarm time from user


	//send alarm time to RTC
}

void settime(void){

	//get time from user Zeit


	//send time to RTC

}

void showtime(uint8_t hours_to_show, uint8_t minutes_to_show){
	if(frontplatte==0){
		//Zeitanzeige f�r Standart Frontplatte
		//Minutenleds
		PORTB |= (1<<PB5);PORTB |= (1<<PB4);PORTB |= (1<<PB3);PORTB |= (1<<PB1);//alle Minutenleds off
			switch(minutes_to_show%5) {//setzen entsprechende Minuten auf GND
				case 1: PORTB &=~ (1<<PB4); break;
				case 2: PORTB &=~ (1<<PB4)^(1<<PB3); break;
				case 3: PORTB &=~ (1<<PB4)^(1<<PB3)^(1<<PB1); break;
				case 4: PORTB &=~ (1<<PB4)^(1<<PB3)^(1<<PB1)^(1<<PB5); break;
			}
			//Ansteuerung der Matrix
			/*
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
			matrix[0].r=V_ON;matrix[0].g=V_ON;matrix[0].b=V_ON;
			matrix[1].r=V_ON;matrix[1].g=V_ON;matrix[1].b=V_ON;
			matrix[3].r=V_ON;matrix[3].g=V_ON;matrix[3].b=V_ON;
			matrix[4].r=V_ON;matrix[4].g=V_ON;matrix[4].b=V_ON;
			matrix[5].r=V_ON;matrix[5].g=V_ON;matrix[5].b=V_ON;






	}else if(frontplatte==1){
		//Zeitanzeige f�r Bin�re Frontplatte
	}else if(frontplatte==2){
		//Zeitanzeige f�r Englische Frontplatte
	}
	ws2812_setleds(matrix,110);
}

void change_frontplatte(uint8_t new_frontplatte){
	frontplatte=new_frontplatte;
}

void init(void){
	//in outputs intit
	//minutenleds + alarmLed
	//setze bit 1 =Ausgang
		DDRB |= (1<<1);
		DDRB |= (1<<3);
		DDRB |= (1<<4);
		DDRB |= (1<<5);
		DDRC |= (1<<3);//AlarmLED
		// setze pin auf vdd = LED aus
		PORTB |= (1<<1);
		PORTB |= (1<<3);
		PORTB |= (1<<4);
		PORTB |= (1<<5);
		PORTC |= (1<<3);//AlarmLED

		//Buzzer als Ausgang setzen und auf +5V schalten = ausgeschaltet
		DDRB |= (1<<2);
		PORTB |= (1<<2);

}

int main(void){
	//itialisierung
	init();
	//settime();//get time from user
	//setalarm();



	while(1){
		_delay_ms(1000);
		PORTB |= (1<<PB3);
		PORTB |= (1<<PB2);
		_delay_ms(1000);
		PORTB &= ~ (1<<PB3);
		PORTB &= ~ (1<<PB2);

	}



	while(1){//Dauerablauf
		showtime(stunden, minuten);

		//Uhrzeit erh�hen testweise
		_delay_ms(1000);
		minuten++;
		if(minuten>=60){minuten=0;stunden++;}
		if(stunden>=13){stunden=1;}
		//ende Uhrzeit Testweise erh�hen

	}
}
