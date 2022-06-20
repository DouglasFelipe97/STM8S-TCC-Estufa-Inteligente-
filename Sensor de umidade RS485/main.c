#include <iostm8s003f3.h>
#include <intrinsics.h>
#include <string.h>
#include "GPIO.h"
#include "delay.h"
   //-------------------------------------------------
   unsigned char int_5mS;
   unsigned int  temp_50_ms;
   unsigned char temporizador_led;
   
   unsigned char end;
   //unsigned char sem_temp[7];
   //unsigned char chaves[4];
   //-------------------------------------------------
   struct{
     unsigned int buf_cheio     : 1; 	 
    }serial;
   //------------------------------------------------- 
    char buff_temp[41];
    char buff[41];
    unsigned char pont_buff_temp;
   //------------------------------------------------- 
   /**
   * The NTC table has 33 interpolation points.
   * Unit:   -10 A 150 C
   *
   */
   //---------------------------------------------//
   unsigned int adc_value_1,adc_value_2,adc_value_3,cont_ad = 0;
   unsigned long int temp_ad_1,temp_ad_2,temp_ad_3 = 0;
   int leitura_1,leitura_2;
   unsigned  int  temperatrura_1;
   unsigned  int  temperatrura_2; 
   //---------------------------------------------//
   int p1,p2;
   int NTC_table[33] = {
     -374, -240, -106, -17, 52, 111, 163, 210, 
     254, 295, 335, 374, 412, 450, 488, 526, 564, 
     604, 645, 687, 732, 779, 830, 886, 947, 1017, 
     1097, 1192, 1311, 1470, 1708, 2172, 2636
   };
   //---------------------------------------------// 
    struct{
      unsigned int erro_s1                 : 1;
      unsigned int erro_s2                 : 1;
      unsigned int negativo_temp_1         : 1;
      unsigned int negativo_temp_2         : 1;
     }modo;
   //-------------   PROTOTIPO DE FUNÇOES   --------------------------// 
   void InitialiseSystemClock(void);
   void inicializar_pinos(void); 
   void TM4_Init(void);
   void SetupTimer1(void);
   void InitialiseTimer1(void);
   void InitialiseTimer2(void);
   void SetupTimer2(void);
   void iwdg_enable(void);
   void iwdg_refresh(void);
   void ADC_Init(void);
   unsigned int ADC_Read(char Canal);
   void eeprom_write(unsigned int  addr, unsigned char buf);
   unsigned char  eeprom_read(unsigned int addr);
   char testa_chaves(void);
   void uart_Write(unsigned char Chr);
   void transmite_string_as1(char *c);
   void transmite_as1(unsigned char Chr);
   void UART_Init(void);
   void trata_serial(void);
   void trata_leitura(void);
   unsigned char testar_str(void);
   void itoa(int n, char s[]);
   void reverse(char s[]);
