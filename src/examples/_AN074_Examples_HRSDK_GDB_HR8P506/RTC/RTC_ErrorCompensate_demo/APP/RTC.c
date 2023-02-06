/*********************************************************
 *Copyright (C), 2015, Shanghai Eastsoft Microelectronics Co., Ltd.
 *文件名:  RTC.c
 *作  者:  yuzr
 *版  本:  V1.00
 *日  期:  2017/10/23
 *描  述:  用户RTC模块程序
 *备  注:  
 本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
 **********************************************************/

#include "RTC.h"

/***************************************************************
  函数名：GPIO_RTC0_Init
  描  述：RTC0引脚初始化，初始化RTC，使能RTC0引脚输出
  输入值：无
  输出值：无
  返回值：无
***************************************************************/
void MyRTC_Init(void)
{
    GPIO_InitSettingType x;

    x.Signal = GPIO_Pin_Signal_Digital;
    x.Dir = GPIO_Direction_Output;
    x.Func = GPIO_Reuse_Func2;
    x.ODE = GPIO_ODE_Output_Disable;
    x.DS = GPIO_DS_Output_Strong;
    x.PDE = GPIO_PDE_Input_Disable;
    x.PUE = GPIO_PUE_Input_Disable;
    GPIO_Init(RTC0_PIN, &x);

    RTC->WP.Word = 0X55AAAA55;     //关闭RTC写保护
    RTC->CON.PON = 0X0;            //时钟复位正常工作
    RTC->CON.CLKS = 0X0;           //选择32.768为时钟源
    RTC->CAL.CLKC = 0x1;           //使能RTC0时钟输出
    RTC->CAL.COCR = 0X3;           //调教之前测试频率设置0x3,
    //调教之后测试则选择0x4
    RTC->WP.Word = 0X00000000;     //写保护
}
/***************************************************************
  函数名：MY_RTC_Init
  描  述：误差补偿计算比如时钟每天快x秒，那么每天RTC的误差
    就是(x/(24小时*60分钟*60秒))*10^6  = x*11.574 ppm
    RTC->CAL.CALF写补偿值为：
    如果CALF<7>=0，则递增调校，增量为((CALF<6:0>) - 1) x 2；
    比如增量为1，补偿为(1/32768/20)*10^6 = 1.525ppm，需要的增量为
    （x*11.574）/1.525，即((CALF<6:0>) - 1) x 2 = （x*11.574）/1.525。
    如果CALF<7>=1，则递减调校，减量为((~CALF<6:0>) + 1) x 2。
    比如增量为1，补偿为(1/32768/20)*10^6 = 1.525ppm，需要的增量为
    （x*11.574）/1.525，即((~CALF<6:0>) + 1) x 2 =（x*11.574）/1.525。
  输入值：uint8_t error
  输出值：无
  返回值：无
***************************************************************/
void Error_Offset(uint8_t error)
{
    RTC->WP.Word = 0X55AAAA55;     //关闭RTC写保护
    RTC->CON.PON = 0X0;            //清除PON，RTC正常工作
    RTC->CON.CLKS = 0X0;           //选择32.768时钟作为时钟源
    RTC->CAL.COCR = 0X4;          //校正后1Hz时钟输出, 必须选择这个补偿才会生效
    RTC->CAL.DEV = 0X0;           //每20S补偿一次
    RTC->CAL.CALF = error;     //填写补偿值
    RTC->WP.Word = 0X00000000;     //写保护
}
