#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__
#include<stdint.h>

typedef union
{
    uint32_t b32;
    uint8_t b08[4];
} u_b32b08_t;

typedef enum
{
    WAIT_REV_INS = 0,    //4:等待接收指令码;
    IN_REV_INS,      //正在接收指令码
    END_REV_INS,     //5:指令码接收完成;

    IN_ANS_INS,     //6:响应指令码
    END_ANS_INS,    //7:响应指令码完成

    WAIT_REV_PARA1,    //8:等待接收参数1
    END_REV_PARA1,     //9:接收参数1完成

    WAIT_REV_PARA2,    //8:等待接收参数2
    END_REV_PARA2,     //9:接收参数2完成

    IN_EXE_INS,       //8:执行指令
    END_EXE_INS,      //9:执行指令结束

    IN_SEND_OVER,       //6:响应执行结果
    END_SEND_OVER,      //7:响应执行结果完成

    OTHER      //错误或未知状态
} isp_step_t;   //ISP指令状态机

typedef enum
{
    LOOPBACK_DIS = 0,
    LOOPBACK_EN = 1,
} loopback_t;

typedef  struct
{
    isp_step_t  step; //指令时序步骤
    uint8_t syn;      //是否完成同步
    uint8_t reset_other;  //复位其他UART标志
    uint8_t cmd;      //指令码
    uint8_t result;   //执行结果
    uint8_t overtime;    //超时限制
    uint16_t rx_len;   //接收长度
    uint16_t tx_len;   //发送长度
    uint16_t rx_cnt;   //接收计数
    uint16_t tx_cnt;   //发送计数
    uint16_t baud;     //自动波特率得到的波特率寄存器值
    uint8_t triger;    //上一步动作完成，触发下一步动作
    u_b32b08_t para1;  //参数1
    u_b32b08_t para2;  //参数2
    uint8_t revs[3];
    uint8_t rx_buf[257];  //接收缓存
    uint8_t revs1[3];
    uint8_t tx_buf[257];  //发送缓存

} isp_data_t;




typedef enum
{
    AUTOBAUD_DIS = 0,
    AUTOBAUD_EN = 1,
} autobaud_t;

#endif

