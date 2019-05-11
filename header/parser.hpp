#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <iostream>
#include <stack>
#include <vector>
#include "command.hpp"
#include "executable.h"
#include "Or.hpp"
#include "And.hpp"
#include "Semicolon.hpp"

using namespace std;

class Parser {
	private:
	string input;	// Holds user's command line input
	//vector<string> commands;
	stack<Command*> commands;

	Connector* WhichConnector(string &s);
	bool isOperator(string &s);
	void MakeTree(vector<string> &);
	void Parse();	// Takes the user input and tokenizes it by "&& || ;" delimiters
					// Instantiates executables as needed
					// instantiates connectors as needed

	public:
	Parser();		// Get user input and store it	
};

#endif // END PARSER_H