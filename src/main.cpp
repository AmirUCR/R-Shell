#include <string>
#include <iostream>
#include "parser.cpp"

using namespace std;

int main() {
    Parser* parser = new Parser();

    while (true) {
        cout << "$ ";
        parser->getInput();
        parser->parse();
    }

    return 0;
}