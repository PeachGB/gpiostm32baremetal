.syntax unified
.cpu cortex-m3
.thumb

.global Reset_Handler
.global Default_Handler

.section .text.Reset_Handler
.type Reset_Handler, %function

Reset_Handler:
  ldr r0, =_sdata // data start in ram
  ldr r1, =_edata // data end in ram
  ldr r2, =_sidata // data start in flash
  movs r3, #0 //offset for loop

Copy_Data:
  adds r4, r0, r3 //adds offset to data start in ram, store it on r4
  cmp r4, r1 // checks if current r4 is end of data in ram
  bcc Copy_Data_Word // if no flag call copy_data_word
  b Zero_Bss //go to next loop if r4 is end of data

Copy_Data_Word:
  ldr r4, [r2, r3] //load data from flash + offset on r4
  str r4, [r0,r3] //stores data from r4 into memory on data start + offset
  adds r3, r3, #4 //adds 4 to offset
  b Copy_Data //loops in copy_data until all data is copied

Zero_Bss: 
  ldr r0, =_sbss // start bss on r0
  ldr r1, =_ebss // end bss on r1
  movs r2, #0 //0 to r2

Zero_Bss_Loop:
  cmp r0, r1 //if r0 is end bss set flag
  bcc Zero_Bss_Word // if no flag calls zero_bss_word
  b start_main //if loop is over start main

Zero_Bss_Word:
str r2, [r0] //stores 0 on r0
adds r0, r0, #4 //offsets r0 by 4
b Zero_Bss_Loop //loops 


start_main:
  bl main  //calls c main

hang:
  b hang //main c func should not return 


.size Reset_Handler, .-Reset_Handler


.section .text.Default_Handler
.type Default_Handler, %function

Default_Handler:
  b Default_Handler

.size Default_Handler, .-Default_Handler



.section .isr_vector, "a",%progbits
.type g_pfnVectors, %object

g_pfnVectors: //vector table
  .word _estack //top of stack 0x20005000 
  .word Reset_Handler //Reset handler address
  // all other not defined handlers calls the Default_Handler you should define them as needed
  .word Default_Handler    /* NMI */         
  .word Default_Handler    /* HardFault */
  .word Default_Handler    /* MemManage */
  .word Default_Handler    /* BusFault */
  .word Default_Handler    /* UsageFault */

  .word 0
  .word 0
  .word 0
  .word 0

  .word Default_Handler    /* SVC */
  .word Default_Handler    /* DebugMon */

  .word 0

  .word Default_Handler    /* PendSV */
  .word Default_Handler    /* SysTick */
