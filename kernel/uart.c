#define UART_BASE 0x10000000UL
#include "uart.h"

void uartPutc(char c) { // writes a single char
    volatile unsigned char *uart = (volatile unsigned char *)UART_BASE;

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