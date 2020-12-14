;*******************************************************************************

; *author     : Eastsoft MCU Software Team
; *version    : V0.01
; *data       : 8/24/2018
;
; *Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd.
; *
; * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
; * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
; * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
; * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
;*******************************************************************************


        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        EXTERN  SystemInit
        PUBLIC  __vector_table

        DATA
__vector_table
        DCD     sfe(CSTACK)
        DCD     Reset_IRQHandler               ; Reset Handler

        DCD     NMI_IRQHandler                 ; NMI Handler
        DCD     HardFault_IRQHandler           ; Hard Fault Handler
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     SVC_IRQHandler                 ; SVCall Handler
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     PendSV_IRQHandler              ; PendSV Handler
        DCD     SysTick_IRQHandler             ; SysTick Handler

        ; External Interrupts
        DCD     PINT0_IRQHandler          ;16, PINT0 IRQHandler
        DCD     PINT1_IRQHandler          ;17, PINT1 IRQHandler
        DCD     PINT2_IRQHandler          ;18, PINT2 IRQHandler
        DCD     PINT3_IRQHandler          ;19, PINT3 IRQHandler
        DCD     PINT4_IRQHandler          ;20, PINT4 IRQHandler
        DCD     PINT5_IRQHandler          ;21, PINT5 IRQHandler
        DCD     PINT6_IRQHandler          ;22, PINT6 IRQHandler
        DCD     PINT7_IRQHandler          ;23, PINT7 IRQHandler
        DCD     T16N0_IRQHandler          ;24, T16N0 IRQHandler
        DCD     T16N1_IRQHandler          ;25, T16N1 IRQHandler
        DCD     T16N2_IRQHandler          ;26, T16N2 IRQHandler
        DCD     T16N3_IRQHandler          ;27, T16N3 IRQHandler
        DCD     T32N0_IRQHandler          ;28, T32N0 IRQHandler
        DCD     0                         ;29, Reserved
        DCD     0                         ;30, Reserved
        DCD     0                         ;31, Reserved
        DCD     WDT_IRQHandler            ;32, WDT IRQHandler
        DCD     RTC_IRQHandler            ;33, RTC IRQHandler
        DCD     KINT_IRQHandler           ;34, KINT IRQHandler
        DCD     ADC_IRQHandler            ;35, ADC IRQHandler
        DCD     0                         ;36, Reserved
        DCD     LVD_IRQHandler            ;37, LVD IRQHandler
        DCD     PLLLK_IRQHandler          ;38, PLLLK IRQHandler
        DCD     UART0_IRQHandler          ;39, UART0 IRQHandler
        DCD     UART1_IRQHandler          ;40, UART1 IRQHandler
        DCD     EUART0_IRQHandler         ;41, EUART0 IRQHandler
        DCD     0                         ;42, Reserved
        DCD     SPI0_IRQHandler           ;43, SPI0 IRQHandler
        DCD     SPI1_IRQHandler           ;44, SPI1 IRQHandler
        DCD     I2C0_IRQHandler           ;45, I2C0 IRQHandler
        DCD     0                         ;46, Reserved
        DCD     CCM_IRQHandler            ;47, CCM IRQHandler

        
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        THUMB

        PUBWEAK Reset_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(2)
Reset_IRQHandler
        LDR     R0, =RegInit
        BLX     R0
        LDR     R0, =SystemInit
        BLX     R0
        LDR     R0, =__iar_program_start
        BX      R0
        
        PUBWEAK NMI_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
NMI_IRQHandler
        B NMI_IRQHandler

        PUBWEAK HardFault_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HardFault_IRQHandler
        B HardFault_IRQHandler

        PUBWEAK SVC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SVC_IRQHandler
        B SVC_IRQHandler

        PUBWEAK PendSV_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
PendSV_IRQHandler
        B PendSV_IRQHandler

        PUBWEAK SysTick_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SysTick_IRQHandler
        B SysTick_IRQHandler

        PUBWEAK PINT0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
