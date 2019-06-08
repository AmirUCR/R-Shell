#ifndef EXECVP_HPP
#define EXECVP_HPP

#include "executable.hpp"

class Execvp: public Executable {
    public:
    Execvp(const char* execName, char** argList, int argListSize) : Executable(execName, argList, argListSize) {}
    bool execute(int input_fd, int output_fd);
    const char * getExecName();
}; 

#endif