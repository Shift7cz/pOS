#ifndef UART_H
#define UART_H

void uartPutc(char c);
char uartGetc(void);
void uartPuts(const char s[]);
void uartPutHex(unsigned long hex); // not implemented

#endif //UART_H
