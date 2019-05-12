#include "../header/parser.hpp"
#include "and.cpp"
#include "or.cpp"
#include "semicolon.cpp"
#include "executable.cpp"
#include <cstring>

Parser::Parser() {
	cout << "$ ";
	getline(cin, input);

	if (input.empty()) {
		exit(1);
	}

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
	vector<char*> cstrings;
	stack<Command*> commands{};
	Connector* c = 0;

	for (int i = 0; i < tokenized.size(); i++) {
		if (isOperator(tokenized.at(i))) {
			//cout << "Setting connector: " <<  &tokenized[i][0] << endl;
			c = WhichConnector(tokenized.at(i));
		}
		else {
			//cout << "Pushing: " <<  &tokenized[i][0] << endl;
			cstrings.push_back(&tokenized[i][0]);
		}

		if ((i + 1 != tokenized.size()) && isOperator(tokenized.at(i + 1)) || i + 1 == tokenized.size()) {
			commands.emplace(new Executable(cstrings[0], cstrings.data()));
			cstrings.clear();
		}

		if (commands.size() >= 2) {
			Command* left = commands.top();
			//left->whoAmI();

			commands.pop();
			Command* right = commands.top();
			//right->whoAmI();
			commands.pop();

			c->SetLeft(left);
			c->SetRight(right);

			commands.push(c);
		}
	}
	//commands.top()->whoAmI();
	commands.top()->execute();
	commands.pop();
}
