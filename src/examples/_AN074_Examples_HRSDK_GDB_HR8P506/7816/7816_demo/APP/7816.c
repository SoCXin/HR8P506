/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  7816.c
*��  ��:  yuzr
*��  ��:  V1.00
*��  ��:  2017/10/11
*��  ��:  7816����ģ�����
*��  ע:  
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "7816.h"

uint8_t SendByte[SendByte_Size];

/*********************************************************
������: User_7816Init
��  ��: 7816������ʼ�����ӳ���
����ֵ: ��
���ֵ: ��
����ֵ: ��
**********************************************************/
void User_7816Init(void)
{
    U7816_InitStruType x;
    GPIO_InitSettingType y;

    /*  7816io�ڳ�ʼ�� PB5--E0CK0 PB4--E0IO0 */
    y.Func = GPIO_Reuse_Func1;
    y.Dir = GPIO_Direction_Output;
    y.DS = GPIO_DS_Output_Strong;
    y.ODE = GPIO_ODE_Output_Disable;
    y.PDE = GPIO_PDE_Input_Disable;
    y.PUE = GPIO_PUE_Input_Disable;
    y.Signal = GPIO_Pin_Signal_Digital;
    GPIO_Init(E0IO0_PIN, &y);
    GPIO_Init(E0CK0_PIN, &y);
    /* PB07-RST */
    y.Signal = GPIO_Pin_Signal_Digital;
    y.Dir = GPIO_Direction_Output;
    y.Func = GPIO_Reuse_Func0;
    y.ODE = GPIO_ODE_Output_Disable;
    y.DS = GPIO_DS_Output_Strong;
    y.PUE = GPIO_PUE_Input_Disable;
    y.PDE = GPIO_PDE_Input_Disable;
    GPIO_Init(E0RST_PIN, &y);               //RST -- PB07

    /* 7816����*/
    EUART_ModeConfig(EUART_Mode_U7816);       //����Ϊ7816ģʽ
    x.U7816_ClockSet = EUART_Clock_1;         //BCSΪ1��������ʱ�ӷ�ƵPCLK
    x.U7816_BaudRate = 10752;                 //������
    x.U7816_ECK0 = Enable;                    //ʹ��ECK0�˿�
    x.U7816_ECK1 = Disable;                   //��ʹ��ECK1�˿�
    x.U7816_EIOCh = U7816_CHS_EIO0;           //ѡ��E0IO0�˿�
    x.U7816_EIODir = U7816_EIODir_Out;        //��ʼ��ʱ���˿�����Ϊ���
    x.U7816_DataForm = U7816_DataForm_Normal; //������
    x.U7816_DataVerify = U7816_Verify_Even;   //żУ��
    x.U7816_AutoRetryRx = Enable;             //�Զ�����ʹ��
    x.U7816_AutoRetryTx = Enable;             //�Զ��ط�ʹ��
    x.U7816_NACK_Width = U7816_NACKWidth_1ETU;//NACK�źſ��
    x.U7816_RetryTimes = U7816_RetryTime_3;   //�ط�����
    x.U7816_CLKS = U7816_PCLK_4;              //Fosc/4
    x.U7816_ETUTime = 0;                      //2��ETU����ʱ��
    U7816_Init(&x);                           //7816��ʼ��

    ESAM_RST_H;
}

