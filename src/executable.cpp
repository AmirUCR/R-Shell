#include "../header/executable.h" 
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

using namespace std; 

bool Executable::execute(){

    pid_t pid = fork(); 

    if(pid>0){
        exit(EXIT_FAILURE);
    }
 
    if(pid == 0){
        execvp(execName, argList);
        exit(0);
    }

    else{
        waitpid(pid, int * status, 0);
        return(status == 0);
    }
}

