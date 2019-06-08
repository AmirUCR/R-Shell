#include "../header/pipe.hpp"
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <iostream>

Pipe::Pipe() : Connector() {}

// Piping hot
bool Pipe::execute(int input_fd, int output_fd) {
    if (rhsCMD && lhsCMD) {
        int f_desc[2];
        int pipe_status = pipe(f_desc);

        if (pipe_status < 0) {
            std::cerr << "In class Pipe: Failed to create pipe.\n";
            return false;
        }

        if (lhsCMD->execute(input_fd, f_desc[1])) {
            close(f_desc[1]);
            if (rhsCMD->execute(f_desc[0], output_fd)) {
                close(f_desc[0]);
                return true;
            }

            return false;
        }

        return false;
    }

    std::cerr << "In class Pipe: One of left hand side or right hand side is missing.\n";
    return false;
}

void Pipe::SetLeft(Command* c) {
    this->lhsCMD = c;
}

void Pipe::SetRight(Command* c) {
    this->rhsCMD = c;
}

const char * Pipe::getExecName() {}