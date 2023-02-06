#include "HR8P506.h"
#include "macro.h"
#include "typedef.h"
#include "lib_flashiap.h"

#define APP_ADDRESS BOOT_TO_ADDR
typedef  void (*FunVoidType)(void);

static uint32_t ApplicationAddress;
static uint32_t m_JumpAddress;
static FunVoidType JumpToApplication;

/***************************************************************
��������sfr_reset
��  ��: ��������ǰ��BootROM��ʹ�õļĴ����ָ���λֵ
����ֵ����
���ֵ����
����ֵ����
***************************************************************/
void sfr_reset(void)
{

    SysTick->CTRL = 0x00;
    SysTick->LOAD = 0;


    UART0->IE.TCIE = 0;  //��������ж�ʹ��
    UART0->IE.RBIE = 0;  //���ջ��������ж�ʹ��
    UART0->CON0.RXEN = 0;  //����ʹ��
    UART0->CON0.TXEN = 0;  //����ʹ��


    GPIO->PADIR.DIR_24 = 1;   //����ر�
    GPIO->PAINEB.INEB_24 = 1; //����ر�
    GPIO->PAFUNC3.PA24 = 0;   //GPIO
    GPIO->PADIR.DIR_22 = 1;   //����ر�
    GPIO->PAINEB.INEB_22 = 1; //����ر�
    GPIO->PAFUNC2.PA22 = 0;   //GPIO
    GPIO->PADIR.DIR_23 = 1;   //����ر�
    GPIO->PAINEB.INEB_23 = 1; //����ر�
    GPIO->PAFUNC2.PA23 = 1;   //GPIO

    WDT->LOCK.Word = 0;

    SCU->PROT.Word = 0;
}

/***************************************************************
��������JumpToApp
��  ��: ��������ָ��λ��
����ֵ��Ŀ���ַ������256byte����
���ֵ����
����ֵ����
***************************************************************/
void JumpToApp(uint32_t addr)
{
    __disable_irq(); //���ж�
    NVIC->ICER[0] = 0xFFFFFFFF;  //�ر�����IRQ

    ApplicationAddress = addr & 0xFFFFFF00; //��֤��ַ256����
    REMAP_EN;
    SCU->TBLOFF.TBLOFF = ApplicationAddress; //�ж�������ӳ��

    m_JumpAddress = *(volatile uint32_t *)(ApplicationAddress + 4);  //��ȡ��λ����
    JumpToApplication = (FunVoidType) m_JumpAddress;

    sfr_reset();  //�ָ��Ĵ���
    __enable_irq();  //ʹ���ж�

    __set_MSP(*(volatile uint32_t *) ApplicationAddress);  //��ʼ��ջ��
    JumpToApplication();  //������ת����λ����ָ���λ��
}
