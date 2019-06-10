#include "../header/output_redirector.hpp"
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <iostream>

OutputRedirector::OutputRedirector() : Connector() {}

// default input_fd = 0, default output_fd = 1
bool OutputRedirector::execute(int input_fd, int output_fd) {
    if (rhsCMD && lhsCMD) {
        const char * execName = rhsCMD->getExecName(); // get name of left side command
        output_fd = open(execName, O_WRONLY | O_CREAT | O_TRUNC, 0644);

        if (output_fd > -1) {
            int status;
            pid_t pid = fork();

            if (pid < 0) {
                std::cerr << "In class Output Redirector: Failed to fork.\n";
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

void OutputRedirector::SetLeft(Command* c) {
    this->lhsCMD = c;
}
void OutputRedirector::SetRight(Command* c) {
    this->rhsCMD = c;
}

const char * OutputRedirector::getExecName() {}