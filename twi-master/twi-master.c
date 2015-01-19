/*
 * twi_master.c
 *
 * Created: 18/01/2015 16:15:07
 *  Author: tedy.saputro
 */ 


#include <avr/io.h>
#include <util/twi.h> 
#include <util/delay.h>
/* define CPU frequency in Mhz here if not defined in Makefile */
#ifndef F_CPU
#define F_CPU 4000000UL
#endif

/* I2C clock in Hz */
#define SCL_CLOCK  100000L
void i2c_init(void)
{
	/* initialize TWI clock: 100 kHz clock, TWPS = 0 => prescaler = 1 */
	
	//TWSR = 0;                         /* no prescaler */
	//TWBR = ((F_CPU/SCL_CLOCK)-16)/2;  /* must be > 10 for stable operation */
	TWBR=0x01;
	TWSR=(0<<TWPS1)|(0<<TWPS0); // Setting prescalar bits
	}/* i2c_init */


void twi_start()
{
	/*
	* TWEN must be set to enable the Two-wire Serial Interface,
	* TWSTA must be written to one to transmit a START condition
	* TWINT must be written to one to clear the TWINT Flag
	*/
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	
	
}

void twi_wait()
{
	while (!(TWCR & (1<<TWINT)));
	
}


void twi_write(uint8_t address)
{
	TWDR = address;
	TWCR = (1<<TWINT) | (1<<TWEN);
	
}
void i2c_stop(void)
{
	/* send stop condition */
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
	
	// wait until stop condition is executed and bus released
	while(TWCR & (1<<TWSTO));

	}/* i2c_stop */

int main(void)
{
	uint8_t   twst;
	DDRD=0xFF;
	PORTD=0x00;
	
	twi_start();
	twi_wait();
	
	// check value of TWI Status Register. Mask prescaler bits.
	twst = TW_STATUS & 0xF8;
	
	//After a START condition has been transmitted, the TWINT Flag is set by hardware, and the status code in TWSR will be $08
	//if ( (twst != TW_START) ) return 1;	
	while((TWSR & 0xF8)!= TW_START); 
	
	PORTD=0x01;
	_delay_ms(200);
	
	twi_write(0x20+0); //address 0b011 0000=30 + W=0
	twi_wait();
	
	twst = TW_STATUS & 0xF8;
	if ( (twst != TW_MT_SLA_ACK)) return 1;
//	while((TWSR & 0xF8) != TW_MT_SLA_ACK); // Check for the acknoledgement
   
	PORTD=0x02;
	twi_write(0xCC);
	twi_wait();
	while((TWSR & 0xF8) != TW_MT_DATA_ACK); // Check for the acknoledgement

//	twst = TW_STATUS & 0xF8;
//	if ( (twst != TW_MT_DATA_ACK)) return 1;
	
	i2c_stop();
	while(1)
    {
        //TODO:: Please write your application code 
    }
	return 0;
	
}