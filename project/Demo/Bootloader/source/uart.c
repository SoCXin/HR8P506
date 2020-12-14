#include "HR8P506.h"
#include "macro.h"
#include "typedef.h"


isp_data_t g_isp_data;   //ͨ��������ͨ��״̬���Ĵ���
extern uint32_t  g_boot_timer;
extern uint32_t  g_frame_timer;


/***************************************************************
��������start_tx
��  ��: ����UART����
����ֵ�����͵��ֽ���
���ֵ����
����ֵ����
***************************************************************/
void start_tx(uint8_t len)
{

    UART0->TBW.Byte[0] = g_isp_data.tx_buf[0];

    g_isp_data.tx_cnt = 0;  //���ͼ�������ʼ��
    g_isp_data.tx_len = len; //���ͳ���
}
/***************************************************************
��������uart0_reset
��  ��: UART0��λ
����ֵ����
���ֵ����
����ֵ����
***************************************************************/
void uart0_reset(void)
{
    UART0->CON0.Word = 1 << 17; //��������λ
    UART0->CON0.Word = 1 << 1; //��������λ
}



/***************************************************************
��������uart_init
��  ��: UART��ʼ��
����ֵ��uart����ַ
���ֵ����
����ֵ����
***************************************************************/
void uart_init(UART_TypeDef *uartx)
{
    /* Select UART function */
    uartx->CON0.RXMOD = 8; //����8bit-żУ��
    uartx->CON0.TXMOD = 8; //����8bit-żУ��
    uartx->CON0.BDEN = 1;  //�Զ�������ʹ��
    uartx->CON0.TXFS = 0;  //����ֹͣλ1bit



    uartx->CON1.RBIM = 0;  //�ֽ��������ж�
    uartx->CON1.BCS = 1;   //������ʱ��ΪPCLK
    uartx->CON1.BDM = 0;   //�Զ�������ģʽ1

    uartx->IE.TCIE = 1;  //��������ж�ʹ��
    uartx->IE.RBIE = 1;  //���ջ��������ж�ʹ��
    uartx->IE.BDEIE = 1; //�Զ������ʴ����ж�ʹ��
    uartx->IE.FEIE = 1;  //����֡�����ж�ʹ��
    uartx->IE.PEIE = 1;  //����У������ж�ʹ��

    uartx->CON0.RXEN = 1;  //����ʹ��
    uartx->CON0.TXEN = 1;  //����ʹ��

}

/***************************************************************
��������UART_TC_IRQHandler
��  ��: UART��������ж�
����ֵ��uart����ַ
���ֵ����
����ֵ����
***************************************************************/
void UART_TC_IRQHandler(UART_TypeDef *uartx)
{
    while ((uartx->IF.TCIF == 1) && (uartx->IE.TCIE == 1)) //��������ж�
    {
        uartx->IF.TCIF = 1;
        g_isp_data.tx_cnt++;

        if (g_isp_data.tx_cnt > g_isp_data.tx_len)   //������ɣ�������һ������
        {
            g_isp_data.triger = 1;//����״̬��������һ��
        }
        else
        {
            uartx->TBW.Byte[0] = g_isp_data.tx_buf[g_isp_data.tx_cnt];
        }

//        break;
    }
}
/***************************************************************
��������UART_RBR_IRQHandler
��  ��: UART����������Ч�ж�
����ֵ��uart����ַ
���ֵ����
����ֵ����
***************************************************************/
void UART_RBR_IRQHandler(UART_TypeDef *uartx)
{
    volatile uint8_t  buf8;

    while ((uartx->IF.RBIF == 1) && (uartx->IE.RBIE == 1)) //����������Ч�ж�
    {
        buf8 = (uint8_t)uartx->RBR.Byte[0];

        if (g_isp_data.syn == 0) //�����û��ͬ���ɹ�
        {
            if (buf8 == SYN && !(UART0->IE.FEIE && UART0->IF.FEIF) || (UART0->IE.PEIE && UART0->IF.PEIF)) //ͬ������ȷ��û����żУ������֡�ṹ����
            {
                g_boot_timer = Boot_OVERTIME_2;
                g_isp_data.tx_buf[0] = ACK;
                g_isp_data.syn = 1;  //ͬ�����
                g_isp_data.reset_other = 1;     //ͬ����ɸ�λ����UART
                g_isp_data.baud = (uint16_t)uartx->BRR.Word; //���ݲ����ʼĴ���

                uartx->TBW.Byte[0] = ACK;
                g_isp_data.tx_cnt = 0;  //���ͼ�������ʼ��
                g_isp_data.tx_len = 0; //���ͳ���
                g_isp_data.result = ACK;
                g_isp_data.step = END_SEND_OVER;

            }
            else                  //���������Ⲩ����
            {
                uartx->CON0.BDEN = 1;      //�Զ������ʼ����¿�ʼ
                UART0->IF.FEIF = 1;        //����жϱ�־
                UART0->IF.PEIF = 1;
            }
        }
        else
        {
            if ((UART0->IE.FEIE && UART0->IF.FEIF) || (UART0->IE.PEIE && UART0->IF.PEIF)) //�����żУ��������֡�ṹ����
            {
                UART0->IF.FEIF = 1;
                UART0->IF.PEIF = 1;
                break;
            }

            if ((buf8 == SYN) && (g_isp_data.step == WAIT_REV_INS))
            {
                g_boot_timer = Boot_OVERTIME_2;
                g_isp_data.tx_buf[0] = ACK;
                g_isp_data.syn = 1;  //ͬ�����
                start_tx(0);
                g_isp_data.result = ACK;
                g_isp_data.step = END_SEND_OVER;
            }
            else
            {
                if (g_isp_data.step == WAIT_REV_INS)
                {
                    g_isp_data.step = IN_REV_INS;  //���ڽ���ָ����
                    g_isp_data.rx_len = 1;
                    g_isp_data.rx_cnt = 0;
                }

                g_isp_data.rx_buf[g_isp_data.rx_cnt] = buf8;
                g_isp_data.rx_cnt++;

                if (g_isp_data.rx_cnt > g_isp_data.rx_len)   //������ɣ�������һ������
                {
                    g_isp_data.triger = 1;  //����״̬��������һ��
                }
            }
        }

//       break;
    }
}

/***************************************************************
��������UART_BDE_IRQHandler
��  ��: UART�Զ������ʼ�����
����ֵ��uart����ַ
���ֵ����
����ֵ����
***************************************************************/
void UART_BDE_IRQHandler(UART_TypeDef *uartx)
{
    while ((uartx->IF.BDEIF == 1) && (uartx->IE.BDEIE == 1)) //�Զ������ʼ�����
    {
        uartx->IF.BDEIF = 1;
        uartx->CON0.BDEN = 1; //���½����Զ�������
    }
}

/***************************************************************
��������UART0_IRQHandler
��  ��: UART0�жϷ������
����ֵ����
���ֵ����
����ֵ����
***************************************************************/
void UART0_IRQHandler(void)
{
    g_frame_timer = FRAME_INTERVAL;
    UART_BDE_IRQHandler(UART0); //�Զ������ʼ�����
    UART_TC_IRQHandler(UART0);  //�������
    UART_RBR_IRQHandler(UART0); //��������
}

