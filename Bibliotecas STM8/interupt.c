#include <iostm8s005K6.h>
#include <intrinsics.h>
#include "GPIO.h"
#include "delay.h"
#include "interupt.h"

extern unsigned int leitura_ad;
//-----------------------//
extern unsigned char int_5mS; 
extern unsigned char int_8mS; 
extern unsigned char int_1S; 
extern unsigned char temporizador_led;
extern unsigned int ledb;
//-----------------------//
extern unsigned char temporizador_pulso_1;
extern unsigned char temporizador_pulso_2;
extern unsigned char temporizador_pulso_3;
extern unsigned int  temporizador_pulso_4;
extern unsigned char temporizador_pwm;
extern unsigned char temporizador_pulso_8;
extern unsigned char temporizador_pulso_9;
extern unsigned char temporizador_pulso_10;
extern unsigned char temporizador_pulso_11;
extern unsigned char temporizador_pulso_12;
extern unsigned char temporizador_pulso_11;
extern unsigned char temporizador_pulso_12;
//-----------------------//
extern unsigned char buceta ;
extern unsigned char pwm1;
extern unsigned char pwm2;
extern unsigned char pwm3;
extern unsigned char audio;
extern unsigned char audio_prog;
extern unsigned char strobo;
extern unsigned int  strobo_temp;
extern unsigned char strobo_temp_ajust;
extern unsigned char strobo_temp_max;
extern unsigned char strobo_temp_mami;
//-----------------------//
extern unsigned char tempo_1;
extern unsigned char tempo_2;
extern unsigned char tempo_3;
extern unsigned char tempo_4;
extern unsigned char tempo_5;
extern unsigned char tempo_8;
extern unsigned char tempo_9;
extern unsigned char tempo_10;
extern struct{
    unsigned int seq       : 1;
    unsigned int prog      : 1;
    unsigned int existente : 1;
    unsigned int salvar    : 1;
    unsigned int trava_led : 1;  
    unsigned int led       : 1;  
    unsigned int bt_verde  : 1;
    unsigned int bt_vermelho: 1;
    unsigned int bt_azul  : 1; 
    unsigned int btstrobo : 1;
    unsigned int btprog   : 1; 
    unsigned int btliga   : 1; 
    unsigned int serial_full: 1;  
    unsigned int sonoro   :1;
    unsigned int aumentar :1;
    unsigned int diminuir :1;
    unsigned int bit_cor  :2;
    unsigned int corrent  :1;
    unsigned int ajustar_corrent:1;
    unsigned int trava_corrent  :1;
  }controle;  
//-----------------------//
extern unsigned int p_larg_1_min;
extern unsigned int p_larg_1_max;
extern unsigned int p_larg_2_min;
extern unsigned int p_larg_2_max;
//-----------------------//
extern unsigned long int buffer_rf;	
extern unsigned int  valor_timer;
extern unsigned char fase;
extern unsigned char cont_bits;
extern unsigned char buff_anticode;
extern unsigned long int buff_rf_temp;
extern unsigned char comando_rf;
extern unsigned char buf_rf1; 
extern unsigned char buf_rf2; 
extern unsigned char buf_rf3;
//--------------------------------------------------
extern union {
  unsigned char bits;
  struct {
  unsigned int ant_curto : 1;                         //bit 0, seta quando a primeira parte do bit for curta
  unsigned int parte : 1;                             //bit 1, em zero a primeira parte do bit  
  unsigned int full: 1;                               //bit 2, indica que recebeu um buffer correto
  } bit;
} cont;
//--------------------------------------------------
extern struct {
		unsigned int buffer_full : 1;
		unsigned int bit_h_3ck :1;
		unsigned int bit_l_3ck :1;
		unsigned int bit_h_1ck :1;
		unsigned int bit_l_1ck :1;
		unsigned int bit_erro  :1;
		unsigned int bit_cont  :8;
		unsigned int bit_passos:8;
	   }ev1527;
	   //---------------//
	   extern unsigned long int buffer_ev1527;
	   extern unsigned long int temp_buffer_ev1527;
//---------------//
extern  struct{ 
     unsigned int stop_bit :1;
   }ajuste;
