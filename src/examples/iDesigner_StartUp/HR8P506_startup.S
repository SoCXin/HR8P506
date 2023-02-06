        .syntax unified
        .cpu cortex-m0
        .arch armv6-m
        .fpu softvfp
        .thumb
 
/*  Stack Configuration
    Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
*/
       
        .equ Stack_Size,  0x00000400
 
        .section  .stack, "wa"
        .align 3
        .global Stack_Mem
        .global Stack_Size
Stack_Mem:     
        .if Stack_Size
        .space   Stack_Size
        .endif
        .size    Stack_Mem,.-Stack_Mem
        .set     Stack_Size,.-Stack_Mem
__initial_sp:
 
 
/*
 <h> Heap Configuration
   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
</h>
*/
 
        .equ     Heap_Size,       0x00000010
 
        .section  .heap, "wa"
        .align 3
 
        .global Heap_Mem_Start
        .global Heap_Mem_End
Heap_Mem_Start:     
        .if Heap_Size
        .space   Heap_Size
        .endif        
Heap_Mem_End:     
 
 
/* Vector Table Mapped to Address 0 at Reset*/
                                        
        .section  .vectors, "wax"
        .global  __vector
        .type  __vector, %object
        
__vector: 
                .long     __initial_sp  /* Top of Stack*/
                .long     Reset_IRQHandler  /*Reset_IRQHandler*/    
                .long     NMI_IRQHandler  /* NMI IRQIRQHandler*/
                .long     HardFault_IRQHandler         /* Hard Fault IRQIRQHandler*/
                .long     0                            /* Reserved*/
                .long     0                            /* Reserved*/
                .long     0                            /* Reserved*/
                .long     0                            /* Reserved*/
                .long     0                            /* Reserved*/
                .long     0                            /* Reserved*/
                .long     0                            /* Reserved*/
                .long     SVC_IRQHandler               /* SVCall IRQIRQHandler*/
                .long     0                            /* Reserved*/
                .long     0                            /* Reserved*/
                .long     PendSV_IRQHandler            /* PendSV IRQIRQHandler*/
                .long     SysTick_IRQHandler           /* SysTick IRQIRQHandler*/
 
                /* External Interrupts*/
                .long     PINT0_IRQHandler /*16, pint0 IRQIRQHandler*/
                .long     PINT1_IRQHandler /*17, pint1 IRQIRQHandler*/
                .long     PINT2_IRQHandler /*18, pint2 IRQIRQHandler*/
                .long     PINT3_IRQHandler /*19, pint3 IRQIRQHandler*/
                .long     PINT4_IRQHandler /*20, pint4 IRQIRQHandler*/
                .long     PINT5_IRQHandler /*21, pint5 IRQIRQHandler*/
                .long     PINT6_IRQHandler /*22, pint6 IRQIRQHandler*/
                .long     PINT7_IRQHandler /*23, pint7 IRQIRQHandler*/
                .long     T16N0_IRQHandler /*24, t16n0 IRQIRQHandler*/
                .long     T16N1_IRQHandler /*25, t16n1 IRQIRQHandler*/
                .long     T16N2_IRQHandler /*26, t16n2 IRQIRQHandler*/
.long     T16N3_IRQHandler /*27, t16n3 IRQIRQHandler*/
                .long     T32N0_IRQHandler /*28, t32n0 IRQIRQHandler*/
                .long     0  /*29, Reserved     */
                .long     0                                  /*30, Reserved              */
                .long     0                                  /*31, Reserved              */
                .long     WDT_IRQHandler /*32, wdt IRQIRQHandler     */
                .long     RTC_IRQHandler /*33, rtc IRQIRQHandler     */
                .long     KINT_IRQHandler /*34, kint IRQIRQHandler    */
                .long     ADC_IRQHandler /*35, adc  IRQIRQHandler    */
                .long     0 /*36, Reserved    */
                .long     LVD_IRQHandler /*37, lvd IRQIRQHandler    */
                .long     PLLLK_IRQHandler /*38, plllk IRQIRQHandler    */
                .long     UART0_IRQHandler /*39, uart0 IRQIRQHandler   */
                .long     UART1_IRQHandler /*40, uart1 IRQIRQHandler   */
                .long     EUART0_IRQHandler /*41, euart0 IRQIRQHandler   */
                .long     0 /*42, Reserved    */
                .long     SPI0_IRQHandler /*43, spi0 IRQIRQHandler  */
                .long     SPI1_IRQHandler /*44, spi1 IRQIRQHandler  */
                .long     I2C0_IRQHandler /*45  i2c0 IRQIRQHandler    */
                .long     0 /*46, Reserved     */
                .long     CCM_IRQHandler /*47, ccm IRQIRQHandler    */
 
               .size  __vector, .-__vector
                
.thumb
                .text
                .thumb_func
                .global  Reset_IRQHandler
                .type Reset_IRQHandler,%function
Reset_IRQHandler:
           
            .extern main
                .extern __start
                .extern InitRam
