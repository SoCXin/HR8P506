/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*�ļ���:  main.c
*��  ��:  yuzr
*��  ��:  V1.00
*��  ��:  2017/10/17
*��  ��:  7816��ʾʵ�飬��ʼ��ESAMģ����λESAM������ESAM��λӦ�����ݣ�
                    ��ESAMд����������ȷִ��������LED��
*��  ע:          PB04--IC_IO   PB05--IC_CLK  PB07--IC_RST   PA06--LED
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "main.h"



/*********************************************************
������: main
��  ��: ������
����ֵ: ��
���ֵ: ��
����ֵ: ��
**********************************************************/
int main(void)
{
    uint8_t ret = 0;
    uint8_t  IC_Ret_Buff[13];    //Ӧ�����ݻ��棬һ��13���ֽ�

    SystemInit();                //ϵͳ���ã�Ĭ������
    DeviceClockAllEnable();        //����ʱ������
    led_init();                  //led��ʼ����PA06
    User_7816Init();                 //7816��ʼ��
    LED_Dark;                    //Ϩ��LED1
    ResetRec(IC_Ret_Buff);      //��λ����ȡ��λ����
    ret = Instruction_Test();  //���Զ�д����

    if (ret == SUCCESS)
    {
        LED_Light;                 //LED1����
    }

    while (1)
    {

    }
}
/*********************************************************
������: led_init
��  ��: led��ʼ��
����ֵ: ��
���ֵ: ��
����ֵ: ��
**********************************************************/
void led_init(void)
{
    GPIO_InitSettingType x;
    x.Signal = GPIO_Pin_Signal_Digital;
    x.Dir = GPIO_Direction_Output;
    x.Func = GPIO_Reuse_Func0;
    x.ODE = GPIO_ODE_Output_Enable;
    x.DS = GPIO_DS_Output_Normal;
    x.PUE = GPIO_PUE_Input_Disable;
    x.PDE = GPIO_PDE_Input_Disable;
    GPIO_Init(LED_PIN, &x);  //LED1 -- PA06
}
