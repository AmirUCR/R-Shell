#ifndef OR_HPP
#define OR_HPP
#include "connector.hpp"

using namespace std;

class Or : public Connector {
    public:
    Or() : Connector() {};    // Initialize
    void SetLeft(Command*);
    void SetRight(Command*);
    bool execute();             // Only return true if left child
                                // and right child execute both return true
};

#endif  // END OF OR_HPP