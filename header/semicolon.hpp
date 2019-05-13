#ifndef SEMICOLON_H
#define SEMICOLON_H
#include "connector.hpp"

using namespace std;

class Semicolon : public Connector {
    public:
    Semicolon() : Connector() {};    // Initialize
    void SetLeft(Command*);
    void SetRight(Command*);
    bool execute();             // Only return true if left child
                                // and right child execute both return true
        void whoAmI() {
        return;
    }
};

#endif  // END OF SEMICOLON_H