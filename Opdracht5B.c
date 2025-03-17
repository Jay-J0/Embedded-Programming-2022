/*
 * Opdracht5B.c
 *
 * Created: 19-3-2022 14:18:18
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void initBlinkTimer();
void initBlink();
void initUsart();

int tijd = 0;
char x;
int totaalTimerTicks;

int main(void)
{
	initUsart();
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
	sei();
	TCCR0A = (1 << WGM01); //zetten CTC bit, en gebruiken 8-bit timer
	TCCR0B = (1 << CS02) | (1 << CS00); //start bij 1024 prescaler
	TIMSK0 = (1 << OCIE0A); //compare match bit word gezet
}

void initUsart(){
	UCSR0A = (1<<RXC0) | (1<<TXC0);
	UCSR0B = (1<<RXEN0) |(1 << TXEN0) | (1 << RXCIE0) | (1 << TXCIE0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
	UBRR0H=00;
	UBRR0L=103;
}

ISR(TIMER0_COMPA_vect){
	tijd++;
	
	if(tijd > 50){
		tijd = 0;
		PORTB ^= (1 << PORTB1);
	}
}

ISR(USART_RX_vect){
	while (!(UCSR0A & (1<<RXC0)));
	x = UDR0;
	
	if(x == 49){
		totaalTimerTicks = 15625;
	}
	if(x == 50){
		totaalTimerTicks = 7813;
	}
	if(x == 51){
		totaalTimerTicks = 3906;
	}
	if(x == 52){
		totaalTimerTicks = 78;
	}
	
	OCR0A = totaalTimerTicks;
}
