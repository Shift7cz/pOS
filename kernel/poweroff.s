shutdown:
    li   t0, 0x100000
    li   t1, 0x5555
    sw   t1, 0(t0)
    j    shutdown
