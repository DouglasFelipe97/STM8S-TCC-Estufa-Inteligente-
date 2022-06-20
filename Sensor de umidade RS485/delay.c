#include <iostm8s003f3.h>
#include <intrinsics.h>
#include "GPIO.h" // definição dos pinos entradas e saidas
#include "delay.h"
//---------------------------------------------------------------------------//
void delay_ms(unsigned int temp){
  unsigned int temp_1;
  while(temp){
   for(temp_1 = 2600;temp_1>1;temp_1--){_NOP();}// atraso calculado para 1mS
    temp --;
  }
}
//---------------------------------------------------------------------------//
void delay_100us(unsigned int temp){
  unsigned int temp_1;
  while(temp){
   for(temp_1 = 255;temp_1>1;temp_1--){_NOP();}// atraso calculado para 1mS
    temp --;
  }
}
 //---------------------------------------------------------------------------// 