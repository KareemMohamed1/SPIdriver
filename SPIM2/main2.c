/*
 * main1.c
 *
 *  Created on: May 2, 2019
 *      Author: karee
 */


#include"lcd.h"
#include"spi.h"
int main(void){
	LCD_init();
	SPI_slaveInit();
	uint8 key;
	while(1){
		key = SPI_reciveByte();
		if((key>=0) && (key<=9))
		{

			LCD_intgerToString(key); //display the pressed key
		}
		else
		{
			LCD_displayCharacter(key);
		}

	}

}
