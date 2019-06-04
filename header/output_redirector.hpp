#ifndef OUTPUT_REDIRECTOR_HPP
#define OUTPUT_REDIRECTOR_HPP
#include "connector.hpp"

using namespace std;

// <
class OutputRedirector : public Connector {
    public:
    OutputRedirector();    // Initialize
    void SetLeft(Command*);
    void SetRight(Command*);
    bool execute();             // Only return true if left child
                                // and right child execute both return true
};

#endif  // END OF OUTPUT_REDIRECTOR_HPP