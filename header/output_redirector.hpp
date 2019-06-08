#ifndef OUTPUT_REDIRECTOR_HPP
#define OUTPUT_REDIRECTOR_HPP
#include "connector.hpp"

// >
class OutputRedirector : public Connector {
    public:
    OutputRedirector();    // Initialize
    void SetLeft(Command*);
    void SetRight(Command*);
    bool execute(int input_fd, int output_fd);
    const char * getExecName();
};

#endif  // END OF OUTPUT_REDIRECTOR_HPP