#include "../header/semicolon.hpp"

// The Semicolon executes both lhs and rhs
bool Semicolon::execute(int input_fd, int output_fd) {
    bool lhs_flag = false;
    bool rhs_flag = false;

    if (this->lhsCMD != 0 && this->lhsCMD->execute()) {
        lhs_flag = true;
    }

    if (this->rhsCMD != 0 && this->rhsCMD->execute()) {
        rhs_flag = true;
    }

    // If neither lhs or rhs succeeded (both were false), then return false.
    if (lhs_flag || rhs_flag) {
        return true;
    } else {
        return false;
    }
}

void Semicolon::SetLeft(Command* c) {
    this->lhsCMD = c;
}
void Semicolon::SetRight(Command* c) {
    this->rhsCMD = c;
}

const char * Semicolon::getExecName() {}