/*
 * InputCapture.cpp
 *
 * Created: 4/5/2024 2:49:10 PM
 * Author : USER
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
volatile uint16_t capt1, capt2;
volatile uint8_t mask = 0;
volatile uint16_t ov;
volatile uint16_t ovf;
uint32_t clk;
double freq;


int main(void)
{
    DDRB &= ~(1 << DDB0);
	// Initial Timer
	cli();
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	TCCR1B |= (1 << ICES1) | (1 << CS10); //Rising Edge, Prescaler=1
	TIMSK1 |= (1 << ICIE1) | (1 << TOIE1);
	sei();
    while (1) 
    {
		if(mask == 2){
			mask = 0;
			clk = ((unsigned long)capt2 + (unsigned long)(65536*ovf)) - (unsigned long)capt1;
			//Tick time = 1/Frequency/Prescaler
			//Tick time = 1/16*10^6 = 62.5 x 10^-9 = 62.5 ns
			clk = clk * 62.5e-3; //e=*10^   CLK -> us
			freq = (1 / (double)clk) * 1000000; //Freq=Hz
			ovf = 0;
			ov = 0;
			TIFR1 = (1 << ICF1) | (1 << TOIE1);
			TIMSK1 |= (1 << ICIE1) | (1 << TOIE1);
        }
	}
}

ISR(TIMER1_OVF_vect) {
	ov++;
}

ISR(TIMER1_CAPT_vect) {
	if(mask == 0){
		capt1 = ICR1;
		ov = 0;
	}
	else if(mask == 1){
		capt2 = ICR1;
		ovf = ov;
		TIMSK1 &= ~((1 << ICIE1) | (1 << TOIE1)); // Disable Input Capture Interrupt, TOV
	}
	mask++;
}

