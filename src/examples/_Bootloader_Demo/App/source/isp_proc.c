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
函数名：next_ans_ins
描  述: 响应指令码后确定下一步
输入值：指令码
输出值：无
返回值：无
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
函数名：in_exe_ins
描  述: 执行各指令码
输入值：指令码
输出值：无
返回值：无
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
            JumpToApp(g_isp_data.para1.b32);  //引导程序
            break;

        case  WRITE_M:
            buf8 = g_isp_data.rx_buf[0] ^ g_isp_data.rx_buf[1];

            for (i = 2; i < (g_isp_data.para2.b32 + 2); i++)
            {
                buf8 = buf8 ^ g_isp_data.rx_buf[i];
            }

            if (buf8 ==  g_isp_data.rx_buf[i]) //下发的数据校验正确
            {
                if (g_isp_data.para1.b32 >= 0x20000000) //RAM数据直接memcpy
                {
                    memcpy((void *)g_isp_data.para1.b32, g_isp_data.rx_buf + 1, g_isp_data.para2.b32 + 1);
                    result = SUCCESS;
                }
                else  //flash数据则IAP
                {
                    iap_addr = g_isp_data.para1.b32;
                    iap_len = g_isp_data.para2.b32 + 1;

                    result = IAP_WordsProgram(iap_addr, (uint32_t)(g_isp_data.rx_buf + 1), iap_len, 0);

                }

                if (result == FAILED) //失败
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

                    if (buf8 ==  g_isp_data.rx_buf[i]) //写入的数据校验是否正确
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
            if (g_isp_data.para1.b08[0] == 0xFF) //全擦
            {
                g_isp_data.result = NACK;  //不支持全擦
                g_isp_data.step = IN_SEND_OVER;
                g_isp_data.triger = 1;
            }
            else  //页擦
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

            if (i != n) //擦除有误
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
函数名：wait_rev_para1
描  述: 参数1处理
输入值：指令码
输出值：无
返回值：无
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
函数名：next_rev_para1
描  述: 参数1处理后的下一步确定
输入值：指令码
输出值：无
返回值：无
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
            if (g_isp_data.rx_buf[0] == 0xFF) //如果全擦
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
函数名：wait_rev_para2
描  述: 参数2处理
输入值：指令码
输出值：无
返回值：无
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
函数名：next_rev_para2
描  述: 参数2处理后的下一步确定
输入值：指令码
输出值：无
返回值：无
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
函数名：fsm_init
描  述: 状态机初始化
输入值：无
输出值：无
返回值：无
***************************************************************/
void fsm_init(void)
{
    g_isp_data.step = WAIT_REV_INS;

    g_isp_data.cmd = 0;  //指令码
    g_isp_data.result = 0;  //执行结果
    g_isp_data.overtime = 0;    //超时限制
    g_isp_data.rx_len = 1;    //接收长度
    g_isp_data.tx_len = 0;    //发送长度
    g_isp_data.rx_cnt = 0;    //接收计数
    g_isp_data.tx_cnt = 0;    //发送计数
    g_isp_data.triger = 0;    //上一步动作完成，触发下一步动作
    g_boot_timer = 20;


}


/***************************************************************
函数名：uart_proc_fsm
描  述: UART命令帧处理状态机
输入值：无
输出值：无
返回值：无
***************************************************************/
void uart_proc_fsm(void)
{
    g_isp_data.triger = 0;

    switch (g_isp_data.step)
    {
        case  IN_REV_INS:  //0:接收指令码
            if (g_isp_data.rx_buf[0] == (uint8_t)(~g_isp_data.rx_buf[1])) //如果同步码校验正确
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

        case  END_REV_INS:  //完成接收指令码
            g_isp_data.step = IN_ANS_INS;  //响应指令码
            g_isp_data.triger = 1;
            break;

        case  IN_ANS_INS:  //响应指令码
            g_isp_data.tx_buf[0] = ACK;
            g_isp_data.step = END_ANS_INS;  //响应指令码完成
            start_tx(0);
            break;

        case  END_ANS_INS:  //完成响应指令码
            next_ans_ins(g_isp_data.cmd);
            break;

        case  WAIT_REV_PARA1://等待接收参数1
            wait_rev_para1(g_isp_data.cmd);
            break;

        case  END_REV_PARA1: //接收参数1完成
            next_rev_para1(g_isp_data.cmd);
            break;

        case  WAIT_REV_PARA2://等待接收参数2
            wait_rev_para2(g_isp_data.cmd);
            break;

        case  END_REV_PARA2://接收参数2完成
            next_rev_para2(g_isp_data.cmd);
            break;

        case  IN_EXE_INS:  //执行指令
            in_exe_ins(g_isp_data.cmd);
            break;

        case  END_EXE_INS: //完成执行指令
            g_isp_data.step = IN_SEND_OVER;
            g_isp_data.triger = 1;
            break;

        case  IN_SEND_OVER:  //发送结束ACK
            g_isp_data.tx_buf[0] = g_isp_data.result;
            g_isp_data.step = END_SEND_OVER;
            start_tx(0);
            break;

        case  END_SEND_OVER:  //完成发送结束ACK
            g_isp_data.step = WAIT_REV_INS;  //等待指令码
            g_frame_timer = 0;
            break;

        default:             //其他状态回归等待同步码状态
            g_isp_data.step = WAIT_REV_INS;  //等待指令码
            g_frame_timer = 0;
            break;
    }
}
