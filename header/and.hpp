#ifndef AND_HPP
#define AND_HPP
#include "connector.hpp"

class And : public Connector {
    public:
    And() : Connector() {};    // Initialize
    void SetLeft(Command*);
    void SetRight(Command*);
    bool execute(int input_fd, int output_fd);             // Only return true if left child
                                                        // and right child execute both return true
    const char * getExecName();
};

#endif  // END OF AND_HPP