//----------------------------------------------------------------------------//
//  Timer 2 Overflow handler.
//
#pragma vector = TIM2_OVR_UIF_vector
__interrupt void TIM2_UPD_OVF_IRQHandler(void)
{
    TIM2_SR1_UIF = 0;               //  Reset the interrupt otherwise it will fire again straight away.
}
//----------------------------------------------------------------------------//
#pragma vector = TIM4_OVR_UIF_vector
__interrupt void _TIM4_OVF(void){ // interupção configurada para cada 1mS
   int_5mS ++;
   if(int_5mS >= 5){ 
      int_5mS = 0;
      
       temporizador_led ++;
        if(temporizador_led >= 210){
         led = 1;
         if(temporizador_led >= 225){
           led = 0;
           temporizador_led = 0;
           }
          }  
      }
   //-----------------------------// 
   //-----------------------------// 
   //-----------------------------// 
     if(temp_50_ms >= 50){
        temp_50_ms =0;
        temp_ad_1 +=  ADC_Read(4);
        temp_ad_2 +=  ADC_Read(3);
        temp_ad_3 +=  ADC_Read(2);
        cont_ad++;
        if(cont_ad >= 10){
           cont_ad = 0;
           adc_value_1 = (temp_ad_1/10);
           adc_value_2 = (temp_ad_2/10);
           adc_value_3 = (temp_ad_3/10);
           temp_ad_1 = 0;
           temp_ad_2 = 0;
           temp_ad_3 = 0;
              //-------------------//
             if(sensor_presente >= adc_value_1){modo.erro_s1 = 1;}else{modo.erro_s1 = 0;}
             if(sensor_presente >= adc_value_2){modo.erro_s2 = 1;}else{modo.erro_s2 = 0;}
              //-------------------//
             /* Estimar o ponto de interpolação antes e depois do valor ADC. */
               p1 = NTC_table[ (adc_value_1 >> 5)  ];
               p2 = NTC_table[ (adc_value_1 >> 5)+1];
               /* Interpola entre os dois pontos. */
               leitura_1 =  p1 + ( (p2-p1) * (adc_value_1 & 0x001F) ) / 32;
               p1 = NTC_table[ (adc_value_2 >> 5)  ];
               p2 = NTC_table[ (adc_value_2 >> 5)+1];
               /* Interpola entre os dois pontos. */
               leitura_2 =  p1 + ( (p2-p1) * (adc_value_2 & 0x001F) ) / 32;
               //-------------------//
               if(leitura_1 & 0x8000){// verificar se numero e negativo
                 temperatrura_1 = ((65535 - leitura_1) + 1) ; 
                 modo.negativo_temp_1 = 1;
                }else{
                   temperatrura_1 = leitura_1;
                   modo.negativo_temp_1 = 0;
                  }
               //-------------------//
               if(leitura_2 &  0x8000){// verificar se numero e negativo
                 temperatrura_2 = ((65535 - leitura_2) + 1) ; 
                 modo.negativo_temp_2 = 1;
                }else{
                   temperatrura_2 = leitura_2;
                   modo.negativo_temp_2 = 0;
                  }	
            }
         }else{
            temp_50_ms ++;
           }  
   //-----------------------------// 
   //-----------------------------// 
   //-----------------------------// 
   iwdg_refresh();// reinicar IWDG
   TIM4_SR = 0x00; // clear irq flag
}
//----------------------------------------------------------------------------//
// Vetores de interrupções Serial
#pragma vector = UART1_R_RXNE_vector
__interrupt void UART1_RX_ISR(void)
{
  unsigned char rx_aux;
  unsigned char cont;
  rx_aux  = UART1_DR;              //lê o caracter recebido
  
  if(rx_aux == '*'){
      pont_buff_temp = 0;                         //reinicia o ponteiro em 0    
    }
	   buff_temp[pont_buff_temp] = rx_aux;        //armazena o caracter recebido
		 pont_buff_temp ++;                             //incrementa o ponteriro
		   if((pont_buff_temp >= 40)||(rx_aux == '>')){ //se o ponteiro chegar no ultimo caracter da string ou receber o caracter \n     
			// buff_temp[pont_buff_temp] = '>';         //finaliza a string
			   if(!serial.buf_cheio){
			     for(cont = 0; cont<= pont_buff_temp; cont++){
			         buff[cont] = buff_temp[cont];  
			        }
			       serial.buf_cheio = 1;  
			     }
			    pont_buff_temp = 0;                          //reinicia o ponteiro em 0  
			 }   
   UART1_SR = 0;
}
//----------------------------------------------------------------------------//
void iwdg_enable(void){
    IWDG_KR  = 0xcc;         //  Start the independent watchdog.
    IWDG_KR  = 0x55;         //  Allow the IWDG registers to be programmed.
    IWDG_PR  = 0x04;         /* prescaler = 64 */ //  Prescalar is 2 => each count is 250uS
    IWDG_RLR = 0xFA;        /* timeout = 250ms *///  Reload counter.
    IWDG_KR  = 0xaa;        //  Reset the counter.
}
//----------------------------------------------------------------------------//
void iwdg_refresh(void){
    IWDG_KR = 0xaa;
}
//----------------------------------------------------------------------------//
void ADC_Init(void){
    ADC_CR1_bit.ADON = 1;               // Dispara uma conversão
    ADC_CR2_bit.ALIGN = 1;              // Conversor em 10 bits    
}
//----------------------------------------------------------------------------//
unsigned int ADC_Read(char Canal){
   unsigned int ADC_Result = 0;        // Cria uma variável temporária
           ADC_CSR_bit.CH = Canal;             // Seleciona um canal
           ADC_CR1_bit.ADON = 1;               // Dispara uma conversão
           while(!ADC_CSR_bit.EOC);            // Espera finalizar a conversão
           ADC_CSR_bit.EOC = 0;                // Indica que finalizou a conversão
           ADC_Result |= ADC_DRL;              // Lê a parte baixa
           ADC_Result |= ADC_DRH<<8;           // Lê a parte alta
           return ADC_Result;                  // Retorna o valor do ADC
}
//---------------------------------------------------------------------------//
//
//  Reset Timer 2 to a known state.
//
void InitialiseTimer1(void)
{
    TIM1_CR1 = 0;               // Turn everything TIM2 related off.
    TIM1_IER = 0;
    TIM1_SR2 = 0;
    TIM1_CCER1 = 0;
    TIM1_CCER2 = 0;
    TIM1_CCER1 = 0;
    TIM1_CCER2 = 0;
    TIM1_CCMR1 = 0;
    TIM1_CCMR2 = 0;
    TIM1_CCMR3 = 0;
    TIM1_CNTRH = 0;
    TIM1_CNTRL = 0;
    
   // TIM1_PSCR = 0;
    TIM1_PSCRH = 0;
    TIM1_PSCRL = 0;
    
    TIM1_ARRH  = 0;
    TIM1_ARRL  = 0;
    TIM1_CCR1H = 0;
    TIM1_CCR1L = 0;
    TIM1_CCR2H = 0;
    TIM1_CCR2L = 0;
    TIM1_CCR3H = 0;
    TIM1_CCR3L = 0;
    TIM1_SR1 = 0;
}
//----------------------------------------------------------------------------//
//
//  Setup Timer 2 to PWM signal.
//
void SetupTimer1(void){
    TIM1_PSCRH = 0;
    TIM1_PSCRL = 0;
   // TIM1_ARRH = 0xc3;       //  High byte of 50,000.
   // TIM1_ARRL = 0x50;       //  Low byte of 50,000.
    TIM1_ARRH = 0x00;       //  High byte of 50,000.
    TIM1_ARRL = 0x7c;       //  Low byte of 50,000.
      //--------//
    //TIM1_CCR1H = 0x00;      //  High byte of 12,500
    //TIM1_CCR1L = 0x7f;      //  Low byte of 12,500
         //--//
   // TIM1_CCR2H = 0x00;      //  High byte of 12,500
   // TIM1_CCR2L = 0x00;      //  Low byte of 12,500
          //--//
    TIM1_CCR3H = 0x00;      //  High byte of 12,500
    TIM1_CCR3L = 0x3e;      //  Low byte of 12,500  
    
   /*
    TIM1_CCR1H = 0x30;      //  High byte of 12,500
    TIM1_CCR1L = 0xd4;      //  Low byte of 12,500
         //--//
    TIM1_CCR2H = 0x30;      //  High byte of 12,500
    TIM1_CCR2L = 0xd4;      //  Low byte of 12,500
          //--//
    TIM1_CCR3H = 0x61;      //  High byte of 12,500
    TIM1_CCR3L = 0xa8;      //  Low byte of 12,500  
*/
    //-----------------//
    //TIM1_CCER1_CC1E = 1;    //  Enable compare mode for channel 1
   // TIM1_CCER1_CC2E = 1;    //  Enable compare mode for channel 2
    TIM1_CCER2_CC3E = 1;    //  Enable compare mode for channel 3
    //-----------------//
    //TIM1_CCMR1 |= 0x60; //PC1 pin is set becom the PWM output,PWM mode 1
    //TIM1_CCMR2 |= 0x60; //PC1 pin is set becom the PWM output,PWM mode 1
    TIM1_CCMR3 |= 0x60; //PC1 pin is set becom the PWM output,PWM mode 1
    //-----------------//
    // TIM1_CCER1_CC1P = 0;    //  Active high.
    TIM1_IER = 0x00; // All interrupt disabled
    TIM1_CR1_CEN = 1;// Finally enable the timer.
    TIM1_BKR |= 0x80;// Enable PWM output 
}
//----------------------------------------------------------------------------//
void SetupTimer2(void)
{
   // TIM2_PSCR = 0x06;       //  Prescaler = 8.
    
     TIM2_PSCR = 0x06;       //  Prescaler = 8.
    
    TIM2_ARRH = 0xf2;       //  High byte of 50,000.
    TIM2_ARRL = 0x30;       //  Low byte of 50,000.
    
    TIM2_IER_UIE = 1;       //  Enable the update interrupts.
    TIM2_CR1_CEN = 1;       //  Finally enable the timer.
}
//
//  Reset Timer 2 to a known state.
//
//----------------------------------------------------------------------------//
void InitialiseTimer2(void)
{
    TIM2_CR1 = 0;               // Turn everything TIM2 related off.
    TIM2_IER = 0;
    TIM2_SR2 = 0;
    TIM2_CCER1 = 0;
    TIM2_CCER2 = 0;
    TIM2_CCER1 = 0;
    TIM2_CCER2 = 0;
    TIM2_CCMR1 = 0;
    TIM2_CCMR2 = 0;
    TIM2_CCMR3 = 0;
    TIM2_CNTRH = 0;
    TIM2_CNTRL = 0;
    TIM2_PSCR = 0;
    TIM2_ARRH  = 0;
    TIM2_ARRL  = 0;
    TIM2_CCR1H = 0;
    TIM2_CCR1L = 0;
    TIM2_CCR2H = 0;
    TIM2_CCR2L = 0;
    TIM2_CCR3H = 0;
    TIM2_CCR3L = 0;
    TIM2_SR1 = 0;
}
//----------------------------------------------------------------------------//
void TM4_Init(void){ // para cada 1mS  ocorre uma interrupção
        //configuração para interupção de 1ms a 16MHZ
	TIM4_PSCR = 0x07; // fCK_CNT = fCK_PSC/2**PSCR (2**7=128)
	TIM4_ARR = TOP1MS; // set TOP value (reset cnt) for 1mS
	TIM4_SR   = 0x00;
	TIM4_IER |= 0x01;
	TIM4_CR1 |= 0x01;
}
//----------------------------------------------------------------------------//
//  Setup the system clock to run at 16MHz using the internal oscillator.
void InitialiseSystemClock(void)
{
    CLK_ICKR = 0;                       //  Reset the Internal Clock Register.
    CLK_ICKR_HSIEN = 1;                 //  Enable the HSI.
    CLK_ECKR = 0;                       //  Disable the external clock.
    while (CLK_ICKR_HSIRDY == 0);       //  Wait for the HSI to be ready for use.
    CLK_CKDIVR = 0;                     //  Ensure the clocks are running at full speed.
    CLK_PCKENR1 = 0xff;                 //  Enable all peripheral clocks.
    CLK_PCKENR2 = 0xff;                 //  Ditto.
    CLK_CCOR = 0;                       //  Turn off CCO.
    CLK_HSITRIMR = 0;                   //  Turn off any HSIU trimming.
    CLK_SWIMCCR = 0;                    //  Set SWIM to run at clock / 2.
    CLK_SWR = 0xe1;                     //  Use HSI as the clock source.
    CLK_SWCR = 0;                       //  Reset the clock switch control register.
    CLK_SWCR_SWEN = 1;                  //  Enable switching.
    while (CLK_SWCR_SWBSY != 0);        //  Pause while the clock switch is busy.
}
//----------------------------------------------------------------------------//
void UART_Init(void){
  /*
    UART1_BRR2 = 0x00;
    UART1_BRR1 = 0x0D;                  // BR = 2MHz/9600 = 208 -> 0xD0
    UART1_CR2  = 0x2C;                   // RIEN ON, TX e RX ON 
    */
   	UART1_CR1 = 0x00; // 0000.0000 Enable UART 8bit, no parity
	UART1_CR3 = 0x00; // 0000.0000 1 stop bit
        
	//UART1_CR6 = 0x08; // 0000.0000 no dma, half duplex
        //UART1_CR5 = 0x08; // 0000.0000 no dma, half duplex
        
	//UART2_BRR2 = 0x03; // set 9600 BPS
	//UART2_BRR1 = 0x68; 
        
	UART1_BRR2 = 0x01; // set 19200 BPS
	UART1_BRR1 = 0x34;         

	UART1_CR2 = 0x2C; // 0010.1100 Enable RX irq, Enable TX and RX 
    
    
}
//------------------------------------------------------------------------------/
void transmite_as1(unsigned char Chr){
    UART1_DR = Chr;                     // Coloca o byte no buffer de saída
    while(!UART1_SR_bit.TXE);           // Espera o byte sair do buffer
  // uart_Write(dado);
}
//------------------------------------------------------------------------------/
void transmite_string_as1(char *c){  
  while(*c){                                         //aguarda o buffer de tx estar vazio
  transmite_as1(*c);
  c++;
  }                                                  // transmite o caracter recebido 
}
//------------------------------------------------------------------------------/
void uart_Write(unsigned char Chr){
    UART1_DR = Chr;                     // Coloca o byte no buffer de saída
    while(!UART1_SR_bit.TXE);           // Espera o byte sair do buffer
}
//----------------------------------------------------------------------------//
void inicializar_pinos(void){
  led_dir   = 1;  //  is output.
  led_Push  = 1;  //  Pin is set to Push-Pull mode. 
  led_fast  = 1;  //  Pin can run up to 10 MHz  
    //--------//
  rs_io_dir   = 1;  //  is output.
  rs_io_Push  = 1;  //  Pin is set to Push-Pull mode. 
  rs_io_fast  = 1;  //  Pin can run up to 10 MHz  
    //--------//
  chave_1_dir   = 0;         //   is Imput.
  chave_1_Push  = 1;         //   Pull-up sem interromper
  chave_1_fast  = 0;         // 
    //--------//
  chave_2_dir   = 0;         //   is Imput.
  chave_2_Push  = 1;         //   Pull-up sem interromper
  chave_2_fast  = 0;         // 
    //--------//  
  chave_3_dir   = 0;         //   is Imput.
  chave_3_Push  = 1;         //   Pull-up sem interromper
  chave_3_fast  = 0;         // 
    //--------// 
  chave_4_dir   = 0;         //   is Imput.
  chave_4_Push  = 1;         //   Pull-up sem interromper
  chave_4_fast  = 0;         // 
    //--------//
  bt_prog_dir   = 0;              //   is Imput.
  bt_prog_Push  = 1;              //   Pull-up sem interromper
  bt_prog_fast  = 0;              // 
    //--------//
  
  
  rs_io = 0;
  led   = 0;
  
}
//----------------------------------------------------------------------------// 
 /* itoa:  convert n to characters in s */
 void itoa(int n, char s[]){
     int i, sign;

     if ((sign = n) < 0)  /* record sign */
         n = -n;          /* make n positive */
     i = 0;
     do {       /* generate digits in reverse order */
         s[i++] = n % 10 + '0';   /* get next digit */
     } while ((n /= 10) > 0);     /* delete it */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     reverse(s);
} 
//----------------------------------------------------------------------------// 
 /* reverse:  reverse string s in place */
 void reverse(char s[]){
     int i, j;
     char c;

     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
} 
//----------------------------------------------------------------------------// 
 unsigned char  testar_str(void){ 
   char sem_temp[7];
   char chaves[4];

   memset(chaves,0,sizeof(chaves));  // limpar buffer antes de usar 
   memset(sem_temp,0,sizeof(sem_temp));
   
    end = testa_chaves(); 
    itoa(end,chaves);
       //------//
    strcat(sem_temp,"<");
    strcat(sem_temp,chaves);
    strcat(sem_temp,">");
       //------//
    if(strstr(buff,sem_temp)){return 1;}else{return 0;}	// aqui verifico se o numero de nossa placa e o mesmo pedido na string
 }
