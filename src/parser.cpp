#include "../header/parser.hpp"
#include "and.cpp"
#include "or.cpp"
#include "semicolon.cpp"
#include "executable.cpp"
#include <cstring>
#include <algorithm>
#include <queue>

void Parser::getInput() {
	string temp;

	getline(cin, temp);
	input += temp;

	while (!quotesMatch()) {
		cout << "> ";
		input += "\n";
		getline(cin, temp);
		input += temp;
	}

}

bool Parser::parenthesesMatch() {
	int count = 0;
	bool inQuotes = false;

	for (int i = 0; i < input.size(); i++) {
		if (input[i] == '"') {
			inQuotes = !inQuotes;
		}
		else if (!inQuotes && input[i] == '(') {
			count++;
		} else if (!inQuotes && input[i] == ')') {
			count--;
		}
	}

	return (count == 0) ? true : false;
}

bool Parser::quotesMatch() {
	int singleQuotesCount = 0;
	int doubleQuotesCount = 0;
	int dqEvenOdd = 0;
	int sqEvenOdd = 0;

	for (int i = 0; i < input.size(); i++) {
		if (input[i] == '"') {
			if (input[i - 1] == '\\') {
				continue;
			} else {
				singleQuotesCount++;
			}
		} else if (input[i] == '\'') {
			if (input[i - 1] == '\\') {
				continue;
			} else {
				doubleQuotesCount++;
			}
		}
	}

	dqEvenOdd = doubleQuotesCount % 2;
	sqEvenOdd = singleQuotesCount % 2;

	return (dqEvenOdd == 0 && sqEvenOdd == 0) ? true : false;
}

bool Parser::escapeChar() {
	size_t index = input.find('\\');
	return (index == string::npos) ? false : true;
}

void Parser::printError(string s) {
	cout << "r'shell: " << s << endl;
}

