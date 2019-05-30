#ifndef TEST_HPP
#define TEST_HPP

#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h> 
#include <sys/types.h>
#include "executable.hpp"

class Test_cmd : public Executable {
    public: 
    Test_cmd(const char* execName, char** argList, int argListSize) : Executable(execName, argList, argListSize) {}

    bool execute();
};

#endif