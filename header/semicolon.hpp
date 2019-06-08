#ifndef SEMICOLON_HPP
#define SEMICOLON_HPP
#include "connector.hpp"

class Semicolon : public Connector {
    public:
    Semicolon() : Connector() {};    // Initialize
    void SetLeft(Command*);
    void SetRight(Command*);
    bool execute(int input_fd, int output_fd);             // Only return true if left child
                                                            // and right child execute both return true
    const char * getExecName();
};

#endif  // END OF SEMICOLON_HPP