/******************************************************************************************
* Copyright (C), 2015, Shanghai Eastsoft Microelectronics Co., Ltd

* 作  者:  ESM Application Team in
* 版  本:  V1.00
* 日  期:  2015/10/27

* 备  注:  
*          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
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

