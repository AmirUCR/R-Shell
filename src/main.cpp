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

    delete parser;
    parser = 0;

    return 0;
}

// test -d ./header/"new folder" && echo hi