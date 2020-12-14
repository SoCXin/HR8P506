/*********************************************************
*Copyright (C), 2018, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.00
*日  期:  2018/07/04
*描  述:  APP_Systick演示程序
          GPIO：PA6
          演示方法请参考文档 AN082_应用笔记_ES8P系列MCU bootloader
*备  注:  本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "HR8P506.h"


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
    SysTick->LOAD = 16000;  //系统时钟16M，1ms产生一次中断
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


    GPIO->PADIR.DIR_6 = 0; //输出打开
    GPIO->PAINEB.INEB_6 = 1; //输入关闭
    GPIO->PAFUNC0.PA6 = 0;   //GPIO

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

int main(void)
{
    gpio_init();
    systick_init();

    WDT->LOCK.Word = 0x1ACCE551;

    while (1)
    {
        WDT->INTCLR.Word = 0xFFFFFFFF; //清狗
    }
}
