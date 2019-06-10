#include "../header/test_cmd.hpp"
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std; 

bool Test_cmd::execute(int input_fd, int output_fd) {
    bool status; 
    struct stat buf;

    if (argListSize < 3) {
        cout << "(False)" << endl;
        return false;
    }
    
    //if a flag is passed in 
    if (strcmp(this->argList[1], "-e") == 0 || strcmp(this->argList[1], "-f") == 0 || strcmp(this->argList[1], "-d") == 0) {
        
        if (argListSize < 4) {
            cout << "(False)" << endl;
            return false;
        }

        int input_dup2_status = dup2(input_fd, 0);

        if (input_dup2_status < 0) {
            std::cerr << "In class Test_cmd: Bad input file descriptor.\n";
            return false;
        }

        int output_dup2_status = dup2(output_fd, 1);

        if (output_dup2_status < 0) {
            std::cerr << "In class Test_cmd: Bad output file descriptor.\n";
            return false;
        }

        if (stat(argList[2], &buf) == 0) {
            if (strcmp(this->argList[1], "-f") == 0) {
                status = S_ISREG(buf.st_mode); 
            }
            else if (strcmp(this->argList[1], "-d") == 0) {
                status = S_ISDIR(buf.st_mode); 
            }
            else {
                status = S_ISDIR(buf.st_mode) || S_ISREG(buf.st_mode);
            }

            if (status) {
                cout << "(True)" << endl;
                return true; 
            }
            else {
                cout << "(False)" << endl;
                return false; 
            }
        }
        else {
            cout << "(False)" << endl;
            return false; 
        }
    }
    //if no flag is passed in default to -e
    else {
        if (stat(argList[1], &buf) == 0) {

            int input_dup2_status = dup2(input_fd, 0);

            if (input_dup2_status < 0) {
                std::cerr << "In class Test_cmd: Bad input file descriptor.\n";
                return false;
            }

            int output_dup2_status = dup2(output_fd, 1);

            if (output_dup2_status < 0) {
                std::cerr << "In class Test_cmd: Bad output file descriptor.\n";
                return false;
            }
            status = S_ISDIR(buf.st_mode) || S_ISREG(buf.st_mode);
            
            if (status) {
                cout << "(True)" << endl; 
                return true; 
            }
            else {
                cout << "(False)" << endl; 
                return false; 
            }
        }
        else {
            cout << "(False)" << endl; 
            return false; 
        }
    }
}

const char * Test_cmd::getExecName() {
    return this->execName;
}