.extern RegInit
                LDR     R0, =RegInit
                BLX     R0 
                LDR     R0, =InitRam
                BLX     R0
                LDR     R0, =main
                BLX      R0
             
               .size  Reset_IRQHandler, .-Reset_IRQHandler
 
                .text
/* Dummy Exception IRQHandlers (infinite loops which can be modified)*/                
               
                 .weak NMI_IRQHandler
                 .type NMI_IRQHandler,%function
NMI_IRQHandler:     
                 B       .
                 .size  NMI_IRQHandler, .-NMI_IRQHandler
                
                 .weak  HardFault_IRQHandler
                 .type  HardFault_IRQHandler,%function
HardFault_IRQHandler:
                B .
                .size  HardFault_IRQHandler, .-HardFault_IRQHandler
                
                .weak SVC_IRQHandler
                .type SVC_IRQHandler,%function
SVC_IRQHandler: 
                B       .
                .size  SVC_IRQHandler, .-SVC_IRQHandler
              
                
                .weak  PendSV_IRQHandler
                .type  PendSV_IRQHandler,%function
PendSV_IRQHandler:
                B .
          .size  PendSV_IRQHandler, .-PendSV_IRQHandler
                 
                .weak  SysTick_IRQHandler
                .type  SysTick_IRQHandler,%function
SysTick_IRQHandler: 
                B .
                .size  SysTick_IRQHandler, .-SysTick_IRQHandler
 
                .global Default_IRQHandler
                .type  Default_IRQHandler,%function
Default_IRQHandler: 
                B       .
                .size  Default_IRQHandler, .-Default_IRQHandler
                .macro IRQ handler
                .weak \handler
                .set \handler,Default_IRQHandler 
                .endm
                
IRQ PINT0_IRQHandler      
IRQ PINT1_IRQHandler      
IRQ PINT2_IRQHandler      
IRQ PINT3_IRQHandler      
IRQ PINT4_IRQHandler      
IRQ PINT5_IRQHandler      
IRQ PINT6_IRQHandler      
IRQ PINT7_IRQHandler      
IRQ T16N0_IRQHandler      
IRQ T16N1_IRQHandler      
IRQ T16N2_IRQHandler      
IRQ T16N3_IRQHandler      
IRQ T32N0_IRQHandler      
IRQ WDT_IRQHandler      
IRQ RTC_IRQHandler        
IRQ KINT_IRQHandler       
IRQ ADC_IRQHandler        
IRQ LVD_IRQHandler       
IRQ PLLLK_IRQHandler       
IRQ UART0_IRQHandler     
IRQ UART1_IRQHandler     
IRQ EUART0_IRQHandler       
IRQ SPI0_IRQHandler    
IRQ SPI1_IRQHandler    
IRQ I2C0_IRQHandler       
IRQ CCM_IRQHandler       
 
 
.text 
                .thumb_func
.global  RegInit
                .type RegInit,%function 
RegInit:
PUSH {LR}
NOP
NOP
NOP
NOP
NOP
LDR     R0, =0x40000080  
LDR     R1, =0xAA559669
STR     R1, [R0]
 
LDR     R0, =0x00100124   
LDR     R7, =0x400000A4   
BL      IP_CAL_LOAD
 
LDR     R0, =0x00100128   
LDR     R7, =0x400000A8  
BL      IP_CAL_LOAD
 
LDR     R0, =0x0010012C   
LDR     R7, =0x4000009C   
BL      IP_CAL_LOAD
 
LDR     R0, =0x00100130  
LDR     R7, =0x400000A0  
BL      IP_CAL_LOAD
 
LDR     R0, =0x40000080  
LDR     R1, =0x00000000
STR     R1, [R0]
 
POP     {PC}
 
IP_CAL_LOAD:
PUSH    {LR}
LDR     R2, =0xFFFFFFFF
LDR     R1, [R0]
CMP     R1, R2
BNE     IP_CAL_VERIFY    
LDR     R1, [R0]         
CMP     R1, R2
BNE     IP_CAL_VERIFY    
 
B       IP_CAL_EMPTY     
 
IP_CAL_VERIFY:
LDR      R5, =0x00000003    
LDR      R4, =0x000000FF
IP_CAL_VERIFY_LOOP:
MOVS     R2, R1
ANDS     R2, R4         
 
LSRS     R3, R1, #8
ANDS     R3, R4
ADD      R2, R2, R3        
 
LSRS     R3, R1, #16
ANDS     R3, R4
ADD      R2, R2, R3        
ANDS     R2, R4
 
LSRS     R3, R1, #24   
 
CMP      R2, R3        
BEQ      IP_LOAD_OK
SUBS     R5, #1
BEQ      IP_CAL_EMPTY    
LDR      R1, [R0]         
B        IP_CAL_VERIFY_LOOP
 
IP_LOAD_OK:
STR      R1, [R7]
 
IP_CAL_EMPTY:
POP      {PC}
 
.align
.ltorg
.end
