#define UART_BASE 0x10000000UL

void uartPutc(char c) { // writes a single char
    volatile char *uart = (volatile char *)UART_BASE;

    while (!(uart[5] & 0x20)) {} // waits till uart is empty

    *uart = c;
}

char uartGetc(void) {
    volatile unsigned char *uart = (volatile unsigned char *)UART_BASE;

    while (!(uart[5] & 0x01)) {} // waits till uart is empty

    return *uart;
}

void uartPuts(const char s[]) { // writes char s[]
    while (*s != '\0') { // loops until string is over
        uartPutc(*s++);
    }
}

void kmain(void) {
    uartPuts("\nWelcome to pOS!!!\n"); // "" annotation automatically adds \0

    while (1) {
        uartPutc(uartGetc());
        //uartGetc();
    }
}