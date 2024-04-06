/*
 * WDT.cpp
 *
 * Created: 4/6/2024 11:53:53 PM
 * Author : USER
 */ 

#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <avr/delay.h>

void wdt_Init(){
	cli();
	wdt_reset();
	wdt_enable(WDTO_4S);
	sei();
}

int main(void)
{
    DDRB |= (1 << DDB5);
	PORTB |= (1 << PORTB5);
	_delay_ms(1000);
	PORTB &= ~(1 << PORTB5);
	wdt_Init();
    while (1) 
    {
		
    }
}

