#ifndef CONNECTOR_H
#define CONNECTOR_H
#include "command.hpp"

using namespace std;

class Connector : public Command {
    protected:
    bool lhsEval;   // Determine if left child succeeded
    bool rhsEval;   // If right child succeeded

    Command* lhsCMD;    // left child
    Command* rhsCMD;    // right child

    public:
    Connector() : Command() {};
    virtual void SetLeft(Command*) = 0;
    virtual void SetRight(Command*) = 0;
    virtual bool execute() = 0;
};


#endif // END OF CONNECTOR_H