.section .text
.global _start
.equ UART, 0x10000000
#right now it just writes pOS and loops
_start:
    li  t0, UART
    li   t1, 'p'              
    sb   t1, 0(t0)

    li   t1, 'O'             
    sb   t1, 0(t0)

    li   t1, 'S'            
    sb   t1, 0(t0)

loop:
    j loop
