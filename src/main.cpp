#include <string>
#include <iostream>
#include "parser.cpp"

using namespace std;

int main() {
    Parser* parser = new Parser();

    // Run our program until "exit" is entered
    while (true) {
        cout << "$ ";
        parser->getInput();
        parser->parse();
    }

    return 0;
}