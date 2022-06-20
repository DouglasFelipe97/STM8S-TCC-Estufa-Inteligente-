#include <iostm8s005K6.h>
#include <intrinsics.h>
//-----------------------------//
#define sda       PB_ODR_ODR5
#define sda_in    PB_IDR_IDR5
#define sda_dir   PB_DDR_DDR5
#define sda_Push  PB_CR1_C15
#define sda_fast  PB_CR2_C25
     //--------------//
#define scl       PB_ODR_ODR4
#define scl_dir   PB_DDR_DDR4
#define scl_Push  PB_CR1_C14
#define scl_fast  PB_CR2_C24
     //--------------//
#define sq       PD_ODR_ODR0
#define sq_dir   PD_DDR_DDR0
#define sq_Push  PD_CR1_C10
#define sq_fast  PD_CR2_C20
     //--------------//
#define tm_data       PD_ODR_ODR2
#define tm_data_in    PD_IDR_IDR2
#define tm_data_dir   PD_DDR_DDR2
#define tm_data_Push  PD_CR1_C12
#define tm_data_fast  PD_CR2_C22
     //--------------//
#define tm_ck       PD_ODR_ODR3
#define tm_ck_dir   PD_DDR_DDR3
#define tm_ck_Push  PD_CR1_C13
#define tm_ck_fast  PD_CR2_C23
     //--------------//
#define tm_stb       PD_ODR_ODR4
#define tm_stb_dir   PD_DDR_DDR4
#define tm_stb_Push  PD_CR1_C14
#define tm_stb_fast  PD_CR2_C24
     //--------------//
#define led_a       PC_ODR_ODR6
#define led_a_dir   PC_DDR_DDR6
#define led_a_Push  PC_CR1_C16
#define led_a_fast  PC_CR2_C26
     //--------------//
#define led_b       PC_ODR_ODR7
#define led_b_dir   PC_DDR_DDR7
#define led_b_Push  PC_CR1_C17
#define led_b_fast  PC_CR2_C27
     //--------------//
#define bot       PC_IDR_IDR5
#define bot_dir   PC_DDR_DDR5
#define bot_Push  PC_CR1_C15
#define bot_fast  PC_CR2_C25
     //--------------//
#define rx       PD_IDR_IDR6
#define rx_dir   PD_DDR_DDR6
#define rx_Push  PD_CR1_C16
#define rx_fast  PD_CR2_C26
     //--------------//
#define tx       PD_IDR_IDR6
#define tx_dir   PD_DDR_DDR6
#define tx_Push  PD_CR1_C16
#define tx_fast  PD_CR2_C26
     //--------------//
#define rs_io       PD_ODR_ODR7
#define rs_io_dir   PD_DDR_DDR7
#define rs_io_Push  PD_CR1_C17
#define rs_io_fast  PD_CR2_C27
     //--------------//
//#define saida_1       PE_ODR_ODR5 invertido com a 4 
//#define saida_1_dir   PE_DDR_DDR5
//#define saida_1_Push  PE_CR1_C15
//#define saida_1_fast  PE_CR2_C25
      //--------------//
#define saida_2       PB_ODR_ODR1
#define saida_2_dir   PB_DDR_DDR1
#define saida_2_Push  PB_CR1_C11
#define saida_2_fast  PB_CR2_C21
      //--------------//
#define saida_3       PB_ODR_ODR2
#define saida_3_dir   PB_DDR_DDR2
#define saida_3_Push  PB_CR1_C12
#define saida_3_fast  PB_CR2_C22
      //--------------//
#define saida_1       PB_ODR_ODR3
#define saida_1_dir   PB_DDR_DDR3
#define saida_1_Push  PB_CR1_C13
#define saida_1_fast  PB_CR2_C23
      //--------------//
#define spwm_1       PC_ODR_ODR1
#define spwm_1_dir   PC_DDR_DDR1
#define spwm_1_Push  PC_CR1_C11
#define spwm_1_fast  PC_CR2_C21
      //--------------//
#define spwm_2       PC_ODR_ODR2
#define spwm_2_dir   PC_DDR_DDR2
#define spwm_2_Push  PC_CR1_C12
#define spwm_2_fast  PC_CR2_C22
      //--------------//
#define spwm_3       PC_ODR_ODR3
#define spwm_3_dir   PC_DDR_DDR3
#define spwm_3_Push  PC_CR1_C13
#define spwm_3_fast  PC_CR2_C23
      //--------------//
#define rf       PC_IDR_IDR4 
//-----------------------------//
#define p_sinc_max_2m2 3954
#define p_sinc_min_2m2 2399
#define p_larg_1_min_2m2 87
#define p_larg_1_max_2m2 167
#define p_larg_2_min_2m2 169
#define p_larg_2_max_2m2 325  

#define p_sinc_max_1m5 2400
#define p_sinc_min_1m5 1320
#define p_larg_1_min_1m5 57
#define p_larg_1_max_1m5 117
#define p_larg_2_min_1m5 115
#define p_larg_2_max_1m5 233
//-----------------------------//
#define p_larg_estouro 3956
#define anticode 5
#define anticode_a 11
//-----------------------------//
#define  valor_strobo_audio 50
#define  temp_controle 50
#define  temp_pulso    37
//--------------------------------------------------------------//
#define _MEM_(mem_addr)         (*(volatile unsigned char *)(mem_addr))
#define EEPROM_START_ADDR       0x4000
#define EEPROM_END_ADDR         0x407F
//--------------------------------------------------------------//
#define TOP2MS		255-1 // Tim4 compare top value for 1mS tick
#define TOP1MS		125-1 // Tim4 compare top value for 1mS tick
          //------//
#define _CLI() asm("SIM")		// disable interrupts
#define _SEI() asm("RIM")		// enable interrupts
#define _NOP() asm("NOP")		// no operation
#define _WDR() IWDG_KR = 0xAA	// kick independent watchdog
//--------------------------------------------------------------//
#define temp_espera_display  400 //600
#define  travar_3_min  180000