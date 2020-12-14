#include "HR8P506.h"
#include "macro.h"
#include "typedef.h"
#include "string.h"
#include "lib_flashiap.h"

extern isp_data_t g_isp_data;
extern uint32_t  g_boot_timer;
extern uint32_t  g_frame_timer;


void fsm_init(void);
void uart_proc_fsm(void);
void ans_ins(uint8_t ins);
void start_tx(uint8_t len);
void JumpToApp(uint32_t addr);



/***************************************************************
��������next_ans_ins
��  ��: ��Ӧָ�����ȷ����һ��
����ֵ��ָ����
���ֵ����
����ֵ����
***************************************************************/
void next_ans_ins(uint8_t ins)
{
    switch (ins)
    {
        case  GET:

            break;

        case  GET_V:

            break;

        case  GET_ID:

            break;

        case  READ_M:
            g_isp_data.step = WAIT_REV_PARA1;
            g_isp_data.rx_len = 4;
            g_isp_data.rx_cnt = 0;
            break;

        case  GO:
            g_isp_data.step = WAIT_REV_PARA1;
            g_isp_data.rx_len = 4;
            g_isp_data.rx_cnt = 0;
            break;

        case  WRITE_M:
            g_isp_data.step = WAIT_REV_PARA1;
            g_isp_data.rx_len = 4;
            g_isp_data.rx_cnt = 0;
            break;

        case  EX_ERASE:
            g_isp_data.step = WAIT_REV_PARA1;
            g_isp_data.rx_len = 2;
            g_isp_data.rx_cnt = 0;
            break;

        case  GET_CRC32:
        case  CHECK_EMPTY:
            g_isp_data.step = WAIT_REV_PARA1;
            g_isp_data.rx_len = 4;
            g_isp_data.rx_cnt = 0;
            break;

        default:

            break;
    }
}

