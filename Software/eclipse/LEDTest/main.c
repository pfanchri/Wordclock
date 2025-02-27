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

#define t_alarm //TODO: Einf�gen der Pins f�r die Taster
#define t_up
#define t_down
#define t_snooze
#define t_mode
#define V_ON_B 0  //Wert f�r LED on 0...255
#define V_ON_G 30  //Wert f�r LED on 0...255
#define V_ON_R 0  //Wert f�r LED on 0...255



struct cRGB matrix[10];
uint8_t stunden=1; //aktueller Stundenwert  1...12
uint8_t minuten=0; //aktueller Minutenwert  0...59
uint8_t frontplatte=0; //Art der Frontplatte; 0:Standartfrontplatte; 1:Bin�re Frontplatte; 2:Englische Frontplatte; ...
uint8_t matrix_on=1;

void setalarm(void){
	//get alarm time from user


	//send alarm time to RTC
}

void settime(void){

	//get time from user Zeit


	//send time to RTC

}

void showtime(uint8_t hours_to_show, uint8_t minutes_to_show){

	//beginn der Frontplattenansteuerung
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





		/*
		//Leeren des Arrays
		for(uint8_t i=0; i<=110; i++){
			matrix[i].r=0;matrix[i].g=0;matrix[i].b=0;
		}
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
		matrix[0].r=V_ON_R;matrix[0].g=V_ON_G;matrix[0].b=V_ON_B;
		matrix[1].r=V_ON_R;matrix[1].g=V_ON_G;matrix[1].b=V_ON_B;
		matrix[3].r=V_ON_R;matrix[3].g=V_ON_G;matrix[3].b=V_ON_B;
		matrix[4].r=V_ON_R;matrix[4].g=V_ON_G;matrix[4].b=V_ON_B;//TODO: ES IST darf nur dann angezeigt werden wenn es das auch soll
		matrix[5].r=V_ON_R;matrix[5].g=V_ON_G;matrix[5].b=V_ON_B;

		//TODO: Anpassen an die aktuellen Ports
		//Minuten anschalten

/*


			switch(((int) (minutes_to_show/5))*5) {
				case 0:PORTD|= (1<<7) ; break;  //x Uhr
				case 5:PORTB|= (1<<1);PORTB|= (1<<7); break; 										//5 nach x
				case 10:PORTB|= (1<<3);PORTB|= (1<<7) ; break; 										//10 nach x
				case 15:PORTB|= (1<<6); hours_to_show++ ; break;      								//viertel x+1
				case 20:PORTB|= (1<<3); PORTA|= (1<<0); PORTA|= (1<<1);hours_to_show++ ; break; 	//zehn vor halb x+1
				case 25:PORTB|= (1<<1); PORTA|= (1<<0); PORTA|= (1<<1);hours_to_show++  ; break;	//f�nf vor halb x+1
				case 30:PORTA|= (1<<1);hours_to_show++  ; break; 									//halb x+1
				case 35:PORTB|= (1<<1); PORTB|= (1<<7); PORTA|= (1<<1);hours_to_show++  ; break; 	//f�nf nach halb x+1
				case 40:PORTB|= (1<<3); PORTB|= (1<<7); PORTA|= (1<<1);hours_to_show++  ; break; 	//f�nf nach halb x+1
				case 45:PORTB|= (1<<5); PORTB|= (1<<6);hours_to_show++ ; break; 					//dreiviertel x+1
				case 50:PORTB|= (1<<3); PORTA|= (1<<0);hours_to_show++ ; break; 					//zehn vor x+1
				case 55:PORTB|= (1<<1); PORTA|= (1<<0);hours_to_show++ ; break; 					//f�nf vor x+1
			}
			if (hours_to_show>=13){hours_to_show=1;}
			switch (hours_to_show){
				case 1:	PORTA|= (1<<4);PORTA|= (1<<5);PORTA|= (1<<6);break; 						//EINS
				case 2: PORTA|= (1<<3);PORTA|= (1<<4);break;  										//ZWEI
				case 3: PORTC|= (1<<7);break; 														//DREI
				case 4: PORTC|= (1<<3);break; 														//VIER
				case 5: PORTC|= (1<<6);break; 														//F�NF
				case 6: PORTC|= (1<<0);break; 														//SECHS
				case 7: PORTA|= (1<<6);PORTA|= (1<<7);break;  										//SIEBEN
				case 8: PORTC|= (1<<2);break;														//ACHT
				case 9: PORTC|= (1<<4);break;														//NEUN
				case 10: PORTC|= (1<<1);break;														//ZEHN
				case 11: PORTC|= (1<<5);break;														//ELF
				case 12: PORTA|= (1<<2);break;														//ZW�LF
			}



			*/


	}else if(frontplatte==1){
		//Zeitanzeige f�r Bin�re Frontplatte
	}else if(frontplatte==2){
		//Zeitanzeige f�r Englische Frontplatte
	}
	//Ende der Frontplattenansteuerung

	if(matrix_on){
		PORTC &= ~ (1<<1);							//TODO:Mosfet anschalten

		ws2812_setleds(matrix,10);

		}else{
									//TODO:Mosfet ausschalten
		}
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

	//mosefet leitet: // ------------------------------------------hier war ich
		//DDRC |= (1<<1);
		//PORTC |= (1<<1);

/*
	while(1){
		_delay_ms(1000);
		PORTB |= (1<<PB3);
		PORTB |= (1<<PB2);
		_delay_ms(1000);
		PORTB &= ~ (1<<PB3);
		PORTB &= ~ (1<<PB2);

	}
*/


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
