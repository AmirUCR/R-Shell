#ifndef PIPE_HPP
#define PIPE_HPP
#include "connector.hpp"

class Pipe : public Connector {
    public:
    Pipe();    // Initialize
    void SetLeft(Command*);
    void SetRight(Command*);
    bool execute(int input_fd, int output_fd);             // Only return true if left child
                                                            // and right child execute both return true
    const char * getExecName();
};

#endif  // END OF PIPE_HPP