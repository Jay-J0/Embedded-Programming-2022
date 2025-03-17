/*
 * Opdracht3A.c
 *
 * Created: 3-3-2022 10:50:38
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define TRUE 1
#define FALSE 0

void initExtInt();

uint8_t aanUit = FALSE;
volatile uint8_t x = 10;

ISR(INT1_vect){
	_delay_ms(500);
	while (!aanUit){
		if (~PIND & (1<<PORTD3)){
			break;
		}
	}
	aanUit = TRUE;
}

int main(void)
{
	DDRB=0xFF;
	DDRD &= ~(1 << PORTD3);
	initExtInt();

	while (1){
		aanUit = FALSE;
		_delay_ms(1000);
		
		PORTB &= ~(1 << PORTB0);
		PORTB |= 1 << PORTB4;
		_delay_ms(50);
		if (x > 47 & x < 58) {
			x = x - 48;
		}

		PORTB = x;
		
		_delay_ms(1000);
		PORTB &= ~(1 << PORTB4);
		
		x = x - 1;
		
		while (x <= 0);
	}
}


void initExtInt(){
	sei();
	EICRA = EICRA | (1 << ISC11);
	EIMSK = EIMSK | (1 << INT1);
}
