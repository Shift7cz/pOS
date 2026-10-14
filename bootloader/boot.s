.section .text
.global _start
#right now it just writes hi and loops
_start:
    li   t0, 0x10000000    # UART adress
    li   t1, 72              # 'H'
    sb   t1, 0(t0)

    li   t1, 105             # 'i'
    sb   t1, 0(t0)

loop:
    j loop
