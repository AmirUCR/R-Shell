#include "../header/pipe.hpp"
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <iostream>

bool Pipe::execute() {
// All yours, JJ
}

void Pipe::SetLeft(Command* c) {
    this->lhsCMD = c;
}

void Pipe::SetRight(Command* c) {
    this->rhsCMD = c;
}