/***************************************************************
��������in_exe_ins
��  ��: ִ�и�ָ����
����ֵ��ָ����
���ֵ����
����ֵ����
***************************************************************/
void in_exe_ins(uint8_t ins)
{
    volatile    uint16_t i=0,/*start,*/n=0;
    uint8_t  buf8;
    uint32_t iap_addr, iap_len, result, buf32, page;

    //uint8_t iap_buf[257];
    g_boot_timer = 300;

    switch (ins)
    {
        case  GET:

            break;

        case  GET_V:

            break;

        case  GET_ID:

            break;

        case  READ_M:
            memcpy(g_isp_data.tx_buf, (const void *)g_isp_data.para1.b32, (uint32_t)g_isp_data.para2.b08[0] + 1);
            g_isp_data.step = END_SEND_OVER;
            g_isp_data.result = ACK;
            start_tx(g_isp_data.para2.b08[0]);
            break;

        case  GO:
            JumpToApp(g_isp_data.para1.b32);  //��������
            break;

        case  WRITE_M:
            buf8 = g_isp_data.rx_buf[0] ^ g_isp_data.rx_buf[1];

            for (i = 2; i < (g_isp_data.para2.b32 + 2); i++)
            {
                buf8 = buf8 ^ g_isp_data.rx_buf[i];
            }

            if (buf8 ==  g_isp_data.rx_buf[i]) //�·�������У����ȷ
            {
                if (g_isp_data.para1.b32 >= 0x20000000) //RAM����ֱ��memcpy
                {
                    memcpy((void *)g_isp_data.para1.b32, g_isp_data.rx_buf + 1, g_isp_data.para2.b32 + 1);
                    result = SUCCESS;
                }
                else  //flash������IAP
                {
                    iap_addr = g_isp_data.para1.b32;
                    iap_len = g_isp_data.para2.b32 + 1;

                    result = IAP_WordsProgram(iap_addr, (uint32_t)(g_isp_data.rx_buf + 1), iap_len, 0);

                }

                if (result == FAILED) //ʧ��
                    //zxf if(i!=(g_isp_data.para2.b32+1))
                {
                    g_isp_data.result = NACK;
                    g_isp_data.step = IN_SEND_OVER;
                    g_isp_data.triger = 1;
                }
                else
                {
                    memcpy(g_isp_data.rx_buf + 1, (void *)g_isp_data.para1.b32, g_isp_data.para2.b32 + 1);
                    buf8 = g_isp_data.rx_buf[0] ^ g_isp_data.rx_buf[1];

                    for (i = 2; i < (g_isp_data.para2.b32 + 2); i++)
                    {
                        buf8 = buf8 ^ g_isp_data.rx_buf[i];
                    }

                    if (buf8 ==  g_isp_data.rx_buf[i]) //д�������У���Ƿ���ȷ
                    {
                        g_isp_data.result = ACK;
                    }
                    else
                    {
                        g_isp_data.result = NACK;
                    }

                    g_isp_data.step = IN_SEND_OVER;
                    g_isp_data.triger = 1;

                }
            }
            else
            {
                g_isp_data.result = NACK;
                g_isp_data.step = IN_SEND_OVER;
                g_isp_data.triger = 1;
            }

            break;

        case  EX_ERASE:
            if (g_isp_data.para1.b08[0] == 0xFF) //ȫ��
            {
                g_isp_data.result = NACK;  //��֧��ȫ��
                g_isp_data.step = IN_SEND_OVER;
                g_isp_data.triger = 1;
            }
            else  //ҳ��
            {
                n = g_isp_data.para2.b32 + 1;

                for (i = 0; i < n; i++)
                {
                    page = (uint16_t)g_isp_data.rx_buf[3 + i * 2] + ((uint16_t)g_isp_data.rx_buf[2 + i * 2] << 8);
                    page = (page << 10);

                    if (IAP_PageErase(page) != SUCCESS)
                        break;

                }
            }

            if (i != n) //��������
            {
                g_isp_data.result = NACK;
            }
            else
            {
                g_isp_data.result = ACK;
            }

            g_isp_data.step = END_EXE_INS;
            g_isp_data.triger = 1;
            break;

        case  GET_CRC32:
            buf32 = get_crc32((uint32_t *)g_isp_data.para1.b32, g_isp_data.para2.b32 + 1);
            memcpy(g_isp_data.tx_buf, (const void *)&buf32, 4);
            g_isp_data.step = END_SEND_OVER;
            start_tx(3);
            break;

        case  CHECK_EMPTY:
            if (CRC_Emptycheck((uint32_t *)g_isp_data.para1.b32, g_isp_data.para2.b32 + 1) == SUCCESS)
            {
                g_isp_data.result = ACK;
            }
            else
            {
                g_isp_data.result = NACK;
            }

            g_isp_data.step = IN_SEND_OVER;
            g_isp_data.triger = 1;
            break;

        default:

            break;
    }
}


