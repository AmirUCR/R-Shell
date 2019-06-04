#ifndef AND_HPP
#define AND_HPP
#include "connector.hpp"

using namespace std;

class And : public Connector {
    public:
    And() : Connector() {};    // Initialize
    void SetLeft(Command*);
    void SetRight(Command*);
    bool execute();             // Only return true if left child
                                // and right child execute both return true
};

#endif  // END OF AND_HPP