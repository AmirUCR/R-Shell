# CS100 RShell
Spring 2019
Amirsadra Mohseni, SID 862085035
Jihad Shalabi, SID 861294360

# Introduction
This program intends to perform the following functions:

1. Print a command prompt (e.g. `$`)
2. Read in a line of command(s) (and connector(s)) from standard input
3. Execute the appropriate commands using _fork_, _execvp_, and _waitpid_

When using this program, your command **must** have the following format:

```
$ executable [argumentList] [connector] [cmd] ...
```

Where you can pass in any number of commands separated by any of ||, &&, or ; which are the only valid connectors. 

The executable can be any program that is located at one of the PATH environment variable locations. Moreover, the [argumentList] is simply a list of zero or more arguments separated by spaces.

The design patter we use for this program is the **Composite Pattern**. 
**TODO: Write brief overview of how inputs are transformed into classes**

# Diagram
![UML Diagram for RShell](https://github.com/cs100/spring-2019-assignment-cs100-dance-team/blob/master/images/UMLDiagram.png)
# Classes
**Abstract Class Base**
* Pure-Virtual function evaluate()
  * The ; connector's evaluate only returns the status of its RHS
  * The && connector's evaluate returns whether if both LHS and RHS are true
  * The || connector's evaluate returns true if either of LHS or RHS are true


**Abstract Base Connector**
* Provides the base class for the other connectors
* Contains protected member variables that other connectors inherit
* Contains base functions evaluate and execute


**Class And**
* Takes in two Command pointer type objects (can be an Executable or another Command) and calls evaluate on them.

* Overrides evaluate
  * The evaluate function returns true if both lhsEval and rhsEval are true

* Overrides execute
  * The execute function takes lhs and rhs Command pointer types and instantiatesnew Command objects.


**Class Semicolon**
* Takes in two Command pointer type objects (can be an Executable or another Command) and calls evaluate on them.

* Overrides evaluate
  * The evaluate function returns the status of the rhsEval

* Overrides execute
  * The execute function takes lhs and rhs Command pointer types and instantiatesnew Command objects.


**Class Pipe**
* Takes in two Command pointer type objects (can be an Executable or another Command) and calls evaluate on them.

* Overrides evaluate
  * The evaluate function returns true if either of rhsEval or rhsEval is true

* Overrides execute
  * The execute function takes lhs and rhs Command pointer types and instantiatesnew Command objects.


**Class Executable**
* Takes in an executable name as well as a vector of string type arguments.

* Overrides evaluate
  * The evaluate function returns the variable successFail, the status of whether the executable is executed or not (true or false).

* Overrides execute
  * This function performs the appropriate syscall, execvp, and waitpid operations to run the given executable name. It also sets the true/false flag for bool successFail. If the execName argument is exit, it does not make a syscall. We early abandon by shutting down the shell.


**Class Parser**
* Has references to the Base classes (Connector, Executable) in order to instantiate such objects.
* Called in main to get the user input on the command shell.

* GetInput
  * Takes the user input string and stores it in the userInput variable.

* Parse
  * Tokenizes the userInput. Stores the tokenized words in the commands vector.

# FORK, EXECVP, AND WAITPID

## fork()
```
#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h>
```
- Makes a child process that is an exact copy of its parent process.
- When fork is called, a duplicate process called a child process is created that
  continues from the point that fork was called in the parent. 
- The child is a new process, so it has its own process ID. 
- You can use getpid to get the process ID
- When you call fork(), the return value in the parent process is the process ID of the child. The return value in the child process is zero since it has no children(this is how you know if a process you're in is a child process).  
- Total number of processes = 2^n where n is the # of fork system calls

Ex:
```
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main ()
{
 pid_t child_pid; //pid_t is simply a variable type for process ID's
 printf ("the main program process ID is %d\n", (int) getpid());
 child_pid = fork () ;
 
 if (child_pid != 0) {
 printf ("this is the parent process, with id %d\n", (int) getpid ());
 printf ("the child's process ID is %d\n",(int) child_pid );
}
 else {
 printf ("this is the child process, with id %d\n", (int) getpid ());
 return 0;
}
```

The first block of the if statement is executed only in parent process, while is executed by the child. 

## execvp()

- The exec family of functions causes a process to cease being an instance of one program and to instead become an instance of another program. 

- Execvp() specifically accepts a program name and searches for that name in the current execution path(does not need the full path of the program). It also accepts an argument list for the new program as a NULL-terminated array of pointers to strings. 

- Since exec replaces the calling program with another, it never returns unless there is an error. 

EX:
Listing 3.4 (fork-exec.c) Using fork and exec Together
```
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

/* Spawn a child process running a new program. PROGRAM is the name
 of the program to run; the path will be searched for this program.
 ARG_LIST is a NULL-terminated list of character strings to be
 passed as the program's argument list. Returns the process ID of
 the spawned process. */
int spawn (char* program, char** arg_list) 
{
 pid_t child_pid;
 /* Duplicate this process. */
 child_pid = fork ();

 if (child_pid != 0)
 /* This is the parent process. */
 return child_pid;
 else {
 /* Now execute PROGRAM, searching for it in the path. */
 execvp (program, arg_list);

 /* The execvp function returns only if an error occurs. */
 fprintf (stderr, "an error occurred in execvp\n");
 
 abort ();
 }
} 
```

## waitpid()

- The wait() system call suspends execution of the current process until one of its children terminates. The call wait(&status) is equivalent to:

waitpid(-1, &status, 0);

- The waitpid() system call suspends execution of the current process until a child specified by pid argument has changed state. By default, waitpid() waits only for terminated children

- Used to wait for state changes in a child of the calling process, and obtain information about the child whose state has changed. A state change is considered to be: the child terminated; the child was stopped by a signal; or the child was resumed by a signal. In the case of a terminated child, performing a wait allows the system to release the resources associated with the child; if a wait is not performed, then terminated the child remains in a "zombie" state. 
