#include "../header/or.hpp"

// The Or only executes rhs if lhs fails.
bool Or::execute(int input_fd, int output_fd) {

    // If lhs fails, execute rhs. If rhs succeeds, return true.
    if (this->lhsCMD && !this->lhsCMD->execute(input_fd, output_fd)) {
        if (this->rhsCMD && this->rhsCMD->execute(input_fd, output_fd)) {
            return true;
        }

        return false;   // If lhs and rhs fail, return false.
    }

    return true;    // If lhs succeeds, return true. Skip executing rhs.
}

void Or::SetLeft(Command* c) {
    this->lhsCMD = c;
}
void Or::SetRight(Command* c) {
    this->rhsCMD = c;
}

const char * Or::getExecName() {}