/*
 * Servo_EX.cpp
 *
 * Created: 4/6/2024 4:36:23 AM
 * Author : USER
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    //Set Fast PWM, TOP in ICR1, Clear OC1A on compare match, clk/8
	TCCR1A = (1 << WGM11) | (1 << COM1A1);
	TCCR1B = (1 << WGM12) | (1 << WGM13) | (1 << CS10) | (1 << CS11);
	ICR1 = 39999; // FPWM = 50HZ (PERIOD = 20ms standard).
	TCNT1 = 0;
	DDRB |= (1 << DDB1); //PWM Pins as Out
	
    while (1) 
    {
		// -90 1ms 0 1.5ms +90 2ms
		// 16MHZ/8 1Tick = 0.5us
		// 
		OCR1A = 1600; // -90 DEGREE
		_delay_ms(1500);
		OCR1A = 3000; // 0 DEGREE
		_delay_ms(1500);
		OCR1A = 5250; // +90 DEGREE
		_delay_ms(1500);
		
		for(int i=1600;i<=5250;i++){
			OCR1A = i;
			_delay_ms(2);
		}
		_delay_ms(500);
		
		for(int i=5250;i>=1600;i=i-1){
			OCR1A = i;
			_delay_ms(2);
		}
		_delay_ms(500);
		
		//1600 -> -90 degree
		//5250 -> 90 degree
		
    }
}

