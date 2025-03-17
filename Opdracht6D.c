/*
 * Opdracht6D.c
 *
 * Created: 26-3-2022 16:14:34
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void initADC();
void initTimer1FastPWM_ICR_l();
void initTimer2FastPWM();
void dimLed(uint8_t);
uint16_t leesADwaarde(uint8_t);

int main(void)
{
	initTimer1FastPWM_ICR_l();
	initTimer2FastPWM(); //initialiseert timer2 op fast PWM
	initADC();

	while (1)
	{
		long adwaarde = leesADwaarde(5);
		adwaarde = adwaarde*255/1023;
		dimLed(adwaarde);      //duty cycle van de PWM
	}
}

void initADC(){
	ADMUX = (1 << REFS0) | (1 << MUX0) | (1 << MUX2); /* reference voltage on AVCC */
	ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2); /* ADC clock prescaler /128 */
	ADCSRA |= (1 << ADEN); /* enable ADC */
}

void initTimer2FastPWM(){
	DDRD = 1 << PORTD3;
	TCCR2A = (1 << WGM00) | (1 << WGM01) | (1 << COM2B1);
	TCCR2B = (1 << CS20) | (1 << CS21) | (1 << CS22);
}

void initTimer1FastPWM_ICR_l(){
	DDRB = 1 << PORTB1;
	TCCR1A = (1 << WGM11) | (1 << COM1A1);
	TCCR1B = (1 << CS10)| (1 << CS12) | (1 << WGM12) | (1 << WGM13); // prescaler 64
	OCR1A = 32767;
	ICR1 = 65535;
}

void dimLed(uint8_t x){
	OCR2B = x;
}

uint16_t leesADwaarde(uint8_t x){
	ADCSRA |= (1 << ADSC | 1 << ADIF); /* start ADC conversion */
	while(~ADCSRA & (1 << ADIF));
	uint8_t y = ADC / x; /* read ADC in */
	return y;
}

