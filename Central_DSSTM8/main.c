#include <iostm8s005K6.h>
#include <intrinsics.h>
#include <string.h>
#include "GPIO.h"
#include "delay.h"
#include "display_lcd.h"
#include "ds1307.h"

struct{
  unsigned int hora_full      : 1; 
  unsigned int segundos_pulso : 1; 
  unsigned int hora_ajuste    : 1;// flag para  ajustar horas 
  unsigned int display_piscar : 1;// flag para piscar display quando estiver em mode de ajustar horas
  unsigned int hora_seletor   : 1;// usado para selecionar lado das horas e dos minutos
  unsigned int passo_menu     : 8;
}ds;

struct{
  unsigned int hora_ligar       	: 8; 
  unsigned int minutos_ligar    	: 8;
  unsigned int hora_rel             	: 8; 
  unsigned int minutos_rel    	: 8;
  unsigned int segundos_rel           : 8;
  unsigned int umisolo_ligar		: 8;
  unsigned int umisolo_desligar	: 8;
  unsigned int temp_ligar		: 8;
  unsigned int temp_desligar		: 8;
  unsigned int umiar_ligar		: 8;
  unsigned int umiar_desligar		: 8;
  unsigned int domingo       	: 1;
  unsigned int segunda       	: 1;
  unsigned int terca         	: 1;
  unsigned int quarta        	: 1;
  unsigned int quinta        	: 1;
  unsigned int sexta         	: 1;
  unsigned int sabado        	: 1;
}conf1;

struct{
  unsigned int h_on			: 1;
  unsigned int m_on			: 1;
  unsigned int d_on			: 1;
  unsigned int i_ok			: 1;
  unsigned int t_ok			: 1;
  
}flags;

struct{
  unsigned int aux_oth        : 8;
  unsigned int aux_oth1        : 8;
  unsigned int aux1           : 8;
  unsigned int aux2           : 8;
  unsigned int aux3           : 8;
  unsigned int aux4           : 8;
  unsigned int ax1            : 1;
  unsigned int aux_cima       : 1;
  unsigned int aux_baixo      : 1;
  unsigned int aux_conf       : 1;
  unsigned int aux_volta      : 1;
}auxiliar;
struct{
  unsigned int men        : 8;
  unsigned int men1       : 8;
  unsigned int dta        : 8;
  unsigned int hra        : 8;
  unsigned int cfn      : 8;
  unsigned int prs      : 8;
  unsigned int prs0      : 8;
  unsigned int prs1      : 8;
  unsigned int prs2      : 8;
  unsigned int prs3      : 8;
  unsigned int ir         : 8;
  unsigned int tmp        : 8;
  unsigned int umi        : 8;
}menu;
//-----------------------------------------------//
int cont;

char text  [] = "IR:AAA       XXX:S/N";
char text1 [] = "T.AR:00.0C  U.AR:00%";
char text2 [] = "T.SL:00.0C  U.SL:00%";
char text3 [] = "HR:00:00 DT:01/01/21";
char tdata [] = "      01/01/00      ";
char thora [] = "      00:00:00      ";
char prs1  [] = "   S T Q Q S S D    "; 
char prs12 [] = "   - - - - - - -    ";
char prs13 [] = "Temp. ar max:00.0C  ";
char prs14 [] = "Temp. ar min:00.0C  ";
char prs15 [] = "Umi.  ar max:00%    ";
char prs16 [] = "Umi.  ar min:00%    ";
char prs17 [] = "Umi. solo max:00.0C ";
char prs18 [] = "Umi. solo min:00.0C ";
char prs2  [] = "   S T Q Q S S D    "; 
char prs22 [] = "   - - - - - - -    ";
char prs23 [] = "Temp. ar max:00.0C  ";
char prs24 [] = "Temp. ar min:00.0C  ";
char prs25 [] = "Umi.  ar max:00%    ";
char prs26 [] = "Umi.  ar min:00%    ";
char prs27 [] = "Umi. solo max:00.0C ";
char prs28 [] = "Umi. solo min:00.0C ";
char prs3  [] = "   S T Q Q S S D    "; 
char prs32 [] = "   - - - - - - -    ";
char prs33 [] = "Temp. ar max:00.0C  ";
char prs34 [] = "Temp. ar min:00.0C  ";
char prs35 [] = "Umi.  ar max:00%    ";
char prs36 [] = "Umi.  ar min:00%    ";
char prs37 [] = "Umi. solo max:00.0C ";
char prs38 [] = "Umi. solo min:00.0C ";


unsigned char hora_rel,             	
min_rel,    	
seg_rel,
dia_rel,
mes_rel,
ano_rel,
sem_rel;
/*----- Variáveis DS1307 Relógio ----------------*/
unsigned char hora;
unsigned char minutos;
unsigned char segundos;
unsigned char semana;
unsigned char dias;
unsigned char meses;
unsigned char anos;
//-------------   Variáveis globais   -----------// 
unsigned char int_5mS;
unsigned char temporizador_led;
unsigned char leitura_ds; 
//-------------   PROTOTIPO DE FUNÇOES   --------------------------// 
void InitialiseSystemClock(void);
void Clock_Init(void);                  // Inicializa o sistema de clock
void SetupTimer2(void);
void InitialiseTimer2(void);
void SetupTimer1(void);
void InitialiseTimer1(void);
void TM4_Init(void); 
void inicializar_pinos(void);
void inicializa_variaveis(void);
void tratar_teclas(void);
void atualizar_menu(void);
void beep(void);
void inicializar_variaveis(void);
void formatar_hr_rel(char buff[],char buff1[],unsigned char h,unsigned char mi,unsigned char s);
void formatar_dt_rel(char buff[],char buff1[],unsigned char h,unsigned char mi,unsigned char s);
void conv_valor(char buff[],unsigned char aux);
void verificar_relogio(void);
//----------------------------------------------------------------------------//	 
#pragma vector = EXTI2_vector
__interrupt void EXTI_PORTC_IRQHandler(void){
}
//------------------------------------------------------------------------------
//  Timer 2 Overflow handler.
//
#pragma vector = TIM2_OVR_UIF_vector
__interrupt void TIM2_UPD_OVF_IRQHandler(void){
  TIM2_SR1_UIF = 0;               //  Reset the interrupt otherwise it will fire again straight away.
}
//------------------------------------------------------------------------------
int main(void){
  InitialiseSystemClock();  // Ajusta o sistema de clock 16MHZ
  inicializar_pinos();      // configurar pinos 
  delay_ms(200);
  __disable_interrupt();
  InitialiseTimer1();   // configurar timmer 2
  InitialiseTimer2();   // configurar timmer 2
  SetupTimer2();
  TM4_Init();          // configurar timmer 4
  //UART_Init();        // Inicializa a UART1 com 9600 8N1
  __enable_interrupt();
  //------------------------// 
  
  inicializa_lcd();   // Inicializa display lcd modo comunicação 4_vias 
  limpa_lcd();
  inicializar_variaveis();  
  while(1){
    
    tratar_teclas();
    atualizar_menu();
    verificar_relogio();
    
  }
}

