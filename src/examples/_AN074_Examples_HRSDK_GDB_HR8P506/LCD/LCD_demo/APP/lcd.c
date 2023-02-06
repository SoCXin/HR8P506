/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  lcd.c
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/29
*��  ��:  LCDģ�����
*��  ע:  
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "lcd.h"

const uint16_t LCD7Code[] =
{
    0x0B0D,
    0x0009,
    0x0907,
    0x010F,
    0x020B,
    0x030E,
    0x0B0E,
    0x0109,
    0x0B0F,
    0x030F
};

/***************************************************************
��������LCDInit(void)
��  ����LCD GPIO�������Լ���ؼĴ�������
����ֵ����
���ֵ����
����ֵ����
***************************************************************/
void LCDInit(void)
{
    GPIO_InitSettingType x;
    LCD_InitStruType y;

    x.Signal = GPIO_Pin_Signal_Analog;
    x.Dir = GPIO_Direction_Output;
    x.Func = GPIO_Reuse_Func0;
    x.ODE = GPIO_ODE_Output_Disable;
    x.DS = GPIO_DS_Output_Normal;
    x.PUE = GPIO_PUE_Input_Disable;
    x.PDE = GPIO_PDE_Input_Disable;

    GPIO_Init(GPIO_Pin_A10, &x);
    GPIO_Init(GPIO_Pin_A11, &x);
    GPIO_Init(GPIO_Pin_A12, &x);
    GPIO_Init(GPIO_Pin_A13, &x);
    GPIO_Init(GPIO_Pin_A14, &x);
    GPIO_Init(GPIO_Pin_A15, &x);
    GPIO_Init(GPIO_Pin_A16, &x);
    GPIO_Init(GPIO_Pin_A17, &x);
    GPIO_Init(GPIO_Pin_A18, &x);
    GPIO_Init(GPIO_Pin_A19, &x);
    GPIO_Init(GPIO_Pin_A20, &x);
    GPIO_Init(GPIO_Pin_A21, &x);

    y.LCD_COMS = LCD_COMS_4;
    y.LCD_SEG = 0x000000FF;
    y.LCD_VLCD = LCD_VLCD_INSIDE;
    y.LCD_WFS = LCD_WFS_A;
    y.LCD_CLK = LCD_CLK_LRC;
    y.LCD_PRS = 10;
    y.LCD_BVS = LCD_BVS_30_30;
    y.LCD_BIAS = LCD_BIAS_1_3;
    y.LCD_RT = LCD_RT_1_64;
    y.LCD_RS = LCD_RS_60K_900K;
    y.LCD_TON = 0;
    y.LCD_TOFF = 0 ;
    y.LCD_FLIK = LCD_FLIK_NO;
    LCD_Init(&y);
}

/***************************************************************
������: LCDDisplayData(uint8_t high, uint8_t low,uint8_t colon)
��  ��: LED GPIO������
����ֵ: high Сʱ/����
                low ����/��
                colon �м�ð����ʾ���
���ֵ: ��
����ֵ: �ɹ�����1
                ʧ�ܷ���-1
***************************************************************/
int32_t LCDDisplayData(uint8_t high, uint8_t low, uint8_t colon)
{
    uint8_t ten, bit;

    if (high > 99 || low > 99 || colon > 1)
        return -1;

    ten = high / 10;
    bit = high % 10;

    LCD_PixelWriteHalfWord(LCD_Pixel_LCDD1, LCD_HalfWord_1, LCD7Code[ten]);
    LCD_PixelWriteHalfWord(LCD_Pixel_LCDD1, LCD_HalfWord_0, LCD7Code[bit]);

    ten = low / 10;
    bit = low % 10;

    if (colon == 1)
        LCD_PixelWriteHalfWord(LCD_Pixel_LCDD0, LCD_HalfWord_1, LCD7Code[ten] | 0x0400);
    else
        LCD_PixelWriteHalfWord(LCD_Pixel_LCDD0, LCD_HalfWord_1, LCD7Code[ten] & 0x0b0f);

    LCD_PixelWriteHalfWord(LCD_Pixel_LCDD0, LCD_HalfWord_0, LCD7Code[bit]);

    return 1;
}
