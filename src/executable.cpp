#include "test_cmd.cpp"
#include "execvp.cpp"
#include <cstring>
#include <algorithm>
#include "../header/executable.hpp"

using namespace std;

bool Executable::execute() {
    bool successFail = false;

    // if execName == test, instantiate test -- return test.execute
    if (strcmp(this->execName, "test") == 0) {
        Test_cmd* t = new Test_cmd(execName, argList);
        successFail = t->execute();
    
        delete t;
        t = 0;

        return successFail;
    } else {
        Execvp* e = new Execvp(execName, argList);
        successFail = e->execute();

        delete e;
        e = 0;

        return successFail;
    }
}