//----------------------------------------------------------------------------// 
//    EX: *LTU:#<1> Leitura de sensores
//----------------------------------------------------------------------------// 
 void trata_serial(void){
   if(serial.buf_cheio){ // Verifico se temos um astring pronta recebida pela serial
     if(testar_str()){  // verificar se string recebida e para nosso numero de placa
        if(strstr(buff,"*LTU:")){trata_leitura();} // tratar pedido
        
        
        if(strstr(buff,"*SOND:")){ } // tenviar valor bruto do sensor da sonda 
        if(strstr(buff,"*CONF:")){ }  
        if(strstr(buff,"*MAX:")){ } 
        if(strstr(buff,"*MIN:")){ } 
        
        
        
        
        
      }
     serial.buf_cheio = 0; 
   }


    /*
    if(strstr(buff_blu,"*SEN:"))   { trata_sen();}
    if(strstr(buff_blu,"*RESET:")) { reset();}	
    if(strstr(buff_blu,"*GRAVAR:")){ trata_prg_rf();}
    if(strstr(buff_blu,"*FOR:"))   { trata_corrente();}
    if(strstr(buff_blu,"*FOR?:"))  { perguntar_corrente();}	
    if(strstr(buff_blu,"*REL:"))   { programar_relogio();}// ajustar relogio e data
    */

 }
