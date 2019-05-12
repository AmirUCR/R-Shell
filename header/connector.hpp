#ifndef CONNECTOR_H
#define CONNECTOR_H
#include "command.hpp"

using namespace std;

class Connector : public Command {
    public:
    Command* lhsCMD = 0;    // left child
    Command* rhsCMD = 0;    // right child

    public:
    Connector() : Command() {};
    virtual void SetLeft(Command*) = 0;
    virtual void SetRight(Command*) = 0;
    virtual bool execute() = 0;
};


#endif // END OF CONNECTOR_H