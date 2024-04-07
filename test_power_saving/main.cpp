/*
 * test_power_saving.cpp
 *
 * Created: 4/7/2024 11:24:26 PM
 * Author : USER
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include <avr/power.h>



int main(void)
{
    // clock_prescale_set(clock_div_256);
	DDRB |= (1 << DDB5);
	PRR |= 0xFF;
	// set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	// sleep_enable();
    while (1) 
    {
		PORTB ^= (1 << PORTB5);
		_delay_ms(500);
		
    }
}

