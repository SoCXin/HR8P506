/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  e2prom.c
*作  者:  AE Team
*版  本:  V1.01
*日  期:  2021/06/01
*描  述:  E2PROM模块程序
*备  注:  本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "e2prom.h"
#include "uart.h"
#include "iic.h"

const uint8_t e2prom_addr = 0xA0;

/*********************************************************
函数名: void e2prom_init(void)
描  述: 初始化e2prom操作条件
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void e2prom_init(void)
{
    UARTInit();
    IICMasterInit();

    return;
}

/*********************************************************
函数名: uint8_t e2prom_byte_write(uint16_t addr, uint8_t u8data, rom_size_type size)
描  述: 向E2PROM中写入一个字节的数据
输入值: addr—E2PROM中的地址
        u8data-待写入数据
		size-E2ROM容量
输出值: 无
返回值: 成功返回0，失败返回1
**********************************************************/
uint8_t e2prom_byte_write(uint16_t addr, uint8_t u8data, rom_size_type size)
{
    uint8_t tx_buf[2];
    uint8_t rx_buf[3];
	uint8_t addr2send = e2prom_addr | (((addr & ((uint16_t)0x7FF >> (4 - size))) >> 8) << 1);
	
    tx_buf[0] = (uint8_t)(addr & ((uint16_t)0x7FF >> (4 - size)));
    tx_buf[1] = u8data;

    IICWriteBuf(addr2send, tx_buf, 2);
    Delay_1ms(10);
    IICReadBuf(addr2send, rx_buf, 3);

    if ((rx_buf[0] != 0x0) || (rx_buf[1] != 0x0) || (rx_buf[2] != 0x0))
        return 1;
    else
        return 0;
}

/*********************************************************
函数名: uint8_t e2prom_page_write(uint16_t addr, uint8_t *u8data, page_size_type psize, rom_size_type size)
描  述: 向E2PROM中写入一个字节的数据
输入值: addr—E2PROM中的地址
        u8data-待写入数据首地址
		psize-页大小
        size-E2ROM容量
输出值: 无
返回值: 成功返回0，失败返回1
**********************************************************/
uint8_t e2prom_page_write(uint16_t addr, uint8_t *u8data, page_size_type psize, rom_size_type size)
{
    uint8_t i;
    uint8_t tx_buf[20];
    uint8_t rx_buf[20];
	uint8_t valid_len;
    uint8_t addr2send = e2prom_addr | (((addr & ((uint16_t)0x7FF >> (4 - size))) >> 8) << 1);
	
	tx_buf[0] = (uint8_t)(addr & ((uint16_t)0x7FF >> (4 - size)));
	valid_len =  psize - addr % psize + 1;
	memcpy(tx_buf + 1, u8data, valid_len);
	IICWriteBuf(addr2send, tx_buf, valid_len + 1);
	Delay_1ms(10);
	
	IICReadBuf(addr2send, rx_buf, valid_len + 2);

    for (i = 0; i < valid_len + 2; i++)
    {
        if (rx_buf[i] != 0x0)
            break;
        else
            continue;
    }

    if (i != valid_len + 2)
        return 1;
    else
        return 0;
}

/*********************************************************
函数名: uint8_t e2prom_random_read(uint16_t addr, uint8_t *u8data, rom_size_type size)
描  述: 从指定地址的E2PROM中读取一字节的数据
输入值: addr—E2PROM中地址
        u8data-用来保存读取的数据的地址
		size-E2ROM容量
输出值: 无
返回值: 无
**********************************************************/
uint8_t e2prom_random_read(uint16_t addr, uint8_t *u8data, rom_size_type size)
{
	uint32_t time_count = 0x0U;
    uint8_t addr2send = e2prom_addr | (((addr & ((uint16_t)0x7FF >> (4 - size))) >> 8) << 1);
	uint8_t targetaddr = (uint8_t)(addr & ((uint16_t)0x7FF >> (4 - size)));

    /* dummy write */
    IIC_ClearITPendingBit(I2C0, IIC_CLR_NA);
    IIC_SendAddress(I2C0, addr2send, IIC_Mode_Write);
    IIC0_SRTrigger();
    while ((IIC_GetFlagStatus(I2C0, IIC_IF_SR) == RESET) && (++time_count < 0xFFF));
    IIC_ClearITPendingBit(I2C0, IIC_CLR_SR);

	time_count = 0x0U;
    while ((IIC_GetTBStatus(I2C0) == RESET) && (++time_count < 0xFFF));
    IIC_SendByte(I2C0, targetaddr);
	time_count = 0x0U;
    while ((IIC_GetFlagStatus(I2C0, IIC_IF_TB) == RESET) && (++time_count < 0xFFF));

    Delay_1ms(10);

    /* 读取 */
    u8data[0] = IICReadByte(addr2send);

    return 0;
}

/*********************************************************
函数名: uint8_t e2prom_sequential_read(uint16_t addr, uint8_t *u8data, uint8_t len, rom_size_type size)
描  述: 从指定地址的E2PROM中读取一字节的数据
输入值: addr—E2PROM中地址
        page_n-页码
        u8data-用来保存读取的数据的地址
        len-待读取数据字节数
		size-E2ROM容量
输出值: 无
返回值: 无
**********************************************************/
uint8_t e2prom_sequential_read(uint16_t addr, uint8_t *u8data, uint8_t len, rom_size_type size)
{
	uint32_t time_count = 0x0U;
    uint8_t addr2send = e2prom_addr | (((addr & ((uint16_t)0x7FF >> (4 - size))) >> 8) << 1);
	uint8_t targetaddr = (uint8_t)(addr & ((uint16_t)0x7FF >> (4 - size)));
	
    /* initiate read operation */
    IIC_ClearITPendingBit(I2C0, IIC_CLR_NA);
    IIC_SendAddress(I2C0, addr2send, IIC_Mode_Write);
    IIC0_SRTrigger();
    while ((IIC_GetFlagStatus(I2C0, IIC_IF_SR) == RESET) && (++time_count < 0xFFF));
    IIC_ClearITPendingBit(I2C0, IIC_CLR_SR);
	
	time_count = 0x0U;
    while ((IIC_GetTBStatus(I2C0) == RESET) && (++time_count < 0xFFF));
    IIC_SendByte(I2C0, targetaddr);

    IICReadBuf(addr2send, u8data, len);

    return 0;
}
