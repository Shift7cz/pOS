#include "command.h"
#include "uart.h"
#include "string.h"
#include "asmCall.c"

void kmain(void);

static int helloCmd(void) {
    uartPuts("\n\"Hello World!\"\n");
    return 0; // means continue
}

static int addrCmd(void) {
    uartPuts("\nAddress of kmain is: ");
    uartPutHex((unsigned long)kmain); // gets the adress of kmain in ram
    uartPuts("\n");
    return 0;
}

static int poweroffCmd(void) {
    uartPuts("\nExiting...\n");
    shutdown();
    return 0;
}

int runCommand(const char *line) {
    static const struct Command commands[] = {
        {"sayhello", helloCmd},
        {"addr", addrCmd},
        {"poweroff", poweroffCmd},
    };

    for (int i = 0; i < sizeof(commands) / sizeof(commands[0]); i++) {
        if (strEq(commands[i].name, line)) {
            uartPuts("\nRunning command at address: ");
            uartPutHex((unsigned long)commands[i].run);
            return commands[i].run();
        }
    }
    uartPuts("\nUnknown command\n");
    return 0;
}
