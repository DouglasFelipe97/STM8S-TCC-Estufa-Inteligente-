#ifndef _INTERUPT_H_
#define _INTERUPT_H_
  //------------------//
#define  protecao_ad_2a    130//122 //2A
#define  protecao_ad_5a    280//278 //5A
#define  protecao_ad_10a   520 //10A
#define  protecao_ad_15a   750
#define  protecao_ad_20a   830
#define  protecao_ad_25a   860
   // 126---150->2A
  //------------------//
  void tm1628_saida(void);
  void tm1628_entrada(void);
  void delay_ms(unsigned int temp);
  void delay_100us(unsigned int temp);
  void int_rf(void);
  void interupecao_5ms(void);
  void ADC_Init(void);                        // Configura o conversor AD
  unsigned int ADC_Read(unsigned char Canal); // Lê um canal do ADC
  void UART_Init(void);
  void transmite_as1(unsigned char Chr);
  void transmite_string_as1(char *c);
  void uart_Write(unsigned char Chr);
#endif