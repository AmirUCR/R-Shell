#ifndef PIPE_HPP
#define PIPE_HPP
#include "connector.hpp"

using namespace std;

class Pipe : public Connector {
    public:
    Pipe();    // Initialize
    void SetLeft(Command*);
    void SetRight(Command*);
    bool execute();             // Only return true if left child
                                // and right child execute both return true
};

#endif  // END OF PIPE_HPP