/***************************************************************
��������wait_rev_para1
��  ��: ����1����
����ֵ��ָ����
���ֵ����
����ֵ����
***************************************************************/
void wait_rev_para1(uint8_t ins)
{
    uint8_t buf8;

    switch (ins)
    {
        case  GET:

            break;

        case  GET_V:

            break;

        case  GET_ID:

            break;

        case  READ_M:
            buf8 = g_isp_data.rx_buf[0] ^ g_isp_data.rx_buf[1];
            buf8 = buf8 ^ g_isp_data.rx_buf[2];
            buf8 = buf8 ^ g_isp_data.rx_buf[3];

            if (g_isp_data.rx_buf[4] == buf8)
            {
                g_isp_data.para1.b08[0] = g_isp_data.rx_buf[3];
                g_isp_data.para1.b08[1] = g_isp_data.rx_buf[2];
                g_isp_data.para1.b08[2] = g_isp_data.rx_buf[1];
                g_isp_data.para1.b08[3] = g_isp_data.rx_buf[0];
                g_isp_data.step = END_REV_PARA1;
                g_isp_data.tx_buf[0] = ACK;
                start_tx(0);
            }
            else
            {
                g_isp_data.result = NACK;
                g_isp_data.step = IN_SEND_OVER;
                g_isp_data.triger = 1;
            }

            break;

        case  GO:
            buf8 = g_isp_data.rx_buf[0] ^ g_isp_data.rx_buf[1];
            buf8 = buf8 ^ g_isp_data.rx_buf[2];
            buf8 = buf8 ^ g_isp_data.rx_buf[3];

            if (g_isp_data.rx_buf[4] == buf8)
            {
                g_isp_data.para1.b08[0] = g_isp_data.rx_buf[3];
                g_isp_data.para1.b08[1] = g_isp_data.rx_buf[2];
                g_isp_data.para1.b08[2] = g_isp_data.rx_buf[1];
                g_isp_data.para1.b08[3] = g_isp_data.rx_buf[0];
                g_isp_data.step = END_REV_PARA1;
                g_isp_data.tx_buf[0] = ACK;
                start_tx(0);
            }
            else
            {
                g_isp_data.result = NACK;
                g_isp_data.step = IN_SEND_OVER;
                g_isp_data.triger = 1;
            }

            break;

        case  WRITE_M:
            buf8 = g_isp_data.rx_buf[0] ^ g_isp_data.rx_buf[1];
            buf8 = buf8 ^ g_isp_data.rx_buf[2];
            buf8 = buf8 ^ g_isp_data.rx_buf[3];

            if (g_isp_data.rx_buf[4] == buf8)
            {
                g_isp_data.para1.b08[0] = g_isp_data.rx_buf[3];
                g_isp_data.para1.b08[1] = g_isp_data.rx_buf[2];
                g_isp_data.para1.b08[2] = g_isp_data.rx_buf[1];
                g_isp_data.para1.b08[3] = g_isp_data.rx_buf[0];
                g_isp_data.step = END_REV_PARA1;
                g_isp_data.tx_buf[0] = ACK;
                start_tx(0);
            }
            else
            {
                g_isp_data.result = NACK;
                g_isp_data.step = IN_SEND_OVER;
                g_isp_data.triger = 1;
            }

            break;

        case  EX_ERASE:
            if (g_isp_data.rx_buf[0] == 0xFF)
            {
                if (g_isp_data.rx_buf[1] == 0xFF)
                {
                    if ((g_isp_data.rx_buf[0] ^ g_isp_data.rx_buf[1]) == g_isp_data.rx_buf[2])
                    {
                        g_isp_data.para1.b32 = 0;
                        g_isp_data.para1.b08[0] = g_isp_data.rx_buf[1];
                        g_isp_data.para1.b08[1] = g_isp_data.rx_buf[0];
                        g_isp_data.step = END_REV_PARA1;
                        g_isp_data.triger = 1;
                    }
                    else
                    {
                        g_isp_data.result = NACK;
                        g_isp_data.step = IN_SEND_OVER;
                        g_isp_data.triger = 1;
                    }
                }
                /*else if(g_isp_data.rx_buf[1] == 0xFE)
                {

                }
                else if(g_isp_data.rx_buf[1] == 0xFD)
                {

                }*/
                else
                {
                    g_isp_data.result = NACK;
                    g_isp_data.step = IN_SEND_OVER;
                    g_isp_data.triger = 1;
                }
            }
            else
            {
                g_isp_data.para1.b32 = 0;
                g_isp_data.para1.b08[0] = g_isp_data.rx_buf[1];
                g_isp_data.para1.b08[1] = g_isp_data.rx_buf[0];
                g_isp_data.step = END_REV_PARA1;
                g_isp_data.triger = 1;

            }

            break;

        case  GET_CRC32:
        case  CHECK_EMPTY:
            buf8 = g_isp_data.rx_buf[0] ^ g_isp_data.rx_buf[1];
            buf8 = buf8 ^ g_isp_data.rx_buf[2];
            buf8 = buf8 ^ g_isp_data.rx_buf[3];

            if (g_isp_data.rx_buf[4] == buf8)
            {
                g_isp_data.para1.b08[0] = g_isp_data.rx_buf[3];
                g_isp_data.para1.b08[1] = g_isp_data.rx_buf[2];
                g_isp_data.para1.b08[2] = g_isp_data.rx_buf[1];
                g_isp_data.para1.b08[3] = g_isp_data.rx_buf[0];

                if ((g_isp_data.para1.b32 % 4) == 0)
                {
                    g_isp_data.step = END_REV_PARA1;
                    g_isp_data.tx_buf[0] = ACK;
                    start_tx(0);
                }
                else
                {
                    g_isp_data.result = NACK;
                    g_isp_data.step = IN_SEND_OVER;
                    g_isp_data.triger = 1;
                }
            }
            else
            {
                g_isp_data.result = NACK;
                g_isp_data.step = IN_SEND_OVER;
                g_isp_data.triger = 1;
            }

            break;

        default:

            break;
    }
}


