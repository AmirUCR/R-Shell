#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <iostream>
#include <stack>
#include <vector>
#include <queue>
#include "command.hpp"
#include "executable.hpp"
#include "or.hpp"
#include "and.hpp"
#include "semicolon.hpp"

using namespace std;

class Parser {
	private:
	string input{};	// Holds user's command line input

	Connector* WhichConnector(string);	// Return a connector object depending on which "&&" "||" or ";" string is passed in
	bool isOperator(string &);	// True if argument is one of the "&&" "||" or ";"
	void ShuntingYard(vector<string>);
	void MakeTree(queue<string> );
	// void trim();		// Unused at the moment
	bool escapeChar();
	bool parenthesesMatch();	// returns true if there is a same number of left "(" and right ")" parentheses in input
	bool quotesMatch();
	void printError(string);

	public:
	Parser(){};
	void getInput();			// getline user input
	void parse();				// Takes the user input and tokenizes it by "&& || ;" delimiters
};

#endif // END PARSER_H