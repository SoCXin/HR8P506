/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.01
*日  期:  2017/07/13
*描  述:  步进电机演示主程序
          步进电机型号：28BYJ-48，驱动方式为4相8拍
          K5按键切换电机运行状态，正转-停止-反转-停止（需要将核心板的跳线帽插短接ZERO）
*备  注:  
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"

const uint8_t MotorClockWiseRotation[8] = {0x09,0x01,0x03,0x02,0x06,0x04,0x0c,0x08};    // 步进电机正转表
const uint8_t MotorNotClockWiseRotation[8] = {0x08,0x0c,0x04,0x06,0x02,0x03,0x01,0x09}; // 步进电机反转表

int main(void)
{
    uint8_t mode;
    uint8_t step;

    SystemInit();
    DeviceClockAllEnable();

    User_SysTickInit();
    MotorInit();
    KeyInit();

    mode = 0;
    step = 0;

    while (1)
    {
        /* 控制电机旋转 */
        switch (mode)
        {
        case 0:                                         //正转
            MotorWrite(MotorClockWiseRotation[step]);
            step++;
            if (step >= 8)
                step = 0;
            Delay_100us(11);
            break;
        case 1:                                         //停止
            break;
        case 2:                                         //反转
            MotorWrite(MotorClockWiseRotation[step]);
            if (step > 0)
                step--;
            else
                step = 7;
            Delay_100us(11);
            break;
        case 3:                                         //停止
            break;
        default:
            break;
        }

        /* 读取按键信息 */
        if (5 == KeyGetValue())                         //判断按键是否是K5
        {
            if (mode == 0)
            {
                if (step == 0)
                    step = 6;
                else if (step == 1)
                    step = 7;
                else
                    step -= 2;
            }
            else if (mode == 2)
            {
                if (step == 7)
                    step = 1;
                else if (step == 6)
                    step = 0;
                else
                    step += 2;
            }

            mode = (mode + 1) % 4;
        }
    }
}
