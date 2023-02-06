#ifndef __MACRO_H__
#define __MACRO_H__

#define  ACK  0x79
#define  NACK 0x1F


#define  SYN       0X3F
#define  GET       0x80
#define  GET_V     0x81
#define  GET_ID    0x82
#define  READ_M    0x91
#define  GO        0xA1
#define  WRITE_M   0xB1
#define  EX_ERASE  0xC4
#define  GET_CUSUM32 0xD0
#define  CHECK_EMPTY 0xD1

#define  APP_ADDR  0x00001000

#define  FRAME_INTERVAL  80  //一帧数据相邻byte间隔时间最大80ms
#define  Boot_OVERTIME_1  20  //复位后如果BootPIN为低，超过20ms没有同步成功则开始引导程序
#define  Boot_OVERTIME_2  300  //同步成功后如果BootPIN为低，超过300ms没有执行命令则开始引导程序

#endif

