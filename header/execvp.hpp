#ifndef EXECVP_HPP
#define EXECVP_HPP

#include "executable.hpp"

class Execvp: public Executable {
    public:
    Execvp(const char* execName, char** argList) : Executable(execName, argList) {}

    bool execute();
}; 

#endif