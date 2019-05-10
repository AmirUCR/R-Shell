#ifndef EXECUTABLE_H
#define EXECUTABLE_H

#include "command.hpp"


class Executable: public Command{

    private: 
    
    char* [] argList;
    string execName; 
 
    public: 

    Executable(string execName, char* [] argList){
        this->execName = execName; 
        this->argList = argList; 
    }

    bool execute(); 

}; 

#endif
