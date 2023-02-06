/***********************************************************************
若用户需要初始化全局变量，需要在进入主函数前调用该函数
************************************************************************/

extern unsigned long _sidata;
extern unsigned long __data_start__;
extern unsigned long __data_end__;
extern unsigned long __bss_start__;
extern unsigned long __bss_end__;

extern unsigned long _my_ram1_start;
extern unsigned long _my_ram1_size;
extern unsigned long _my_ram2_start;
extern unsigned long _my_ram2_size;
extern unsigned long _my_ram3_start;
extern unsigned long _my_ram3_size;
extern unsigned long _my_rom_end;

void  InitRam(void)
{
    unsigned long volatile *pulSrc, *pulDest;
    unsigned int volatile _my_rom_address;
    
    /***********************************************************************
    初始化有初始值的变量
    _sidata标识符就是初始化变量的rom镜像的起始地址，这是链接文件上定义的。
    __data_start__标识符就是全局变量在ram中的起始地址,__data_end__标识符就是ram中的结束地址
    ************************************************************************/
    pulSrc = &_sidata;
    for(pulDest = (unsigned long volatile *)&__data_start__; pulDest <(unsigned long volatile *)&__data_end__; )
    {
        *(pulDest++) = *(pulSrc++);
    }

	
    /*同理下面就是无初始值的变量，全清零*/
    for(pulDest = (unsigned long volatile *)&__bss_start__; pulDest < (unsigned long volatile *)&__bss_end__; )
    {
        *(pulDest++) = 0;
    }
	
	/*初始化Ram程序*/
	memcpy(&_my_ram1_start, &_my_rom_end, &_my_ram1_size);
	_my_rom_address = (unsigned int)&_my_rom_end + (unsigned int)&_my_ram1_size;
	memcpy(&_my_ram2_start, _my_rom_address, &_my_ram2_size);
	_my_rom_address = (unsigned int)&_my_rom_end + (unsigned int)&_my_ram1_size + (unsigned int)&_my_ram2_size;
	memcpy(&_my_ram3_start, _my_rom_address, &_my_ram3_size);
}