#include "../header/parser.hpp"
#include "and.cpp"
#include "or.cpp"
#include "semicolon.cpp"
#include "executable.cpp"
#include <cstring>

Parser::Parser() {
	cout << "$ ";
	getline(cin, input);
	this->Parse();
}

void Parser::Parse() {
	vector<string> tokenized;

	// We erase anything after # -- Don't want to parse comments
	size_t findComment = input.find('#');
	if (findComment != string::npos) {
		input.erase(findComment);
	}

	// Trim start and trailing whitespace
	size_t firstChar = input.find_first_not_of(' ');
	size_t lastChar = input.find_last_not_of(' ');
	size_t inputRange = lastChar - firstChar + 1;
	input = input.substr(firstChar, inputRange);

	unsigned current = 0;
	unsigned trail = 0;

	// Begin tokenizing
	while (current < input.length()) {
		// When we find a quotation mark...
		if (input[current] == '"') {
			trail = current + 1;
			current++;

			// ...keep looking for its second pair
			while (current + 1 < input.length() && input[current] != '"') {
				current++;
			}

			// When second pair found, or when we reach the end of string:
			tokenized.push_back(input.substr(trail, current - trail));

			// If there are more characters after the quote, jump over the space. Move trail
			if (input[current + 1] == ' ') {
				current++;
				trail = current + 1;
			} else {
				trail = current + 1;
			}

		}

		else if (current + 1 >= input.length()) {
			tokenized.push_back(input.substr(trail));
			break;		// We've reached the end of input
		}
		else if (input[current] == ' ') {
			tokenized.push_back(input.substr(trail, current - trail));
			trail = current + 1;
		}
		else if (input[current] == ';') {
			if (trail < current) {
				tokenized.push_back(input.substr(trail, current - trail));
				trail = current;
			} else {
				tokenized.push_back(input.substr(trail, trail + 1));
				current++;
				trail = current + 1;
			}
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

void Parser::MakeTree(vector<string> &tokenized) {
	vector<string> argsVector{};
	vector<char*> cstrings{};
	Connector* lastConnector = 0;

	for (auto it = tokenized.begin(); it != tokenized.end(); it++) {
		// If it's a word
		if (!isOperator(*it)) {
			argsVector.push_back(*it);

			if ((it + 1) == tokenized.end() || isOperator(*(it + 1))) {
                
				for(auto& s: argsVector) {
					cstrings.push_back(&s[0]);
				}

				char** argList = new char*[argsVector.size() + 1];

				for (int i = 0; i < cstrings.size(); i++) {
					argList[i] = cstrings[i];
				}

				argList[argsVector.size()] = NULL;
            	
				commands.emplace(new Executable(argList[0], argList));

				for (int i = 0; i < argsVector.size(); i++) {
					cout << argList[i] << endl;
				}

				// commands.top()->whoAmI();

				// if (commands.size() >= 2 ) {
				// 	commands.top()->whoAmI();
				// 	commands.pop();
				// 	commands.top()->whoAmI();
				// }

				cstrings.clear();
				argsVector.clear();
			}
		}
		else if (isOperator(*it)) {
			lastConnector = WhichConnector(*it);
		}

		if (commands.size() >= 2 && lastConnector != 0) {
			Command* rhs = commands.top();
			commands.pop();
			Command* lhs = commands.top();
			commands.pop();

			lastConnector->SetRight(rhs);
			lastConnector->SetLeft(lhs);

			commands.push(lastConnector);

			commands.top()->whoAmI();

			lastConnector = 0;
		}
	}

	commands.top()->whoAmI();
	this->commands.top()->execute();
	this->commands.pop();
}
