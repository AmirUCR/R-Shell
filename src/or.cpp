#ifndef OR_H
#define OR_H
#include "../header/or.hpp"

Or::Or(Command* lhs, Command* rhs) {
    this->lhsCMD = lhs;
    this->rhsCMD = rhs;
}

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


#endif // END OF OR_H