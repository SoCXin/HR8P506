/*********************************************************
*Copyright (C), 2015, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  type.h
*��  ��:  TianZW
*��  ��:  V1.00
*��  ��:  2015/12/03
*��  ��:  type define
*��  ע:  
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#ifndef __TYPE_H__
#define __TYPE_H__

typedef enum {Disable = 0x0, Enable = 0x1} TYPE_FUNCEN;
typedef enum {DISABLE = 0, ENABLE = !DISABLE} FuncState;
typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus, PinStatus;
typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;

#endif
