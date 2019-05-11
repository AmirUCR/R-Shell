#include "../header/or.hpp"

// The Or only executes rhs if lhs fails.
bool Or::execute() {

    // If lhs fails, execute rhs. If rhs succeeds, return true.
    if (!lhsCMD->execute()) {
        if (rhsCMD->execute()) {
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