/*
 * twi_slave.c
 *
 * Created: 18/01/2015 16:50:13
 *  Author: tedy.saputro
 */ 


#include <util/twi.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

//uint8_t buffer_address;
//uint8_t txbuffer[0xFF];
//uint8_t rxbuffer[0xFF];
//unsigned char write_data,recv_data;

void twi_init_slave(uint8_t address)
{
	// load address into TWI address register
	TWAR = address;
	// set the TWCR to enable address matching and enable TWI, clear TWINT, enable TWI interrupt
	TWCR = (1<<TWIE) | (1<<TWEA) | (1<<TWINT) | (1<<TWEN);
	
}
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

ISR(TWI_vect){
//	PORTD=0x03;
	
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
	/*else if( (TWSR & 0xF8) == TW_ST_DATA_ACK ){ // device has been addressed to be a transmitter
		
		// copy data from TWDR to the temporary memory
		data = TWDR;
		
		// if no buffer read address has been sent yet
		if( buffer_address == 0xFF ){
			buffer_address = data;
		}
		
		// copy the specified buffer address into the TWDR register for transmission
		TWDR = txbuffer[buffer_address];
		// increment buffer read address
		buffer_address++;
		
		// if there is another buffer address that can be sent
		if(buffer_address < 0xFF){
			// clear TWI interrupt flag, prepare to send next byte and receive acknowledge
			TWCR |= (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
		}
		else{
			// clear TWI interrupt flag, prepare to send last byte and receive not acknowledge
			TWCR |= (1<<TWIE) | (1<<TWINT) | (0<<TWEA) | (1<<TWEN);
		}
		
	}
	else{
		// if none of the above apply prepare TWI to be addressed again
		TWCR |= (1<<TWIE) | (1<<TWEA) | (1<<TWEN);
	}*/
}


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