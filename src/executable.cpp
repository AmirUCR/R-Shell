#include "../header/executable.h" 
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

using namespace std;

bool Executable::execute() {

    int status; 
    pid_t pid = fork(); 
    
    if (execName == "exit") {
        exit(0); 
    }

    if (pid < 0) {
        perror("Failure to fork");
    }
 
    if (pid == 0) {
        execvp(this->execName, this->argList);
       // this->successExec = false; 
        exit(1); 
    }

    else {
      waitpid(pid, &status, 0); 
      if (status == 0) {
          return true; 
      }
       return false;  
    }
}

