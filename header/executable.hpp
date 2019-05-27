#ifndef EXECUTABLE_HPP
#define EXECUTABLE_HPP

#include "command.hpp"

class Executable: public Command {
    protected: 
    char** argList;
    const char* execName; 
    bool successExec;

    public:
    Executable(const char* execName, char** argList) : Command() {
        this->execName = execName;
        this->argList = argList;
        this->successExec = true;
    }

    virtual bool execute();
}; 

#endif