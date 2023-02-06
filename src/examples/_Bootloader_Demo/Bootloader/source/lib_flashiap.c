#include "HR8P506.h"
#include "macro.h"
#include "typedef.h"
#include "string.h"
#include "lib_flashiap.h"

/***************************************************************
��������get_cusum32
��  ��: ��ȡ32bit�ۼӺ�
����ֵ����ʼ��ַ���ֽڳ���
���ֵ����
����ֵ��32bit�ۼӺͽ��
***************************************************************/
uint32_t  get_cusum32(uint32_t *data_ptr, uint32_t len)
{
    uint32_t  i, buf32;

    if ((((uint32_t)data_ptr) % 4 != 0) || (len % 4 != 0))
    {
        return 0;
    }

    buf32 = 0;

    for (i = 0; i < len; i += 4)
    {
        buf32 += *(data_ptr++);
    }

    return buf32;
}

/***************************************************************
��������check_empty
��  ��:
����ֵ����ʼ��ַ���ֽڳ���
���ֵ����
����ֵ��32bit�ۼӺͽ��
***************************************************************/
uint8_t check_empty(uint32_t *data_ptr, uint32_t len)
{
    uint32_t  i;

    if ((((uint32_t)data_ptr) % 4 != 0) || (len % 4 != 0))
    {
        return FAILED;
    }

    for (i = 0; i < len; i += 4)
    {
        if (*(data_ptr++) != 0xFFFFFFFF)
        {
            break;
        }
    }

    if (i != len)
    {
        return FAILED;
    }
    else
    {
        return SUCCESS;
    }
}


