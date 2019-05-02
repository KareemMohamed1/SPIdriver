/*
 * main1.c
 *
 *  Created on: May 2, 2019
 *      Author: karee
 */


#include"keypad.h"
#include"spi.h"
int main(void){
	SPI_masterInit();
	uint8 key;
	_delay_ms(500);
	while(1){
		key=KeyPad_getPressedKey();
		SPI_sendByte(key);
		_delay_ms(500); //press time is 500msec


	}

}
