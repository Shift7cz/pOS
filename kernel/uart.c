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

void uartPutHex(unsigned long hex) {
    const char *digits = "0123456789abcdef";
    uartPuts("0x");
    _Bool hasStarted = 0;

    for (int shift = 60; shift >= 0; shift -= 4) {
        int i = (hex >> shift) & 0xF; // grabs 4 bits
        char c = digits[i];

        if (c == '0') {
            if (hasStarted) uartPutc(c);
        }
        else {
            if (!hasStarted) hasStarted = 1;
            uartPutc(c);
        }
    }
}