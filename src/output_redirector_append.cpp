#include "../header/output_redirector_append.hpp"
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <iostream>

OutputRedirectorAppend::OutputRedirectorAppend() : Connector() {}

bool OutputRedirectorAppend::execute(int input_fd, int output_fd) {
    if (rhsCMD && lhsCMD) {
        const char * execName = rhsCMD->getExecName(); // get name of left side command
        output_fd = open(execName, O_WRONLY | O_CREAT | O_APPEND, 0644);

        if (output_fd > -1) {
            int status;
            pid_t pid = fork();

            if (pid < 0) {
                std::cerr << "In class Output Redirector Append: Failed to fork.\n";
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

        close(output_fd);       // Close our file
    }

    return false;
}

void OutputRedirectorAppend::SetLeft(Command* c) {
    this->lhsCMD = c;
}
void OutputRedirectorAppend::SetRight(Command* c) {
    this->rhsCMD = c;
}

const char * OutputRedirectorAppend::getExecName() {}