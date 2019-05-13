#ifndef OR_H
#define OR_H
#include "connector.hpp"

using namespace std;

class Or : public Connector {
    public:
    Or() : Connector() {};    // Initialize
    void SetLeft(Command*);
    void SetRight(Command*);
    bool execute();             // Only return true if left child
                                // and right child execute both return true
    void whoAmI() {
        return;
    }
};

#endif  // END OF OR_H