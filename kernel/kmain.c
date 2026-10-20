#include "uart.h"
#include "string.h"
#define INPUT_BUFFER_SIZE 64

void kmain(void); // kmain at the top o it cna be accessed

int dummyCommands(char str[]) {
    if (strEq(str, "sayhello")) {
        uartPuts("\n\"Hello World!\"\n");
        return 0; // means continue
    }
    if (strEq(str, "exit")) {
        uartPuts("\nExiting...\n");
        return 1; // means shutdown
    }
    if (strEq(str, "addr")) {
        uartPuts("\nAddress of kmain is: ");
        uartPutHex((unsigned long)kmain); // gets the adress of kmain in ram
        uartPuts("\n");
        return 0;
    }
    // etc

    uartPuts("\nUnknown command\n");
    return 0;
}

void kmain(void) {
    uartPuts("\nWelcome to pOS!!!\n"); // "" annotation automatically adds \0
    uartPutc('\n');

    char inputBuffer[INPUT_BUFFER_SIZE] = {0}; // 64 byte input buffer filled with '\0'
    int count = 0; // current position in the input buffer

    while (1) {
        char c = uartGetc();

        if (c == '\r' || c == '\n') {
            int msg = dummyCommands(inputBuffer);

            if (msg == 1) {
                uartPuts("[![FAKE SHUTDOWN]]!"); // idk how to quit properly
                return;
            } // etc, this can also be a switch

            for (int i = 0; i < INPUT_BUFFER_SIZE; i++) {
                inputBuffer[i] = 0; // resets input buffer to '\0'
            }
            count = 0;
        }
        else if (c == 0x7F || c == 0x08) { // backspace not working properly for some reson idk how to do backspace
            if (count > 0) {
                count--;
                inputBuffer[count] = '\0';
                uartPuts("\b \b"); // Deletes previous character
            }
        }
        else {
            inputBuffer[count] = c;

            if (count == INPUT_BUFFER_SIZE - 1) { // prevents overflow
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
            if (c >= 32 && c < 127) {
                uartPutc(c); // writes back what the user wrote, if its a letter
            }
        }
    }
}