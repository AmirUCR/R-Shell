#ifndef INPUT_REDIRECTOR_HPP
#define INPUT_REDIRECTOR_HPP
#include "connector.hpp"

using namespace std;

// >
class InputRedirector : public Connector {
    public:
    InputRedirector();    // Initialize
    void SetLeft(Command*);
    void SetRight(Command*);
    bool execute();             // Only return true if left child
                                // and right child execute both return true
};

#endif  // END OF INPUT_REDIRECTOR_HPP