#ifndef COMMAND_H
#define COMMAND_H
#include "command.hpp"

using namespace std;

class Connector : public Command {
    protected:
    bool lhsEval;   // Determine if left child succeeded
    bool rhsEval;   // If right child succeeded

    Command* lhsCMD;    // left child
    Command* rhsCMD;    // right child

    public:
    Connector(Command*, Command*);  // Save lhs and rhs commands
    bool execute();
};


#endif // END OF COMMAND_H