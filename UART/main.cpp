/*
 * UART.cpp
 *
 * Created: 4/8/2024 11:17:22 PM
 * Author : USER
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

void USART_Init(unsigned int ubrr){
	//set baud rate
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	//enable receiver and transmitter
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
	//set frame format: 8data, 2stop bit
	UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);
}

void USART_Transmit(unsigned char data){
	//wait for empty transmit buffer
	while(! (1 << UCSR0A & (1 << UDRE0))); //wait for empty transmit buffer
	UDR0 = data;
}

unsigned char USART_Receive(void){
	//wait for data to be received
	while(! (UCSR0A & (1 << RXC0)));
	//get and return received data from buffer
	return UDR0;
}


int main(void)
{
    USART_Init(MYUBRR);
	char m;
	
    while (1) 
    {
		m = USART_Receive();
		USART_Transmit(m);
		USART_Transmit('\r');
		_delay_ms(500);
    }
}

