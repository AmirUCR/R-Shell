#ifndef COMMAND_H
#define COMMAND_H

class Command {
    public: 
    virtual bool execute() = 0;
    virtual void whoAmI() = 0;
};

#endif