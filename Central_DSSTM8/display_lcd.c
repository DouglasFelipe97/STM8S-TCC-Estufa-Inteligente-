#include <iostm8s005K6.h>
#include <intrinsics.h>
#include "GPIO.h" // definição dos pinos entradas e saidas
#include "delay.h"
/*-------------------------------------------------------------------*/ 
void escreve_lcd(unsigned char d){   
  
  if(d & 0x80)lcd_7 = 1;
  else lcd_7 = 0;
  if(d & 0x40)lcd_6 = 1;
  else lcd_6 = 0;
  if(d & 0x20)lcd_5 = 1;
  else lcd_5 = 0;
  if(d & 0x10)lcd_4 = 1;
  else lcd_4 = 0;
  
  delay_100us(1);
  lcd_e = 1;
  delay_100us(1);
  lcd_e = 0;
  delay_100us(1);
  
  if(d & 0x08)lcd_7 = 1;
  else lcd_7 = 0;
  if(d & 0x04)lcd_6 = 1;
  else lcd_6 = 0;     
  if(d & 0x02)lcd_5 = 1;
  else lcd_5 = 0;
  if(d & 0x01)lcd_4 = 1;
  else lcd_4 = 0;
  
  delay_100us(1);
  lcd_e = 1;
  delay_100us(1);
  lcd_e = 0;
  delay_100us(1);
 }
/*-------------------------------------------------------------------*/
 void escreve_comando_lcd(unsigned char d){   
    lcd_rs = 0;
    escreve_lcd(d);
 }
/*-------------------------------------------------------------------*/
 void escreve_dado_lcd(unsigned char d){   
    lcd_rs = 1;
    escreve_lcd(d);
 }
/*-------------------------------------------------------------------*/
 void limpa_lcd(void){   
    escreve_comando_lcd(0x01);
    delay_ms(4);
   }
/*-------------------------------------------------------------------*/
 void linha_1_lcd(void){   
    escreve_comando_lcd(0x80);
    delay_ms(4);
  }    
/*-------------------------------------------------------------------*/
 void linha_2_lcd(void){   
    escreve_comando_lcd(0xC0);
    delay_ms(4);
  } 
/*-------------------------------------------------------------------*/
 void linha_3_lcd(void){   
   escreve_comando_lcd(0x94);
   delay_ms(4);
  } 
/*-------------------------------------------------------------------*/
 void linha_4_lcd(void){   
   escreve_comando_lcd(0xD4);
   delay_ms(4);
  }   
/*-------------------------------------------------------------------*/
 void inicializa_lcd(void){   
    lcd_rw = 0;
    lcd_e = 0;
    delay_ms(20);
    escreve_comando_lcd(0x33);                         /*inicializa lcd*/
    delay_ms(5);
    escreve_comando_lcd(0x33);                         /*inicializa lcd*/
    delay_ms(100);
    escreve_comando_lcd(0x33);                         /*inicializa lcd*/
    escreve_comando_lcd(0x32);                         /*comunicação em 4 bits*/
    delay_ms(100);
    limpa_lcd();
    escreve_comando_lcd(0x0C);                         /*liga display sem cursor*/
    delay_ms(2);
    escreve_comando_lcd(0x06);                         /*seleciona incremento automático a direita*/
    delay_ms(2);
    limpa_lcd();
 }
 /*-------------------------------------------------------------------*/
  void reinicializar_lcd(void){   
     lcd_rw = 0;
     lcd_e = 0;
     delay_ms(20);
     escreve_comando_lcd(0x33);                         /*inicializa lcd*/
     delay_ms(5);
     escreve_comando_lcd(0x33);                         /*inicializa lcd*/
     delay_ms(100);
     escreve_comando_lcd(0x33);                         /*inicializa lcd*/
     escreve_comando_lcd(0x32);                         /*comunicação em 4 bits*/
     delay_ms(100);
     escreve_comando_lcd(0x0C);                         /*liga display sem cursor*/
     delay_ms(2);
     escreve_comando_lcd(0x06);                         /*seleciona incremento automático a direita*/
     delay_ms(2);
  } 
/*-------------------------------------------------------------------*/
void escreve_string_lcd(unsigned char *str,unsigned char linha){   
unsigned char p;


switch(linha){
	   case 1 :
		 linha_1_lcd();  
	   break;
	   case 2 :
		 linha_2_lcd();  
	   break;
	   case 3 :
		 linha_3_lcd();  
	   break;
	   case 4 :
		 linha_4_lcd();  
	   break;
}
//---------//
while(*str){                                         //aguarda o buffer de tx estar vazio
  *str = toupper(*str);	 // converter para maiusculo 
  escreve_dado_lcd(*str);
  str++;
} 
}
/*-------------------------------------------------------------------*/
void escreve_string(unsigned char *str){   
while(*str){                                         //aguarda o buffer de tx estar vazio
escreve_dado_lcd(*str);
str++;
} 
}