void Parser::parse() {
	vector<string> tokenized;

	// If parentheses don't match, return with an error message
	if (!parenthesesMatch()) {
		printError("mismatched parentheses");
		return;
	}

	// TODO: no support for \char escaping yet
	if (escapeChar()) {
		printError("character escaping is not supported");
		return;
	}

	// Trim start and trailing whitespace
	size_t firstChar = input.find_first_not_of(' ');
	size_t lastChar = input.find_last_not_of(' ');

	// If input is just whitespace, return.
	if (firstChar == string::npos && lastChar == string::npos) {
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
	// Here be dragons...
	while (current < input.length()) {

		// When we find a quotation mark
		if (input[current] == '"') {
			bool isAttached = true;
			bool inQuotes = true;

			if (input[current - 1] == ' ') {
				isAttached = false;
				trail = current + 1;
			}
			current++;

			while (current + 1 < input.length()) {
				if (input[current] == '"') {
					inQuotes = !inQuotes;
				}

				else if (!inQuotes && input[current] == ' ') {
					break;
				}

				current++;
			}

			string sub = input.substr(trail, current - trail);

			if (isAttached) {
				// find and erase all '"'
				string::iterator end_pos = remove(sub.begin(), sub.end(), '"');
				sub.erase(end_pos, sub.end());
			}

			tokenized.push_back(sub);

			// If there are more characters after the quotes, jump over the space. Move trail
			if (input[current + 1] == ' ') {
				current++;
				trail = current + 1;
			} else {
				trail = current + 1;
			}

		}
		// The rest of the input is discarded (except if in quotes which is handled above)
		else if (input[current] == '#') {
			if (trail < current) {
				//cout << "Comments\n";
				tokenized.push_back(input.substr(trail, current - trail));
				break;
			} else {
				break;
			}
		}
		// If we are at a whitespace
		else if (input[current] == ' ') {		
			// Push the previous word to tokenized
			tokenized.push_back(input.substr(trail, current - trail));
			trail = current + 1;
		}
		
		// If we are at a semicolon or parentheses
		else if (input[current] == ';' || input[current] == '(' || input[current] == ')') {

			// If there is a character immediately followed by a semicolon, '(', or ')' (e.g, echo A;)
			if (trail < current) {
				tokenized.push_back(input.substr(trail, current - trail));
				trail = current;

				// If we are at the end of input, simply push the last ';', '(', or ')'
				if (current + 1 == input.size()) {
					tokenized.push_back(input.substr(trail, 1));
				}
			}

			// If a ';', '(', or ')' is followed by a char
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

		
		// We've reached the end of input
		else if (current + 1 >= input.length()) {
			tokenized.push_back(input.substr(trail));
			break;
		}

		current++;		// We are at a character
	}

	// FOR DEBUGGING
	// for (int i = 0; i < tokenized.size(); i++) {
	// 	cout << "\"" << tokenized[i] << "\"" << " ";
	// }

	this->ShuntingYard(tokenized);
}

bool Parser::isOperator(string &s) {
	return (s == "&&" || s == ";" || s == "||") ? true : false;
}

Connector* Parser::WhichConnector(string s) {
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

// 
// Algorithm from: https://en.wikipedia.org/wiki/Shunting-yard_algorithm#The_algorithm_in_detail
//
void Parser::ShuntingYard(vector<string> tokenized) {
	stack<string> operators{};
	queue<string> output{};

	for (int i = 0; i < tokenized.size(); i++) {

		// If the token is a word (not a connector or parentheses), keep going until we find one
		while (!isOperator(tokenized.at(i)) && tokenized.at(i) != "(" && tokenized.at(i) != ")") {
			output.push(tokenized.at(i));
			i++;

			if (i >= tokenized.size() || isOperator(tokenized.at(i)) || tokenized.at(i) == "(" || tokenized.at(i) == ")") {
				output.push("\0");

				if (i >= tokenized.size()) {
					break;
				}
			}
		}

		if (i >= tokenized.size()) {
			break;
		}

		if (isOperator(tokenized.at(i))) {
			while (!operators.empty() && operators.top() != "(") {
				output.push(operators.top());
				operators.pop();
			}

			operators.push(tokenized.at(i));
		}

		else if (tokenized.at(i) == "(") {
			operators.push(tokenized.at(i));
		}

		else if (tokenized.at(i) == ")") {
			while (operators.top() != "(") {
				output.push(operators.top());
				operators.pop();			
			}

			if (operators.top() == "(") {
				operators.pop();
			}
		}
	}

	while (!operators.empty()) {
		output.push(operators.top());
		operators.pop();
	}

	// FOR DEBUGGING
	// while (!output.empty()) {
	// 	cout << output.front() << " ";
	// 	output.pop();
	// }

	this->MakeTree(output);
}

// 
// Algorithm to evaluate postfix. From: https://en.wikipedia.org/wiki/Reverse_Polish_notation#Postfix_evaluation_algorithm
//
void Parser::MakeTree(queue<string> output) {
	stack<Command*> s{};
	vector<string> outputVector;
	vector<vector<char*>> cstrings(output.size());
	int index = 0;

	while (!output.empty()) {
		outputVector.push_back(output.front());
		output.pop();
	}

	for (int i = 0; i < outputVector.size(); i++) {
		if (isOperator(outputVector[i])) {
			Connector* c = WhichConnector(outputVector[i]);

			if (!s.empty()) {
				Command* right = s.top();
				c->SetRight(right);
				s.pop();
			}

			if (!s.empty()) {
				Command* left = s.top();
				c->SetLeft(left);
				s.pop();
			}

			s.push(c);
		}
		else {
			while (outputVector[i] != "\0") {
				cstrings[index].push_back(&outputVector[i][0]);
				i++;
			}

			s.emplace(new Executable(cstrings[index][0], cstrings[index].data()));
			
			index++;
		};
	}

	if (!s.empty()) {
		s.top()->execute();

		// for (size_t y = 0; y < cstrings.size(); y++) {
		// 	for (size_t x = 0; x < cstrings[y].size(); x++) {
		// 		cstrings[y][x] = 0;
		// 	}
		// 	cstrings[y].clear();
		// }
		// cstrings.clear();
		// outputVector.clear();

		s.pop();
	}
}