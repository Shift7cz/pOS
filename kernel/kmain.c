#include "uart.h"
#include "string.h"
#define INPUT_BUFFER_SIZE 64

void dummyCommands(char str[]) {
    if (strcmp(str, "tst")) {
        uartPuts("\n\"Hello World!\"\n");
    }
    // etc
    else {
        uartPuts("\nUnknown command\n");
    }
}

void kmain(void) {
    uartPuts("\nWelcome to pOS!!!\n"); // "" annotation automatically adds \0

    char inputBuffer[INPUT_BUFFER_SIZE] = {0}; // 64 byte input buffer filled with '\0'
    int count = 0; // current position in the input buffer

    while (1) {
        char c = uartGetc();

        if (c == '\r') {
            dummyCommands(inputBuffer);

            for (int i = 0; i < INPUT_BUFFER_SIZE; i++) {
                inputBuffer[i] = 0; // resets input buffer to '\0'
            }
            count = 0;
        }
        else {
            inputBuffer[count] = c;

            if (count == INPUT_BUFFER_SIZE) { // prevents overflow
                uartPuts("\nInput buffer full\n");
                for (int i = 0; i < INPUT_BUFFER_SIZE; i++) {
                    inputBuffer[i] = 0; // resets input buffer to '\0'
                }
                count = 0;
            }
            else {
                count++;
                inputBuffer[count] = '\0';
            }

            uartPutc(c); // writes back what the user wrote
        }
    }
}