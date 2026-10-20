.section .text
.global _start
.equ UART, 0x10000000 

_start:
    la   sp, stack_top      # point sp at the TOP of our stack (it grows down)

    li   t0, UART          #load UART address into t0
    la   t1, boot_text     #load boot text pointer into t1

   boot_text_loop:
   lbu   t2, 0(t1)          #load byte from boot_text to t2
   beqz   t2, after_boot_text  #if t2 is 0 exit loop
   sb   t2, 0(t0)            #load t2 to UART
   addi  t1, t1, 1            #move pointer once
   j boot_text_loop


after_boot_text:

    call kmain              # jump into C

loop:                       # safety net: if kmain ever returns, don't run into garbage
    j loop


boot_text: .string "booting...\n" 

.section .bss               # reserves 16kb for sp
.align 4
stack_bottom:
    .skip 16384
stack_top:
