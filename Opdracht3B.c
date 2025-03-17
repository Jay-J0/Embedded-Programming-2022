/*
 * Opdracht3B.c
 *
 * Created: 5-3-2022 10:19:20
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define TRUE 1
#define FALSE 0

void initExtInt();
void initUsart();
void initPort();

volatile uint8_t x;
uint8_t aanUit = FALSE;

ISR(INT1_vect){
	_delay_ms(500);
	while (!aanUit){
		if (~PIND & (1<<PORTD3)){
			break;
		}
	}
	aanUit = TRUE;
}

ISR(USART_RX_vect){
	while (!(UCSR0A & (1<<RXC0)));
	x = UDR0;
	//teller = x;
}

int main(void)
{
	initPort();
	initExtInt();
	initUsart();

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

void initUsart(){
	UCSR0A = (1<<RXC0) | (1<<TXC0);
	UCSR0B = (1<<RXEN0) |(1 << TXEN0) | (1 << RXCIE0) | (1 << TXCIE0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); 
	UBRR0H=00;
	UBRR0L=103;
}

void initPort(){
	DDRB=0xFF;
	DDRD &= ~(1 << PORTD3);
}



