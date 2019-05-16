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
	size_t inputRange = lastChar - firstChar + 1;

	// If input is just whitespace, quit.
	if (firstChar == string::npos && lastChar == string::npos) {
		exit(1);
	}

	// Only trim whitespaces if input is not empty.
	if (!input.empty()) {
		input = input.substr(firstChar, inputRange);
	}

	unsigned current{0};
	unsigned trail{0};

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
	stack<Command*> tree{};		// The stack we put our connectors and executables on
	Connector* c{0};		// Keep a reference to the last connector
	vector<vector<char*>> cstrings(tokenized.size());
	int index{0};


	// string temp{};
	// stack<string> operators{};
	// queue<string> output{};
	// vector<Executable*> execs{};

	// for (int i = 0; i < tokenized.size(); i++) {
	// 	string token = tokenized.at(i);

	// 	// If the token is a command (not a connector)
	// 	if (!isOperator(token)) {
	// 		temp += token + " ";
	// 	}

	// 	else if (isOperator(token)) {
	// 		while (!operators.empty() && token != "(") {

	// 			if (!temp.empty()) {
	// 				temp = temp.substr(0, temp.size() - 1);
	// 			}

	// 			output.push(operators.top());
	// 			operators.pop();
	// 		}

	// 		operators.push(token);
	// 	}
	// }


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
		if ((i + 1 != tokenized.size()) && isOperator(tokenized.at(i + 1)) || i + 1 == tokenized.size()) {

			cstrings[index].push_back(NULL);

			// Create a new executable and push onto stack
			tree.emplace(new Executable(cstrings[index][0], cstrings[index].data()));

			index++;
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
