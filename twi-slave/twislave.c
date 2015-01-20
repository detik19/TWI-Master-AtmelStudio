/*
 * twislave.c
 *
 * Created: 20/01/2015 7:53:04
 *  Author: tedy.saputro
 */
#include <util/twi.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "twislave.h"


void twi_init_slave(uint8_t address)
{
	// load address into TWI address register
	TWAR = address;
	// set the TWCR to enable address matching and enable TWI, clear TWINT, enable TWI interrupt
	TWCR = (1<<TWIE) | (1<<TWEA) | (1<<TWINT) | (1<<TWEN);
	
}

ISR(TWI_vect){

	
	// temporary stores the received data
	uint8_t data;
	
	// own address has been acknowledged
	if( (TWSR & 0xF8) == TW_SR_SLA_ACK ){
//		PORTD=0x04;
//		buffer_address = 0xFF;
		// clear TWI interrupt flag, prepare to receive next byte and acknowledge
		TWCR |= (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
	}
	else if( (TWSR & 0xF8) == TW_SR_DATA_ACK ) // data has been received in slave receiver mode
	{ 
		
		// save the received byte inside data
		PORTD = TWDR;
//		recv_data=TWDR;
		
		// check wether an address has already been transmitted or not
		//if(buffer_address == 0xFF){
			
		//	buffer_address = data;
			
			// clear TWI interrupt flag, prepare to receive next byte and acknowledge
			TWCR |= (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);

		//}
		//else{ // if a databyte has already been received
			
			// store the data at the current address
		//	rxbuffer[buffer_address] = data;
					
			// increment the buffer address
		//	buffer_address++;
			
			// if there is still enough space inside the buffer
		//	if(buffer_address < 0xFF){
				// clear TWI interrupt flag, prepare to receive next byte and acknowledge
		//		TWCR |= (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
		//	}
		//	else{
		//		// clear TWI interrupt flag, prepare to receive last byte and don't acknowledge
		//		TWCR |= (1<<TWIE) | (1<<TWINT) | (0<<TWEA) | (1<<TWEN);
		//	}
		//}
	}

}