/***************************************************************
��������next_rev_para1
��  ��: ����1��������һ��ȷ��
����ֵ��ָ����
���ֵ����
����ֵ����
***************************************************************/
void next_rev_para1(uint8_t ins)
{
    switch (ins)
    {
        case  GET:

            break;

        case  GET_V:

            break;

        case  GET_ID:

            break;

        case  READ_M:
            g_isp_data.step = WAIT_REV_PARA2;
            g_isp_data.rx_len = 1;
            g_isp_data.rx_cnt = 0;
            break;

        case  GO:
            g_isp_data.step = WAIT_REV_PARA2;
            g_isp_data.triger = 1;
            break;

        case  WRITE_M:
            g_isp_data.step = WAIT_REV_PARA2;
            g_isp_data.rx_len = 0;
            g_isp_data.rx_cnt = 0;
            break;

        case  EX_ERASE:
            if (g_isp_data.rx_buf[0] == 0xFF) //���ȫ��
            {
                g_isp_data.step = IN_EXE_INS;
                g_isp_data.triger = 1;
            }
            else
            {
                g_isp_data.step = WAIT_REV_PARA2;
                g_isp_data.rx_len = (g_isp_data.para1.b32 + 2) * 2;
            }

            break;

        case  GET_CRC32:
        case  CHECK_EMPTY:
            g_isp_data.step = WAIT_REV_PARA2;
            g_isp_data.rx_len = 4;
            g_isp_data.rx_cnt = 0;
            break;

        default:

            break;
    }
}


