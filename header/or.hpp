#ifndef OR_H
#define OR_H
#include "connector.hpp"

using namespace std;

class Or : public Connector {
    public:
    Or(Command*, Command*) : Connector() {};    // Initialize
    bool execute();             // Only return true if left child
                                // and right child execute both return true
};

#endif  // END OF OR_H