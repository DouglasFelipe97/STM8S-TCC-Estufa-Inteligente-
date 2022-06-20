#ifndef _DISPLAY_LCD_H_
#define _DISPLAY_LCD_H_


void inicializa_lcd(void);
void limpa_lcd(void);
void linha_1_lcd(void);
void linha_2_lcd(void);
void linha_3_lcd(void);
void linha_4_lcd(void);
void escreve_dado_lcd(unsigned char d);
void escreve_comando_lcd(unsigned char d);
void escreve_string_lcd(unsigned char *str,unsigned char linha);
void escreve_str_lcd(unsigned char *str,unsigned char linha);



#endif
