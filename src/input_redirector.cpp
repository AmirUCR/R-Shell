#include "../header/input_redirector.hpp"
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <iostream>

InputRedirector::InputRedirector() : Connector() {}

bool InputRedirector::execute() {
    bool successFail = false;

    if (rhsCMD && lhsCMD) {
        int stdin_copy = dup(0);
        close(0);   // Release stdin

        // TODO:  FIX THIS 
        const char * execName = static_cast<const char *>("text.txt"); // get name of right side command
        int fdin = open(execName, O_RDONLY, 0644);

        if (fdin > -1) {
            int status;
            pid_t pid = fork();

            if (pid < 0) {
                perror("Failure to fork");
            }

            if (pid == 0) {
                lhsCMD->execute();
                exit(1);
            }

            else {
                waitpid(pid, &status, 0);   // Wait for child process to terminate

                // Return whether child process terminated normally
                if (WIFEXITED(status)) {
                    successFail = true; 
                } else {
                    //cout << lhs->getname << " command not found"
                    successFail = false; 
                }
            }
        } else {
            std::cout << "r'shell: " << execName << ": No such file or directory\n";
            successFail = false;
        }

        close(fdin);                // Close our file
        dup2(stdin_copy, 0);        // Put stdin back where it belongs
        close(stdin_copy);          // Close the copy
    }

    return successFail;
}

void InputRedirector::SetLeft(Command* c) {
    this->lhsCMD = c;
}
void InputRedirector::SetRight(Command* c) {
    this->rhsCMD = c;
}