/*
 * spi.c
 *
 *  Created on: May 2, 2019
 *      Author: karee
 */


#include"spi.h"

void SPI_masterInit(void){
	/*SLAVE SELECT PIN IS SET TO BE OUTPUT PIN*/
	SET_BIT(DDRB,PB4);
	/*MASTER OUTPUT SLAVE INPUT PIN IS SET TO BE OTUPUT PIN TO MASTER*/
	SET_BIT(DDRB,PB5);
	/*SCLK PIN IS SET TO BE OUTPUT PIN*/
	SET_BIT(DDRB,PB7);
	/*MASTER INPUT SLAVE OUTPUT PIN IS CLEARED TO BE INPUT PIN*/
	CLEAR_BIT(DDRB,PB6);
	/************************************
	 * THIS REGISTER IS SPI CONTROL REGSITER
	 * SET_BIT(SPCR,SPE);//ENABLE SPI
	 * SET_BIT(SPCR,MSTR);//SELECT THIS MICRO AS MASTER
	 * CLEAR_BIT(SPCR,SPIE);//WE WILL NOT USE INTERRUPT METHOD IN THIS APP
	 * CLEAR_BIT(SPCR,DORD);//DORD bit is written to zero, the MSB of the data word is transmitted first.
	 * CLEAR_BIT(SPCR,CPOL);// CLOCK POLARITY: SCK is low when idle START FROM (0) LOGIC LOW
	 * CLEAR_BIT(SPCR,CPHA);//READ DATA AT RISING EDGE OF CLOCK
	 * CLEAR_BIT(SPCR,SPR1) AND CLEAR_BIT(SPCR,SPR1) , WE FREQ PRE-SCLAER F/4
	 * ******************************/
	SPCR = (1<<SPE)|(1<<MSTR);
}

void SPI_slaveInit(void){
	/*SLAVE SELECT PIN IS CLEARED TO BE INPUT PIN*/
	CLEAR_BIT(DDRB,PB4);
	/*MASTER OUTPUT SLAVE INPUT PIN IS SET TO BE INPUT PIN TO SLAVE DEVICE*/
	CLEAR_BIT(DDRB,PB5);
	/*SCLK PIN IS CLEARED TO BE INTPUT PIN TO SLAVE*/
	CLEAR_BIT(DDRB,PB7);
	/*MASTER INPUT SLAVE OUTPUT PIN IS SET TO BE OUTPUT PIN TO SLAVE*/
	SET_BIT(DDRB,PB6);
	/************************************
	 * THIS REGISTER IS SPI CONTROL REGSITER
	 * SET_BIT(SPCR,SPE);//ENABLE SPI
	 * CLEAR_BIT(SPCR,MSTR);//SELECT THIS MICRO AS SLAVE
	 * CLEAR_BIT(SPCR,SPIE);//WE WILL NOT USE INTERRUPT METHOD IN THIS APP
	 * CLEAR_BIT(SPCR,DORD);//DORD bit is written to zero, the MSB of the data word is transmitted first.
	 * CLEAR_BIT(SPCR,CPOL);// CLOCK POLARITY: SCK is low when idle START FROM (0) LOGIC LOW
	 * CLEAR_BIT(SPCR,CPHA);//READ DATA AT RISING EDGE OF CLOCK
	 * CLEAR_BIT(SPCR,SPR1) AND CLEAR_BIT(SPCR,SPR1) , WE FREQ PRE-SCLAER F/4
	 * ******************************/
	SPCR = (1<<SPE);

}

void SPI_sendByte(uint8 data){
	/* store the data in the SPI data register to be ready to send*/
	SPDR=data;
	/*pulling method is used in this driver
	 * we check in the SPI interrupt flag
	 * The interrupt flag is set to one when the transmition is completed
	 * so we check if it is still low we stuck here until data is send,
	 *  and the register is ready to send another data
	 *  this is pulling method */
	while(BIT_IS_CLEAR(SPSR,SPIF));

}

uint8 SPI_reciveByte(void){
	while(BIT_IS_CLEAR(SPSR,SPIF));
	return SPDR;
}
