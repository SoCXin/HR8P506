/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/29
*��  ��:  XTAL����
*��  ע:  
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "main.h"

//ע��ʹ��ǰʹ��JlinkBurner�޸�������CFG_OSC_PIN��Ĭ��ʹ��PB8��PB9��8M���񼴿ɣ�
//ע���˴�������ҪPB8��PB9����8M���񣬲�Ҫʹ��ĸ�壨ĸ��������·��Ծ������Ӱ�죩��ֻ��Ҫʹ���Ӱ弴��

int main(void)
{
    SystemInit();
    SCU_OpenXTAL();
    SCU_SysClkSelect(SCU_CLK_XTAL);
    SystemCoreClock = 8000000;          //����������ڴ˴��޸ļ���
    DeviceClockAllEnable();

    User_SysTickInit();
    LightInit();

    while (1)
    {
        GPIO_WriteBit(GPIO_Pin_A6, 1);
        Delay_100us(2000);
        GPIO_WriteBit(GPIO_Pin_A6, 0);
        Delay_100us(2000);
    }
}
