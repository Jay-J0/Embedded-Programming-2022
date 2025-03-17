/*
 * Opdracht4B.c
 *
 * Created: 12-3-2022 15:30:16
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#define WAARDE1 200

void initAD();
void initUsart();
void writeChar(uint16_t x);
void writeString(uint16_t st[]);
void writeInt(uint16_t x);

int main(void) {
	
	uint16_t adcValue;
	uint16_t ldrValue;
	DDRB = 0x10;
	initAD();
	initUsart();

	// ------ Event loop ------ //
	while (1) {

        ADMUX |= 0b00000100;
		ADCSRA |= (1 << ADSC | 1 << ADIF); /* start ADC conversion */
		while(~ADCSRA & (1 << ADIF));
		adcValue = ADC; /* read ADC in */
		writeInt(adcValue);
		writeChar('\t');
		ADMUX &= ~(0b00000100);
		
        ADMUX |= 0b00000101;
        ADCSRA |= (1 << ADSC | 1 << ADIF); /* start ADC conversion */
        while(~ADCSRA & (1 << ADIF));
		ldrValue = ADC;
	    writeInt(ldrValue);
		writeChar('\n');
		writeChar('\r');
		ADMUX &= ~(0b00000101);

		if(ldrValue > adcValue){
			PORTB |=(1 << PORTB4);
		}

		else{
			PORTB &= ~(1 << PORTB4);
		}

		_delay_ms(250);
		} /* End event loop */
		return (0); /* This line is never reached */
	}
	
void initAD(){
		ADMUX |= (1 << REFS0); /* reference voltage on AVCC */
		ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2); /* ADC clock prescaler /128 */
		ADCSRA |= (1 << ADEN); /* enable ADC */
}

	
	void initUsart(){
		UCSR0A = 0;
		UCSR0B = (1<<RXEN0) |(1 << TXEN0); // Enable de USART Transmitter and Receiver
		UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); /* 8 data bits, 1 stop bit */
		UBRR0H=00;
		UBRR0L=103; //baudrade 9600 bij
	}
	
	void writeChar(uint16_t x) {
		while(~UCSR0A & (1 << UDRE0));
		UDR0 = x;
	}

	void writeString(uint16_t st[]) {
		for(uint8_t i = 0 ; st[i] != 0 ; i++) {
			writeChar( st[i] );
		}
	}

	void writeInt(uint16_t x) {
		char buffer[8];
		itoa(x,buffer,10);
		writeString(buffer);
	}

