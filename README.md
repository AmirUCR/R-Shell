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

The design patter we use for this program is the **Composite Pattern**. The user input is taken by the Parser and each word is tokenized and stored in a vector. We may use stacks and queues to build an expression tree of executable and connector objects, however, this decision is not concrete as of this time. From there, each connector will query the evaluate function of its lhs and rhs to see if they succeeded or failed. Depending on these evaluates, the connector will make its own evaluate function which returns an appropriate true or false depending on the connector type. Each Executable object uses execvp, syscall forks, and waitpid to carry out its job.

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

Ex:(taken from Advanced Linux Programming by Mark Mitchell, Jeffrey Oldham, Alex Samuel)

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

EX:(taken from Advanced Linux Programming by Mark Mitchell, Jeffrey Oldham, Alex Samuel)
Using fork and exec Together
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

# Development and Testing Roadmap

## Classes and Functions
1. [Abstract Class Base](https://github.com/cs100/spring-2019-assignment-cs100-dance-team/issues/1)
1. [Parser Class](https://github.com/cs100/spring-2019-assignment-cs100-dance-team/issues/2)
    1. Create the function GetInput
    1. Create the function Parse
1. [Executable Class](https://github.com/cs100/spring-2019-assignment-cs100-dance-team/issues/3)
    1. Create the execute function. This function should handle the special command _exit_ as well as any other command using execvp, syscall forks, and waitpid. Moreover, it should set the flag for successFail depending on the outcome of the executable.
    1. Create the evaluate function. This function returns the successFail boolean.
1. [Abstract Connector Class](https://github.com/cs100/spring-2019-assignment-cs100-dance-team/issues/4)
    1. Create the base class for all other connectors to inherit from
1. [And Class](https://github.com/cs100/spring-2019-assignment-cs100-dance-team/issues/5)
    1. Create the evaluate function. This function returns true only if both lhsEval and rhsEval are true.
    1. Create the execute function. This function executes the lhs and rhs Command type objects. It stores the success/fail status of these Commands in lhsEval and rhsEval
1. [Semicolon Class](https://github.com/cs100/spring-2019-assignment-cs100-dance-team/issues/6)
    1. Create the evaluate function. This function returns the status of the rhsEval.
    1. Create the execute function. This function executes the lhs and rhs Command type objects. It stores the success/fail status in lhsEval and rhsEval.
1. [Pipe Class](https://github.com/cs100/spring-2019-assignment-cs100-dance-team/issues/7)
    1. Create the evaluate function. This function returns true if either of lhsEval or rhsEval are true.
    1. Create the execute function. This function executes the lhs and rhs Command type objects. It stores the success/fail status in lhsEval and rhsEval.

## Unit/Integration Testing
### Parser
1. Test that [GetInput](https://github.com/cs100/spring-2019-assignment-cs100-dance-team/issues/8) works correctly
    1. By calling GetInput and passing in a single executable such as ls
    1. Pass in an executable with an argument
    1. Pass in an executable, an argument, and a connector
    1. Pass in an empty string
    1. Pass in numeric digits

1. Test that [Parse](https://github.com/cs100/spring-2019-assignment-cs100-dance-team/issues/9) works correctly
    1. Create a temporary function that iterates through the commands vector and outputs its contents
    1. Pass in a combination of executables, arguments, and connectors
    1. (After all other classes are built) Test that the parser creates the appropriate Command type objects, and correctly passes the argument list to Executable

### Executable
1. Test that [evaluate](https://github.com/cs100/spring-2019-assignment-cs100-dance-team/issues/10) works correctly
    1. Create a mock successFail variable and test if evaluate returns it

1. Test that [execute](https://github.com/cs100/spring-2019-assignment-cs100-dance-team/issues/11) works correctly
    1. Pass in a valid shell executable command (such as echo) and check the results
    1. Pass in a valid shell executable with an argument and check the results
    1. Pass in a valid shell executable with multiple arguments
    1. Pass in an invalid shell executable and evaluate

### [And](https://github.com/cs100/spring-2019-assignment-cs100-dance-team/issues/12)
1. Test the constructor by using a temporary getter function
1. Test execute by passing in two Command type objects, and then observe the output(s)
1. Test evaluate by passing in two valid Command type objects and expect True
1. Test evaluate by passing in one valid and one invalid Command type objects and expect False
    1. Expect the rhs executable not to run when the lhs first fails
1. Test evaluate by passing in two invalid Command type objects and expect False

### [Semicolon](https://github.com/cs100/spring-2019-assignment-cs100-dance-team/issues/13)
1. Test the constructor by using a temporary getter function
1. Test execute by passing in two Command type objects, and then observe the output(s)
1. Test evaluate by passing in two valid Command type objects and expect True
1. Test evaluate by passing in one valid and one invalid Command type objects and expect False
     1. Expect the rhs to run even if lhs fails
1. Test evaluate by passing in two invalid Command type objects and expect False

### [Pipe](https://github.com/cs100/spring-2019-assignment-cs100-dance-team/issues/14)
1. Test the constructor by using a temporary getter function
1. Test execute by passing in two Command type objects, and then observe the output(s)
1. Test evaluate by passing in two valid Command type objects and expect True
1. Test evaluate by passing in one valid and one invalid Command type objects and expect True
     1. Expect the rhs to run even if lhs fails
1. Test evaluate by passing in two invalid Command type objects and expect False


### [Integration Test](https://github.com/cs100/spring-2019-assignment-cs100-dance-team/issues/15)
1. Using the Parser, enter executable names, arguments, and connectors
1. If everything that you passed in is known to be valid, expect the output to be valid
1. Using the Parser, enter invalid executable names. Expect the output to be invalid
1. Enter a mix of valid and invalid executable names or connectors, and expect the output to behave accordingly
