/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  7816.c
*作  者:  yuzr
*版  本:  V1.00
*日  期:  2017/10/11
*描  述:  7816主机模块程序
*备  注:  
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "7816.h"

uint8_t SendByte[SendByte_Size];

/*********************************************************
函数名: User_7816Init
描  述: 7816主机初始化函子程序
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void User_7816Init(void)
{
    U7816_InitStruType x;
    GPIO_InitSettingType y;

    /*  7816io口初始化 PB5--E0CK0 PB4--E0IO0 */
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

    /* 7816配置*/
    EUART_ModeConfig(EUART_Mode_U7816);       //配置为7816模式
    x.U7816_ClockSet = EUART_Clock_1;         //BCS为1，波特率时钟分频PCLK
    x.U7816_BaudRate = 10752;                 //波特率
    x.U7816_ECK0 = Enable;                    //使能ECK0端口
    x.U7816_ECK1 = Disable;                   //不使能ECK1端口
    x.U7816_EIOCh = U7816_CHS_EIO0;           //选择E0IO0端口
    x.U7816_EIODir = U7816_EIODir_Out;        //初始化时，端口设置为输出
    x.U7816_DataForm = U7816_DataForm_Normal; //正极性
    x.U7816_DataVerify = U7816_Verify_Even;   //偶校验
    x.U7816_AutoRetryRx = Enable;             //自动重收使能
    x.U7816_AutoRetryTx = Enable;             //自动重发使能
    x.U7816_NACK_Width = U7816_NACKWidth_1ETU;//NACK信号宽度
    x.U7816_RetryTimes = U7816_RetryTime_3;   //重发三次
    x.U7816_CLKS = U7816_PCLK_4;              //Fosc/4
    x.U7816_ETUTime = 0;                      //2个ETU保护时间
    U7816_Init(&x);                           //7816初始化

    ESAM_RST_H;
}

/***********************************************************************
函数名: Get_7816_Char
描  述: ESAM接收一个字节数据函数
输入值: 无
输出值: uint8_t *Data
返回值: 成功：SUCCESS，失败：ERROR
************************************************************************/
uint8_t Get_7816_Char(uint8_t *Data)
{
    uint16_t  temp16;

    EUART_EIODirection(U7816_EIODir_In);          //接收数据

    for (temp16 = 0x00; temp16 < 20000; temp16++) //循环等待接收成功
    {
        if (SET == EUART_GetFlagStatus(EUART_FLAG_RB)) //接收缓冲器满中断
        {
            break;
        }
    }

    if ((temp16 == 20000) || (EUART0->RB01.PE0 == 1)) //超时或者校验错误
    {
        return ERROR;
    }
    else
    {
        *Data = EUART_RecByte();                     //取数据
        return SUCCESS;
    }
}
/***********************************************************************
函数名：Snd_7816_Byte
描  述：ESAM 发送一个byte数据函数
输入值：uint8_t Data
输出值：无
返回值：SUCCESS or  ERROR
************************************************************************/
uint8_t  Snd_7816_Byte(uint8_t Data)
{
    uint16_t  temp16;

    EUART_EIODirection(U7816_EIODir_Out);
    EUART_SendByte(Data);
    EUART0->IF.TCIF = 1;                           //发送完成标志软件清0

    for (temp16 = 0x00; temp16 < 20000; temp16++)  //等待发送完成
    {
        if (EUART0->IF.TCIF == 1)
        {
            break;
        }
    }

    if ((temp16 == 20000) || (EUART0->CON2.RNACK)) //超时或NACK返回失败
        return ERROR;
    else
        return SUCCESS;
}
/***********************************************************************
函数名：Instruction_Test
描  述：向ESAM发送00 a4 00 00 02 3f 00数据，接收到61xx或者9000则表示成功
输入值：无
输出值：无
返回值：SUCCESS or  ERROR
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

    for (i = 0 ; i < 5; i++) //向ESAM发送五个字节命令头
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
            for (; i < 7;)             //发送剩余字节
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
函数名：Random_Test
描  述：向ESAM发送00 84 00 00 08,接收随机数
输入值：无
输出值：uint8_t *data随机数(8字节)
返回值：SUCCESS or  ERROR
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

    for (i = 0 ; i < 5; i++)               //向ESAM发送五个字节命令头
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

        if (RecByte == SendByte[1])   //随机数数据，包括状态字节
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

            if ((data[8] == 0x90) && (data[9] == 0x00)) //判断ESAM是否正确接收命令
                return SUCCESS;

            return ERROR;
        }
    }
}
/***********************************************************************
函数名: ResetRec
描  述: ESAM复位,判断是否应答，并且读取应答数据
输入值: 无
输出值: 所读取的数据RxBuf
返回值: 成功：SUCCESS，失败：ERROR
************************************************************************/
uint8_t ResetRec(uint8_t *RxBuf)
{
    uint8_t result, temp_ATR;
    uint8_t n;

    ESAM_RST_L;                 // RST引脚拉低
    DLY_X100us(2);              //Tb>=400/f
    ESAM_RST_H;                 //RST引脚拉高，等待复位应答

    for (n = 0; n < 13; n++)        //接收十三个复位应答数据
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
函数名: DLY_X100us
描  述: 简单延时函数
输入值: uint16_t Count_x100us
输出值: 无
返回值: 无
************************************************************************/
void DLY_X100us(uint16_t Count_x100us)           //100us
{
    uint16_t i, j;

    for (i = Count_x100us; i > 0; i--)
        for (j = 255; j > 0; j--)
        { ; }
}

