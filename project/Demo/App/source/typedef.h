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
    WAIT_REV_INS = 0,    //4:�ȴ�����ָ����;
    IN_REV_INS,      //���ڽ���ָ����
    END_REV_INS,     //5:ָ����������;

    IN_ANS_INS,     //6:��Ӧָ����
    END_ANS_INS,    //7:��Ӧָ�������

    WAIT_REV_PARA1,    //8:�ȴ����ղ���1
    END_REV_PARA1,     //9:���ղ���1���

    WAIT_REV_PARA2,    //8:�ȴ����ղ���2
    END_REV_PARA2,     //9:���ղ���2���

    IN_EXE_INS,       //8:ִ��ָ��
    END_EXE_INS,      //9:ִ��ָ�����

    IN_SEND_OVER,       //6:��Ӧִ�н��
    END_SEND_OVER,      //7:��Ӧִ�н�����

    OTHER      //�����δ֪״̬
} isp_step_t;   //ISPָ��״̬��

typedef enum
{
    LOOPBACK_DIS = 0,
    LOOPBACK_EN = 1,
} loopback_t;

typedef  struct
{
    isp_step_t  step; //ָ��ʱ����
    uint8_t syn;      //�Ƿ����ͬ��
    uint8_t reset_other;  //��λ����UART��־
    uint8_t cmd;      //ָ����
    uint8_t result;   //ִ�н��
    uint8_t overtime;    //��ʱ����
    uint16_t rx_len;   //���ճ���
    uint16_t tx_len;   //���ͳ���
    uint16_t rx_cnt;   //���ռ���
    uint16_t tx_cnt;   //���ͼ���
    uint16_t baud;     //�Զ������ʵõ��Ĳ����ʼĴ���ֵ
    uint8_t triger;    //��һ��������ɣ�������һ������
    u_b32b08_t para1;  //����1
    u_b32b08_t para2;  //����2
    uint8_t revs[3];
    uint8_t rx_buf[257];  //���ջ���
    uint8_t revs1[3];
    uint8_t tx_buf[257];  //���ͻ���

} isp_data_t;




typedef enum
{
    AUTOBAUD_DIS = 0,
    AUTOBAUD_EN = 1,
} autobaud_t;

#endif

