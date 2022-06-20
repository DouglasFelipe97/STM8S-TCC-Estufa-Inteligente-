#include "ds1307.h"
#include "GPIO.h" // definição dos pinos entradas e saidas
#define Cpu_Delay100US  delay_100us
extern unsigned char hora;
extern unsigned char minutos;
extern unsigned char segundos;
extern unsigned char semana;
extern unsigned char dias;
extern unsigned char meses;
extern unsigned char anos;
extern unsigned char str_hora[16];
extern unsigned char str_data[16];

//--------------------------------
void sda_saida(void){
  sda_dir   = 1;  //  is output.
  sda_Push  = 1;  //  Pin is set to Push-Pull mode. 
  sda_fast  = 1;  //  Pin can run up to 10 MHz 
  Cpu_Delay100US(1);
}
//--------------------------------
void sda_entrada(void){
  sda_Push  = 1;      // Pull-up sem interromper
  sda_fast  = 0;      // 
   //----//
  sda_dir   = 0;      //   is Imput.  nãos ei porquer motivo ele trava quando configuro antes esse registrar para entrada
  Cpu_Delay100US(1);
}
//--------------------------------
void start(void){
  sda_saida();
  sda = 1;
  scl = 1;
  Cpu_Delay100US(1);
  sda = 0;
  Cpu_Delay100US(1); //espera um tempinho
  scl = 0;
}
//--------------------------------
void stop(void){
  sda_saida();
  sda = 0;
  scl = 0;
  Cpu_Delay100US(1);
  sda = 1;
  scl = 1;
  Cpu_Delay100US(1);
}
//--------------------------------
void rtc_1(void){
 sda = 1;
 Cpu_Delay100US(1);
 scl = 1;
 Cpu_Delay100US(1); 
 scl = 0;
 sda = 0;
 Cpu_Delay100US(1);
}
//--------------------------------
void rtc_0(void){
 sda = 0;
 Cpu_Delay100US(1);
 scl = 1;
 Cpu_Delay100US(1); 
 scl = 0;
 Cpu_Delay100US(1);
}
//--------------------------------
void clok(void){
scl = 1; 
Cpu_Delay100US(1);   //esperar ack
scl = 0;
Cpu_Delay100US(1);
}
//---------------------------------
unsigned char end_leitura(void){
unsigned char x=0;
    start();
    rtc_1();
    rtc_1();
    rtc_0();
    rtc_1();    //1101000 endereço ds1307
    rtc_0();
    rtc_0();
    rtc_0();
    rtc_1();  // leitura

    sda_entrada();
    scl = 1; 
    Cpu_Delay100US(1);   //testo ack
    if(sda_in){x =1;} //incremento flag para sair se ultrapassa 6 erro ds oculpado
    scl = 0; 
    Cpu_Delay100US(1);
    return x;
}
//---------------------------------
unsigned char  converter_bcb(unsigned char x){ 
  unsigned char temp = 0;
  unsigned char temp1 = 0;
  temp  = x & 0xF0;
  temp1 = x & 0x0F;
  temp = temp >>4;// voltar 4 casas
  x = (temp * 10 +temp1); 
  return x;
}
//---------------------------------
unsigned char  end_escrita(void){
unsigned char x=0;
    start();
    rtc_1();
    rtc_1();
    rtc_0();
    rtc_1();    //1101000 endereço ds1307
    rtc_0();
    rtc_0();
    rtc_0();
    rtc_0();  // escrita
    
    sda_entrada();
    scl = 1; 
    x=0;
    Cpu_Delay100US(1);   //testo ack
    if(sda_in){x =1;} //incremento flag para sair se ultrapassa 6 erro ds oculpado
    scl = 0; 
    Cpu_Delay100US(1);
    sda_saida();
    return x;
}
//-------------------------------------
unsigned char ler_ds1307(unsigned char endereco){  
unsigned char temp = 0;
unsigned char dado = 0; 

   if(end_escrita()){stop(); return 0;}  //se voltar 1 saio

   
   
       //--------------------------------------------------------
       for(temp=0;temp < 8;temp++){  //posiçãoram ds1307 onde vai ser escrito
           if(endereco & 0x80){ rtc_1();}else{rtc_0();}
           endereco = endereco<<1; //rotaciono 1 bit e atribuo na variável
         }//--------------------------------------------------------
 

  
          sda_entrada();
          scl = 1; 
          Cpu_Delay100US(1); //testo ack
          if(sda_in){sda_saida(); stop();return 0;}
          scl = 0; 
          Cpu_Delay100US(1);
          
          
          if(end_leitura()){
             stop();
             return 0 ;
          }  //se voltar 1 saio

            //-------------------------------------------------------- 
             for(temp=0;temp<8;temp++){  //
                  scl = 1; 
                  Cpu_Delay100US(1);   
                  //if(sda){dado = dado |0x01;}
                  if(sda_in){dado  += 1;}
                   scl = 0;
                   Cpu_Delay100US(1);
                   if(temp<7){dado = dado << 1;} //atribuo o valor na mesma variável invertido
                 }              //no laço ele repeti 8 vezes e sai uma rotação de bit a mas devo fazer apenas 6 rotações 
               
                clok(); //mas um clok porque o sale gera um ack

                stop();
                return dado;//retorno o valor comvertido
  }
