#ifndef SEMICOLON_HPP
#define SEMICOLON_HPP
#include "connector.hpp"

using namespace std;

class Semicolon : public Connector {
    public:
    Semicolon() : Connector() {};    // Initialize
    void SetLeft(Command*);
    void SetRight(Command*);
    bool execute();             // Only return true if left child
                                // and right child execute both return true
};

#endif  // END OF SEMICOLON_HPP