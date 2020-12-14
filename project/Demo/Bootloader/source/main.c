/*********************************************************
*Copyright (C), 2018, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.00
*日  期:  2018/07/04
*描  述:  Bootloader演示程序

          RX：PA22  TX：PA23  BootPin：PA24
          波特率：自适应  校验位：偶校验  停止位：1位
          演示方法请参考文档 AN082_应用笔记_ES8P系列MCU bootloader
*备  注:  本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "HR8P506.h"
#include "macro.h"
#include "typedef.h"
#include "lib_flashiap.h"

extern isp_data_t g_isp_data;
extern uint32_t  g_boot_timer;
extern uint8_t   g_boot;

void uart_init(UART_TypeDef *uartx);
void uart_proc_fsm(void);
void fsm_init(void);
void JumpToApp(uint32_t addr);
/***************************************************************
函数名：systick_init
描  述: Systick初始化
输入值：无
输出值：无
返回值：无
***************************************************************/
void systick_init(void)
{
    SysTick->CTRL = 0x07;
    SysTick->LOAD = 16000;  //系统时钟24M，1ms产生一次中断
    SysTick->VAL = 0;
}

/***************************************************************
函数名：gpio_init
描  述: GPIO初始化
输入值：无
输出值：无
返回值：无
***************************************************************/
void gpio_init(void)
{
    SCU->PROT.Word = 0X55AA6996;
    SCU->PCLKEN.GPIO_EN = 1;
    SCU->PCLKEN.UART0_EN = 1;

    //BootPIN:PA24
    GPIO->PADIR.DIR_24 = 1; //输出关闭
    GPIO->PAINEB.INEB_24 = 0; //输入打开
    GPIO->PAPDE.PDE_24 = 1; //弱下拉打开
    GPIO->PAFUNC3.PA24 = 0;   //GPIO

    //RX:PA22
    GPIO->PADIR.DIR_22 = 1; //输出关闭
    GPIO->PAINEB.INEB_22 = 0; //输入打开
    GPIO->PAFUNC2.PA22 = 1;   //FUNC1 RXD

    //TX:PA23
    GPIO->PADIR.DIR_23 = 0; //输出打开
    GPIO->PAINEB.INEB_23 = 1; //输入关闭
    GPIO->PAFUNC2.PA23 = 1;   //FUNC1 TXD


}

int SystemInit(void)
{

    return 0;
}
/***************************************************************
函数名：main
描  述: boot 主函数
输入值：无
输出值：无
返回值：无
***************************************************************/
volatile uint32_t DATA;
int main(void)
{
    g_isp_data.syn = 0; //尚未完成启动
    gpio_init();
    uart_init(UART0);

    systick_init();
    fsm_init();  //状态机初始化

    NVIC_EnableIRQ(UART0_IRQn);
    WDT->LOCK.Word = 0x1ACCE551;

    while (1)
    {
        WDT->INTCLR.Word = 0xFFFFFFFF; //清狗

        if (g_isp_data.triger == 1)
        {
            __disable_irq();  //临界段代码保护

            while (g_isp_data.triger == 1)
            {
                uart_proc_fsm();  //isp命令状态机处理
            }

            __enable_irq();
        }

        if (g_boot == 1) //需要引导程序到flash
        {
            JumpToApp(APP_ADDR);
        }
    }
}
