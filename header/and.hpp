#ifndef AND_H
#define AND_H
#include "connector.hpp"

using namespace std;

class And : public Connector {
    public:
    And(Command*, Command*) : Connector() {};    // Initialize
    bool execute();             // Only return true if left child
                                // and right child execute both return true
};

#endif  // END OF AND_H