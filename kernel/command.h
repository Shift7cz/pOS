#ifndef COMMAND_H
#define COMMAND_H

typedef int (*CommandFn)(void); // creates a new type that's a pointer to a command function

struct Command {
    const char *name;
    CommandFn run;
};

int runCommand(const char *line);

#endif //_COMMAND_H
