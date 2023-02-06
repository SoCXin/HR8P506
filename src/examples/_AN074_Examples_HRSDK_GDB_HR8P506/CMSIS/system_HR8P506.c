/******************************************************************************************
* Copyright (C), 2015, Shanghai Eastsoft Microelectronics Co., Ltd

* ��  ��:  ESM Application Team in
* ��  ��:  V1.00
* ��  ��:  2015/10/27

* ��  ע:  
*          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
*******************************************************************************************/

#include "system_HR8P506.h"
#include "HR8P506.h"
#include "lib_scu.h"
#include "lib_gpio.h"

const uint32_t SystemCoreClock = 32000000;

void SystemInit(void)
{
	SCU_SysClkSelect(SCU_CLK_HRC);
}

