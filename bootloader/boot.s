.section .text
.global _start
.equ UART, 0x10000000

_start:
    la   sp, stack_top      # point sp at the TOP of our stack (it grows down)

    li  t0, UART

    li   t1, 'b'            # writes 'booting...'
    sb   t1, 0(t0)
    li   t1, 'o'
    sb   t1, 0(t0)
    li   t1, 'o'
    sb   t1, 0(t0)
    li   t1, 't'
    sb   t1, 0(t0)
    li   t1, 'i'
    sb   t1, 0(t0)
    li   t1, 'n'
    sb   t1, 0(t0)
    li   t1, 'g'
    sb   t1, 0(t0)
    li   t1, '.'
    sb   t1, 0(t0)
    li   t1, '.'
    sb   t1, 0(t0)
    li   t1, '.'
    sb   t1, 0(t0)

    call kmain              # jump into C

loop:                       # safety net: if kmain ever returns, don't run into garbage
    j loop

.section .bss               # reserves 16kb for sp
.align 4
stack_bottom:
    .skip 16384
stack_top: