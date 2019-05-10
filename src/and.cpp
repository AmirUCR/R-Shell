#include "../header/and.hpp"

And::And(Command* lhs, Command* rhs) {
    this->lhsCMD = lhs;
    this->rhsCMD = rhs;
}

// The And only executes rhs if lhs fails.
bool And::execute() {

    // We call both lhs and rhs commands to execute.
    // We only execute the rhs command if lhs succeeds.
    // If both lhs and rhs succeed, return true.
    if (lhsCMD->execute()) {
        if(rhsCMD->execute()) {
            return true;
        }
    }

    return false;
}