//---------------// 
 extern  struct{
    unsigned int buf_cheio     : 1; 	 
  }serial;
  //---------------// 
  extern unsigned char buff_blu_temp[41];
  extern unsigned char pont_buff_blu_temp;
  extern unsigned char buff_blu[41];
     //--------------------------------------------- 
   extern struct{
      unsigned int hora_full      : 1; 
      unsigned int segundos_pulso : 1; 
      unsigned int hora_ajuste    : 1;// flag para  ajustar horas 
      unsigned int display_piscar : 1;// flag para piscar display quando estiver em mode de ajustar horas
      unsigned int hora_seletor   : 1;// usado para selecionar lado das horas e dos minutos
      unsigned int passo_menu     : 8;
   }ds;
 /*----- Variáveis DS1307 Relógio ----------------*/
   extern unsigned char hora;
   extern unsigned char minutos;
   extern unsigned char segundos;
   extern unsigned char semana;
   extern unsigned char dias;
   extern unsigned char meses;
   extern unsigned char anos;
   extern unsigned char str_hora[9];
   extern unsigned char str_data[16];
   extern unsigned char pulso;
          //----// 
   extern unsigned char ajuste_hora;
   extern unsigned char ajuste_minutos;
   extern unsigned char ajuste_dias;
   extern unsigned char ajuste_mes;
   extern unsigned char ajuste_semana;
   extern unsigned char ajuste_ano;
          //----// 
   extern unsigned char fonte;
   extern unsigned int  temp_3segundos;
   extern unsigned int  temp_ds_3segundos;
   extern unsigned int  temp_timmer_3segundos;
   extern unsigned long int  temp_s1;
   extern unsigned long int  temp_s2; // usado para controlar quando for ligar não interferi no controle manual
   extern unsigned long int  temp_s3;
   extern unsigned long int  temp_s4;
   extern unsigned long int  temp_s1_desliga;
   extern unsigned long int  temp_s2_desliga; // usado para controlar quando for ligar não interferi no controle manual
   extern unsigned long int  temp_s3_desliga;
   extern unsigned long int  temp_s4_desliga;
          //----// 
   extern unsigned char leitura_ds; 
//--------------------------------------------- 
extern struct{
    unsigned int s1_hora_ligar       : 8; 
    unsigned int s1_minutos_ligar    : 8; 
    unsigned int s1_hora_desligar    : 8; 
    unsigned int s1_minutos_desligar : 8; 
    unsigned int s2_hora_ligar       : 8; 
    unsigned int s2_minutos_ligar    : 8; 
    unsigned int s2_hora_desligar    : 8; 
    unsigned int s2_minutos_desligar : 8; 
    unsigned int s3_hora_ligar       : 8; 
    unsigned int s3_minutos_ligar    : 8; 
    unsigned int s3_hora_desligar    : 8; 
    unsigned int s3_minutos_desligar : 8; 
    unsigned int s4_hora_ligar       : 8; 
    unsigned int s4_minutos_ligar    : 8;
    unsigned int s4_hora_desligar    : 8; 
    unsigned int s4_minutos_desligar : 8; 
    unsigned int prog_tivo_s1     : 1;// informa qual saida está com programa ativo
    unsigned int prog_tivo_s2     : 1;
    unsigned int prog_tivo_s3     : 1;
    unsigned int prog_tivo_s4     : 1;
    unsigned int programar_s1     : 1;//informa que está programando saidas 
    unsigned int programar_s2     : 1;
    unsigned int programar_s3     : 1;
    unsigned int programar_s4     : 1;
    unsigned int passo_programa   : 8;
    unsigned int piscar_led       : 1;
    unsigned int seletor          : 1;
         //----//
    unsigned int s1_domingo       : 1;
    unsigned int s1_segunda       : 1;
    unsigned int s1_terca         : 1;
    unsigned int s1_quarta        : 1;
    unsigned int s1_quinta        : 1;
    unsigned int s1_sexta         : 1;
    unsigned int s1_sabado        : 1;
         //----//
    unsigned int s2_domingo       : 1;
    unsigned int s2_segunda       : 1;
    unsigned int s2_terca         : 1;
    unsigned int s2_quarta        : 1;
    unsigned int s2_quinta        : 1;
    unsigned int s2_sexta         : 1;
    unsigned int s2_sabado        : 1;
    //----//
	  unsigned int s3_domingo       : 1;
	  unsigned int s3_segunda       : 1;
	  unsigned int s3_terca         : 1;
	  unsigned int s3_quarta        : 1;
	  unsigned int s3_quinta        : 1;
	  unsigned int s3_sexta         : 1;
	  unsigned int s3_sabado        : 1;
		  //----//
	  unsigned int s4_domingo       : 1;
	  unsigned int s4_segunda       : 1;
	  unsigned int s4_terca         : 1;
	  unsigned int s4_quarta        : 1;
	  unsigned int s4_quinta        : 1;
	  unsigned int s4_sexta         : 1;
	  unsigned int s4_sabado        : 1;    
	  //----//
	  unsigned int timmer_s1_ativado  : 1;
	  unsigned int timmer_s2_ativado  : 1;
	  unsigned int timmer_s3_ativado  : 1;
	  unsigned int timmer_s4_ativado  : 1;
	  unsigned int apagar_prog        : 1;
	  unsigned int passo_deletar_prog : 8;
	  unsigned int apaar_prog_temp    : 8;
 }saidas;