//----------------------------------------------------------------------------//
void trata_leitura(void){
  char temp[7];
  char chaves[4];
   //------//
  rs_io = 1;  // ativo pino RS-485 Para transmissão
  delay_ms(5);
  transmite_string_as1("*RLTU:");
         //-------------//
   memset(temp,0,sizeof(temp));// limpar buffer antes de usar 
   if(modo.erro_s1){
     transmite_string_as1("S1_ERROR,");
     }else{
       if(modo.negativo_temp_1){transmite_string_as1("-");}else{transmite_string_as1("+");} // verificar se temperatura e negativa
       itoa(temperatrura_1,temp); // converter temperatura em string
       transmite_string_as1(temp);
       transmite_string_as1(",");
     } 
         //-------------//
    memset(temp,0,sizeof(temp));// limpar buffer antes de usar 
   if(modo.erro_s2){
     transmite_string_as1("S2_ERROR,");
     }else{
       if(modo.negativo_temp_2){transmite_string_as1("-");}else{transmite_string_as1("+");} // verificar se temperatura e negativa
       itoa(temperatrura_2,temp); // converter temperatura em string
       transmite_string_as1(temp);
       transmite_string_as1(",");
     } 
         //-------------//
    memset(temp,0,sizeof(temp));// limpar buffer antes de usar 
   
    itoa(adc_value_3,temp);
    transmite_string_as1(temp);
       //-------------//
  memset(chaves,0,sizeof(chaves));  // limpar buffer antes de usar  
  itoa(end,chaves);
  transmite_string_as1("#<");
  transmite_string_as1(chaves);
  transmite_string_as1(">\r\n");
  
  rs_io = 0; // abilito pino RS-485 Para recepção
}
//----------------------------------------------------------------------------//
  char testa_chaves(void) {
     unsigned char ch_aux;  
     unsigned char ch_cont;  
     unsigned char ch_aux_temp;   
     
     ch_cont = 10;
     ch_aux_temp = 0;
       while(ch_cont){
       ch_aux = 0;
         if(!chave_1) ch_aux += 0x01;             /*leitura das chaves*/
         if(!chave_2) ch_aux += 0x02;
         if(!chave_3) ch_aux += 0x04;
         if(!chave_4) ch_aux += 0x08;
         if(ch_aux == ch_aux_temp){
           ch_cont--; 
           }else{
             ch_cont = 10;
             ch_aux_temp = ch_aux;
             }
          }
    return ch_aux;
  }
//------------------------------------------------------------------------------/ 
int main(void){
  InitialiseSystemClock();  // Ajusta o sistema de clock 16MHZ
  inicializar_pinos();      // configurar pinos
  __disable_interrupt();
    TM4_Init();         // configurar timmer 4
    InitialiseTimer1(); // configurar timmer PWM para 128KHZ
    SetupTimer1();    
    UART_Init();        // Inicializa a UART1 com 19200 8N1
    ADC_Init();         // Configura o ADC
    iwdg_enable();
  __enable_interrupt(); 
   //-------------//
    iwdg_refresh();
   //-------------//
  while(1){
     trata_serial(); //Verificar strings recebidas pela serial
    }
}
//------------------------------------------------------------------------------/ 
//------------------------------------------------------------------------------/ 