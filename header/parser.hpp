#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <iostream>
#include <stack>
#include <vector>
#include "command.hpp"
#include "executable.h"
#include "or.hpp"
#include "and.hpp"
#include "semicolon.hpp"

using namespace std;

class Parser {
	private:
	string input{};	// Holds user's command line input

	Connector* WhichConnector(string &s);
	bool isOperator(string &s);
	void MakeTree(vector<string> &);

	public:
	Parser(){};
	void getInput();
	bool parenthesesMatch();
	void parse();	// Takes the user input and tokenizes it by "&& || ;" delimiters
				// Instantiates executables as needed
				// instantiates connectors as needed

};

#endif // END PARSER_H