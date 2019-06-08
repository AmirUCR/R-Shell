#ifndef CONNECTOR_H
#define CONNECTOR_H
#include "command.hpp"

class Connector : public Command {
    public:
    Command* lhsCMD = 0;    // left child
    Command* rhsCMD = 0;    // right child

    public:
    Connector() : Command() {};
    virtual void SetLeft(Command*) = 0;
    virtual void SetRight(Command*) = 0;
    virtual bool execute(int input_fd, int output_fd) = 0;
    virtual const char * getExecName() = 0;
};


#endif // END OF CONNECTOR_H