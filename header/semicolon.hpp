#ifndef SEMICOLON_H
#define SEMICOLON_H
#include "connector.hpp"

using namespace std;

class Semicolon : public Connector {
    public:
    Semicolon(Command*, Command*) : Connector() {};    // Initialize
    bool execute();             // Only return true if left child
                                // and right child execute both return true
};

#endif  // END OF SEMICOLON_H