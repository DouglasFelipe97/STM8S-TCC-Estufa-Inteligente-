#include <iostm8s005K6.h>
#include <intrinsics.h>
#include "delay.h"
#include "GPIO.h"
/*------------- Define LCD Use -----------------*/
/*Note: Comment which not use */

#define LCD16xN //For lcd16x2 or lcd16x4
//#define LCD20xN //For lcd20x4

/*------------ Declaring Function Prototype -------------*/
void lcd_init(void);
void lcd_write(uint8_t type,uint8_t data);
void lcd_puts(uint8_t x, uint8_t y, int8_t *string);
void lcd_clear(void);
#endif