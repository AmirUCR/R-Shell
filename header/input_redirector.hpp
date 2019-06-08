#ifndef INPUT_REDIRECTOR_HPP
#define INPUT_REDIRECTOR_HPP
#include "connector.hpp"

// <
class InputRedirector : public Connector {
    public:
    InputRedirector();    // Initialize
    void SetLeft(Command*);
    void SetRight(Command*);
    bool execute(int input_fd, int output_fd);
    const char * getExecName();
};

#endif  // END OF INPUT_REDIRECTOR_HPP