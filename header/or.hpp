#ifndef OR_HPP
#define OR_HPP
#include "connector.hpp"

class Or : public Connector {
    public:
    Or() : Connector() {};    // Initialize
    void SetLeft(Command*);
    void SetRight(Command*);
    bool execute(int input_fd, int output_fd);             // Only return true if left child
                                                            // and right child execute both return true
    const char * getExecName();
};

#endif  // END OF OR_HPP