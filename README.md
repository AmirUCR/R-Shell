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
#Classes
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
  *The evaluate function returns true if both lhsEval and rhsEval are true

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
