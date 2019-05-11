#include "..\header\parser.hpp"

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
	size_t inputRange = firstChar - lastChar + 1;
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

	// for (auto &str : tokenized) {
	// 	cout << str << endl;
	// }
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
}

void Parser::MakeTree(vector<string> &tokenized) {
	vector<string>::iterator it = tokenized.begin();
	string argsList;
	string name;
	Connector* lastConnector;

	while (it != tokenized.end()) {
		while (!isOperator(*it)) {
			argsList.append(*it + " ");
			it++;
		}
		
		// Found an operator
		lastConnector = WhichConnector(*it);

		char * cstr = new char [argsList.length() + 1];
  		strcpy(cstr, argsList.c_str());
		
		int i = 0;
		while (argsList[i] != ' ') {
			i++;
		}

		name = argsList.substr(0, i);

		Executable* exec = new Executable(name, &cstr);

		commands.push(exec);

		if (commands.size() >= 2) {
			Command* rhs = commands.top();
			commands.pop();
			Command* lhs = commands.top();
			commands.pop();

			lastConnector->SetRight(rhs);
			lastConnector->SetLeft(lhs);

			commands.push(lastConnector);
		}

		it++;
	}

	lastConnector->execute();
}
