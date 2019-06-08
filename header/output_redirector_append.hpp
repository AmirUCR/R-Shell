#ifndef OUTPUT_REDIRECTOR_APPEND_HPP
#define OUTPUT_REDIRECTOR_APPEND_HPP
#include "connector.hpp"

// >>
class OutputRedirectorAppend : public Connector {
    public:
    OutputRedirectorAppend();    // Initialize
    void SetLeft(Command*);
    void SetRight(Command*);
    bool execute(int input_fd, int output_fd);
    const char * getExecName();
};

#endif  // END OF OUTPUT_REDIRECTOR_APPEND_HPP