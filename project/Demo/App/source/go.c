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


    UART0->IE.TCIE = 0;  //发送完成中断使能
    UART0->IE.RBIE = 0;  //接收缓冲器满中断使能
    UART0->CON0.RXEN = 0;  //接收使能
    UART0->CON0.TXEN = 0;  //发送使能


    GPIO->PADIR.DIR_24 = 1;   //输出关闭
    GPIO->PAINEB.INEB_24 = 1; //输入关闭
    GPIO->PAFUNC3.PA24 = 0;   //GPIO
    GPIO->PADIR.DIR_22 = 1;   //输出关闭
    GPIO->PAINEB.INEB_22 = 1; //输入关闭
    GPIO->PAFUNC2.PA22 = 0;   //GPIO
    GPIO->PADIR.DIR_23 = 1;   //输出关闭
    GPIO->PAINEB.INEB_23 = 1; //输入关闭
    GPIO->PAFUNC2.PA23 = 1;   //GPIO

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
