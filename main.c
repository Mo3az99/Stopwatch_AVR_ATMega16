#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "amraya.h"

/*FUCK SOCIETY */
/*FUCK SOCIETY */
/*FUCK SOCIETY */

short seconds = 0;
short minutes = 0;
short hours = 0 ;
short temp = 0 ;

int main(void)
{
    SREG  |= (1<<7);   // Enable global interrupts in MC. (WA5DO COPY AH ^^)
	INT0_init();
	INT1_init();
	INT2_init();
	PORTC_init();
	PORTA_init();
	TIMER1_init();


	while(1){
		_delay_ms(5);
		show_right_seconds();
		_delay_ms(5);
		show_seconds();
		_delay_ms(5);
		show_minutes();
		_delay_ms(5);
		show_right_minutes();
		_delay_ms(5);
		show_hours();
		_delay_ms(5);
		show_right_hours();
	}
}
ISR(INT0_vect){
	seconds = 0;
	minutes = 0;
	hours = 0 ;

}
ISR(INT1_vect){
    TCCR1B &= ~(1<<CS10);
    TCCR1B &= ~(1<<CS12) ;


}
ISR(INT2_vect){
	 TCCR1B |= (1<<CS10);
	 TCCR1B |= (1<<CS12) ;

}
ISR(TIMER1_COMPA_vect){
	seconds++;
	if (seconds  == 60){
		seconds = 0;
		minutes++;
	}
	if (minutes == 60){
		minutes = 0;
		hours++;
	}
	if (hours == 24){
		hours = 0;
	}
}

void show_right_seconds(void){
	PORTA = 0X40;
	if (seconds <10){
			//enable first 7-segment
			//temp = seconds%10;
			PORTC = (PORTC & 0xF0) | (seconds & 0x0F);
	}else{
			//enable first 7-segment
			temp = seconds%10;
			PORTC = (PORTC & 0xF0) | (temp & 0x0F);
		}
}

void show_seconds(void){
//here we will print the time of the seconds every 5 ms
	PORTA = 0X20;

	if (seconds <10){
		//enable second 7-segment
		//temp = seconds%10;
		PORTC = (PORTC & 0xF0) | (0 & 0x0F);
	}else{
		//enable second 7-segment
		temp = seconds/10;
		PORTC = (PORTC & 0xF0) | (temp & 0x0F);
	}
}
void show_right_minutes(void){
//here we will print the time of the seconds every 5 ms
	PORTA = 0X10;

	if (minutes<10){
		//enable first 7-segment
		//temp = minutes%10;
		PORTC = (PORTC & 0xF0) | (minutes & 0x0F);
	}else{
		//enable second 7-segment
		temp = minutes%10;
		PORTC = (PORTC & 0xF0) | (temp & 0x0F);
	}
}
void show_minutes(void){
//here we will print the time of the seconds every 5 ms
	PORTA = 0X08;

	if (minutes<10){
		//enable first 7-segment
		//temp = minutes%10;
		PORTC = (PORTC & 0xF0) | (0 & 0x0F);
	}else{
		//enable second 7-segment
		temp = minutes/10;
		PORTC = (PORTC & 0xF0) | (temp & 0x0F);
	}
}
void show_right_hours(void){
//here we will print the time of the seconds every 5 ms
	PORTA = 0X04;
	if (hours <10){
		//enable first 7-segment
		//temp = hours%10;
		PORTC = (PORTC & 0xF0) | (hours & 0x0F);
	}else{
		//enable second 7-segment
		temp = hours%10;
		PORTC = (PORTC & 0xF0) | (temp & 0x0F);
	}
}
void show_hours(void){
//here we will print the time of the seconds every 5 ms
	PORTA = 0X02;
	if (hours <10){
		//enable first 7-segment
		//temp = hours%10;
		PORTC = (PORTC & 0xF0) | (0 & 0x0F);
	}else{
		//enable second 7-segment
		temp = hours/10;
		PORTC = (PORTC & 0xF0) | (temp & 0x0F);
	}
}

void INT0_init(void){

    DDRD &= (~(1<<PD2));   // set pd2 to input
    PORTD |= (1<<PD2) ;   // set pd2 to pull up mode
    GICR |= (1<<INT0);    // enable int 0

    // set int 0 to falling edge
    MCUCR |= (1<<ISC01);
    MCUCR &= (~(1<<ISC00));

}

void INT1_init(void){

    DDRD &= (~(1<<PD3)); // set pd3 to input
    GICR |= (1<<INT1);  // enable int 1
    MCUCR |= (1<<ISC11) | (1<<ISC10); // set int 1 to rising edge
}

void INT2_init(void){

    DDRB &= (~(1<<PB2));  // set pb2 to input
    PORTB |= (1<<PB2) ;   // set pb2 to pull up mode
    GICR |= (1<<INT2);    // enable int 2
    MCUCSR &= (~(1<<ISC2));  // set int 2 to falling edge

}

void PORTC_init(void){

    DDRC |= 0x0F; // SET FIRST FOUR PINS IN PORT C TO OUTPUT PINS

}

void PORTA_init(void){

    DDRA |= 0x7E; // SET (1 -> 6) PINS IN PORT A TO OUTPUT PINS
}

void TIMER1_init(void){
    TCNT1 = 0;
    TCCR1A =  (1<<FOC1A);
    TCCR1B = (1<<WGM12) | (1<<CS10) | (1<<CS12) ;
    TIMSK |= (1<<OCIE1A);
    OCR1A = 798;
}
