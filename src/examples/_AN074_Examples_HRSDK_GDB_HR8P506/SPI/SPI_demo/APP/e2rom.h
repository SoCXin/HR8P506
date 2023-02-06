/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  flash.h
*作  者:  AE Team
*版  本:  V1.01
*日  期:  2021/05/28
*描  述:
*备  注:  本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#ifndef __FLASH_H__
#define __FLASH_H__

#include "lib_config.h"
#include "systick.h"


/* 函数声明 */
void E2rom_init(void);
void E2romReadData(uint8_t addr, uint8_t *buf);
void E2romWriteData(uint8_t addr, uint8_t buf);
void E2romEraseAll(void);

#endif
