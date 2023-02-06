/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  buzzer.c
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/29
*��  ��:  ������ģ��API
*��  ע:  
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "buzzer.h"

uint16_t Old_Frequency = 10000;     // �ɵ�PWMʹ��ֵ
uint16_t Cur_Frequency = 10000;     // ��ǰPWMʹ��ֵ

/* ����Ƶ�ʱ����ڣ� */
const uint16_t BuzzerTab[] =
{
    00,     //Null
    748, //3816,//�������ף�
    807, //3540,
    940, //3039,
    997, //2865,
    1120, //2551,
    1257, //2272,
    1411, //2024,
    00,     //Null
    00,     //Null
    00,     //Null
    1494, //1912,//�������ף�
    1651, //1730,
    1883, //1517,
    1995, //1432,
    2239, //1276,
    2515, //1136,
    2823, //1012,
    00,     //Null
    00,     //Null
    00,     //Null
    2988, //956, //�������ף�
    3357, //851,
    3769, //758,
    3996, //715,
    4485, //637,
    5030, //568,
    5646, //506,
    00,     //Null
    00,     //Null
    00,     //Null
    3715, //769, //����һ�����ף�
    4177, //684,
    4645, //615,
    4951, //577,
    5569, //513,
    6197, //461,
    6968, //410,
    7440, //384,
};

/*********************************************************
������: void Buzzer_On(void)
��  ��: ��������������
����ֵ: ��
���ֵ: ��
����ֵ: ��
**********************************************************/
void Buzzer_On(void)
{
    GPIO_WriteBit(GPIO_Pin_B8, 1);
}

/*********************************************************
������: void Buzzer_Off(void)
��  ��: �رշ���������
����ֵ: ��
���ֵ: ��
����ֵ: ��
**********************************************************/
void Buzzer_Off(void)
{
    GPIO_WriteBit(GPIO_Pin_B8, 0);
}

/*********************************************************
������: void Buzzer_Init(void)
��  ��: ��������ʼ��
����ֵ: ��
���ֵ: ��
����ֵ: ��
**********************************************************/
void Buzzer_Init(void)
{
    T16Nx_BaseInitStruType x;
    GPIO_InitSettingType y;
    T16Nx_PWMInitStruType z;

    /* ��ʼ��T16Nx��ʱ��*/
    x.T16Nx_ClkS = T16Nx_ClkS_PCLK;             //�ⲿʱ��PCLK
    x.T16Nx_SYNC = Disable;
    x.T16Nx_EDGE = T16Nx_EDGE_Rise;
    x.T16Nx_Mode = T16Nx_Mode_PWM;              //PWM����
    x.T16Nx_PREMAT = 1;                         //Ԥ��Ƶ��Ϊ1:1
    T16Nx_BaseInit(T16N1, &x);                  //��ʼ����ʱ��T16N1

    /*����T16N0ͨ��01���*/
    z.T16Nx_MOE0 = Enable;                      //ͨ��0�������
    z.T16Nx_MOE1 = Disable;                     //ͨ��1�������
    z.T16Nx_POL0 = POSITIVE;                    //���������
    z.T16Nx_POL1 = POSITIVE;                    //���������
    z.T16Nx_PWMMODE = T16Nx_PWMMode_INDEP;      //����ģʽ���
    z.PWMDZE = Disable;                         //�رջ���ģʽ��������
    T16Nx_PMWOutInit(T16N1, &z);

    T16Nx_MAT0ITConfig(T16N1, T16Nx_Clr_Int);   //CNT0ƥ�䵽MAT1�������¼���
    T16Nx_MAT0Out0Config(T16N1, T16Nx_Out_Switch); //CNT0ƥ�䵽MAT0�˿�0ȡ��
    T16Nx_SetCNT0(T16N1, 0);                    //����T16N3��ʼֵΪ0
    T16Nx_SetMAT0(T16N1, 10000);                //����T16N3MAT0ֵΪ10000
		
    /* ��ʼ���������������� */
    y.Signal = GPIO_Pin_Signal_Digital;
    y.Dir = GPIO_Direction_Output;
    y.Func = GPIO_Reuse_Func0;
    y.ODE = GPIO_ODE_Output_Disable;
    y.DS = GPIO_DS_Output_Normal;
    y.PUE = GPIO_PUE_Input_Disable;
    y.PDE = GPIO_PDE_Input_Disable;
    GPIO_Init(GPIO_Pin_B8, &y);
    Buzzer_Off();

    /* ��ʼ���������������� */
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
������: void Buzzer_ChangeFrequency(uint16_t Frequency)
��  ��: �ı������������Ƶ��
����ֵ: Frequency: �µ�Ƶ��ֵ
���ֵ: ��
����ֵ: ��
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
������: void PlayMusic(const uint8_t *sheet)
��  ��: ʹ�÷�������������
����ֵ: sheet: �������ݱ�
���ֵ: ��
����ֵ: ��
**********************************************************/
void PlayMusic(const uint8_t *sheet)
{
    uint16_t tone, length;

    while (1)
    {
        if (*sheet == 0xFF)         //������
        {
            return;
        }
        else if (*sheet == 0)       //������β����
        {
            Buzzer_Off();           //BUZ1�ر�
            sheet++;
            length = *sheet;        //��ȡʱ��
            Delay10ms(length);      //��ʱ����λ10ms
            sheet++;
        }
        else                        //��������
        {
            Buzzer_On();            //BUZ1����
            tone = *sheet;
            Buzzer_ChangeFrequency(BuzzerTab[tone]);    //���PWMƵ�ʣ�ռ�ձ�50%
            sheet++;
            length = *sheet;    //��ȡʱ��
            Delay10ms(length);  //��ʱ����λ10ms
            sheet++;
        }
    }
}

/*********************************************************
������: void PlayTone(void)
��  ��: ʹ�÷�����������������
����ֵ: ��
���ֵ: ��
����ֵ: ��
**********************************************************/
void PlayTone(void)
{
    uint8_t i;

    Buzzer_On();                                //BUZ1����

    for (i = 1; i <= 7; i++)
    {
        Buzzer_ChangeFrequency(BuzzerTab[i]);
        Delay10ms(100);
    }

    Buzzer_Off();                               //BUZ1�ر�
    Delay10ms(50);

    Buzzer_On();                                //BUZ1����

    for (i = 11; i <= 17; i++)
    {
        Buzzer_ChangeFrequency(BuzzerTab[i]);
        Delay10ms(100);
    }

    Buzzer_Off();                               //BUZ1�ر�
    Delay10ms(50);

    Buzzer_On();                                //BUZ1����

    for (i = 21; i <= 27; i++)
    {
        Buzzer_ChangeFrequency(BuzzerTab[i]);
        Delay10ms(100);
    }

    Buzzer_Off();                               //BUZ1�ر�
    Delay10ms(50);
}



