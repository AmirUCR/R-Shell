#ifndef EXECUTABLE_HPP
#define EXECUTABLE_HPP

#include "command.hpp"

class Executable: public Command {
    protected: 
    char** argList;
    const char* execName; 
    bool successExec;
    int argListSize;

    public:
    Executable(const char* execName, char** argList, int argListSize) : Command() {
        this->execName = execName;
        this->argList = argList;
        this->successExec = true;
        this->argListSize = argListSize;
    }

    virtual bool execute();
}; 

#endif