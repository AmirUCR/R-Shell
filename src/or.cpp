#include "../header/or.hpp"

// The Or only executes rhs if lhs fails.
bool Or::execute(int input_fd, int output_fd) {

    // If lhs fails, execute rhs. If rhs succeeds, return true.
    if (this->lhsCMD != 0 && !this->lhsCMD->execute()) {
        if (this->rhsCMD != 0 && this->rhsCMD->execute()) {
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