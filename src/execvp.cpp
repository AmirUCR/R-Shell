#include "../header/execvp.hpp" 
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <cstring>
#include <iostream>

using namespace std;

bool Execvp::execute() {

    int status; 
    pid_t pid = fork(); 
    
    if (strcmp(this->execName, "exit") == 0) {
        exit(0); 
    }

    if (pid < 0) {
        perror("Failure to fork");
    }
 
    if (pid == 0) {
        execvp(this->execName, this->argList);
        exit(1); 
    }

    else {
        waitpid(pid, &status, 0);
        
        if (WIFEXITED(status)) {
            return true;
        }

        cout << execName << ": command not found\n";
        return false;  
    }
}