//--------  Variáveis  interupçao  ---------------------------//
extern unsigned char temp_150ms;
extern unsigned char temp_100ms;
extern unsigned char passos;
extern unsigned char temp_50ms;
extern unsigned char sequencia;
extern unsigned char leitura_ds;
extern unsigned char temp_pisca_ajust;
extern unsigned int  temp_prot_corente;
extern unsigned char temp_led;  
extern unsigned int  temporizador_gravar;
//---------------------------------------------------------------------------//
void int_rf(void){
    valor_timer = 0;
   valor_timer |= TIM2_CNTRH;              // Lê a parte baixa
   valor_timer <<=8;
   valor_timer |= TIM2_CNTRL;           // Lê a parte alta  
   TIM2_CNTRH = 0;
   TIM2_CNTRL = 0;
   
  // led_b = !led_b;
   	/*--------------------------------------------------------------------------------
	  --- decoder  EV1527  tempo base 3CK = (730us á 1.64mS)  1CK = (196uS á 547uS) -- 
	  --------------------------------------------------------------------------------*/
    switch(ev1527.bit_passos){
      case 0:     //recebendo o bits primeira parte
        if(!rf){                                     //verifica se a entrada mudou para 0
              if((valor_timer >= 190)&&(valor_timer <= 424)){ // 730uS á 1.64mS
           	     ev1527.bit_h_3ck = 1;
           	     ev1527.bit_passos = 1;
               }else{
              	 if((valor_timer >= 50)&&(valor_timer <= 141)){  // 196uS á 547mS 
              		ev1527.bit_h_1ck = 1; 
              		ev1527.bit_passos = 1;
              	 }else{
               	    ev1527.bit_h_3ck = 0; // zerar flags
               	    ev1527.bit_h_1ck = 0; 
               	    ev1527.bit_passos = 0;
              	 }// voltar e pegar bit valido     
               }
          }else{
        	  ev1527.bit_h_3ck = 0;
        	  ev1527.bit_h_1ck = 0; 
        	  ev1527.bit_passos = 0;
          }// voltar e pegar bit valido       
      break;
      //---------------//
      case 1:   //recebendo o bits segunda parte

          if(rf){                                     //verifica se a entrada mudou para 0
             if((valor_timer >= 180)&&(valor_timer <= 424)){// bit =  ( 0)
          	     if(ev1527.bit_h_1ck == 1){
          	    	if(ev1527.bit_cont > 1 ){temp_buffer_ev1527 = temp_buffer_ev1527 << 1;}
          	     }else{ev1527.bit_erro = 1;}
               }else{  // verificar se chegou parte alta ou baixar 
              	 if((valor_timer >= 50)&&(valor_timer <= 141)){// bit =  ( 0)
              		if(ev1527.bit_h_3ck == 1){ 
              			temp_buffer_ev1527 += 1; 
              			if(ev1527.bit_cont > 1 ){temp_buffer_ev1527 = temp_buffer_ev1527 << 1;}
              		}else{ev1527.bit_erro = 1;}
              	 }else{ev1527.bit_erro = 1;}// sinalizar erro   
               } 
            }else{
            	     ev1527.bit_erro = 1;
                 }   	  
          //--------------------------// 
		 if(!ev1527.bit_erro){
			 if(ev1527.bit_cont){
				 ev1527.bit_cont --;
				 if(!ev1527.bit_cont){
					  buffer_ev1527 =  temp_buffer_ev1527; 
					  ev1527.buffer_full = 1;
					  ev1527.bit_passos = 0;  // se  der algum erro zerar flags e voltar do inicio
					  ev1527.bit_h_1ck = 0;
					  ev1527.bit_l_1ck = 0;
					  ev1527.bit_h_3ck = 0;
					  ev1527.bit_l_3ck = 0;
					  ev1527.bit_erro  = 0;
					  ev1527.bit_cont  = 24;   
					  temp_buffer_ev1527 = 0;
				    }

			 } 
			 ev1527.bit_passos = 0; // pegar outro bit
		   }else{
			  ev1527.bit_passos = 0;  // se  der algum erro zerar flags e voltar do inicio
			  ev1527.bit_h_1ck = 0;
			  ev1527.bit_l_1ck = 0;
			  ev1527.bit_h_3ck = 0;
			  ev1527.bit_l_3ck = 0;
			  ev1527.bit_erro  = 0;
			  ev1527.bit_cont  = 24;   
			  temp_buffer_ev1527 = 0;
		   }
      break;
    }
//----------------------------------------------------------------------	
     switch(fase){

       
       case 0:                                        //recebendo o bit de sincronismo
         if(rf){ 
      
        	 //verifica se a entrada mudou para 1
           if((valor_timer >= p_sinc_min_1m5)&&(valor_timer <= p_sinc_max_1m5)){
			   fase = 1; 
			   p_larg_1_min = p_larg_1_min_1m5;
			   p_larg_1_max = p_larg_1_max_1m5;
			   p_larg_2_min = p_larg_2_min_1m5;
			   p_larg_2_max = p_larg_2_max_1m5;
           } 
        
           
           
           if((valor_timer >= p_sinc_min_2m2)&&(valor_timer <= p_sinc_max_2m2)){
        	  
			   fase = 1; 
			   p_larg_1_min = p_larg_1_min_2m2;
			   p_larg_1_max = p_larg_1_max_2m2;
			   p_larg_2_min = p_larg_2_min_2m2;
			   p_larg_2_max = p_larg_2_max_2m2;
           }
           
           
         }
       break;

       case 1:                                        //recebendo o start bit
         if(!rf){                                     //verifica se a entrada mudou para 0
           if((valor_timer >= p_larg_1_min)&&(valor_timer <= p_larg_1_max)){
        
			   fase = 2; 
			   cont_bits = 0;
			   cont.bit.ant_curto = 0;                    //limpa o flag
			   cont.bit.parte = 0;                        //limpa o flag
			   buff_rf_temp = 0;                          //limpa o buffer de rx
           
           } 
         } else {                                     //se neste ponto a entrada não for 0 é erro
           fase = 0;                                  //reinicia o processo
           }
       break;
       
       
       case 2:                                        //recebendo os bits 
         if(!cont.bit.parte){                         //se não recebeu a primeira parte do bit
          
           if(rf){                                    //verifica se a entrada mudou para 1
             if((valor_timer >= p_larg_1_min)&&(valor_timer <= p_larg_1_max)){ // se a parte recebida fo largura 1
             cont.bit.parte = 1;                      //indica que ja recebeu a primeira parte do bit
             cont.bit.ant_curto = 1;                  //indica que a parte recebida foi curta
             } else {
                 if((valor_timer >= p_larg_2_min)&&(valor_timer <= p_larg_2_max)){ // se a parte recebida fo largura 2
                 cont.bit.parte = 1;                  //indica que ja recebeu a primeira parte do bit
                 cont.bit.ant_curto = 0;              //indica que a parte recebida não foi curta
                 } else {                             //se naõ for largura 1 nem 2 é erro
                   fase = 0;
                   }
               } 
           } else {                                   //se não for 1 é erro
             fase = 0;
             }

         } else {                                     //recebe a segunda parte do bit
             if(!rf){                                 //verifica se a entrada mudou para 10
             buff_rf_temp <<= 1;                      //desloca o buffer 1 bit 

               if(cont.bit.ant_curto){                //se o bit anterior for curto
                 if((valor_timer >= p_larg_2_min)&&(valor_timer <= p_larg_2_max)){ // se a parte recebida fo largura 2 recebeu um bit 0
                 cont_bits++;
                   if(cont_bits == 24){               //se ja recebeu os 24 bits
                   fase = 3; 
                   cont_bits = 0;
                   cont.bit.ant_curto = 0;            //limpa o flag
                   cont.bit.parte = 0;                //limpa o flag
                   buff_anticode = 0;                 //limpa o buffer de rx 
                   }
                
                 } else {                             //se não receber um bit longo é erro
                   fase = 0;
                   }

               } else {                               //se o bit anterior foi longo
                   if((valor_timer >= p_larg_1_min)&&(valor_timer <= p_larg_1_max)){ // se a parte recebida fo largura 1 recebeu um bit 1
                    buff_rf_temp |= 1;                //insere o bit 1 recebido no buffer
                    cont_bits++;
                     if(cont_bits == 24){             //se ja recebeu os 24 bits
                     fase = 3; 
                     cont_bits = 0;
                     cont.bit.ant_curto = 0;          //limpa o flag
                     cont.bit.parte = 0;              //limpa o flag
                     buff_anticode = 0;               //limpa o buffer de rx 
                     }
                   } else {                           //se não receber um bit curto é erro
                     fase = 0;
                     } 
                 }

             } else {                                 //se não for 0 é erro
               fase = 0;
               }
           cont.bit.parte = 0;                        //limpa o flag para iniciar um novo ciclo
           }
         
       break;
       

       case 3:                                        //recebendo o anticode
         if(!cont.bit.parte){                         //se não recebeu a primeira parte do bit
          
           if(rf){                                    //verifica se a entrada mudou para 1
             if((valor_timer >= p_larg_1_min)&&(valor_timer <= p_larg_1_max)){ // se a parte recebida fo largura 1
             cont.bit.parte = 1;                      //indica que ja recebeu a primeira parte do bit
             cont.bit.ant_curto = 1;                  //indica que a parte recebida foi curta
             } else {
                 if((valor_timer >= p_larg_2_min)&&(valor_timer <= p_larg_2_max)){ // se a parte recebida fo largura 2
                 cont.bit.parte = 1;                  //indica que ja recebeu a primeira parte do bit
                 cont.bit.ant_curto = 0;              //indica que a parte recebida não foi curta
                 } else {                             //se naõ for largura 1 nem 2 é erro
                   fase = 0;
                   }
               } 
           } else {                                   //se não for 1 é erro
             fase = 0;
             }

         } else {                                     //recebe a segunda parte do bit
             if(!rf){                                 //verifica se a entrada mudou para 10
             buff_anticode <<= 1;                     //desloca o buffer 1 bit 

               if(cont.bit.ant_curto){                //se o bit anterior for curto
                 if((valor_timer >= p_larg_2_min)&&(valor_timer <= p_larg_2_max)){ // se a parte recebida for largura 2 recebeu um bit 0
                 cont_bits++;
                   if(cont_bits == 4){                //se ja recebeu os 4 bits
                   fase = 0; 
                     if((buff_anticode == anticode)||(anticode_a)){
                     
                       if(!cont.bit.full){            //se o buffer estiver vazio
                       buffer_rf = buff_rf_temp;      //copia o buffer temporario recebido
                       cont.bit.full = 1;             //seta para indicar que o buffer esta cheio;
                       }
                     
                     }
                   }
                 } else {                             //se não receber um bit longo é erro
                   fase = 0;
                   }

               } else {                               //se o bit anterior foi longo
                   if((valor_timer >= p_larg_1_min)&&(valor_timer <= p_larg_1_max)){ // se a parte recebida for largura 1 recebeu um bit 1
                   buff_anticode |= 1;                //insere o bit 1 recebido no buffer
                   cont_bits++;
                     if(cont_bits == 4){              //se ja recebeu os 4 bits
                     fase = 0; 
                    
                       if((buff_anticode == anticode)||(anticode_a)){
                         
                         if(!cont.bit.full){          //se o buffer estiver vazio
                         buffer_rf = buff_rf_temp;    //copia o buffer temporario recebido
                         cont.bit.full = 1;           //seta para indicar que o buffer esta cheio;
                         if(buff_anticode == anticode){ajuste.stop_bit = 1;}else{ajuste.stop_bit = 0;}// diferencia um controle do outro
                         }
                       }
                     }
                   } else {                           //se não receber um bit curto é erro
                     fase = 0;
                     } 
                 }
             } else {                                 //se não for 0 é erro
               fase = 0;
               }
           cont.bit.parte = 0;                        //limpa o flag para iniciar um novo ciclo
           }
         
       break;
       
       default:
       fase = 0;
       break;
     }    
}
//--------------------------------------------------//
void interupecao_5ms(void){
   int_5mS ++;
   if(int_5mS >=5){
    int_5mS = 0;
    //----------------//
    if(!controle.corrent && !controle.trava_corrent){
      if(!controle.trava_led){ 
          temporizador_led ++;
          if(!controle.prog){
              if(temporizador_led >= 200){
                 led_a = 1;
                 if(temporizador_led >= 220){
                   led_a = 0;
                   temporizador_led = 0;
                 }  
              }
          }else{
              if(temporizador_led >= 15){
                 led_a = 1;
                 if(temporizador_led >= 18){
                   led_a = 0;
                   temporizador_led = 0;
                 }  
              }
          } 
      }
    }else{if(!controle.trava_corrent){led_a = 1;}}// si tiver em curto ficar com led aceso informando erro 
    //----------------// 
    if(controle.prog){
       temporizador_gravar ++;
       if(temporizador_gravar >= 2000){
         controle.prog = 0;
         temporizador_gravar = 0;
       }
    }else{temporizador_gravar = 0;}
    
  //---------------------------------------------//  
		        if(temporizador_pulso_1){
		        temporizador_pulso_1 --; 
		          if(!temporizador_pulso_1){
		          saida_1 = 0;
		          }
		        }
		    /*
		       if(temporizador_pulso_2){
		        temporizador_pulso_2 --; 
		          if(!temporizador_pulso_2){
		          saida_2 = 0;
		          }
		        }

		        if(temporizador_pulso_3){
		        temporizador_pulso_3 --; 
		          if(!temporizador_pulso_3){
		          saida_3 = 0;
		          }
		        }  
                       */

		        if(temporizador_pulso_4){
		        temporizador_pulso_4 --; 
		          if(!temporizador_pulso_4){
		        	  audio = 0;
		        	  controle.sonoro = 0;
		          }
		        }
		      
		      
		        if(temporizador_pulso_8){
		        temporizador_pulso_8 --; 
		          if(!temporizador_pulso_8){

		          }
		        }
		        if(temporizador_pulso_9){
		        temporizador_pulso_9 --; 
		          if(!temporizador_pulso_9){

		          }
		        }
		        if(temporizador_pulso_10){
		        temporizador_pulso_10 --; 
		          if(!temporizador_pulso_10){

		          }
		        }
		        
		        if(temporizador_pulso_11){
		          temporizador_pulso_11 --; 
		           if(!temporizador_pulso_11){
	                 controle.aumentar = 0;
		            }
		         }	        
		        
		        if(temporizador_pulso_12){
		          temporizador_pulso_12 --; 
		           if(!temporizador_pulso_12){
	                 controle.diminuir = 0;
		            }
		         }		        
		        
		        if(temporizador_pwm){
		        	temporizador_pwm --; 
		          if(!temporizador_pwm){
		        	  audio = 0;
		          }
		        }	 
		        

		        if(tempo_1){
		        tempo_1 --; 
		        }
		        
		        if(tempo_2){
		        tempo_2 --; 
		        }
		        
		        if(tempo_3){
		        tempo_3 --; 
		        }
		        
		        if(tempo_4){
		        tempo_4 --; 
		        }
		        
		        if(tempo_5){
		        tempo_5 --; 
		        }
		        

		        
		        if(tempo_8){
		        tempo_8 --; 
		        }
		        
		        if(tempo_9){
		        tempo_9 --; 
		        }
		        if(tempo_10){
		        tempo_10 --; 
		        } 
  
    //-------------------
    if(leitura_ds >= 80){
	leitura_ds = 0;
	ds.hora_full = 1;
        //led_b = !led_b;
	ds.segundos_pulso = !ds.segundos_pulso;
      }else{
	  leitura_ds ++;
	  }
    //-------------------
  //-------------------		        
    if(ds.hora_ajuste){
       if(temp_pisca_ajust >= 50){
    	   temp_pisca_ajust = 0;
    	   ds.display_piscar = !ds.display_piscar;	
    	  }else{temp_pisca_ajust ++;}	
		}else{temp_pisca_ajust = 0;}
//-------------------			        
    if(controle.corrent){
    	if(temp_prot_corente){temp_prot_corente --;}
    	   if(!temp_prot_corente){
    		   controle.corrent = 0;
    	  }
      }
//-----     Lógica para programar programas    ---------///		        
        if(saidas.programar_s1 || saidas.programar_s2  || saidas.programar_s3  || saidas.programar_s4 || saidas.apagar_prog){// flag usado para piscar led da saida  quando for programar
           if(temp_led >= 50){
        	   temp_led = 0;
        	   saidas.piscar_led = !saidas.piscar_led;	
        	  }else{temp_led ++;}	
    		}else{temp_led = 0;}
    //------  Usado para  horas e dias da semana que os canais iram ligar  -----//			        
	if(temp_3segundos){
		temp_3segundos --;
		if(!temp_3segundos){	
		     switch(saidas.passo_programa){
				   case 0:
					   saidas.passo_programa = 1;
					   break;
					   //----//
				   case 1:
					   saidas.passo_programa = 2;
					   break;
					   //----//
				   case 2:
					   saidas.passo_programa = 3;
					   break;
					   //----//
				   case 3:
					   saidas.passo_programa = 4;
					   break;
					   //----//
				   case 4:
					   saidas.passo_programa = 5;
					   break;
					   /*
					   //----//
				   case 5:
					   saidas.passo_programa = 6;
					   break;
					   //----//
				   case 6:
					   saidas.passo_programa = 7;
					   break;
					   //----//
				   case 7:
					   saidas.passo_programa = 8;
					   break;
					   //----//
				   case 8:
					   saidas.passo_programa = 9;
					   break;
					   //----//
				   case 9:
					   saidas.passo_programa = 10;
					   break;
					   //----//
				   case 10:
					   saidas.passo_programa = 11;
					   break;
					   //----//
				   case 11:
					   saidas.passo_programa = 0;
					   saidas.programar_s1 = 0; // desligar flags de programação
					   saidas.programar_s2 = 0;
					   saidas.programar_s3 = 0;
					   saidas.programar_s4 = 0;
					   break;
					   //----//
					    */
			   } 
		}
	}
    //------  Usado para  programar relogio horas e dias da semana  -----//			        
	if(temp_ds_3segundos){
		temp_ds_3segundos --;
		if(!temp_ds_3segundos){	
		     switch(ds.passo_menu){
				   case 0:
					   ds.passo_menu = 1;
					   break;
					   //----//
				   case 1:
					   ds.passo_menu = 2;
					   break;
					   //----//
				   case 2:
					   ds.passo_menu = 3;
					   break;
					   //----//
				   case 3:
					   ds.passo_menu = 4;
					   break;
					   //----//
				   case 4:
					   ds.passo_menu = 5;
					   break;
					   //----//
				   case 5:
					   ds.passo_menu = 6;
					   break;

					   //----//
				   case 6:
					   ds.passo_menu =7;
					   break;

					   //----//
				   case 7:
					   ds.passo_menu = 8;
					   break;
					   //----//
				   case 8:
					   ds.passo_menu = 9;
					   break;
				
			   } 
		}
	}
    //------  Usado para  programar relogio horas e dias da semana  -----//			        
	if(temp_timmer_3segundos){
		temp_timmer_3segundos --;
		if(!temp_timmer_3segundos){	
		     switch(saidas.passo_deletar_prog){
				   case 0:
					   if(saidas.timmer_s1_ativado || saidas.timmer_s2_ativado || saidas.timmer_s3_ativado || saidas.timmer_s4_ativado ){
						   saidas.passo_deletar_prog = 2;
						   if(saidas.timmer_s1_ativado){saidas.apaar_prog_temp = saidas.apaar_prog_temp | 0x01;}
						   if(saidas.timmer_s2_ativado){saidas.apaar_prog_temp = saidas.apaar_prog_temp | 0x02;}
						   if(saidas.timmer_s3_ativado){saidas.apaar_prog_temp = saidas.apaar_prog_temp | 0x04;}
						   if(saidas.timmer_s4_ativado){saidas.apaar_prog_temp = saidas.apaar_prog_temp | 0x08;}
					     }else{
					    	 temp_timmer_3segundos = temp_espera_display; 
					    	 saidas.passo_deletar_prog = 1; 
					     }
					   break;
					   //----//
				   case 1:
					   saidas.apagar_prog = 0;
					   saidas.passo_deletar_prog = 0;
					   break;
			   } 
		}
	}		
 //------  Usado para controlar acionamento do timmer automatico paranão interferi no manual  -----//	
	if(temp_s1){temp_s1 --;}
	if(temp_s2){temp_s2 --;}	
	if(temp_s3){temp_s3 --;}	
	if(temp_s4){temp_s4 --;}	
	
	if(temp_s1_desliga){temp_s1_desliga --;}
	if(temp_s2_desliga){temp_s2_desliga --;}	
	if(temp_s3_desliga){temp_s3_desliga --;}	
	if(temp_s4_desliga){temp_s4_desliga --;}
//----------------------------------------------------------//
        leitura_ad = ADC_Read(0);
           //----//
    	switch(fonte){
	case 0 :// sensor corrent deslifado OFF display
	default:
          
		break;
		//---//
       case 2 :
		if(leitura_ad >= protecao_ad_2a){  
			 controle.corrent = 1;
			 pwm1 = 255;
			 pwm2 = 255;
			 pwm3 = 255;
			 temp_prot_corente = 1000;
		   }
		break;
	case 5 :
		if(leitura_ad >= protecao_ad_5a){  
			 controle.corrent = 1;
			 pwm1 = 255;
			 pwm2 = 255;
			 pwm3 = 255;
			 temp_prot_corente = 1000;
		   }
		break;
		//---//
	case 10 :
		if(leitura_ad >= protecao_ad_10a){  
			 controle.corrent = 1;
			 pwm1 = 255;
			 pwm2 = 255;
			 pwm3 = 255;
			 temp_prot_corente = 1000;
		   }
		break;
		//---//
	case 15 :
		if(leitura_ad >= protecao_ad_15a){  
			 controle.corrent = 1;
			 pwm1 = 255;
			 pwm2 = 255;
			 pwm3 = 255;
			 temp_prot_corente = 1000;
		   }
		break;
		//---//
	case 20 :
		if(leitura_ad >= protecao_ad_20a){  
			 controle.corrent = 1;
			 pwm1 = 255;
			 pwm2 = 255;
			 pwm3 = 255;
			 temp_prot_corente = 1000;
		   }
		break;
		//---//
	case 25 :
		if(leitura_ad >= protecao_ad_25a){  
			 controle.corrent = 1;
			 pwm1 = 255;
			 pwm2 = 255;
			 pwm3 = 255;
			 temp_prot_corente = 1000;
		   }
		break;
		//---//
	}
   }		
}
//------------------------------------------------------------------------------
void ADC_Init(void){
    ADC_CR1_bit.ADON = 1;   // Dispara uma conversão
    ADC_CR2_bit.ALIGN = 1;  // Conversor em 10 bits    
}
//------------------------------------------------------------------------------
unsigned int ADC_Read(unsigned char Canal){
   unsigned int ADC_Result = 0;        // Cria uma variável temporária
           ADC_CSR_bit.CH = Canal;             // Seleciona um canal
           ADC_CR1_bit.ADON = 1;               // Dispara uma conversão
           while(!ADC_CSR_bit.EOC);            // Espera finalizar a conversão
           ADC_CSR_bit.EOC = 0;                // Indica que finalizou a conversão
           ADC_Result |= ADC_DRL;              // Lê a parte baixa
           ADC_Result |= ADC_DRH<<8;           // Lê a parte alta
           return ADC_Result;                  // Retorna o valor do ADC
}
//----------------------------------------------------------------------------
void UART_Init(void){
  /*
    UART1_BRR2 = 0x00;
    UART1_BRR1 = 0x0D;                  // BR = 2MHz/9600 = 208 -> 0xD0
    UART1_CR2  = 0x2C;                   // RIEN ON, TX e RX ON 
    */
   	UART2_CR1 = 0x00; // 0000.0000 Enable UART 8bit, no parity
	UART2_CR3 = 0x00; // 0000.0000 1 stop bit
        
	UART2_CR6 = 0x08; // 0000.0000 no dma, half duplex
        
	//UART2_BRR2 = 0x03; // set 9600 BPS
	//UART2_BRR1 = 0x68; 
	UART2_BRR2 = 0x01; // set 19200 BPS
	UART2_BRR1 = 0x34;         

	UART2_CR2 = 0x2C; // 0010.1100 Enable RX irq, Enable TX and RX 
    
    
}
//---------------------------------------------------------------------------
void transmite_as1(unsigned char Chr){
    UART2_DR = Chr;                     // Coloca o byte no buffer de saída
    while(!UART2_SR_bit.TXE);           // Espera o byte sair do buffer
  // uart_Write(dado);
}
/*--------------------------------------------------*/
void transmite_string_as1(char *c){  
  while(*c){                                         //aguarda o buffer de tx estar vazio
  transmite_as1(*c);
  c++;
  }                                                  // transmite o caracter recebido 
}
//---------------------------------------------------------------------------
void uart_Write(unsigned char Chr){
    UART2_DR = Chr;                     // Coloca o byte no buffer de saída
    while(!UART2_SR_bit.TXE);           // Espera o byte sair do buffer
}
//----------------------------------------------------------------------------