/*-------------------------------------------------------------------*/
unsigned char  escrever_ds1307(unsigned char endereco, unsigned char dado){  
unsigned char temp = 0; 

   if(end_escrita()){stop();return 0;}  //se voltar 1 saio
   
       //--------------------------------------------------------
       for(temp=0;temp<8;temp++){  //posiçãoram ds1307 onde vai ser escrito
           if(endereco & 0x80){ rtc_1();}else{rtc_0();}
           endereco = endereco<<1; //rotaciono 1 bit e atribuo na variável
         }//--------------------------------------------------------

          sda_entrada();
          scl = 1; 
          Cpu_Delay100US(1); //testo ack
          if(sda_in){stop();return 0;}
           scl = 0; 
          Cpu_Delay100US(1);
        //-------------------------------------------------------------------//     
          
        sda_saida();
        for(temp=0;temp<8;temp++){  //dado a ser escrito  ds1307 
           if(dado & 0x80){ rtc_1();}else{rtc_0();}
             dado = dado<<1; //rotaciono 1 bit e atribuo na variável
         }        

        
        
        
        
        
          sda_entrada();
          scl = 1; 
          Cpu_Delay100US(1); //testo ack
          if(sda_in){stop();return 0;}
          scl = 0; 
          Cpu_Delay100US(1);
          stop();
          return 1;//retorna 1 escrita ok
      
   return 0;
  }
