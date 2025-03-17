/*
 * Opdracht2.c
 *
 * Created: 13-2-2022 14:17:00
 */ 


#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

void initUsart();
char readChar();
void zetLedB0_B3(char x);
void writeChar(char x);
void writeString(char st[]);

int main(void) {
	DDRB= 0xFF;
	char x;
	initUsart();
 
	while (1) {
		writeString("Zet een HEX waarde op de pinnen B0...B3\n\r");
		x = readChar();
		zetLedB0_B3(x);
	}
}


void initUsart(){
		UCSR0A = 0;
		UCSR0B = (1<<RXEN0) |(1 << TXEN0); // Enable de USART Transmitter and Receiver
		UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); /* 8 data bits, 1 stop bit */
		UBRR0H=00;
		UBRR0L=103; //baudrade 9600 bij
}

char readChar(){
	while (!(UCSR0A & (1<<RXC0))); // wait for data to be received
	return UDR0; // Get and return received data from buffer 
	
}

void zetLedB0_B3(char x){
	PORTB &= ~(1 << PORTB0);
	_delay_ms(50);
	if (x >= 47 & x < 58) {
		x = x - 48;
		PORTB = x;
	}
	
	else if (x > 64 & x < 71){
		x = x - 55;
		PORTB = x;
	}
	
	else if (x > 96  & x < 103 ){
		x = x - 87;
		PORTB = x;
	}
}

void writeChar(char x) {
	while(~UCSR0A & (1 << UDRE0));
	UDR0 = x;
}

void writeString(char st[]) {
	for(uint8_t i = 0 ; st[i] != 0 ; i++) {
		writeChar( st[i] );
	}
}


