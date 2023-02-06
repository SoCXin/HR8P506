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

    UART0->CON0.RRST = 1;
    UART0->CON0.TRST = 1;
    UART0->CON0.Word = 0;
    UART0->CON1.Word = 0;
    UART0->IE.Word = 0;
    UART0->IF.Word = 0;
    UART0->BRR.Word = 0;

    GPIO->PADATA.Word = 0;
    GPIO->PADIR.Word = 0xFFFFFFFF;
    GPIO->PAINEB.Word = 0;
    GPIO->PAFUNC2.Word = 0;
    GPIO->PAFUNC3.Word = 0;
    GPIO->PAPDE.Word = 0;

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
