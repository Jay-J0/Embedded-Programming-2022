/*
 * Opdracht6C.c
 *
 * Created: 26-3-2022 14:51:54
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void initADC();
void initTimer1Fast10PWM();
void initTimer2FastPWM();
void dimLed(uint8_t);
void pasPeriodeTijdTimer1Aan(uint8_t);

uint16_t leesADwaarde(uint8_t);

int main(void)
{
	uint8_t periodeijden[] = {1,2,3,4,5}; //prescalers
	initTimer1Fast10PWM();
	initTimer2FastPWM(); //initialiseert timer2 op fast PWM
	//initADC();
	_delay_ms(1000); //wacht 1 sec
	dimLed(50);      // De duty cycle van de PWM is 1
	_delay_ms(1000); //wacht 1 sec
	
	while (1)
	{
	    //long adwaarde = leesADwaarde(5);
		//adwaarde = adwaarde*255/1023;
	    //dimLed(adwaarde);      //duty cycle van de PWM
		for (int i=0; i<5; i++){
			pasPeriodeTijdTimer1Aan(periodeijden[i]); //met deze functie wordt de frequentie aangepast f=1/periodetijd
			_delay_ms(1000);
		}
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

void initTimer1Fast10PWM(){
	DDRB = 1 << PORTB1;
	TCCR1A = (1 << WGM10) | (1 << WGM11) | (1 << WGM12) | (1 << COM1A1);
	TCCR1B = (1 << CS10) | (1 << CS11); // prescaler 64
	OCR1A = 512;
}

void pasPeriodeTijdTimer1Aan(uint8_t i){
	if (i ==1)
	TCCR1B = (1 << CS10) | (1 << CS11);
	if (i ==2)
	TCCR1B = (1 << CS12);
	if (i ==3)
    TCCR1B = (1 << CS12);
	if (i ==4)
	TCCR1B = (1 << CS12);
	if (i ==5)
	TCCR1B = (1 << CS10) | (1 << CS12);
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

