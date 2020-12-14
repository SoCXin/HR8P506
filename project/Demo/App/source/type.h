/*********************************************************
*Copyright (C), 2015, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  type.h
*作  者:  TianZW
*版  本:  V1.00
*日  期:  2015/12/03
*描  述:  type define
*备  注:  
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#ifndef __TYPE_H__
#define __TYPE_H__

typedef enum {Disable = 0x0, Enable = 0x1} TYPE_FUNCEN;
typedef enum {DISABLE = 0, ENABLE = !DISABLE} FuncState;
typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus, PinStatus;
typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;

#endif
