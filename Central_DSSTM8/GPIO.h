#include <iostm8s005K6.h>
#include <intrinsics.h>
//-----------------------------//
#define rs_io       PD_ODR_ODR7
#define rs_io_dir   PD_DDR_DDR7
#define rs_io_Push  PD_CR1_C17
#define rs_io_fast  PD_CR2_C27
//-----------------------------//
#define lcd_rs            PB_ODR_ODR0
#define lcd_rs_dir        PB_DDR_DDR0
#define lcd_rs_Push       PB_CR1_C10
#define lcd_rs_fast       PB_CR2_C20
//-----------------------------//
#define lcd_rw            PB_ODR_ODR1
#define lcd_rw_dir        PB_DDR_DDR1
#define lcd_rw_Push       PB_CR1_C11
#define lcd_rw_fast       PB_CR2_C21
//-----------------------------//
#define lcd_e            PE_ODR_ODR5
#define lcd_e_dir        PE_DDR_DDR5
#define lcd_e_Push       PE_CR1_C15
#define lcd_e_fast       PE_CR2_C25
//-----------------------------//
#define lcd_4            PC_ODR_ODR1
#define lcd_4_dir        PC_DDR_DDR1
#define lcd_4_Push       PC_CR1_C11
#define lcd_4_fast       PC_CR2_C21
//-----------------------------//
#define lcd_5            PC_ODR_ODR2
#define lcd_5_dir        PC_DDR_DDR2
#define lcd_5_Push       PC_CR1_C12
#define lcd_5_fast       PC_CR2_C22
//-----------------------------//
#define lcd_6            PC_ODR_ODR3
#define lcd_6_dir        PC_DDR_DDR3
#define lcd_6_Push       PC_CR1_C13
#define lcd_6_fast       PC_CR2_C23
//-----------------------------//
#define lcd_7            PC_ODR_ODR4
#define lcd_7_dir        PC_DDR_DDR4
#define lcd_7_Push       PC_CR1_C14
#define lcd_7_fast       PC_CR2_C24
//-----------------------------//
#define conf            PC_IDR_IDR5
#define conf_dir        PC_DDR_DDR5
#define conf_Push       PC_CR1_C15
#define conf_fast       PC_CR2_C25
//-----------------------------//
#define baixo            PC_IDR_IDR6
#define baixo_dir        PC_DDR_DDR6
#define baixo_Push       PC_CR1_C16
#define baixo_fast       PC_CR2_C26
//-----------------------------//
#define cima            PC_IDR_IDR7
#define cima_dir        PC_DDR_DDR7
#define cima_Push       PC_CR1_C17
#define cima_fast       PC_CR2_C27
//-----------------------------//
#define volta            PA_IDR_IDR2
#define volta_dir        PA_DDR_DDR2
#define volta_Push       PA_CR1_C12
#define volta_fast       PA_CR2_C22
//-----------------------------//
#define L1            PD_ODR_ODR2
#define L1_dir        PD_DDR_DDR2
#define L1_Push       PD_CR1_C12
#define L1_fast       PD_CR2_C22
//-----------------------------//
#define L2            PD_ODR_ODR3
#define L2_dir        PD_DDR_DDR3
#define L2_Push       PD_CR1_C13
#define L2_fast       PD_CR2_C23
//-----------------------------//
#define BZ            PB_ODR_ODR2
#define BZ_dir        PB_DDR_DDR2
#define BZ_Push       PB_CR1_C12
#define BZ_fast       PB_CR2_C22
//-----------------------------//
#define sda       PB_ODR_ODR5
#define sda_in    PB_IDR_IDR5
#define sda_dir   PB_DDR_DDR5
#define sda_Push  PB_CR1_C15
#define sda_fast  PB_CR2_C25
//-----------------------------//
#define scl       PB_ODR_ODR4
#define scl_dir   PB_DDR_DDR4
#define scl_Push  PB_CR1_C14
#define scl_fast  PB_CR2_C24
//-----------------------------//
#define rx       PD_IDR_IDR6
#define rx_dir   PD_DDR_DDR6
#define rx_Push  PD_CR1_C16
#define rx_fast  PD_CR2_C26
//-----------------------------//
#define tx       PD_IDR_IDR6
#define tx_dir   PD_DDR_DDR6
#define tx_Push  PD_CR1_C16
#define tx_fast  PD_CR2_C26
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