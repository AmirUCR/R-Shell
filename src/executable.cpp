#include "test_cmd.cpp"
#include "execvp.cpp"
#include <cstring>
#include <algorithm>
#include "../header/executable.hpp"

using namespace std;

bool Executable::execute() {

    // if execName == test, instantiate test -- return test.execute
    if (strcmp(this->execName, "test") == 0) {
        Test_cmd* t = new Test_cmd(execName, argList);
        return t->execute();
    } else {
        Execvp* e = new Execvp(execName, argList);
        return e->execute();
    }
}
