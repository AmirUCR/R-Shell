#ifndef OUTPUT_REDIRECTOR_APPEND_HPP
#define OUTPUT_REDIRECTOR_APPEND_HPP
#include "connector.hpp"

using namespace std;

// <
class OutputRedirectorAppend : public Connector {
    public:
    OutputRedirectorAppend();    // Initialize
    void SetLeft(Command*);
    void SetRight(Command*);
    bool execute();             // Only return true if left child
                                // and right child execute both return true
};

#endif  // END OF OUTPUT_REDIRECTOR_APPEND_HPP