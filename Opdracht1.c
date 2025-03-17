/*
 * Opdracht1.c
 *
 * Created: 13-2-2022 14:20:17
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

void initialisatie();
void zetLedAan();
void zetLedUit();

int main(void)
{
	initialisatie();

	while (1)
	{
		
		zetLedAan();
	}
	return 0;
}

void initialisatie(){
	DDRD = 0xFF;
}

void zetLedAan(){
	int i;
	for(i = 0; i <= 7; i++){
		PORTD |= 1 << i;
		_delay_ms(250);
		zetLedUit(i);
	}
}
void zetLedUit(int i){
	PORTD &= ~(1 << i);
}


