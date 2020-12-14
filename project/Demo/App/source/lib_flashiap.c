#include "HR8P506.h"
#include "macro.h"
#include "typedef.h"
#include "string.h"
#include "lib_flashiap.h"


uint32_t  get_crc32(uint32_t *data_ptr, uint32_t len)
{

    return 0;

}

uint8_t CRC_Emptycheck(uint32_t *data_ptr, uint32_t len)
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


