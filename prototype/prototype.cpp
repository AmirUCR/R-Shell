#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <iostream>
using namespace std; 

int main(){

   //pid_t is of process id type. Here we are creating a child process 
   //and setting it equal to pid 
   pid_t pid = fork(); 

   //now you should check if there was an error
   //in forking 
   if (pid < 0){
      cout << "There was a fork error" << endl; 
      exit(EXIT_FAILURE); 
   }
   //if the pid is zero, then fork returned zero and you're currently in the
   //child process
   if (pid == 0){
      cout << "I am currently in the child process" << endl; 
      
      //now use execvp to change the change this process from being an
      //instance of one program to instead an instance of another(in this case
      //we'll do c-echo"
      
      char * argv_list[] = {"ls", "-a", NULL};
      execvp("ls",argv_list); 
      exit(0); 
   }
   //otherwise you are in the parent process
   else{
     cout << "Now I am in the parent process and will wait for the child process" << endl; 
     waitpid(pid, NULL, 0); 
     cout << "now the child has terminated" << endl;  
   }

   return 0; 
}

