/*
 * twi_slave.c
 *
 * Created: 18/01/2015 16:50:13
 *  Author: tedy.saputro
 */ 


//#include <util/twi.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include "twislave.h"
//#include <util/delay.h>

//uint8_t buffer_address;
//uint8_t txbuffer[0xFF];
//uint8_t rxbuffer[0xFF];
//unsigned char write_data,recv_data;
/*
void twi_init_slave(uint8_t address)
{
	// load address into TWI address register
	TWAR = address;
	// set the TWCR to enable address matching and enable TWI, clear TWINT, enable TWI interrupt
	TWCR = (1<<TWIE) | (1<<TWEA) | (1<<TWINT) | (1<<TWEN);
	
}
*/
/*
void TWI_match_read_slave(void) //Function to match the slave address and slave dirction bit(read)
{
	while((TWSR & 0xF8)!= 0x60)  // Loop till correct acknoledgement have been received
	{
		// Get acknowlegement, Enable TWI, Clear TWI interrupt flag
		TWCR=(1<<TWEA)|(1<<TWEN)|(1<<TWINT);
		while (!(TWCR & (1<<TWINT)));  // Wait for TWINT flag
	}
}
void TWI_read_slave(void)
{
	// Clear TWI interrupt flag,Get acknowlegement, Enable TWI
	TWCR= (1<<TWINT)|(1<<TWEA)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT))); // Wait for TWINT flag
	while((TWSR & 0xF8)!=0x80); // Wait for acknowledgement
	recv_data=TWDR; // Get value from TWDR
	PORTD=recv_data; // send the receive value on PORTB
}
*/



int main(void)
{
	twi_init_slave(0x20);
	DDRD=0xFF;
	PORTD=0x01;
	// allow interrupts
	sei();
//	PORTD=rxbuffer[0];
    while(1)
    {
    // PORTD=TWDR;
    }
}