/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.01
*日  期:  2017/06/29
*描  述:  蜂鸣器演示主程序
         （1）单击K4：演奏《两只老虎》
         （2）单击K3：演奏《新年好》
         （3）单击K2：演奏《粉刷匠》
         （4）单击K1：演奏《拔萝卜》
         （5）单击K5：演奏音符音阶（需要将核心板的跳线帽插短接ZERO）
*备  注:  
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"

int main(void)
{
    uint32_t key;

    SystemInit();
    DeviceClockAllEnable();

    User_SysTickInit();
    Buzzer_Init();
    KeyInit();

    while (1)
    {
        key = KeyGetValue();        /* 获取按键值 */

        switch (key)                /* 根据按键值，播放对应的音乐 */
        {
            case 5:
                PlayTone();
                break;

            case 4:
                PlayMusic(Music4);
                break;

            case 3:
                PlayMusic(Music3);
                break;

            case 2:
                PlayMusic(Music2);
                break;

            case 1:
                PlayMusic(Music1);
                break;

            default:
                break;
        }

        Delay10ms(2);               /* 播放音乐后，延时一会儿 */
    }
}