/*-------------------------------------------------------------------*/
unsigned char formatar_hora(unsigned char dado){
 unsigned char temp_1,temp_2;
   temp_1 = 0;
   temp_2  = 0;	
   
   for(;dado>=10;dado -=10)temp_1++;
   for(;dado>=1;dado -=1)temp_2++;
   
    dado = temp_1 <<4;
    dado = dado | temp_2;
    return dado;	
}
/*-------------------------------------------------------------------*/
void ajustar_relogio(unsigned char ho,unsigned char min,unsigned char segu){
  unsigned char dado1,dado2,dado3;	
     dado1 = formatar_hora(ho);
     dado2 = formatar_hora(min);
     dado3 = formatar_hora(segu);
   
	(void)escrever_ds1307(0x00,dado3);//endereço,dado--segundos
	(void)escrever_ds1307(0x01,dado2);//endereço,dado--minutos
	(void)escrever_ds1307(0x02,dado1);//endereço,dado--horas                                                                      // 1  // 2
	/* o bayte e dividido em 4 bits cada grupo de 4 coresponde por exemplo 12 = 0001 0010*/
}
/*-------------------------------------------------------------------*/
void ajustar_data(unsigned char sem,unsigned char dia,unsigned char mes,unsigned char ano){
  unsigned char dado1,dado2,dado3,dado4;	
     dado1 = formatar_hora(sem);
     dado2 = formatar_hora(dia);
     dado3 = formatar_hora(mes);
     dado4 = formatar_hora(ano);
   
	(void)escrever_ds1307(0x03,dado1);
	(void)escrever_ds1307(0x04,dado2);
	(void)escrever_ds1307(0x05,dado3);    
	(void)escrever_ds1307(0x06,dado4);
	/* o bayte e dividido em 4 bits cada grupo de 4 coresponde por exemplo 12 = 0001 0010*/
}
/*-------------------------------------------------------------------*/
void read_rtc(void){
  unsigned char temp,temp_1,temp_segundos,temp_minutos,temp_hora,temp_semana,temp_dias,temp_meses,temp_anos; 
	   temp_segundos = ler_ds1307(0x00); //endereço que eu quero ler retona dado
	   temp_minutos  = ler_ds1307(0x01); //endereço que eu quero ler retona dado
	   temp_hora     = ler_ds1307(0x02); //endereço que eu quero ler retona dado
	   temp_semana   = ler_ds1307(0x03); //endereço dias_semanha 1-7
	   temp_dias     = ler_ds1307(0x04); //endereço dias_semanha 1-30
	   temp_meses    = ler_ds1307(0x05); //endereço meses 1-12
	   temp_anos     = ler_ds1307(0x06); //endereço mano 1-99
	//------------------------------------//
	   temp = temp_hora;
	   temp = temp & 0xF0;
	   temp = temp >>4;
	   temp = (temp*10);
	/*--------------------------*/
	   temp_1 = temp_hora;
	   temp_1 = temp_1 & 0x0F;
	   hora = (temp + temp_1);
	/*--------------------------*/
	   temp = temp_minutos;
	   temp = temp & 0xF0;
	   temp = temp >>4;
	   temp = (temp *10);
	/*--------------------------*/
	   temp_1 = temp_minutos;
	   temp_1 = temp_1 & 0x0F;
	   minutos = (temp + temp_1);
	/*--------------------------*/
           temp = temp_segundos;
           temp = temp & 0xF0;
           temp = temp >>4;
           temp = (temp *10);
	/*--------------------------*/
	   temp = temp_segundos;
	   temp = temp & 0x0F;
	   segundos = (temp + temp_1);
	/*--------------------------*/  
	   temp = temp_semana;      // ler semana
	   temp = temp & 0x07;
	   semana = temp;
	 /*--------------------------*/ 
	   temp = temp_dias;
	   temp = temp & 0x0F; // ler dias do mes 
	 	        //----//
	   temp_1 = temp_dias;
	   temp_1 = temp_1 & 0xF0;
	   temp_1 = temp_1 >>4;
	   dias  = ((temp_1*10)+temp);
	  /*--------------------------*/ 
	   temp = temp_meses;
	   temp = temp & 0x0F; // ler meses do ano
	       //----//
	   temp_1 = temp_meses;
	   temp_1 = temp_1 & 0x10;
	   temp_1 = temp_1 >>4;
	   meses  = ((temp_1*10)+temp);
	   /*--------------------------*/
	   temp = temp_anos;
	   temp = temp & 0x0F;  // ler anos
	       //----//
	  temp_1 = temp_anos;
	  temp_1 = temp_1 & 0xF0;
	  temp_1 = temp_1 >>4;
	  anos   = ((temp_1*10)+temp); 
                 
 }
