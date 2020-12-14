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

#define  FRAME_INTERVAL  80  //һ֡��������byte���ʱ�����80ms
#define  Boot_OVERTIME_1  20  //��λ�����BootPINΪ�ͣ�����20msû��ͬ���ɹ���ʼ��������
#define  Boot_OVERTIME_2  300  //ͬ���ɹ������BootPINΪ�ͣ�����300msû��ִ��������ʼ��������

#endif

