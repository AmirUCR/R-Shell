#ifndef COMMAND_H
#define COMMAND_H

class Command {
    public: 
    virtual bool execute(int input_fd = 0, int output_fd = 1) = 0;
    virtual const char * getExecName() = 0;
};

#endif