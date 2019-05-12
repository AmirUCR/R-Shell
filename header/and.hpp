#ifndef AND_H
#define AND_H
#include "connector.hpp"

using namespace std;

class And : public Connector {
    public:
    And() : Connector() {};    // Initialize
    void SetLeft(Command*);
    void SetRight(Command*);
    bool execute();             // Only return true if left child
                                // and right child execute both return true
                                void whoAmI() {
        return;
    }
};

#endif  // END OF AND_H