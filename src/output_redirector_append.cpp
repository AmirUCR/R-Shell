#include "../header/output_redirector_append.hpp"
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <iostream>

OutputRedirectorAppend::OutputRedirectorAppend() : Connector() {}

bool OutputRedirectorAppend::execute() {
    bool successFail = false;

    if (rhsCMD && lhsCMD) {
        int stdout_copy = dup(1);
        close(1); // Release stdout

        // TODO FIX THIS HARDCODED DOO DOO
        const char * execName = static_cast<const char *>("text2.txt"); // get name of left side command
        int fdout = open(execName, O_WRONLY | O_CREAT | O_APPEND, 0644);

        if (fdout > -1) {
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

        close(fdout);                // Close our file
        dup2(stdout_copy, 1);        // Put stdout back where it belongs
        close(stdout_copy);          // Close the copy
    }

    return successFail;
}

void OutputRedirectorAppend::SetLeft(Command* c) {
    this->lhsCMD = c;
}
void OutputRedirectorAppend::SetRight(Command* c) {
    this->rhsCMD = c;
}