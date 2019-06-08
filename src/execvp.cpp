#include "../header/execvp.hpp" 
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <cstring>
#include <iostream>

using std::cerr;

bool Execvp::execute(int input_fd, int output_fd) {

    int status; 
    pid_t pid = fork();
    
    if (strcmp(this->execName, "exit") == 0) {
        exit(EXIT_SUCCESS); 
    }

    if (pid < 0) {
        std::cerr << "In class Execvp: Failed to fork.\n";
        return false;
    }
 
    if (pid == 0) {
        int input_dup2_status = dup2(input_fd, 0);

        if (input_dup2_status < 0) {
            std::cerr << "In class Execvp: Bad input file descriptor.\n";
            exit(EXIT_FAILURE);
        }

        int output_dup2_status = dup2(output_fd, 1);

        if (output_dup2_status < 0) {
            std::cerr << "In class Execvp: Bad output file descriptor.\n";
            exit(EXIT_FAILURE);
        }

        int execvp_status = execvp(this->execName, this->argList);

        if (execvp_status < 0) {
            std::cerr << "Execvp failed.\n";
            exit(EXIT_FAILURE); 
        }
    }

    else {
        waitpid(pid, &status, 0);
        
        if (WIFEXITED(status)) {
            return true;
        }

        std::cerr << execName << ": command not found\n";
        return false;  
    }
}

const char * Execvp::getExecName() {}