PINT0_IRQHandler
        B PINT0_IRQHandler

        PUBWEAK PINT1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
PINT1_IRQHandler
        B PINT1_IRQHandler

        PUBWEAK PINT2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
PINT2_IRQHandler
        B PINT2_IRQHandler

        PUBWEAK PINT3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
PINT3_IRQHandler
        B PINT3_IRQHandler

        PUBWEAK PINT4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
PINT4_IRQHandler
        B PINT4_IRQHandler

        PUBWEAK PINT5_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
PINT5_IRQHandler
        B PINT5_IRQHandler

        PUBWEAK PINT6_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
PINT6_IRQHandler
        B PINT6_IRQHandler

        PUBWEAK PINT7_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
PINT7_IRQHandler
        B PINT7_IRQHandler

        PUBWEAK T16N0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
T16N0_IRQHandler
        B T16N0_IRQHandler

        PUBWEAK T16N1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
T16N1_IRQHandler
        B T16N1_IRQHandler

        PUBWEAK T16N2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
T16N2_IRQHandler
        B T16N2_IRQHandler

        PUBWEAK T16N3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
T16N3_IRQHandler
        B T16N3_IRQHandler

        PUBWEAK T32N0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
T32N0_IRQHandler
        B T32N0_IRQHandler

        PUBWEAK WDT_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
WDT_IRQHandler
        B WDT_IRQHandler

        PUBWEAK RTC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RTC_IRQHandler
        B RTC_IRQHandler

        PUBWEAK KINT_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
KINT_IRQHandler
        B KINT_IRQHandler

        PUBWEAK ADC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ADC_IRQHandler
        B ADC_IRQHandler

        PUBWEAK LVD_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LVD_IRQHandler
        B LVD_IRQHandler

        PUBWEAK PLLLK_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
PLLLK_IRQHandler
        B PLLLK_IRQHandler

        PUBWEAK UART0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
UART0_IRQHandler
        B UART0_IRQHandler

        PUBWEAK UART1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
UART1_IRQHandler
        B UART1_IRQHandler

        PUBWEAK EUART0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EUART0_IRQHandler
        B EUART0_IRQHandler

        PUBWEAK SPI0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI0_IRQHandler
        B SPI0_IRQHandler

        PUBWEAK SPI1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI1_IRQHandler
        B SPI1_IRQHandler

        PUBWEAK I2C0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C0_IRQHandler
        B I2C0_IRQHandler

        PUBWEAK CCM_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CCM_IRQHandler
        B CCM_IRQHandler

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; calibration value initial
;;
        THUMB


        SECTION .text:CODE:NOROOT:REORDER(2)
RegInit 
        PUSH  {LR}
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


IP_CAL_LOAD
        PUSH    {LR}
        LDR     R2, =0xFFFFFFFF
        LDR     R1, [R0]
        CMP     R1, R2
        BNE     IP_CAL_VERIFY    
        LDR     R1, [R0]         
        CMP     R1, R2
        BNE     IP_CAL_VERIFY    

        B       IP_CAL_EMPTY     

IP_CAL_VERIFY
        LDR      R5, =0x00000003    
        LDR      R4, =0x000000FF
IP_CAL_VERIFY_LOOP
        MOVS     R2, R1
        ANDS     R2, R4         

        LSRS     R3, R1, #8
        ANDS     R3, R4
        ADD     R2, R3        

        LSRS     R3, R1, #16
        ANDS     R3, R4
        ADD     R2, R3        
        ANDS     R2, R4

        LSRS     R3, R1, #24   

        CMP      R2, R3        
        BEQ      IP_LOAD_OK
        SUBS     R5, #1
        BEQ      IP_CAL_EMPTY    
        LDR      R1, [R0]         
        B        IP_CAL_VERIFY_LOOP

IP_LOAD_OK
        STR      R1, [R7]

IP_CAL_EMPTY
        POP      {PC}


                
        END
;************************ (C) COPYRIGHT Eastsoft *****END OF FILE*****
