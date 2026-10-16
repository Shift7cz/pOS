.section .text
.global _start
.equ UART, 0x10000000
#right now it just writes hi and loops
_start:
    li   t0, 112              # 'p'
    sb   t0, UART

    li   t0, 79             # 'O'
    sb   t0, UART

    li   t0, 83             # 'S'
    sb   t0, UART

loop:
    j loop