/***************************************************************
��������wait_rev_para2
��  ��: ����2����
����ֵ��ָ����
���ֵ����
����ֵ����
***************************************************************/
void wait_rev_para2(uint8_t ins)
{
    uint8_t i, buf8;

    switch (ins)
    {
        case  GET:

            break;

        case  GET_V:

            break;

        case  GET_ID:

            break;

        case  READ_M:
            if (g_isp_data.rx_buf[0] == (uint8_t)(~g_isp_data.rx_buf[1]))
            {
                g_isp_data.para2.b08[0] = g_isp_data.rx_buf[0];
                g_isp_data.step = END_REV_PARA2;
                g_isp_data.tx_buf[0] = ACK;
                start_tx(0);
            }
            else
            {
                g_isp_data.result = NACK;
                g_isp_data.step = IN_SEND_OVER;
                g_isp_data.triger = 1;
            }

            break;

        case  GO:
            g_isp_data.step = END_REV_PARA2;
            g_isp_data.tx_buf[0] = ACK;
            start_tx(0);
            break;

        case  WRITE_M:
            g_isp_data.para2.b32 = g_isp_data.rx_buf[0];
            g_isp_data.step = IN_EXE_INS;
            g_isp_data.rx_len = g_isp_data.rx_buf[0] + 2;
            break;

        case  EX_ERASE:
            buf8 = g_isp_data.rx_buf[0] ^ g_isp_data.rx_buf[1];

            for (i = 2; i < g_isp_data.rx_len; i++)
            {
                buf8 = buf8 ^ g_isp_data.rx_buf[i];
            }

            if (buf8 == g_isp_data.rx_buf[g_isp_data.rx_len])
            {
                g_isp_data.para2.b32 = 0;
                g_isp_data.para2.b08[0] = g_isp_data.rx_buf[1];
                g_isp_data.para2.b08[1] = g_isp_data.rx_buf[0];
                g_isp_data.step = IN_EXE_INS;
                g_isp_data.triger = 1;
            }
            else
            {
                g_isp_data.result = NACK;
                g_isp_data.step = IN_SEND_OVER;
                g_isp_data.triger = 1;
            }

            break;

        case  GET_CRC32:
            buf8 = g_isp_data.rx_buf[0] ^ g_isp_data.rx_buf[1];
            buf8 = buf8 ^ g_isp_data.rx_buf[2];
            buf8 = buf8 ^ g_isp_data.rx_buf[3];

            if (g_isp_data.rx_buf[4] == buf8)
            {
                g_isp_data.para2.b08[0] = g_isp_data.rx_buf[3];
                g_isp_data.para2.b08[1] = g_isp_data.rx_buf[2];
                g_isp_data.para2.b08[2] = g_isp_data.rx_buf[1];
                g_isp_data.para2.b08[3] = g_isp_data.rx_buf[0];

                if ((g_isp_data.para2.b32 + 1) % 4 == 0)
                {
                    g_isp_data.step = END_REV_PARA2;
                    g_isp_data.tx_buf[0] = ACK;
                    start_tx(0);
                }
                else
                {
                    g_isp_data.result = NACK;
                    g_isp_data.step = IN_SEND_OVER;
                    g_isp_data.triger = 1;
                }

            }
            else
            {
                g_isp_data.result = NACK;
                g_isp_data.step = IN_SEND_OVER;
                g_isp_data.triger = 1;
            }

            break;

        case  CHECK_EMPTY:
            buf8 = g_isp_data.rx_buf[0] ^ g_isp_data.rx_buf[1];
            buf8 = buf8 ^ g_isp_data.rx_buf[2];
            buf8 = buf8 ^ g_isp_data.rx_buf[3];

            if (g_isp_data.rx_buf[4] == buf8)
            {
                g_isp_data.para2.b08[0] = g_isp_data.rx_buf[3];
                g_isp_data.para2.b08[1] = g_isp_data.rx_buf[2];
                g_isp_data.para2.b08[2] = g_isp_data.rx_buf[1];
                g_isp_data.para2.b08[3] = g_isp_data.rx_buf[0];

                if ((g_isp_data.para2.b32 + 1) % 4 == 0)
                {
                    g_isp_data.step = END_REV_PARA2;
                    g_isp_data.tx_buf[0] = ACK;
                    start_tx(0);
                }
                else
                {
                    g_isp_data.result = NACK;
                    g_isp_data.step = IN_SEND_OVER;
                    g_isp_data.triger = 1;
                }

            }
            else
            {
                g_isp_data.result = NACK;
                g_isp_data.step = IN_SEND_OVER;
                g_isp_data.triger = 1;
            }

            break;

        default:

            break;
    }
}


/***************************************************************
��������next_rev_para2
��  ��: ����2��������һ��ȷ��
����ֵ��ָ����
���ֵ����
����ֵ����
***************************************************************/
void next_rev_para2(uint8_t ins)
{
    switch (ins)
    {
        case  GET:

            break;

        case  GET_V:

            break;

        case  GET_ID:

            break;

        case  READ_M:
            g_isp_data.step = IN_EXE_INS;
            g_isp_data.triger = 1;
            break;

        case  GO:
            g_isp_data.step = IN_EXE_INS;
            g_isp_data.triger = 1;
            break;

        case  WRITE_M:

            break;

        case  EX_ERASE:

            break;

        case  GET_CRC32:
        case  CHECK_EMPTY:
            g_isp_data.step = IN_EXE_INS;
            g_isp_data.triger = 1;
            break;

        default:

            break;
    }

}


/***************************************************************
��������fsm_init
��  ��: ״̬����ʼ��
����ֵ����
���ֵ����
����ֵ����
***************************************************************/
void fsm_init(void)
{
    g_isp_data.step = WAIT_REV_INS;

    g_isp_data.cmd = 0;  //ָ����
    g_isp_data.result = 0;  //ִ�н��
    g_isp_data.overtime = 0;    //��ʱ����
    g_isp_data.rx_len = 1;    //���ճ���
    g_isp_data.tx_len = 0;    //���ͳ���
    g_isp_data.rx_cnt = 0;    //���ռ���
    g_isp_data.tx_cnt = 0;    //���ͼ���
    g_isp_data.triger = 0;    //��һ��������ɣ�������һ������
    g_boot_timer = 20;


}


/***************************************************************
��������uart_proc_fsm
��  ��: UART����֡����״̬��
����ֵ����
���ֵ����
����ֵ����
***************************************************************/
void uart_proc_fsm(void)
{
    g_isp_data.triger = 0;

    switch (g_isp_data.step)
    {
        case  IN_REV_INS:  //0:����ָ����
            if (g_isp_data.rx_buf[0] == (uint8_t)(~g_isp_data.rx_buf[1])) //���ͬ����У����ȷ
            {
                g_isp_data.step = END_REV_INS;
                g_isp_data.cmd = g_isp_data.rx_buf[0];
                g_isp_data.triger = 1;
            }
            else
            {
                g_isp_data.result = NACK;
                g_isp_data.step = IN_SEND_OVER;
                g_isp_data.triger = 1;
            }

            break;

        case  END_REV_INS:  //��ɽ���ָ����
            g_isp_data.step = IN_ANS_INS;  //��Ӧָ����
            g_isp_data.triger = 1;
            break;

        case  IN_ANS_INS:  //��Ӧָ����
            g_isp_data.tx_buf[0] = ACK;
            g_isp_data.step = END_ANS_INS;  //��Ӧָ�������
            start_tx(0);
            break;

        case  END_ANS_INS:  //�����Ӧָ����
            next_ans_ins(g_isp_data.cmd);
            break;

        case  WAIT_REV_PARA1://�ȴ����ղ���1
            wait_rev_para1(g_isp_data.cmd);
            break;

        case  END_REV_PARA1: //���ղ���1���
            next_rev_para1(g_isp_data.cmd);
            break;

        case  WAIT_REV_PARA2://�ȴ����ղ���2
            wait_rev_para2(g_isp_data.cmd);
            break;

        case  END_REV_PARA2://���ղ���2���
            next_rev_para2(g_isp_data.cmd);
            break;

        case  IN_EXE_INS:  //ִ��ָ��
            in_exe_ins(g_isp_data.cmd);
            break;

        case  END_EXE_INS: //���ִ��ָ��
            g_isp_data.step = IN_SEND_OVER;
            g_isp_data.triger = 1;
            break;

        case  IN_SEND_OVER:  //���ͽ���ACK
            g_isp_data.tx_buf[0] = g_isp_data.result;
            g_isp_data.step = END_SEND_OVER;
            start_tx(0);
            break;

        case  END_SEND_OVER:  //��ɷ��ͽ���ACK
            g_isp_data.step = WAIT_REV_INS;  //�ȴ�ָ����
            g_frame_timer = 0;
            break;

        default:             //����״̬�ع�ȴ�ͬ����״̬
            g_isp_data.step = WAIT_REV_INS;  //�ȴ�ָ����
            g_frame_timer = 0;
            break;
    }
}