//----------------------------------------------------------------------------//
void inicializar_variaveis(void){
  
  menu.men = 0x01;                         //armazena número da tela atual do menu 
  menu.dta  = 0x00;
  menu.hra  = 0x00;
  menu.prs  = 0x00;
  menu.prs0  = 0x03;
  menu.cfn  = 0x00;
  menu.men1 = 0x05;
  auxiliar.aux_oth = 0x00;
  hora_rel = 0x00;             	
  min_rel = 0x00;    	
  seg_rel = 0x00;
  dia_rel = 0x01;
  mes_rel = 0x01;
  ano_rel = 0x00;
  sem_rel = 0x01;
  
}
void inicializar_pinos(void){
  scl_dir   = 1;  //  is output.
  scl_Push  = 1;  //  Pin is set to Push-Pull mode. 
  scl_fast  = 1;  //  Pin can run up to 10 MHz  
  //--------//
  sda_dir   = 1;      //   is output 
  sda_Push  = 1;      // 
  sda_fast  = 1;      // 
  
  lcd_rs_dir   = 1;  //  is output.
  lcd_rs_Push  = 1;  //  Pin is set to Push-Pull mode. 
  lcd_rs_fast  = 1;  //  Pin can run up to 10 MHz  
  //--------//
  lcd_rw_dir   = 1;  //  is output.
  lcd_rw_Push  = 1;  //  Pin is set to Push-Pull mode. 
  lcd_rw_fast  = 1;  //  Pin can run up to 10 MHz  
  //--------//
  lcd_rs_dir   = 1;  //  is output.
  lcd_rs_Push  = 1;  //  Pin is set to Push-Pull mode. 
  lcd_rs_fast  = 1;  //  Pin can run up to 10 MHz 
  
  lcd_e_dir   = 1;  //  is output.
  lcd_e_Push  = 1;  //  Pin is set to Push-Pull mode. 
  lcd_e_fast  = 1;  //  Pin can run up to 10 MHz  
  //--------//
  lcd_4_dir   = 1;  //  is output.
  lcd_4_Push  = 1;  //  Pin is set to Push-Pull mode. 
  lcd_4_fast  = 1;  //  Pin can run up to 10 MHz  
  //--------//
  lcd_5_dir   = 1;  //  is output.
  lcd_5_Push  = 1;  //  Pin is set to Push-Pull mode. 
  lcd_5_fast  = 1;  //  Pin can run up to 10 MHz  
  //--------//
  lcd_6_dir   = 1;  //  is output.
  lcd_6_Push  = 1;  //  Pin is set to Push-Pull mode. 
  lcd_6_fast  = 1;  //  Pin can run up to 10 MHz  
  //--------//
  lcd_7_dir   = 1;  //  is output.
  lcd_7_Push  = 1;  //  Pin is set to Push-Pull mode. 
  lcd_7_fast  = 1;  //  Pin can run up to 10 MHz  
  //--------//
  //--------//
  L1_dir   = 1;  //  is output.
  L1_Push  = 1;  //  Pin is set to Push-Pull mode. 
  L1_fast  = 1;  //  Pin can run up to 10 MHz  
  //--------//
  L2_dir   = 1;  //  is output.
  L2_Push  = 1;  //  Pin is set to Push-Pull mode. 
  L2_fast  = 1;  //  Pin can run up to 10 MHz 
  
  BZ_dir   = 1;  //  is output.
  BZ_Push  = 1;  //  Pin is set to Push-Pull mode. 
  BZ_fast  = 1;  //  Pin can run up to 10 MHz 
  //--------//
  conf_dir   = 0;  //  is output.
  conf_Push  = 1;  //  Pin is set to Push-Pull mode. 
  conf_fast  = 0;  //  Pin can run up to 10 MHz  
  //--------//
  baixo_dir   = 0;  //  is output.
  baixo_Push  = 1;  //  Pin is set to Push-Pull mode. 
  baixo_fast  = 0;  //  Pin can run up to 10 MHz  
  //--------//
  cima_dir   = 0;  //  is output.
  cima_Push  = 1;  //  Pin is set to Push-Pull mode. 
  cima_fast  = 0;  //  Pin can run up to 10 MHz  
  //--------//
  volta_dir   = 0;  //  is output.
  volta_Push  = 1;  //  Pin is set to Push-Pull mode. 
  volta_fast  = 0;  //  Pin can run up to 10 MHz  
  //--------//
  //led_b_dir   = 1;  //  is output.
  //led_b_Push  = 1;  //  Pin is set to Push-Pull mode. 
  //led_b_fast  = 1;  //  Pin can run up to 10 MHz  
  //--------//
  //bot_dir   = 0;         //   is Imput.
  //bot_Push  = 1;         // Pull-up sem interromper
  //bot_fast  = 0;         // 
  //--------//
  rs_io_dir   = 1;  //  is output.
  rs_io_Push  = 1;  //  Pin is set to Push-Pull mode. 
  rs_io_fast  = 1;  //  Pin can run up to 10 MHz  
}
//---------------------------------------------------------------------------//
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
//---------------------------------------------------------------------------//
//
//  Reset Timer 2 to a known state.
//
void InitialiseTimer1()
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
//---------------------------------------------------------------------------//
//
//  Setup Timer 2 to PWM signal.
//
void SetupTimer1()
{
  /*
  TIM1_ARRH = (char)(1000 >> 8); //Auto-reload Hi-byte, 2mHz/1000 = 2kHz
  TIM1_ARRL = (char)(1000); //Auto-reload Lo-byte
  
  TIM1_PSCRH = 0x00; //Prescaler Hi-byte, fCK_PSC/(PSCR[15:0]+1)
  TIM1_PSCRL = 0x08; //Prescaler Lo-byte
  
  TIM1_CCR1H = (char)(200 >> 8); //Duty cycle Hi-byte
  TIM1_CCR1L = (char)(200); //Duty cycle Lo-byte
  
  TIM1_CCR2H = (char)(200 >> 8); //Duty cycle Hi-byte
  TIM1_CCR2L = (char)(200); //Duty cycle Lo-byte
  
  TIM1_CCR3H = (char)(200 >> 8); //Duty cycle Hi-byte
  TIM1_CCR3L = (char)(200); //Duty cycle Lo-byte
  
  
  TIM1_CCMR1 |= 0x60; //PC1 pin is set becom the PWM output,PWM mode 1
  TIM1_CCMR2 |= 0x60; //PC1 pin is set becom the PWM output,PWM mode 1
  TIM1_CCMR3 |= 0x60; //PC1 pin is set becom the PWM output,PWM mode 1
  
  //TIM1_CCER1 |= 0x01; //Capture enabled
  TIM1_CCER1_CC1E = 1;    //  Enable compare mode for channel 1
  TIM1_CCER1_CC2E = 1;    //  Enable compare mode for channel 2
  TIM1_CCER2_CC3E = 1;    //  Enable compare mode for channel 2
  
  
  TIM1_IER = 0x00; //All interrupt disabled
  TIM1_CR1 = 0x01; //Countrol enable 
  TIM1_BKR |= 0x80; //Enable PWM output  
  
  */
  TIM1_PSCRH = 0;
  TIM1_PSCRL = 0;
  // TIM1_ARRH = 0xc3;       //  High byte of 50,000.
  // TIM1_ARRL = 0x50;       //  Low byte of 50,000.
  TIM1_ARRH = 0xff;       //  High byte of 50,000.
  TIM1_ARRL = 0xff;       //  Low byte of 50,000.
  //--------//
  
  TIM1_CCR1H = 0x00;      //  High byte of 12,500
  TIM1_CCR1L = 0x00;      //  Low byte of 12,500
  //--//
  TIM1_CCR2H = 0x00;      //  High byte of 12,500
  TIM1_CCR2L = 0x00;      //  Low byte of 12,500
  //--//
  TIM1_CCR3H = 0x00;      //  High byte of 12,500
  TIM1_CCR3L = 0x00;      //  Low byte of 12,500  
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
  //PWM1_SetRatio8(255);
  //PWM2_SetRatio8(255);
  //PWM3_SetRatio8(255);  
  
  TIM1_CCER1_CC1E = 1;    //  Enable compare mode for channel 1
  TIM1_CCER1_CC2E = 1;    //  Enable compare mode for channel 2
  TIM1_CCER2_CC3E = 1;    //  Enable compare mode for channel 3
  //-----------------//
  TIM1_CCMR1 |= 0x60; //PC1 pin is set becom the PWM output,PWM mode 1
  TIM1_CCMR2 |= 0x60; //PC1 pin is set becom the PWM output,PWM mode 1
  TIM1_CCMR3 |= 0x60; //PC1 pin is set becom the PWM output,PWM mode 1
  //-----------------//
  // TIM1_CCER1_CC1P = 0;    //  Active high.
  TIM1_IER = 0x00; //All interrupt disabled
  TIM1_CR1_CEN = 1;   //  Finally enable the timer.
  TIM1_BKR |= 0x80; //Enable PWM output 
}
//---------------------------------------------------------------------------//
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
void TM4_Init(void){
  //  configuração para interupção de 1ms a 16MHZ
  TIM4_PSCR = 0x07; // fCK_CNT = fCK_PSC/2**PSCR (2**7=128)
  TIM4_ARR = TOP1MS; // set TOP value (reset cnt) for 1mS
  TIM4_SR   = 0x00;
  TIM4_IER |= 0x01;
  TIM4_CR1 |= 0x01;
}
//----------------------------------------------------------------------------//
#pragma vector = TIM4_OVR_UIF_vector
__interrupt void _TIM4_OVF(void){
  int_5mS ++;
  if(int_5mS >= 5){ 
    int_5mS = 0;
    cont++;
    if (cont ==20)cont = 0;
    temporizador_led ++;
    if(temporizador_led >= 105)ds.hora_full = 1;
    if(temporizador_led >= 210){
      L1 = 1;
      
      //BZ = 1;
      if(temporizador_led >= 225){
        L1 = 0;
        //BZ = 0;
        temporizador_led = 0;
      }
    }
    if(leitura_ds >= 80){
      leitura_ds = 0;
      ds.hora_full = 1;
      //led_b = !led_b;
      // ds.segundos_pulso = !ds.segundos_pulso;
    }else{
      leitura_ds ++;
    } 
  }
  
  TIM4_SR = 0x00; // clear irq flag
}
//------------------------------------------------------------------------------
void beep(void){
  BZ = 1;
  L2 = 1;
  delay_ms(15);
  BZ = 0;
  L2 = 0;
}
//------------------------------------------------------------------------------
void tratar_teclas(void){                           //Função para leitura dos botões
  if(!auxiliar.aux_oth){
    //-------------------------tecla cima--------------------------//      
    auxiliar.aux1 = 50;
    while(!cima && auxiliar.aux1){
      auxiliar.aux1--;
    }  
    if(!auxiliar.aux1)auxiliar.aux_cima  = 1;                          //seta aux_mais, se botão pressionado
    if(cima && auxiliar.aux_cima){                         //botão mais solto e flag setada?
      beep();                                            //sim...
      auxiliar.aux_cima = 0;                                 //limpa flag
      menu.men--;                                       //incrementa screen
      if(menu.men < 1)menu.men = menu.men1;                   //se maior que valor máximo, retorna ao valor 1
      
      limpa_lcd();                                 
      
    } //end if mais solto
    //-------------------------tecla baixo-------------------------//
    auxiliar.aux2 = 50;
    while(!baixo && auxiliar.aux2 ){
      auxiliar.aux2--;
    }
    if(!auxiliar.aux2)auxiliar.aux_baixo = 1;                             //seta aux_menos, se botão pressionado
    
    if(baixo && auxiliar.aux_baixo){           //botão menos solto e flag setada?
      beep();                                         //sim...
      auxiliar.aux_baixo = 0;                              //limpa flag
      menu.men++;                                     //decrementa menu
      if(menu.men > menu.men1) {menu.men = 1;}                //se menor que 1, retorna ao valor máximo
      
      limpa_lcd();                                 
      
    } //end if menos solt
    //--------------------------tecla conf-------------------------//
    auxiliar.aux3 = 50;
    while(!conf && auxiliar.aux3){
      auxiliar.aux3 --;
    } 
    if(!auxiliar.aux3)auxiliar.aux_conf = 1;
    
    if(conf && auxiliar.aux_conf){
      beep();
      auxiliar.aux_oth = 1;
      if(auxiliar.aux_conf && menu.men ==1){
        menu.men = 1;
        auxiliar.aux_oth = 0;
      }
      if(auxiliar.aux_conf && menu.men ==2){
        menu.hra = 1;
      }
      if(auxiliar.aux_conf && menu.men ==3){
        menu.dta = 1;
      }
      if(auxiliar.aux_conf && menu.men ==4){
        menu.prs = 1;
      }
      if(auxiliar.aux_conf && menu.men ==5){
        menu.cfn = 1;
      }
      auxiliar.aux_conf = 0;
      limpa_lcd();  
    }
    
    //---VOLTA---//
    auxiliar.aux4 = 50;
    while(!volta && auxiliar.aux4){
      auxiliar.aux4--;
    } 
    if(!auxiliar.aux4)auxiliar.aux_volta = 1;
    if(volta && auxiliar.aux_volta && menu.men>1){
      beep();
      menu.men = 1;
      auxiliar.aux_volta = 0;
    }
  }
  
  if(menu.hra){
    auxiliar.aux3 = 50;
    while(!conf && auxiliar.aux3){
      auxiliar.aux3 --;
    } 
    if(!auxiliar.aux3)auxiliar.aux_conf = 1;
    if(conf && auxiliar.aux_conf){
      beep();
      menu.hra++;
      auxiliar.aux_conf = 0;
      if(menu.hra>3){
        //auxiliar.aux_conf = 0;
        menu.hra = 0;
        auxiliar.aux_oth = 0;
      }
      
    }
    auxiliar.aux4 = 50;
    while(!volta && auxiliar.aux4){
      auxiliar.aux4 --;
    } 
    if(!auxiliar.aux4)auxiliar.aux_volta = 1;
    if(volta && auxiliar.aux_volta){
      beep();
      menu.hra--;
      auxiliar.aux_volta = 0;
      if(menu.hra<1){
        //auxiliar.aux_conf = 0;
        auxiliar.aux_oth = 0;
      }
      
    }
  }
  if(menu.dta){
    auxiliar.aux3 = 50;
    while(!conf && auxiliar.aux3){
      auxiliar.aux3 --;
    } 
    if(!auxiliar.aux3)auxiliar.aux_conf = 1;
    if(conf && auxiliar.aux_conf){
      beep();  
      menu.dta++;
      auxiliar.aux_conf = 0;
      if(menu.dta>4){
        auxiliar.aux_oth = 0;
        menu.dta = 0;
      }
      
    }
    auxiliar.aux4 = 50;
    while(!volta && auxiliar.aux4){
      auxiliar.aux4 --;
    } 
    if(!auxiliar.aux4)auxiliar.aux_volta = 1;
    if(volta && auxiliar.aux_volta){
      beep();  
      menu.dta--;
      auxiliar.aux_volta = 0;
      if(menu.dta<1){
        auxiliar.aux_oth = 0;
        
      }
      
    }
    
  }
  if(menu.prs && !auxiliar.aux_oth1){
    delay_ms(20);
    auxiliar.aux1 = 50;
    while(!cima && auxiliar.aux1){
      auxiliar.aux1--;
    }
    if(!auxiliar.aux1) auxiliar.aux_cima =1;
    if(cima && auxiliar.aux_cima){
      beep();
      menu.prs--;
      auxiliar.aux_cima = 0;
      //seta aux_mais, se botão pressionado                       
      if(menu.prs<1){
        menu.prs = 3;
      }
    }
    
    auxiliar.aux2 = 50;
    while(!baixo && auxiliar.aux2 ){
      auxiliar.aux2 --;
    }
    if(!auxiliar.aux2)auxiliar.aux_baixo =1;
    if(auxiliar.aux_baixo && !auxiliar.ax1 && baixo){
      beep();
      auxiliar.aux_baixo = 0;
      menu.prs++;
      if(menu.prs>3){
        menu.prs = 1;
      }
    }
    
    auxiliar.aux3 = 50;
    while(!conf && auxiliar.aux3){
      auxiliar.aux3 --;
    } 
    if(!auxiliar.aux3)auxiliar.aux_conf = 1;
    if(conf && auxiliar.aux_conf){
      auxiliar.aux_oth1 =1;
      beep(); 
      if(auxiliar.aux_conf && menu.prs ==1){
        menu.prs1 = 1;
        
      }
      if(auxiliar.aux_conf && menu.prs ==2){
        menu.prs2 = 1;
        
      }
      if(auxiliar.aux_conf && menu.prs ==3){
        menu.prs3 = 1;
        
      } 
      auxiliar.aux_conf = 0;
    }
    
    
    auxiliar.aux4 = 50;
    while(!volta && auxiliar.aux4){
      auxiliar.aux4 --;
    } 
    if(!auxiliar.aux4)auxiliar.aux_volta = 1;
    if(volta && auxiliar.aux_volta){
      beep();  
      menu.prs = 0;
      auxiliar.aux_volta = 0;
      auxiliar.aux_oth = 0;
      
    }
    
  }
  if(menu.prs1){
    delay_ms(20);
    auxiliar.aux1 = 50;
    while(!cima && auxiliar.aux1){
      auxiliar.aux1--;
    }
    if(!auxiliar.aux1) auxiliar.aux_cima =1;
    if(cima && auxiliar.aux_cima){
      beep();
      menu.prs1--;
      auxiliar.aux_cima = 0;
      //seta aux_mais, se botão pressionado                       
      if(menu.prs1<1){
        menu.prs1 = 2;
      }
    }
    
    auxiliar.aux2 = 50;
    while(!baixo && auxiliar.aux2 ){
      auxiliar.aux2 --;
    }
    if(!auxiliar.aux2)auxiliar.aux_baixo =1;
    if(auxiliar.aux_baixo && !auxiliar.ax1 && baixo){
      beep();
      auxiliar.aux_baixo = 0;
      menu.prs1++;
      if(menu.prs1>2){
        menu.prs1 = 1;
      }
    }
    
    auxiliar.aux3 = 50;
    while(!conf && auxiliar.aux3){
      auxiliar.aux3 --;
    } 
    if(!auxiliar.aux3)auxiliar.aux_conf = 1;
    if(conf && auxiliar.aux_conf){
      menu.prs1 = 0;
      limpa_lcd();
      auxiliar.aux_oth1 = 0;
      beep(); 
      auxiliar.aux_conf = 0;
    }
    
    
    auxiliar.aux4 = 50;
    while(!volta && auxiliar.aux4){
      auxiliar.aux4 --;
    } 
    if(!auxiliar.aux4)auxiliar.aux_volta = 1;
    if(volta && auxiliar.aux_volta){
      beep();  
      menu.prs1 = 0;
      limpa_lcd();
      auxiliar.aux_volta = 0;
      //auxiliar.aux_oth = 0;
      auxiliar.aux_oth1 = 0;
    }
    
  }
  if(menu.prs2){
    delay_ms(20);
    auxiliar.aux1 = 50;
    while(!cima && auxiliar.aux1){
      auxiliar.aux1--;
    }
    if(!auxiliar.aux1) auxiliar.aux_cima =1;
    if(cima && auxiliar.aux_cima){
      beep();
      menu.prs2--;
      auxiliar.aux_cima = 0;
      //seta aux_mais, se botão pressionado                       
      if(menu.prs2<1){
        menu.prs2 = 2;
      }
    }
    
    auxiliar.aux2 = 50;
    while(!baixo && auxiliar.aux2 ){
      auxiliar.aux2 --;
    }
    if(!auxiliar.aux2)auxiliar.aux_baixo =1;
    if(auxiliar.aux_baixo && !auxiliar.ax1 && baixo){
      beep();
      auxiliar.aux_baixo = 0;
      menu.prs2++;
      if(menu.prs2>2){
        menu.prs2 = 1;
      }
    }
    
    auxiliar.aux3 = 50;
    while(!conf && auxiliar.aux3){
      auxiliar.aux3 --;
    } 
    if(!auxiliar.aux3)auxiliar.aux_conf = 1;
    if(conf && auxiliar.aux_conf){
      menu.prs2 = 0;
      limpa_lcd();
      auxiliar.aux_oth1 = 0;
      beep(); 
      auxiliar.aux_conf = 0;
    }
    
    
    auxiliar.aux4 = 50;
    while(!volta && auxiliar.aux4){
      auxiliar.aux4 --;
    } 
    if(!auxiliar.aux4)auxiliar.aux_volta = 1;
    if(volta && auxiliar.aux_volta){
      beep();  
      menu.prs2 = 0;
      limpa_lcd();
      auxiliar.aux_volta = 0;
      //auxiliar.aux_oth = 0;
      auxiliar.aux_oth1 = 0;
    }
    
  }
  if(menu.prs3){
    delay_ms(20);
    auxiliar.aux1 = 50;
    while(!cima && auxiliar.aux1){
      auxiliar.aux1--;
    }
    if(!auxiliar.aux1) auxiliar.aux_cima =1;
    if(cima && auxiliar.aux_cima){
      beep();
      menu.prs3--;
      auxiliar.aux_cima = 0;
      //seta aux_mais, se botão pressionado                       
      if(menu.prs3<1){
        menu.prs3 = 2;
      }
    }
    
    auxiliar.aux2 = 50;
    while(!baixo && auxiliar.aux2 ){
      auxiliar.aux2 --;
    }
    if(!auxiliar.aux2)auxiliar.aux_baixo =1;
    if(auxiliar.aux_baixo && !auxiliar.ax1 && baixo){
      beep();
      auxiliar.aux_baixo = 0;
      menu.prs3++;
      if(menu.prs3>2){
        menu.prs3 = 1;
      }
    }
    
    auxiliar.aux3 = 50;
    while(!conf && auxiliar.aux3){
      auxiliar.aux3 --;
    } 
    if(!auxiliar.aux3)auxiliar.aux_conf = 1;
    if(conf && auxiliar.aux_conf){
      menu.prs3 = 0;
      limpa_lcd();
      auxiliar.aux_oth1 = 0;
      beep(); 
      auxiliar.aux_conf = 0;
    }
    
    
    auxiliar.aux4 = 50;
    while(!volta && auxiliar.aux4){
      auxiliar.aux4 --;
    } 
    if(!auxiliar.aux4)auxiliar.aux_volta = 1;
    if(volta && auxiliar.aux_volta){
      beep();  
      menu.prs3 = 0;
      limpa_lcd();
      auxiliar.aux_volta = 0;
      //auxiliar.aux_oth = 0;
      auxiliar.aux_oth1 = 0;
    }
    
  }
  
}

