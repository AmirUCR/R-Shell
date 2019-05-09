#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>

using namespace std;

class Parser {
	private:
	string input;	// Holds user's command line input
	vector<string> commands;

	public:
	Parser();		// Get user input and store it

	void Parse();	// Takes the user input and tokenizes it by "&& || ;" delimiters
					// Instantiates executables as needed
					// instantiates connectors as needed
};

#endif // END PARSER_H