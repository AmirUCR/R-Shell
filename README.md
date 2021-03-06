# RShell

Authors: Amir Mohseni, Jihad Shalabi

# Introduction
This program intends to perform the following functions:

1. Print a command prompt (e.g. `$`)
2. Read in a line of command(s) (and connector(s)) from standard input
3. Execute the appropriate commands using _fork_, _execvp_, and _waitpid_, _dup2_, _pipe_, and file descriptors

When using this program, your command **must** have the following format:

```
$ executable [argumentList] [connector] [cmd] ...
```

Where you can pass in any number of commands separated by any of ||, &&, or ; which are the only valid connectors. 

The executable can be any program that is located at one of the PATH environment variable locations. Moreover, the [argumentList] is simply a list of zero or more arguments separated by spaces.

RShell supports precedence operators (i.e, left paren "(" and right paren ")"). For example, the following code
`echo Hello! && echo Bonjour! || echo Aloha! && echo Ciao!`
would produce the following results:
```
Hello!
Bonjour!
Ciao!
```
Using parentheses, we can write 
```
(echo Hello! && echo Bonjour!) || (echo Aloha! && echo Ciao!)
```
Which would produce:
```
Hello!
Bonjour!
```

Moreover, with RShell, you can type in `echo "hello` and the program prompts you to continue your input until you input a second quotation mark (I'm ~~quote~~ quite proud of this one. -Amir).

R'Shell support I/O redirection. You can input commands such as `test -f text.txt && cat < text.txt | sort | tr a-z A-Z` and if `text.txt` exists, the contents of the file is output to the terminal after being sorted and translated into uppercase. The supported operators are:
```
<
>
>>
```
where `>>` appends to a text file if it exists, or creates it if it's not present.

The design pattern we use for this program is the **Composite Pattern**. This is because a base class exists from which two other classes inherit from. Furthermore, each Connector object can contain other Connectors, or other Exectuables. The Connector abstract class is our composite, while the Executable is the base class that serves as the interface for the execvp and test_cmd subclasses. 

# How it Works
The user input is taken by the Parser and each word is tokenized and stored in a vector. All strings before a connector is transformed into an Exectuable object. This Exectuable is then pushed onto a stack. If there are >= 2 Commands on the stack, we take the last connector, and assign to it a left and a right Command child (this child can be another Connector, or an Exectuable). From there, each connector will make a call to the execute function of its lhs and rhs children and, depending on the success or failure of these children, the connector will make its own execute function return true or false. Each Executable object will call one of the subclasses(execvp or test_cmd) to carry out the work depending on what command name is passed in. 

# Diagram
![UML Diagram for RShell](https://github.com/AmirUCR/R-Shell/blob/master/images/UMLDiagram.png)
# Classes
**Abstract Class Command**
* Pure-Virtual function execute()
  * The ; connector's execute only returns the status of its RHS
  * The && connector's execute returns whether if both LHS and RHS are true
  * The || connector's execute returns true if either of LHS or RHS are true
  * The < connector is an input redirector.
  * The > connector is an output redirector.
  * The >> connector is an appending output redirector.


**Abstract Base Connector**
* Provides the base class for the other connectors
* Contains base function execute
* Contains a set left child and a set right child function.


**Class And**
* Takes in two Command pointer type objects (can be an Executable or another Command) and calls execute on them.

* Overrides execute
  * The execute function takes lhs and rhs Command pointer types and instantiates new Command objects, returning true if both lhs and rhs return true. 


**Class Semicolon**
* Takes in two Command pointer type objects (can be an Executable or another Command) and calls execute. 

* Overrides execute
  * The execute function takes lhs and rhs Command pointer types and instantiates new Command objects. It then returns the status of the rhsEval.


**Class Pipe**
* Takes in two Command pointer type objects (can be an Executable or another Command) and calls execute on them.

* Overrides execute
  * The execute function takes lhs and rhs Command pointer types and instantiates new Command objects, returning true if either rhsEval or lhsEval is true. 

**Class Input Redirector**
* Takes in two Command pointer type objects (can be an Executable or another Command) and calls execute. 

* Overrides execute
  * The execute function takes lhs and rhs Command pointer types and instantiates new Command objects. It then returns the status of the lhsEval.
  
**Class Output Redirector and Output Redirector Append**
* Takes in two Command pointer type objects (can be an Executable or another Command) and calls execute. 

* Overrides execute
  * The execute function takes lhs and rhs Command pointer types and instantiates new Command objects. It then returns the status of the lhsEval.

**Class Executable**
* Takes in an executable name as well as an array of character type arguments.
* Instantiates a new Execvp, or Test_cmd, based on the name argument given. If `test` was given, instantiates a Test_cmd object and passes the argument list. Otherwise, instantiates an Execvp.

**Class Test_cmd**
* Takes in the execname and an array of character type arguments 

* Overrides execute
  * This function will use the stat() function that will return information about a file/directory passed in. The function will also consider the flag passed in (-f, -d, -e, or no flag) and will return and output true or false depending on whether the flag passed in matches the actual state of the file/directory.

**Class Execvp**
* Takes in the execname and an array of charcter type arguments. 

* Overrides execute
  * This function will use syscalls fork(), execvp(), and waitpid(), to create child processes in which certain commands can be executed. It will return true if the command passes and false if the command fails. 

**Class Parser**
* Has references to the abstract base Command classes (Connector, Executable) in order to instantiate such objects.

* Called in main to get the user input on the command shell.

* Parse
  * Takes the user input string and stores it in the string input variable. Tokenizes the userInput. Stores the tokenized words in a vector.

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
1. Abstract Class Command
1. Parser Class
    1. Create the function Parse
1. Executable Class
    1. Create the execute function. This function should handle the special command _exit_ as well as any other command using execvp, syscall forks, and waitpid. It will return true if the execution succeeds and false otherwise. 
1. Abstract Connector Class
    1. Create the base class for all other connectors to inherit from
1. And Class
    1. Create the execute function. This function executes the lhs and rhs Command type objects. It returns true if both lhs and rhs succeed. 
1. Semicolon Class
    1. Create the execute function. This function executes the lhs and rhs Command type objects. It returns true if rhs succeeds. 
1. Pipe Class
    1. Create the execute function. This function executes the lhs and rhs Command type objects. It returns true if either lhs or rhs succeed. 

## Unit/Integration Testing
### Parser
1. Test that GetInput works correctly
    1. By calling GetInput and passing in a single executable such as ls
    1. Pass in an executable with an argument
    1. Pass in an executable, an argument, and a connector
    1. Pass in an empty string
    1. Pass in numeric digits

1. Test that Parse works correctly
    1. Create a temporary function that iterates through the commands vector and outputs its contents
    1. Pass in a combination of executables, arguments, and connectors
    1. (After all other classes are built) Test that the parser creates the appropriate Command type objects, and correctly passes the argument list to Executable

### Executable
1. Test that execute works correctly
    1. Pass in a valid shell executable command (such as echo) and valid arguments. 
    1. Pass in a valid shell executable commmand and an invalid argument. 
    1. Pass in an invalid shell executable command and a valid argument. 
    1. Pass in an invalid shell executable command and an invalid argument. 
    1. Pass in an empty shell executable commmand. 
    1. Pass in a valid executable command and an empty argument. 

### And
1. Test the constructor by using a temporary getter function
1. Test execute by passing in two Command type objects, and then observe the output(s)
1. Test execute by passing in two valid Command type objects and expect True
1. Test execute by passing in one valid and one invalid Command type objects and expect False
    1. Expect the rhs executable not to run when the lhs first fails
1. Test execute by passing in two invalid Command type objects and expect False

### Semicolon
1. Test the constructor by using a temporary getter function
1. Test execute by passing in two Command type objects, and then observe the output(s)
1. Test execute by passing in two valid Command type objects and expect True
1. Test execute by passing in one valid and one invalid Command type objects and expect False
     1. Expect the rhs to run even if lhs fails
1. Test execute by passing in two invalid Command type objects and expect False

### Pipe
1. Test the constructor by using a temporary getter function
1. Test execute by passing in two Command type objects, and then observe the output(s)
1. Test execute by passing in two valid Command type objects and expect True
1. Test execute by passing in one valid and one invalid Command type objects and expect True
     1. Expect the rhs to run even if lhs fails
1. Test execute by passing in two invalid Command type objects and expect False

### Input Redirector
1. Test whether `<` returns true if a valid file is passed in.
1. Test whether `<` returns false if an invalid file is passed in.

### Test_cmd
1. Test all the flags when a file is passed in.
1. Test all the flags when a directory is passed in.
1. Test when no flag is passed in with directory and file. 
1. Test when no file or directory are passed in.  

### Integration Test
1. Using the Parser, enter executable names, arguments, and connectors
1. If everything that you passed in is known to be valid, expect the output to be valid
1. Using the Parser, enter invalid executable names. Expect the output to be invalid
1. Enter a mix of valid and invalid executable names or connectors, and expect the output to behave accordingly
1. Test I/O redirectors in conjunction with other connectors
