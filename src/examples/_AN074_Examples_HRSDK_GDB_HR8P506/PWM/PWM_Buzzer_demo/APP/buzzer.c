/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  buzzer.c
*作  者:  Liut
*版  本:  V1.01
*日  期:  2017/06/29
*描  述:  蜂鸣器模块API
*备  注:  
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "buzzer.h"

uint16_t Old_Frequency = 10000;     // 旧的PWM使用值
uint16_t Cur_Frequency = 10000;     // 当前PWM使用值

/* 音符频率表（周期） */
const uint16_t BuzzerTab[] =
{
    00,     //Null
    748, //3816,//（低音阶）
    807, //3540,
    940, //3039,
    997, //2865,
    1120, //2551,
    1257, //2272,
    1411, //2024,
    00,     //Null
    00,     //Null
    00,     //Null
    1494, //1912,//（中音阶）
    1651, //1730,
    1883, //1517,
    1995, //1432,
    2239, //1276,
    2515, //1136,
    2823, //1012,
    00,     //Null
    00,     //Null
    00,     //Null
    2988, //956, //（高音阶）
    3357, //851,
    3769, //758,
    3996, //715,
    4485, //637,
    5030, //568,
    5646, //506,
    00,     //Null
    00,     //Null
    00,     //Null
    3715, //769, //（另一套音阶）
    4177, //684,
    4645, //615,
    4951, //577,
    5569, //513,
    6197, //461,
    6968, //410,
    7440, //384,
};

/*********************************************************
函数名: void Buzzer_On(void)
描  述: 开启蜂鸣器发声
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void Buzzer_On(void)
{
    GPIO_WriteBit(GPIO_Pin_B8, 1);
}

/*********************************************************
函数名: void Buzzer_Off(void)
描  述: 关闭蜂鸣器发声
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void Buzzer_Off(void)
{
    GPIO_WriteBit(GPIO_Pin_B8, 0);
}

/*********************************************************
函数名: void Buzzer_Init(void)
描  述: 蜂鸣器初始化
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void Buzzer_Init(void)
{
    T16Nx_BaseInitStruType x;
    GPIO_InitSettingType y;
    T16Nx_PWMInitStruType z;

    /* 初始化T16Nx定时器*/
    x.T16Nx_ClkS = T16Nx_ClkS_PCLK;             //外部时钟PCLK
    x.T16Nx_SYNC = Disable;
    x.T16Nx_EDGE = T16Nx_EDGE_Rise;
    x.T16Nx_Mode = T16Nx_Mode_PWM;              //PWM调制
    x.T16Nx_PREMAT = 1;                         //预分频比为1:1
    T16Nx_BaseInit(T16N1, &x);                  //初始化定时器T16N1

    /*配置T16N0通道01输出*/
    z.T16Nx_MOE0 = Enable;                      //通道0输出开启
    z.T16Nx_MOE1 = Disable;                     //通道1输出开启
    z.T16Nx_POL0 = POSITIVE;                    //输出正极性
    z.T16Nx_POL1 = POSITIVE;                    //输出正极性
    z.T16Nx_PWMMODE = T16Nx_PWMMode_INDEP;      //独立模式输出
    z.PWMDZE = Disable;                         //关闭互补模式死区功能
    T16Nx_PMWOutInit(T16N1, &z);

    T16Nx_MAT0ITConfig(T16N1, T16Nx_Clr_Int);   //CNT0匹配到MAT1清零重新计数
    T16Nx_MAT0Out0Config(T16N1, T16Nx_Out_Switch); //CNT0匹配到MAT0端口0取反
    T16Nx_SetCNT0(T16N1, 0);                    //设置T16N3初始值为0
    T16Nx_SetMAT0(T16N1, 10000);                //设置T16N3MAT0值为10000
		
    /* 初始化蜂鸣器开关引脚 */
    y.Signal = GPIO_Pin_Signal_Digital;
    y.Dir = GPIO_Direction_Output;
    y.Func = GPIO_Reuse_Func0;
    y.ODE = GPIO_ODE_Output_Disable;
    y.DS = GPIO_DS_Output_Normal;
    y.PUE = GPIO_PUE_Input_Disable;
    y.PDE = GPIO_PDE_Input_Disable;
    GPIO_Init(GPIO_Pin_B8, &y);
    Buzzer_Off();

    /* 初始化蜂鸣器发音引脚 */
    y.Signal = GPIO_Pin_Signal_Digital;
    y.Dir = GPIO_Direction_Output;
    y.Func = GPIO_Reuse_Func1;
    y.ODE = GPIO_ODE_Output_Disable;
    y.DS = GPIO_DS_Output_Normal;
    y.PUE = GPIO_PUE_Input_Disable;
    y.PDE = GPIO_PDE_Input_Disable;
    GPIO_Init(GPIO_Pin_B13, &y);

    T16Nx_Enable(T16N1);
}

/*********************************************************
函数名: void Buzzer_ChangeFrequency(uint16_t Frequency)
描  述: 改变蜂鸣器发声的频率
输入值: Frequency: 新的频率值
输出值: 无
返回值: 无
**********************************************************/
void Buzzer_ChangeFrequency(uint16_t Frequency)
{
    if(Frequency == 0)
    {
      while(1);
    }
    else
    {
      Cur_Frequency = (SystemCoreClock / 2) / Frequency;
      T16N1->MAT0.MAT0 = Cur_Frequency;      
    }
}

/*********************************************************
函数名: void PlayMusic(const uint8_t *sheet)
描  述: 使用蜂鸣器播放音乐
输入值: sheet: 音乐数据表
输出值: 无
返回值: 无
**********************************************************/
void PlayMusic(const uint8_t *sheet)
{
    uint16_t tone, length;

    while (1)
    {
        if (*sheet == 0xFF)         //结束符
        {
            return;
        }
        else if (*sheet == 0)       //拖音（尾音）
        {
            Buzzer_Off();           //BUZ1关闭
            sheet++;
            length = *sheet;        //读取时长
            Delay10ms(length);      //延时，单位10ms
            sheet++;
        }
        else                        //音符数据
        {
            Buzzer_On();            //BUZ1开启
            tone = *sheet;
            Buzzer_ChangeFrequency(BuzzerTab[tone]);    //输出PWM频率，占空比50%
            sheet++;
            length = *sheet;    //读取时长
            Delay10ms(length);  //延时，单位10ms
            sheet++;
        }
    }
}

/*********************************************************
函数名: void PlayTone(void)
描  述: 使用蜂鸣器播放音符音阶
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void PlayTone(void)
{
    uint8_t i;

    Buzzer_On();                                //BUZ1开启

    for (i = 1; i <= 7; i++)
    {
        Buzzer_ChangeFrequency(BuzzerTab[i]);
        Delay10ms(100);
    }

    Buzzer_Off();                               //BUZ1关闭
    Delay10ms(50);

    Buzzer_On();                                //BUZ1开启

    for (i = 11; i <= 17; i++)
    {
        Buzzer_ChangeFrequency(BuzzerTab[i]);
        Delay10ms(100);
    }

    Buzzer_Off();                               //BUZ1关闭
    Delay10ms(50);

    Buzzer_On();                                //BUZ1开启

    for (i = 21; i <= 27; i++)
    {
        Buzzer_ChangeFrequency(BuzzerTab[i]);
        Delay10ms(100);
    }

    Buzzer_Off();                               //BUZ1关闭
    Delay10ms(50);
}



