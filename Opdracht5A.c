/*
 * Opdracht5A.c
 *
 * Created: 19-3-2022 12:45:03
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void initBlinkTimer();
void initBlink();

int tijd = 0;

int main(void)
{
	initBlinkTimer();
	initBlink();
	while (1)
	{
	}
	return 0;
}
void initBlink() {
	DDRB = 1 << PORTB1;
}

void initBlinkTimer(){
	TCCR0A = (1 << WGM01); //zetten CTC bit
	TCCR0B = (1 << CS02) | (1 << CS00); //start bij 1024 prescaler
	OCR0A = 156;
	TIMSK0 = (1 << OCIE0A);
	sei();
}

ISR(TIMER0_COMPA_vect){
	tijd++;
	
	if(tijd > 50){
		tijd = 0;
		PORTB ^= (1 << PORTB1);
	}
}

