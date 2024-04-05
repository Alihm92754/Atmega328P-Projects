/*
 * PWM_EX.cpp
 *
 * Created: 4/6/2024 12:07:08 AM
 * Author : USER
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	uint8_t duty1, duty2, Freq;
	DDRD |= (1 << DDD5);
	DDRD |= (1 << DDD6);
	DDRB &= ~((1 << DDB0) | (1 << DDB1) | (1 << DDB2));
	PORTB |= (1 << PORTB0) | (1 << PORTB1) | (1 << PORTB2); //PULL UP
	TCCR0A |= (1 << COM0A1) | (1 << COM0B1) | (1 << WGM01) | (1 << WGM00);
	//TCCR0B |= (1 << CS02); //Prescaler = 256 Freq = (16MHZ/(256*256))
	//OCR0A = 180; //PD6
	//OCR0B = 50; //PD5
    
    while (1) 
    {
		if((PINB & (1 << PINB0)) == 0){
			_delay_ms(10);
			while((PINB & (1 << PINB)) == 0);
			duty1++;
			if(duty1 > 10)duty1=0;
			OCR0A = duty1*25;//0-255
		}
		
		if((PINB & (1 << PINB1)) == 0){
			_delay_ms(10);
			while((PINB & (1 << PINB1)) == 0);
			Freq++;
			if(Freq > 5)Freq = 0;
			switch(Freq){
				
				case 0:
				TCCR0B&=~((1 << CS00) | (1 << CS01) | (1 << CS02)); //TCCR0B = 0;
				break;
				
				case 1:
				TCCR0B &= ~((1 << CS01) | (1 << CS02));
				TCCR0B |= (1 << CS00);
				break;
				
				case 2:
				TCCR0B &= ~((1 << CS00) | (1 << CS02));
				TCCR0B |= (1 << CS01);
				break;
				
				case 3:
				TCCR0B &= ~(1 << CS02);
				TCCR0B |= (1 << CS00) | (1 << CS01);
				break;
				
				case 4:
				TCCR0B &= ~((1 << CS00) | (1 << CS01));
				TCCR0B |= (1 << CS02);
				break;
				
				case 5:
				TCCR0B &= ~(1 << CS01);
				TCCR0B |= (1 << CS02) | (1 << CS00);
				break;

			}
		}
		
		if((PINB & (1 << PINB2)) == 0){
			_delay_ms(10);
			while((PINB & (1 << PINB2)) == 0);
			duty2++;
			if(duty2 > 10)duty2 = 0;
			OCR0B = duty2*25;
		}
    }
}

