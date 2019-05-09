#include <string>
#include <vector>
#include <cstring>

using namespace std;

class Parser {
	private:
	string input;
	vector<string> commands;
	public:
	Parser();
	void Parse();
};