void atualizar_menu(void){
  switch(menu.men){
    //-----//
  case 1 : 
    if(cont<=20){
      escreve_string_lcd(text,1);
      escreve_string_lcd(text1,2); 
      escreve_string_lcd(text2,3); 
      escreve_string_lcd(text3,4);
    }
    /*if(cont1==51)LCD_Clear();
    if (cont1>50){
    LCD_String_xy(1,6,"DATA");
    LCD_String_xy(2,1,message1);}*/
    
    break;
    //-----//
  case 2 :
    switch(menu.hra){
    case 0 :
      escreve_string_lcd("Conf. Relogio     <-",1);
      escreve_string_lcd("Conf. Data          ",2);
      escreve_string_lcd("Conf. Pre set       ",3);
      escreve_string_lcd("Conf. Manual        ",4);
      break;
    case 1:
      escreve_string_lcd("       Horas:       ",2);
      delay_ms(20);
      auxiliar.aux1 = 50;
      while(!cima && auxiliar.aux1){
        auxiliar.aux1--;
      }
      if(!auxiliar.aux1) auxiliar.aux_cima =1;
      if(cima && auxiliar.aux_cima){
        beep();
        hora_rel++;
        auxiliar.aux_cima = 0;
      }                             //seta aux_mais, se botão pressionado                       
      if(hora_rel>23){
        hora_rel = 0;
      }
      
      auxiliar.aux2 = 50;
      while(!baixo && auxiliar.aux2 ){
        auxiliar.aux2 --;
      }
      if(!hora_rel){
        auxiliar.ax1=1;
      }
      if(hora_rel){
        auxiliar.ax1=0;
      }
      if(!auxiliar.aux2)auxiliar.aux_baixo =1;
      if(auxiliar.aux_baixo && !auxiliar.ax1 && baixo){
        beep();
        auxiliar.aux_baixo = 0;
        hora_rel--;
      }                             //seta aux_menos, se botão pressionado
      
      
      formatar_hr_rel(text3, thora, hora_rel, min_rel, seg_rel);
      escreve_string_lcd(thora,3);
      
      break;
    case 2 :
      escreve_string_lcd("      Minutos:      ",2);
      delay_ms(20);
      auxiliar.aux1 = 50;
      while(!cima && auxiliar.aux1){
        auxiliar.aux1--;
      }  
      if(!auxiliar.aux1)auxiliar.aux_cima =1; //seta aux_mais, se botão pressionado	
      if(auxiliar.aux_cima && cima){
        beep();
        min_rel++;
        auxiliar.aux_cima = 0;}
      if(min_rel>59){
        min_rel = 0;
      }
      auxiliar.aux2 = 50;
      while(!baixo && auxiliar.aux2){
        auxiliar.aux2--;
      }
      if(!auxiliar.aux2 && !auxiliar.ax1)auxiliar.aux_baixo = 1;//seta aux_menos, se botão pressionado
      if(auxiliar.aux_baixo && !auxiliar.ax1 && baixo){
        beep();
        min_rel--;
        auxiliar.aux_baixo = 0;}
      if(!min_rel){
        auxiliar.ax1=1;
      }
      if(min_rel){
        auxiliar.ax1=0;
      }//seta aux_menos, se botão pressionado
      
      formatar_hr_rel(text3, thora, hora_rel, min_rel, seg_rel);
      escreve_string_lcd(thora,3);
      
      break;
    case 3 :
      escreve_string_lcd("      Segundos:      ",2);
      delay_ms(20);
      auxiliar.aux1 = 50;
      while(!cima && auxiliar.aux1){
        auxiliar.aux1--;
      }  
      if(!auxiliar.aux1)auxiliar.aux_cima =1; //seta aux_mais, se botão pressionado	
      if(auxiliar.aux_cima && cima){
        beep();
        seg_rel++;
        auxiliar.aux_cima = 0;}
      if(seg_rel>59){
        seg_rel = 0;
      }
      auxiliar.aux2 = 50;
      while(!baixo && auxiliar.aux2){
        auxiliar.aux2--;
      }
      if(!auxiliar.aux2 && !auxiliar.ax1)auxiliar.aux_baixo = 1;//seta aux_menos, se botão pressionado
      if(auxiliar.aux_baixo && !auxiliar.ax1 && baixo){
        beep();
        seg_rel--;
        auxiliar.aux_baixo = 0;}
      if(!seg_rel){
        auxiliar.ax1=1;
      }
      if(seg_rel){
        auxiliar.ax1=0;
      }//seta aux_menos, se botão pressionado
      
      formatar_hr_rel(text3, thora, hora_rel, min_rel, seg_rel);
      escreve_string_lcd(thora,3);
      ajustar_relogio(hora_rel,min_rel,seg_rel);
    }
    break;
  case 3:
    switch(menu.dta){
    case 0 :
      escreve_string_lcd("Conf. Relogio       ",1);
      escreve_string_lcd("Conf. Data        <-",2);
      escreve_string_lcd("Conf. Pre set       ",3);
      escreve_string_lcd("Conf. Manual        ",4);
      break;
    case 1:
      escreve_string_lcd("        Ano:        ",2);
      delay_ms(20);
      auxiliar.aux1 = 50;
      while(!cima && auxiliar.aux1){
        auxiliar.aux1--;
      }
      if(!auxiliar.aux1) auxiliar.aux_cima =1;
      if(cima && auxiliar.aux_cima){
        beep();
        ano_rel++;
        auxiliar.aux_cima = 0;
      }                             //seta aux_mais, se botão pressionado                       
      if(ano_rel>99){
        ano_rel = 0;
      }
      
      auxiliar.aux2 = 50;
      while(!baixo && auxiliar.aux2 ){
        auxiliar.aux2 --;
      }      
      if(!ano_rel){
        auxiliar.ax1=1;
      }
      if(ano_rel){
        auxiliar.ax1=0;
      }
      if(!auxiliar.aux2)auxiliar.aux_baixo =1;
      if(auxiliar.aux_baixo && !auxiliar.ax1 && baixo){
        beep();
        auxiliar.aux_baixo = 0;
        ano_rel--;
      }                             //seta aux_menos, se botão pressionado
      
      
      formatar_dt_rel(text3, tdata, dia_rel, mes_rel, ano_rel);
      escreve_string_lcd(tdata,3);
      break;
      
    case 2:
      escreve_string_lcd("        Mes:        ",2);
      delay_ms(20);
      auxiliar.aux1 = 50;
      while(!cima && auxiliar.aux1){
        auxiliar.aux1--;
      }
      if(!auxiliar.aux1) auxiliar.aux_cima =1;
      if(cima && auxiliar.aux_cima){
        beep();
        mes_rel++;
        auxiliar.aux_cima = 0;
      }                             //seta aux_mais, se botão pressionado                       
      if(mes_rel>12){
        mes_rel = 1;
      }
      
      auxiliar.aux2 = 50;
      while(!baixo && auxiliar.aux2 ){
        auxiliar.aux2 --;
      }
      //seta aux_menos, se botão pressionado
      if(mes_rel==1){
        auxiliar.ax1=1;
      }
      if(mes_rel>1){
        auxiliar.ax1=0;
      }
      if(!auxiliar.aux2)auxiliar.aux_baixo =1;
      if(auxiliar.aux_baixo && !auxiliar.ax1 && baixo ){
        beep();
        auxiliar.aux_baixo = 0;
        mes_rel--;
      }                             //seta aux_menos, se botão pressionado
      
      
      formatar_dt_rel(text3, tdata, dia_rel, mes_rel, ano_rel);
      escreve_string_lcd(tdata,3);
      break;
    case 3:
      escreve_string_lcd("        Dia:        ",2);
      delay_ms(20);
      auxiliar.aux1 = 50;
      while(!cima && auxiliar.aux1){
        auxiliar.aux1--;
      }
      if(mes_rel == 2){
        if(dia_rel>28){
          dia_rel = 1;
        }
      }
      if(mes_rel == 4 || mes_rel==6 || mes_rel==8){
        if(dia_rel>30){
          dia_rel = 1;
        }
      }
      else{
        if(dia_rel>31){
          dia_rel = 1;
        }
      }
      if(!auxiliar.aux1) auxiliar.aux_cima =1;
      if(cima && auxiliar.aux_cima){
        beep();
        dia_rel++;
        auxiliar.aux_cima = 0;
      }                             //seta aux_mais, se botão pressionado                       
      
      auxiliar.aux2 = 50;
      while(!baixo && auxiliar.aux2 ){
        auxiliar.aux2 --;
      }
      //seta aux_menos, se botão pressionado
      if(!auxiliar.aux2)auxiliar.aux_baixo =1;
      if(auxiliar.aux_baixo && !auxiliar.ax1 && baixo ){
        
        beep();
        dia_rel--;                             //seta aux_menos, se botão pressionado
        if(mes_rel == 2){
          if(!dia_rel){
            dia_rel = 28;
          }
        }
        if(mes_rel == 4 || mes_rel==6 || mes_rel==8){
          if(!dia_rel){
            dia_rel = 30;
          }
        }
        else{
          if(!dia_rel){
            dia_rel = 31;
          }
        }
        auxiliar.aux_baixo = 0;
      }                             //seta aux_menos, se botão pressionado
      
      
      formatar_dt_rel(text3, tdata, dia_rel, mes_rel, ano_rel);
      escreve_string_lcd(tdata,3);
      break;
    case 4:
      escreve_string_lcd("       Semana:      ",2);
      delay_ms(20);
      auxiliar.aux1 = 50;
      while(!cima && auxiliar.aux1){
        auxiliar.aux1--;
      }
      if(!auxiliar.aux1) auxiliar.aux_cima =1;
      if(cima && auxiliar.aux_cima){
        beep();
        sem_rel++;
        auxiliar.aux_cima = 0;
      }                             //seta aux_mais, se botão pressionado                       
      if(sem_rel>7){
        sem_rel = 1;
      }
      
      auxiliar.aux2 = 50;
      while(!baixo && auxiliar.aux2 ){
        auxiliar.aux2 --;
      }
      //seta aux_menos, se botão pressionado
      if(sem_rel==1){
        auxiliar.ax1=1;
      }
      if(sem_rel>1){
        auxiliar.ax1=0;
      }
      if(!auxiliar.aux2)auxiliar.aux_baixo =1;
      if(auxiliar.aux_baixo && !auxiliar.ax1 && baixo ){
        beep();
        auxiliar.aux_baixo = 0;
        sem_rel--;
      }
      if(sem_rel==1){
        escreve_string_lcd("      Domingo       ",3);
        delay_ms(10);
      }
      if(sem_rel==2){
        escreve_string_lcd("      Segunda       ",3);
        delay_ms(10);
      }
      if(sem_rel==3){
        escreve_string_lcd("       Terca        ",3);
        delay_ms(10);
      }
      if(sem_rel==4){
        escreve_string_lcd("       Quarta       ",3);
        delay_ms(10);
      }
      if(sem_rel==5){
        escreve_string_lcd("       Quinta       ",3);
        delay_ms(10);
      }
      if(sem_rel==6){
        escreve_string_lcd("       Sexta        ",3);
        delay_ms(10);
      }
      if(sem_rel==7){
        escreve_string_lcd("       Sabado       ",3);
        delay_ms(10);
      }
      
      ajustar_data(sem_rel,dia_rel,mes_rel,ano_rel);
      
    }
    break;
  case 4 :
    switch(menu.prs){
    case 0 :
      escreve_string_lcd("Conf. Relogio       ",1);
      escreve_string_lcd("Conf. Data          ",2);
      escreve_string_lcd("Conf. Pre set     <-",3);
      escreve_string_lcd("Conf. Manual        ",4);
      break;
    case 1 :
      if(!auxiliar.aux_oth1){
        escreve_string_lcd("Preset 01         <-",1);
        escreve_string_lcd("Preset 02           ",2);
        escreve_string_lcd("Preset 03           ",3);
      }
      switch(menu.prs1){
      case 1 :
        escreve_string_lcd(prs1,1);
        escreve_string_lcd(prs12,2);
        escreve_string_lcd(prs13,3);
        escreve_string_lcd(prs14,4);
        break;
      case 2:
        escreve_string_lcd(prs15,1);
        escreve_string_lcd(prs16,2);
        escreve_string_lcd(prs17,3);
        escreve_string_lcd(prs18,4);
        break;
      }
      break;
    case 2 :
      if(!auxiliar.aux_oth1){
        escreve_string_lcd("Preset 01           ",1);
        escreve_string_lcd("Preset 02         <-",2);
        escreve_string_lcd("Preset 03           ",3);
      }
      switch(menu.prs2){
      case 1 :
        escreve_string_lcd(prs1,1);
        escreve_string_lcd(prs12,2);
        escreve_string_lcd(prs13,3);
        escreve_string_lcd(prs14,4);
        break;
      case 2:
        escreve_string_lcd(prs15,1);
        escreve_string_lcd(prs16,2);
        escreve_string_lcd(prs17,3);
        escreve_string_lcd(prs18,4);
        break;
      }
      break;
    case 3 :
      if(!auxiliar.aux_oth1){
        escreve_string_lcd("Preset 01           ",1);
        escreve_string_lcd("Preset 02           ",2);
        escreve_string_lcd("Preset 03         <-",3);
      }
      switch(menu.prs3){
      case 1 :
        escreve_string_lcd(prs1,1);
        escreve_string_lcd(prs12,2);
        escreve_string_lcd(prs13,3);
        escreve_string_lcd(prs14,4);
        break;
      case 2:
        escreve_string_lcd(prs15,1);
        escreve_string_lcd(prs16,2);
        escreve_string_lcd(prs17,3);
        escreve_string_lcd(prs18,4);
        break;
      }
    }
    break;
  case 5 :
    switch(menu.cfn){
    case 0 :
      escreve_string_lcd("Conf. Relogio       ",1);
      escreve_string_lcd("Conf. Data          ",2);
      escreve_string_lcd("Conf. Pre set       ",3);
      escreve_string_lcd("Conf. Manual      <-",4);
      break;
    }
    break;
    
  }
}


