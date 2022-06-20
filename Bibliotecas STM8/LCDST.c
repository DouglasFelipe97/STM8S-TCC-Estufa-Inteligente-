
#include <iostm8s005K6.h>
#include <intrinsics.h>
#include "LCDSTM8S.h"
#include "delay.h"
#include "GPIO.h"

/*--------------- Initialize LCD ------------------*/
void lcd_init(void)
{
	
	delay_ms(40);
	
	//PIN_LOW(D4_PORT,D4_PIN);
	D4 = 0; //D4_dir=0;
	//PIN_HIGH(D5_PORT,D5_PIN);
	D5 = 1; //D5_dir=1;
	//PIN_LOW(D6_PORT,D6_PIN);
	D6 = 0; //D6_dir=0;
	//PIN_LOW(D7_PORT,D7_PIN);
	D7 = 0; //D7_dir=0;
	//PIN_LOW(RS_PORT,RS_PIN);
	RS = 0; //EN_dir=0;
	
	//PIN_HIGH(EN_PORT,EN_PIN);
	EN = 1;
	//PIN_LOW(EN_PORT,EN_PIN);
	EN = 0;
	
	lcd_write(0,0x28);
	lcd_write(0,0x0c);
	lcd_write(0,0x06);
	lcd_write(0,0x01);
}

/*--------------- Write To LCD ---------------*/
void lcd_write(uint8_t type,uint8_t data)
{
	delay_ms(2);
	if(type)
	{
		//PIN_HIGH(RS_PORT,RS_PIN);
		RS = 1;
	}else
	{
		//PIN_LOW(RS_PORT,RS_PIN);
		RS = 0;
	}
	
	//Send High Nibble
	if(data&0x80)
	{
		//PIN_HIGH(D7_PORT,D7_PIN);
		D7 = 1;
	}else
	{
		//PIN_LOW(D7_PORT,D7_PIN);
		D7 = 0;
	}
	
	if(data&0x40)
	{
		//PIN_HIGH(D6_PORT,D6_PIN);
		D6 = 1;
	}else
	{
		//PIN_LOW(D6_PORT,D6_PIN);
		D6 = 0;
	}
	
	if(data&0x20)
	{
		//PIN_HIGH(D5_PORT,D5_PIN);
		D5 = 1;
	}else
	{
		//PIN_LOW(D5_PORT,D5_PIN);
		D5 = 0;
	}
	
	if(data&0x10)
	{
		//PIN_HIGH(D4_PORT,D4_PIN);
		D4 = 1;
	}else
	{
		//PIN_LOW(D4_PORT,D4_PIN);
		D5 = 0;
	}
	//PIN_HIGH(EN_PORT,EN_PIN);
	EN = 1;
	//PIN_LOW(EN_PORT,EN_PIN);
	EN = 0;
	

	//Send Low Nibble
	if(data&0x08){
	//PIN_HIGH(D7_PORT,D7_PIN);
		D7 = 1;
	}else
	{
		//PIN_LOW(D7_PORT,D7_PIN);
		D7 = 0;
	}
	
	if(data&0x04)
	{
		//PIN_HIGH(D6_PORT,D6_PIN);
		D6 = 1;
	}else
	{
		//PIN_LOW(D6_PORT,D6_PIN);
		D6 = 0;
	}
	
	if(data&0x02)
	{
		//PIN_HIGH(D5_PORT,D5_PIN);
		D5 = 1;
	}else
	{
		//PIN_LOW(D5_PORT,D5_PIN);
		D5 = 0;
	}
	
	if(data&0x01)
	{
		//PIN_HIGH(D4_PORT,D4_PIN);
		D4 = 1;
	}else
	{
		//PIN_LOW(D4_PORT,D4_PIN);
		D5 = 0;
	}
	//PIN_HIGH(EN_PORT,EN_PIN);
	EN = 1;
	PIN_LOW(EN_PORT,EN_PIN);
	//EN = 0;
}

void lcd_puts(uint8_t x, uint8_t y, int8_t *string)
{
	//Set Cursor Position
	#ifdef LCD16xN	//For LCD16x2 or LCD16x4
	switch(x)
	{
		case 0: //Row 0
			lcd_write(0,0x80+0x00+y);
			break;
		case 1: //Row 1
			lcd_write(0,0x80+0x40+y);
			break;
		case 2: //Row 2
			lcd_write(0,0x80+0x10+y);
			break;
		case 3: //Row 3
			lcd_write(0,0x80+0x50+y);
			break;
	}
	#endif
	
	#ifdef LCD20xN	//For LCD20x4
	switch(x)
	{
		case 0: //Row 0
			lcd_write(0,0x80+0x00+y);
			break;
		case 1: //Row 1
			lcd_write(0,0x80+0x40+y);
			break;
		case 2: //Row 2
			lcd_write(0,0x80+0x14+y);
			break;
		case 3: //Row 3
			lcd_write(0,0x80+0x54+y);
			break;
	}
	#endif
	
	while(*string)
	{
		lcd_write(1,*string);
		string++;
	}
}
void lcd_clear(void)
{
	lcd_write(0,0x01);
}