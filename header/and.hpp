#ifndef CONNECTOR_H
#define CONNECTOR_H
#include "connector.hpp"

using namespace std;

class And : public Connector {
    public:
    And(Command*, Command*) : Connector() {};    // Initialize
    bool execute();             // Only return true if left child
                                // and right child execute both return true
};

#endif  // END OF CONNECTOR_H