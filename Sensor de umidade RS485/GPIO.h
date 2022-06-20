#include <iostm8s003f3.h>
#include <intrinsics.h>
//-----------------------------//
#define rs_io       PD_ODR_ODR4
#define rs_io_dir   PD_DDR_DDR4
#define rs_io_Push  PD_CR1_C14
#define rs_io_fast  PD_CR2_C24
//-----------------------------//
#define chave_1       PB_IDR_IDR4
#define chave_1_dir   PB_DDR_DDR4
#define chave_1_Push  PB_CR1_C14
#define chave_1_fast  PB_CR2_C24
//-----------------------------//
#define chave_2       PC_IDR_IDR5
#define chave_2_dir   PC_DDR_DDR5
#define chave_2_Push  PC_CR1_C15
#define chave_2_fast  PC_CR2_C25
//-----------------------------//
#define chave_3       PC_IDR_IDR6
#define chave_3_dir   PC_DDR_DDR6
#define chave_3_Push  PC_CR1_C16
#define chave_3_fast  PC_CR2_C26
//-----------------------------//
#define chave_4       PC_IDR_IDR7
#define chave_4_dir   PC_DDR_DDR7
#define chave_4_Push  PC_CR1_C17
#define chave_4_fast  PC_CR2_C27
//----------------------------//
#define led       PA_ODR_ODR3
#define led_dir   PA_DDR_DDR3
#define led_Push  PA_CR1_C13
#define led_fast  PA_CR2_C23
     //--------------//
#define bt_prog       PB_IDR_IDR5
#define bt_prog_dir   PB_DDR_DDR5
#define bt_prog_Push  PB_CR1_C15
#define bt_prog_fast  PB_CR2_C25
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
#define  sensor_presente   50
//--------------------------------------------------------------//