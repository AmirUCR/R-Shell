#ifndef EXECUTABLE_H
#define EXECUTABLE_H

#include "command.hpp"
#include <string>

using namespace std; 

class Executable: public Command{

    private: 
    
    char** argList;
    const char* execName; 
    bool successExec; 
    public: 

    Executable(const char* execName, char** argList){
        this->execName = execName; 
        this->argList = argList;
        this->successExec = true;  
    }

    bool execute(); 

}; 

#endif
