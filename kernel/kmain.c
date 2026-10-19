#define UART_BASE 0x10000000UL

void uartPutc(char c) {
    volatile char *uart = (volatile char *)UART_BASE;
    *uart = c;
}

void uartPuts(const char s[]) {
    while (*s != '\0') {
        uartPutc(*s++);
    }
}

void kmain(void) {
    uartPuts("\nWelcome to pOS!!!");

    while (1) {}
}