//------------------------------------//
uint8_t I2C_ReadOneByteDataFromSlave(uint8_t address){
  volatile uint8_t t;
  //delay_100us(1);
  //---------- Sinal de partida I2C --------------
  I2C_CR2_START=1;//gera uma condição inicial
  while(!(I2C_SR1_SB==1))// Leia o registro SR1 e limpe o sinalizador SB.
  //_5NOPS; // De acordo com a folha de dados, após detectar o sinalizador, insira 5 NOPs para atrasar
  //------- Enviar gravação endereço escravo I2C ---------
  I2C_DR=0xD0; // envia endereço escravo
  while(!(I2C_SR1_ADDR==1));// Leia o registro SR1, limpe o sinalizador ADDR
  //_5NOPS; // De acordo com a folha de dados, após detectar o sinalizador, insira 5 NOPs para atrasar
  if(I2C_SR3_TRA==0)return 1;//?SR3???,??ADDR???
  //  0: Data bytes received
  //  1: Data bytes transmitted
  // ----- Grava o endereço de registro do dispositivo escravo I2C -------- 
  I2C_DR=address;
  while(!(I2C_SR1_BTF==1)); // aguardando o envio do endereço
  // _5NOPS; // De acordo com a folha de dados, após detectar o sinalizador, insira 5 NOPs para atrasar
  //-------- I2C repete o sinal de início -----------
  I2C_CR2_START=1;// Repeat gera uma condição inicial
  while(!(I2C_SR1_SB==1)); // Leia o registro SR1 e limpe o sinalizador SB.
  // _5NOPS; // De acordo com a folha de dados, após detectar o sinalizador, insira 5 NOPs para atrasar
  // ------- Enviar endereço de escravo I2C lido --------- 
  I2C_DR=0xD1; // envia endereço escravo
  while(!(I2C_SR1_ADDR==1));// Leia o registro SR1, limpe o sinalizador ADDR
  // _5NOPS; // De acordo com a folha de dados, após detectar o sinalizador, insira 5 NOPs para atrasar
  if(I2C_SR3_TRA==1)return 1;// ler o registro SR3, limpe o sinalizador ADDR
  // ------------- sinal de parada -------------
  I2C_CR2_ACK=0; // ACK bit controla o sinal ACK, este bit é 0 pode gerar um sinal NOACK
  I2C_CR2_STOP=1;
  //------------- Esperando para receber dados -------------
  while(!(I2C_SR1_RXNE==1));// aguardando o envio do endereço 
  //------------- Ler dados -------------
  t=I2C_DR;
  return t;
}
//------------------------------------//
uint8_t I2C_ReadMultiBytesFromSlave(uint8_t address,uint8_t *rxbuf,uint8_t len){
  volatile uint8_t i=0;
  //delay_100us(1);
  if(len==0)return 1;//Se o comprimento do byte de gravação for 0, saia
  I2C_CR2_ACK=1;
  //----------Sinal de partida I2C--------------
  I2C_CR2_START=1;//Gere uma condição inicial
  while(!(I2C_SR1_SB==1));//Leia o registro SR1 e limpe a bandeira SB.
  //-------Enviar endereço de escravo I2C de gravação--------- 
  I2C_DR=0xD0;//Enviar endereço escravo
  while(!(I2C_SR1_ADDR==1));//Leia o registro SR1 e limpe o sinalizador ADDR.
  if(I2C_SR3_TRA==0)return 1;//Leia o registro SR3 e limpe o sinalizador ADDR.
  //  0: Data bytes received
  //  1: Data bytes transmitted
  //-----Gravar endereço de registro escravo I2C-------- 
  I2C_DR=address;
  while(!(I2C_SR1_BTF==1));//Aguardando o endereço ser enviado
  
  //--------I2C repetir sinal de início-----------
  I2C_CR2_START=1;//Repita para gerar uma condição inicial
  while(!(I2C_SR1_SB==1));//Leia o registro SR1 e limpe a bandeira SB.
  
  //-------Enviar endereço escravo I2C de leitura--------- 
  I2C_DR=0xD1;//Enviar endereço escravo
  while(!(I2C_SR1_ADDR==1));//Leia o registro SR1 e limpe o sinalizador ADDR.
  if(I2C_SR3_TRA==1)return 1;//Leia o registro SR3 e limpe o sinalizador ADDR.
  //-------------Ler dados-------------
  if(len>1)
  {
      for( i=len;i>1;i-- )
      {
        while(!(I2C_SR1_RXNE==1));//Aguardando I2C1_DR para receber o número
        *rxbuf++ = I2C_DR;  
      }
  }
  //-------------Sinal de parada-------------
  I2C_CR2_ACK=0;//O bit ACK controla o sinal ACK, que é 0 para gerar um sinal NOACK.
  I2C_CR2_STOP=1;
  
  while(!(I2C_SR1_RXNE==1));//Aguardando I2C1_DR para receber o número
  *rxbuf++ = I2C_DR; 
  
  return 0;
}
//------------------------------------//
void I2C_Init(void){ 
//  CLK_PCKENR1_PCKEN13=1;//
  I2C_CR1_PE=0;
  I2C_CR2_ACK=1;  
  I2C_FREQR_FREQ=0x10;//16MHz Selecao de freqüência do relógio de entrada
  //  The allowed range is between 1 MHz and 16 MHz
  //000000: not allowed
  //000001: 1 MHz
  //000010: 2 MHz
  //...
  //010000: 16 MHz   

    I2C_CCRH=0;
   //I2C1_CCRH_F_S=0; //Standard mode I2C
   //I2C1_CCRH_DUTY=0; 
  I2C_CCRL=0xea;    // SCL high time configuration
  // configura??o de tempo alto do SCL
  // O relógio SCK do I2C é definido como 100KHz, ent?o o período SCK é 10us.
  // Como I2C1_FREQR_FREQ = 0x02, ou seja, a frequência do relógio de entrada I2C é 2M, o período é de 0,5us
  // CCR = 10, o tempo baixo de SCK é tlow = 10 * 0.5us = 5us, e o tempo alto de SCk é coxa = 10 * 0.5us = 5us
  // Ent?o, quando CCR = 10, a frequência de saída SCK é 100KHz.
  I2C_TRISER_TRISE=1;//in standard mode, the maximum allowed SCL rise time is 1000 ns.
  //1 us / 0.5 us = 2 + 1
  I2C_CR1_PE=1;
}
  

  
  
  
