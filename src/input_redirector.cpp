#include "../header/input_redirector.hpp"
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <iostream>

InputRedirector::InputRedirector() : Connector() {}

bool InputRedirector::execute(int input_fd, int output_fd) {
    if (rhsCMD && lhsCMD) {
        const char * execName = rhsCMD->getExecName(); // get name of right side command
        input_fd = open(execName, O_RDONLY, 0644);

        if (input_fd > -1) {
            int status;
            pid_t pid = fork();

            if (pid < 0) {
                std::cerr << "In class Input Redirector: Failed to fork.\n";
            }

            if (pid == 0) {
                lhsCMD->execute(input_fd, output_fd);
                exit(EXIT_FAILURE);
            }

            else {
                waitpid(pid, &status, 0);   // Wait for child process to terminate

                // Return whether child process terminated normally
                if (WIFEXITED(status)) {
                    return true; 
                } else {
                    //cout << lhs->getname << " command not found"
                    return false; 
                }
            }
        } else {
            std::cerr << "r'shell: " << execName << ": No such file or directory\n";
            return false;
        }

        close(input_fd);                // Close our file
    }

    return false;
}

void InputRedirector::SetLeft(Command* c) {
    this->lhsCMD = c;
}
void InputRedirector::SetRight(Command* c) {
    this->rhsCMD = c;
}

const char * InputRedirector::getExecName() {}