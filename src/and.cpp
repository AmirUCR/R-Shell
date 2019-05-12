#include "../header/and.hpp"

// The And only executes rhs if lhs fails.
bool And::execute() {
    //cout << "Execute AND\n";

    // We call both lhs and rhs commands to execute.
    // We only execute the rhs command if lhs succeeds.
    // If both lhs and rhs succeed, return true.
    if (this->lhsCMD->execute()) {
        if (this->rhsCMD->execute()) {
            return true;
        }
    }

    return false;
}

void And::SetLeft(Command* c) {
    this->lhsCMD = c;
}
void And::SetRight(Command* c) {
    this->rhsCMD = c;
}