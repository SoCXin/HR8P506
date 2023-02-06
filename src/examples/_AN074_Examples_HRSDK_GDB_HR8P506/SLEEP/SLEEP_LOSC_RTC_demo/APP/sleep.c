/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  sleep.c
*��  ��:
*��  ��:  V1.01
*��  ��:  2018/03/26
*��  ��:  ���ߺ���
*��  ע:  
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "sleep.h"

/***************************************************************
 ��������void sleep(void)
 ��  �������ߺ���
 ����ֵ����
 ���ֵ����
 ����ֵ����
***************************************************************/
void sleep(void)
{

    uint32_t i;
    GPIO_InitSettingType y;
    KINT_InitSettingType z;
    __disable_irq(); //�ر�IRQ���ж�
    WDT_Clear();  //�幷
    DeviceClockAllEnable();
    SCU_OpenXTAL();  //ʹ���ⲿ����
    GPIO->PAINEB.Word = 0XFFFFFFFF; //����ر�
    GPIO->PBINEB.Word = 0XFFFFFFFF;
    GPIO->PADIR.Word = 0X00000000;  //�����
    GPIO->PBDIR.Word = 0X00000000;
    GPIO->PADATA.Word = 0X00000040;  //PA6����߹ر�LED1
    GPIO->PBDATA.Word = 0X00000080;  //PB7����������

    y.Signal = GPIO_Pin_Signal_Digital;
    y.Func = GPIO_Reuse_Func0;
    y.Dir = GPIO_Direction_Input;
    y.ODE = GPIO_ODE_Output_Disable;
    y.DS = GPIO_DS_Output_Normal;
    y.PUE = GPIO_PUE_Input_Enable;
    y.PDE = GPIO_PDE_Input_Disable;
    GPIO_Init(GPIO_Pin_A22, &y);


    z.IE_Set = KINT_IE_Set_Enable;
    z.Trigger_Style = KINT_Trigger_Trailing_Edge;
    KINT_Init(GPIO_Pin_A22, &z);                     //��ʼ�������ж�

    SCU_RegUnLock();
    SCU_LVDVS_4V();    //LVD���ѵ�ѹ4V
    SCU_LVDIFS_Fall(); //LVD��ѹ���߼��
    SCU_LVDFLT_Enable();
    SCU_LVD_Enable();
    SCU->SCLKEN0.CLKFLT_BY = 0x55;//CLKFLT��·��CLKFLTΪϵͳʱ���˲���
    SCU->SCLKEN1.PLL_EN = 0;//PLL��Ƶ������ֹ
    SCU->SCLKEN0.SYSCLK_DIV = 0;// ϵͳʱ�Ӻ��Ƶ1:1
    SCU->WAKEUPTIME.MOSC_EN = 1; //��˯����ʱ���Զ��رս�ֹ
    SCU->WAKEUPTIME.WAKEUPTIME = 0x280; //����ʱ��  //����ʱ�䲻��С��40us
    SCU->WAKEUPTIME.CLKFLT_EN = 0;
    SCB_SystemLPConfig(SCB_LP_SleepDeep, Enable);  //���˯��ģʽ
    SCU_RegLock();

    RTC_Init(RTC_LOSC, RTC_HOUR24); //ʵʱʱ�ӳ�ʼ��
    RTC_WriteSecond(30);
    RTC_InterruptEnable(RTC_Interrupt_Source_Second);//ʹ��ʵʱʱ�ӵ����ж�


    WDT_RegUnLock();//WDT�ر�д����
    WDT_ITEnable(); //IEʹ��

    NVIC_EnableIRQ(RTC_IRQn);  //ʹ���뻽��Դ
    NVIC_EnableIRQ(LVD_IRQn);  //ʹ��LVD����Դ
    NVIC_EnableIRQ(WDT_IRQn);  //ʹ��WDT����Դ
    NVIC_EnableIRQ(KINT_IRQn); //ʹ�ܰ�������
    RTC->WP.WP = 0x55AAAA55;   //RTC�ر�д����


    while (1) //������ѭ��
    {
        SCU_RegUnLock();
        SCU->SCLKEN1.HRC_EN = 0; //HRC�ر�ϵͳʱ���Զ��л���LRC //ϵͳʱ�����ڲ���С��2us
        NVIC->ICPR[0] = 0XFFFFFFFF; //��NVIC�����ʶ
        __NOP();
        __NOP();
        __WFI(); //����
        __NOP();
        __NOP();
        SCU->SCLKEN1.HRC_EN = 1;
        SCU_RegLock();

        if (WDT_GetFlagStatus() != RESET)
        {
            WDT_Clear();  //�幷
        }

        if (RTC_GetFlagStatus(RTC_Interrupt_Source_Second) != RESET
                && RTC_GetITStatus(RTC_Interrupt_Source_Second) != RESET)  //�뻽��
        {
            RTC->IF.Word = 1U << 0; //�����жϱ�ʶ
            GPIO_ToggleBit(GPIO_Pin_A23);   //PA23��ת
        }

        if (SCU_GetLVDFlagStatus(SCU_LVDFlag_IF) != RESET) //LVD����
        {
            SCU_RegUnLock();
            SCU_LVDClearIFBit();
            SCU_RegLock();
            NVIC_SystemReset();   //��λ����
        }

        if (KINT_GetITFlag(GPIO_Pin_A22) != RESET)  //KINT����
        {
            KINT_ClearITFlag(GPIO_Pin_A22);      // ��������жϱ�־λ
            GPIO_ToggleBit(GPIO_Pin_A23);   //PA23��ת

            for (i = 0; i < 165350; i++);

            GPIO_ToggleBit(GPIO_Pin_A23);   //PA23��ת

            for (i = 0; i < 165350; i++);

            GPIO_ToggleBit(GPIO_Pin_A23);   //PA23��ת

            for (i = 0; i < 165350; i++);

            GPIO_ToggleBit(GPIO_Pin_A23);   //PA23��ת

            for (i = 0; i < 165350; i++);

            GPIO_ToggleBit(GPIO_Pin_A23);   //PA23��ת

            for (i = 0; i < 165350; i++);

            GPIO_ToggleBit(GPIO_Pin_A23);   //PA23��ת

            for (i = 0; i < 165350; i++);

            GPIO_ToggleBit(GPIO_Pin_A23);   //PA23��ת
        }
    }
}
