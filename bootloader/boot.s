.section .text
.global _start
.equ UART, 0x10000000
#right now it just writes hi and loops
_start:
    li   t0, 72              # 'H'
    sb   t0, UART

    li   t0, 105             # 'i'
    sb   t0, UART

loop:
    j loop