/***********************************************************************
������: Get_7816_Char
��  ��: ESAM����һ���ֽ����ݺ���
����ֵ: ��
���ֵ: uint8_t *Data
����ֵ: �ɹ���SUCCESS��ʧ�ܣ�ERROR
************************************************************************/
uint8_t Get_7816_Char(uint8_t *Data)
{
    uint16_t  temp16;

    EUART_EIODirection(U7816_EIODir_In);          //��������

    for (temp16 = 0x00; temp16 < 20000; temp16++) //ѭ���ȴ����ճɹ�
    {
        if (SET == EUART_GetFlagStatus(EUART_FLAG_RB)) //���ջ��������ж�
        {
            break;
        }
    }

    if ((temp16 == 20000) || (EUART0->RB01.PE0 == 1)) //��ʱ����У�����
    {
        return ERROR;
    }
    else
    {
        *Data = EUART_RecByte();                     //ȡ����
        return SUCCESS;
    }
}
/***********************************************************************
��������Snd_7816_Byte
��  ����ESAM ����һ��byte���ݺ���
����ֵ��uint8_t Data
���ֵ����
����ֵ��SUCCESS or  ERROR
************************************************************************/
uint8_t  Snd_7816_Byte(uint8_t Data)
{
    uint16_t  temp16;

    EUART_EIODirection(U7816_EIODir_Out);
    EUART_SendByte(Data);
    EUART0->IF.TCIF = 1;                           //������ɱ�־�����0

    for (temp16 = 0x00; temp16 < 20000; temp16++)  //�ȴ��������
    {
        if (EUART0->IF.TCIF == 1)
        {
            break;
        }
    }

    if ((temp16 == 20000) || (EUART0->CON2.RNACK)) //��ʱ��NACK����ʧ��
        return ERROR;
    else
        return SUCCESS;
}
/***********************************************************************
��������Instruction_Test
��  ������ESAM����00 a4 00 00 02 3f 00���ݣ����յ�61xx����9000���ʾ�ɹ�
����ֵ����
���ֵ����
����ֵ��SUCCESS or  ERROR
************************************************************************/
uint8_t  Instruction_Test(void)
{
    uint8_t i, ret, RecByte, Temp_SW1, Temp_SW2;

    SendByte[0] = 0x00;
    SendByte[1] = 0xa4;
    SendByte[2] = 0x00;
    SendByte[3] = 0x00;
    SendByte[4] = 0x02;
    SendByte[5] = 0x3f;
    SendByte[6] = 0x00;
    DLY_X100us(15);

    for (i = 0 ; i < 5; i++) //��ESAM��������ֽ�����ͷ
    {
        ret = Snd_7816_Byte(SendByte[i]);

        if (SUCCESS != ret)
        {
            return ERROR;
        }
    }

    while (1)
    {
        ret = Get_7816_Char(&RecByte);

        if (ret != SUCCESS)
        {
            return ERROR;
        }

        if (RecByte == SendByte[1])
        {
            for (; i < 7;)             //����ʣ���ֽ�
            {
                ret = Snd_7816_Byte(SendByte[i++]);

                if (SUCCESS != ret)
                {
                    return ERROR;
                }
            }
        }
        else
        {
            Temp_SW1 = RecByte & 0xf0;

            if ((Temp_SW1 == 0x60) || (Temp_SW1 == 0x90))
            {
                ret = Get_7816_Char(&Temp_SW2);

                if (ret != SUCCESS)
                {
                    return ERROR;
                }

                if ((RecByte == 0x61) || (RecByte == 0x90))
                    return SUCCESS;

                return ERROR;
            }
        }
    }
}
/***********************************************************************
��������Random_Test
��  ������ESAM����00 84 00 00 08,���������
����ֵ����
���ֵ��uint8_t *data�����(8�ֽ�)
����ֵ��SUCCESS or  ERROR
************************************************************************/
uint8_t Random_Test(uint8_t *data)
{
    uint8_t i, ret, RecByte;

    SendByte[0] = 0x00;
    SendByte[1] = 0x84;
    SendByte[2] = 0x00;
    SendByte[3] = 0x00;
    SendByte[4] = 0x08;
    DLY_X100us(15);

    for (i = 0 ; i < 5; i++)               //��ESAM��������ֽ�����ͷ
    {
        ret = Snd_7816_Byte(SendByte[i]);

        if (SUCCESS != ret)
        {
            return ERROR;
        }
    }

    while (1)
    {
        ret = Get_7816_Char(&RecByte);

        if (ret != SUCCESS)
        {
            return ERROR;
        }

        if (RecByte == SendByte[1])   //��������ݣ�����״̬�ֽ�
        {
            for (i = 0; i < 10; i++)
            {
                ret = Get_7816_Char(&RecByte);

                if (ret != SUCCESS)
                {
                    return ERROR;
                }

                data[i] = RecByte;
            }

            if ((data[8] == 0x90) && (data[9] == 0x00)) //�ж�ESAM�Ƿ���ȷ��������
                return SUCCESS;

            return ERROR;
        }
    }
}
/***********************************************************************
������: ResetRec
��  ��: ESAM��λ,�ж��Ƿ�Ӧ�𣬲��Ҷ�ȡӦ������
����ֵ: ��
���ֵ: ����ȡ������RxBuf
����ֵ: �ɹ���SUCCESS��ʧ�ܣ�ERROR
************************************************************************/
uint8_t ResetRec(uint8_t *RxBuf)
{
    uint8_t result, temp_ATR;
    uint8_t n;

    ESAM_RST_L;                 // RST��������
    DLY_X100us(2);              //Tb>=400/f
    ESAM_RST_H;                 //RST�������ߣ��ȴ���λӦ��

    for (n = 0; n < 13; n++)        //����ʮ������λӦ������
    {
        result = Get_7816_Char(&temp_ATR);

        if (result != SUCCESS)
        {
            return ERROR;
        }

        RxBuf[n] = temp_ATR;
    }

    if ((RxBuf[0] != 0x3b) || (RxBuf[1] != 0x69))
    {
        return ERROR;
    }

    return SUCCESS;
}

/***********************************************************************
������: DLY_X100us
��  ��: ����ʱ����
����ֵ: uint16_t Count_x100us
���ֵ: ��
����ֵ: ��
************************************************************************/
void DLY_X100us(uint16_t Count_x100us)           //100us
{
    uint16_t i, j;

    for (i = Count_x100us; i > 0; i--)
        for (j = 255; j > 0; j--)
        { ; }
}

