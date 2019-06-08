#include "test_cmd.cpp"
#include "execvp.cpp"
#include <cstring>
#include <algorithm>
#include "../header/executable.hpp"
#include <iostream>

Executable::Executable(const char* execName, char** argList, int argListSize) : Command() {
        this->execName = execName;
        this->argList = argList;
        this->successExec = true;
        this->argListSize = argListSize;
}

bool Executable::execute(int input_fd = 0, int output_fd = 1) {
    bool successFail = false;

    // if execName == test, instantiate test -- return test->execute
    if (strcmp(this->execName, "test") == 0) {
        Test_cmd* t = new Test_cmd(execName, argList, argListSize);
        successFail = t->execute(input_fd, output_fd);
    
        delete t;
        t = 0;

        return successFail;
    } else {
        Execvp* e = new Execvp(execName, argList, argListSize);
        successFail = e->execute(input_fd, output_fd);

        delete e;
        e = 0;

        return successFail;
    }
}

const char * Executable::getExecName() {
    return this->execName;
}