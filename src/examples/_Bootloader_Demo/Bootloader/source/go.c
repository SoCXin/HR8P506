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
函数名：sfr_reset
描  述: 引导程序前对BootROM里使用的寄存器恢复复位值
输入值：无
输出值：无
返回值：无
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
函数名：JumpToApp
描  述: 引导程序到指定位置
输入值：目标地址，必须256byte对齐
输出值：无
返回值：无
***************************************************************/
void JumpToApp(uint32_t addr)
{
    __disable_irq(); //关中断
    NVIC->ICER[0] = 0xFFFFFFFF;  //关闭所有IRQ

    ApplicationAddress = addr & 0xFFFFFF00; //保证地址256对齐
    REMAP_EN;
    SCU->TBLOFF.TBLOFF = ApplicationAddress; //中断向量重映射

    m_JumpAddress = *(volatile uint32_t *)(ApplicationAddress + 4);  //获取复位向量
    JumpToApplication = (FunVoidType) m_JumpAddress;

    sfr_reset();  //恢复寄存器
    __enable_irq();  //使能中断

    __set_MSP(*(volatile uint32_t *) ApplicationAddress);  //初始化栈顶
    JumpToApplication();  //程序跳转到复位向量指向的位置
}
