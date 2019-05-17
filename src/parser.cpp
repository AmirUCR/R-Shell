#include "../header/parser.hpp"
#include "and.cpp"
#include "or.cpp"
#include "semicolon.cpp"
#include "executable.cpp"
#include <cstring>
#include <queue>

void Parser::getInput() {
	getline(cin, input);
}

bool Parser::parenthesesMatch() {
	int count{0};

	for (int i{0}; i < input.size(); i++) {
		if (input[i] == '(') {
			count++;
		} else if (input[i] == ')') {
			count--;
		}
	}

	return (count == 0) ? true : false;
}

// void Parser::removeComments(string &s)

// void Parser::trim

void Parser::parse() {
	vector<string> tokenized;

	// We erase anything after # -- Don't want to parse comments
	size_t findComment = input.find('#');
	if (findComment != string::npos) {
		input.erase(findComment);
	}

	// Trim start and trailing whitespace
	size_t firstChar = input.find_first_not_of(' ');
	size_t lastChar = input.find_last_not_of(' ');

	// If input is just whitespace, return.
	if (firstChar == string::npos && lastChar == string::npos) {
		return;
	}

	// If parentheses don't match, return with an error message
	if (!parenthesesMatch()) {
		cout << "r'shell: mismatched parentheses\n";
		return;
	}

	size_t inputRange = lastChar - firstChar + 1;

	// Only trim whitespaces if input is not empty.
	if (!input.empty()) {
		input = input.substr(firstChar, inputRange);

		bool inQuotes = false;

		// Remove subsequent whitespaces
		for (int i = 0; i < input.size(); i++) {
			
			// Mark that we are/aren't in a quote. Don't want to trim whitespace inside quotes.
			if (input[i] == '"') {
				inQuotes = !inQuotes;
			}

			// If we aren't in quotes, check for subsequent whitespaces. Erase if any found.
			if ((inQuotes == false) && (input[i] == ' ')) {
				while (input[i + 1] == ' ') {
					input.erase(input.begin() + i + 1);
				}
			}
		}
	}

	int current{0};
	int trail{0};

	// Begin tokenizing
	while (current < input.length()) {

		// When we find a quotation mark, jump over it and...
		if (input[current] == '"') {
			trail = current + 1;
			current++;

			// ...keep looking for its second pair
			while (current + 1 < input.length() && input[current] != '"') {
				current++;
			}

			// When second pair found, or when we reach the end of string, push everything between quotes to our vector
			tokenized.push_back(input.substr(trail, current - trail));

			// If there are more characters after the quotes, jump over the space. Move trail
			if (input[current + 1] == ' ') {
				current++;
				trail = current + 1;
			} else {
				trail = current + 1;
			}

		}
		else if (input[current] == ' ') {		// If we are at a whitespace
			// Push the previous word to tokenized
			tokenized.push_back(input.substr(trail, current - trail));
			trail = current + 1;
		}
		else if (input[current] == ';' || input[current] == '(' || input[current] == ')') {

			// If there is a character immediately followed by a semicolon, (, or )
			if (trail < current) {
				tokenized.push_back(input.substr(trail, current - trail));
				trail = current;

				// If we are at the end of input, simply push the last ; ( )
				if (current + 1 == input.size()) {
					tokenized.push_back(input.substr(trail, 1));
				}
			}

			// If a ;, (, or ) is followed by a char, push this
			else if (current + 1 != input.size() && input[current + 1] != ' ') {
				tokenized.push_back(input.substr(trail, 1));
				trail++;
			}

			// If there's a space before semicolon
			else {		
				tokenized.push_back(input.substr(trail, 1));
				current++;
				trail = current + 1;
			}
		}
		else if (current + 1 >= input.length()) {
			tokenized.push_back(input.substr(trail));
			break;		// We've reached the end of input
		}

		current++;		// We are at a character
	}

	this->MakeTree(tokenized);
}

bool Parser::isOperator(string &s) {
	return (s == "&&" || s == ";" || s == "||") ? true : false;
}

Connector* Parser::WhichConnector(string &s) {
	if (s == "&&") {
		return new And();
	}

	if (s == "||") {
		return new Or();
	}

	if (s == ";") {
		return new Semicolon();
	}

	return 0;
}

// TODO:: Change name of fxn to ShuntingYard
void Parser::MakeTree(vector<string> &tokenized) {
	stack<Command*> tree{};		// The stack we put our connectors and executables on
	Connector* c{0};		// Keep a reference to the last connector
	vector<vector<char*>> cstrings(tokenized.size());
	int index{0};


	for (int i = 0; i < tokenized.size(); i++) {

		// If we are at a connector
		if (isOperator(tokenized.at(i))) {
			
			// Save it
			c = WhichConnector(tokenized.at(i));
		}
		else {
			// If not a connector, push to temp
			cstrings[index].push_back(&tokenized[i][0]);
		}

		// If the next string is not the end, and if it's a connector -- Or if we are at the end..
		if ((i + 1 != tokenized.size()) && isOperator(tokenized.at(i + 1)) || (i + 1 == tokenized.size() && !isOperator(tokenized.at(i)))) {

			// NULL terminate cstrings (execvp likes them..)
			cstrings[index].push_back(NULL);

			// Create a new executable and push it onto our stack
			tree.emplace(new Executable(cstrings[index][0], cstrings[index].data()));

			index++;
		} else if (i + 1 == tokenized.size() && isOperator(tokenized.at(i)) && tokenized.at(i) != ";") {
			cout << "r'shell: syntax error near unexpected token '" << tokenized.at(i) << "'\n";
			return;
		}

		if (tree.size() >= 2) {
			Command* right = tree.top();
			tree.pop();
			Command* left = tree.top();
			tree.pop();

			c->SetLeft(left);
			c->SetRight(right);

			tree.push(c);
		}
	}

	if (!tree.empty()) {
		tree.top()->execute();
		tree.pop();
	}
}
