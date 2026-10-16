.section .text
.global _start
.equ UART, 0x10000000
#right now it just writes pOS and loops
_start:
    li   t0, 'p'              
    sb   t0, UART

    li   t0, 'O'             
    sb   t0, UART

    li   t0, 'S'            
    sb   t0, UART

loop:
    j loop
