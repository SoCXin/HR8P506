/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  e2prom.h
*作  者:  AE Team
*版  本:  V1.01
*日  期:  2021/06/01
*描  述:  E2PROM模块程序头文件
*备  注:  本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#ifndef __E2PROM_H__
#define __E2PROM_H__

#include "lib_config.h"
#include "uart.h"
#include "systick.h"

typedef enum
{
    page_size_8  = 8,
    page_size_16 = 16
} page_size_type;

typedef enum
{
    rom_size_1k = 0,
	rom_size_2k = 1,
    rom_size_4k = 2,
	rom_size_8k = 3,
	rom_size_16k = 4
} rom_size_type;

void e2prom_init(void);
uint8_t e2prom_byte_write(uint16_t addr, uint8_t u8data, rom_size_type size);
uint8_t e2prom_page_write(uint16_t addr, uint8_t *u8data, page_size_type psize, rom_size_type size);
uint8_t e2prom_random_read(uint16_t addr, uint8_t *u8data, rom_size_type size);
uint8_t e2prom_sequential_read(uint16_t addr, uint8_t *u8data, uint8_t len, rom_size_type size);

#endif
