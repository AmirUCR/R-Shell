#include "../header/semicolon.hpp"

Semicolon::Semicolon(Command* lhs, Command* rhs) {
    this->lhsCMD = lhs;
    this->rhsCMD = rhs;
}

// The Seimicolon executes both lhs and rhs
bool Semicolon::execute() {
    bool lhs_flag = false;
    bool rhs_flag = false;

    if (lhsCMD->execute()) {
        lhs_flag = true;
    }

    if (rhsCMD->execute()) {
        rhs_flag = true;
    }

    // If both lhs and rhs did not succeed (false), then return false.
    if (lhs_flag || rhs_flag) {
        return true;
    } else {
        return false;
    }
}