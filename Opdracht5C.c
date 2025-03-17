/*
 * Opdracht5C.c
 *
 * Created: 19-3-2022 16:26:33
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

#define NOTE_D 293.66
#define NOTE_Ds 311.13
#define NOTE_F 349.23
#define NOTE_G 392
#define TestTIJDSDUUR1 1800
#define TestTIJDSDUUR2 1200

void initialisatie();
void introBeethoven();
void playNoot(float, uint16_t);
void rust(uint16_t);


int main(void)
{
	initialisatie();
	for(int i = 0; i < 3;i++) {
		introBeethoven();
		rust(2000);
	}
	while (1)
	{
	}
}

void initialisatie() {
	DDRB |= 1 << PORTB2;// het genereren van een toon gebeurd op een output
	TCCR1A = 1 << COM1B0;
	TCCR1B = (1 << WGM12); // geen prescaling 
}

void playNoot(float freq, uint16_t tijd) {
	
		TCCR1B |= (1 << CS10);
	    OCR1A = F_CPU/(2*1*freq) - 1;
		rust(tijd);
		OCR1A = 0;
		TCCR1B &= ~(1<< CS10);
}

void introBeethoven(){
	playNoot(NOTE_G,TestTIJDSDUUR1 - 1500);
	rust(TestTIJDSDUUR2 - 1150);
	playNoot(NOTE_G,TestTIJDSDUUR1 - 1500);
	rust(TestTIJDSDUUR2 - 1150);
	playNoot(NOTE_G,TestTIJDSDUUR1 - 1500);
	rust(TestTIJDSDUUR2 - 1150);
	playNoot(NOTE_Ds,TestTIJDSDUUR1);
	rust(TestTIJDSDUUR2);
	playNoot(NOTE_F,TestTIJDSDUUR1 - 1500);
	rust(TestTIJDSDUUR2 - 1150);
	playNoot(NOTE_F,TestTIJDSDUUR1 - 1500);
	rust(TestTIJDSDUUR2 - 1150);
	playNoot(NOTE_F,TestTIJDSDUUR1 - 1500);
	rust(TestTIJDSDUUR2 - 1150);
	playNoot(NOTE_D,TestTIJDSDUUR1);
	OCR1A = 0;
}

void rust(uint16_t v) {
	for(uint16_t i=0; i < v; ++i){
		_delay_ms(1);
		}
}


