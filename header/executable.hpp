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
    Executable(const char* execName, char** argList, int argListSize);
    const char * getName();
    bool execute(int input_fd, int output_fd);
    const char * getExecName();
}; 

#endif