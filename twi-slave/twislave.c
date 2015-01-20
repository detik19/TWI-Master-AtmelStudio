/*
 * twislave.c
 *
 * Created: 20/01/2015 7:53:04
 *  Author: tedy.saputro
 */
#include <util/twi.h>
#include <avr/interrupt.h>


#include "twislave.h"


void twi_init_slave(uint8_t address)
{
	// load address into TWI address register
	TWAR = address;
	// set the TWCR to enable address matching and enable TWI, clear TWINT, enable TWI interrupt
	TWCR = (1<<TWIE) | (1<<TWEA) | (1<<TWINT) | (1<<TWEN);
	
}
 