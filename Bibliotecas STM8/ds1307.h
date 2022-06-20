#ifndef _DS1307_H_
#define _DS1307_H_

#define uint8_t unsigned char


  uint8_t I2C_ReadOneByteDataFromSlave(uint8_t address);
  uint8_t I2C_ReadMultiBytesFromSlave(uint8_t address,uint8_t *rxbuf,uint8_t len);
  void I2C_Init(void);


  void sda_entrada(void);
  void sda_saida(void);
  void start(void);
  void stop(void);
  void rtc_1(void);
  void rtc_0(void);
  void clok(void);
  unsigned char  end_escrita(void);
  unsigned char  end_leitura(void);
  unsigned char  ler_ds1307(unsigned char endereco);
  unsigned char  escrever_ds1307(unsigned char endereco, unsigned char dado);
  unsigned char  converter_bcb(unsigned char x);
  void read_rtc(void);
  void ajustar_relogio(unsigned char ho,unsigned char min,unsigned char segu);
  unsigned char formatar_hora(unsigned char dado);
 void ajustar_data(unsigned char sem,unsigned char dia,unsigned char mes,unsigned char ano);
#endif