void formatar_dt_rel(char buff[],char buff1[],unsigned char h,unsigned char mi,unsigned char s){
  
  unsigned char dezena,unidade,centena;
  unsigned int aux;
  centena = 0;
  dezena  = 0;
  unidade = 0;
  //---------------------------------//
  aux = h; 
  for(;aux>=100;aux -=100){centena++;}
  for(;aux>=10;aux -=10){dezena++;}
  for(;aux>=1;aux -=1){unidade++;}
  //------///
  centena = centena + 48;
  dezena  = dezena  + 48;
  unidade = unidade + 48;
  //----//
  buff[12] = dezena;
  buff[13] = unidade;
  buff1[6] = dezena;
  buff1[7] = unidade;
  //---------------------------------//
  centena = 0;
  dezena  = 0;
  unidade = 0;
  aux = mi; 
  for(;aux>=100;aux -=100){centena++;}
  for(;aux>=10;aux -=10){dezena++;}
  for(;aux>=1;aux -=1){unidade++;}
  //------///
  centena = centena + 48;
  dezena  = dezena  + 48;
  unidade = unidade + 48;
  //----//
  buff[15] = dezena;
  buff[16] = unidade;
  buff1[9] = dezena;
  buff1[10] = unidade;
  //---------------------------------//
  centena = 0;
  dezena  = 0;
  unidade = 0;
  aux = s; 
  for(;aux>=100;aux -=100){centena++;}
  for(;aux>=10;aux -=10){dezena++;}
  for(;aux>=1;aux -=1){unidade++;}
  //------///
  centena = centena + 48;
  dezena  = dezena  + 48;
  unidade = unidade + 48;
  //----//
  buff[18] = dezena;
  buff[19] = unidade;
  buff1[12] = dezena;
  buff1[13] = unidade;
}
void formatar_hr_rel(char buff[],char buff1[],unsigned char h,unsigned char mi,unsigned char s){
  unsigned char dezena,unidade,centena;
  unsigned int aux;
  centena = 0;
  dezena  = 0;
  unidade = 0;
  //---------------------------------//
  aux = h; 
  for(;aux>=100;aux -=100){centena++;}
  for(;aux>=10;aux -=10){dezena++;}
  for(;aux>=1;aux -=1){unidade++;}
  //------///
  centena = centena + 48;
  dezena  = dezena  + 48;
  unidade = unidade + 48;
  //----//
  buff[3] = dezena;
  buff[4] = unidade;
  buff1[6] = dezena;
  buff1[7] = unidade;
  //---------------------------------//
  centena = 0;
  dezena  = 0;
  unidade = 0;
  aux = mi; 
  for(;aux>=100;aux -=100){centena++;}
  for(;aux>=10;aux -=10){dezena++;}
  for(;aux>=1;aux -=1){unidade++;}
  //------///
  centena = centena + 48;
  dezena  = dezena  + 48;
  unidade = unidade + 48;
  //----//
  buff[6] = dezena;
  buff[7] = unidade;
  buff1[9] = dezena;
  buff1[10] = unidade;
  //---------------------------------//
  centena = 0;
  dezena  = 0;
  unidade = 0;
  aux = s; 
  for(;aux>=100;aux -=100){centena++;}
  for(;aux>=10;aux -=10){dezena++;}
  for(;aux>=1;aux -=1){unidade++;}
  //------///
  centena = centena + 48;
  dezena  = dezena  + 48;
  unidade = unidade + 48;
  //----//
  buff1[12] = dezena;
  buff1[13] = unidade;
}
void conv_valor(char buff[],unsigned char aux){
  unsigned char dezena,unidade,centena;
  unsigned int aux1;
  centena = 0;
  dezena  = 0;
  unidade = 0;
  aux1 = aux; 
  for(;aux>=100;aux -=100){centena++;}
  for(;aux>=10;aux -=10){dezena++;}
  for(;aux>=1;aux -=1){unidade++;}
  
  centena = (centena + 48);
  dezena  = (dezena  + 48);
  unidade = (unidade + 48);
  
  
  buff[5] = dezena;
  buff[6] = unidade;
}
void verificar_relogio(void){
  if(ds.hora_full){
    read_rtc();
    formatar_hr_rel(text3, thora, hora, minutos, segundos);
    formatar_dt_rel(text3, tdata, dias, meses, anos);
    ds.hora_full = 0;
  }
}
