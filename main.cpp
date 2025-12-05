// main.cpp
#include <iostream>
#include <string>
#include "include/lexer.h"
#include "include/token.h"

using namespace std;

int main() {
    cout << "Starting lexer test..." << endl;

    while (true) {
        int Tok = getNextToken(); // use getNextToken to update CurrentToken

        if (Tok == tok_eof) {
            cout << "<EOF>" << endl;
            break;
        }

        switch (Tok) {
            case tok_def:
                cout << "<tok_def>" << endl;
                break;
            case tok_extern:
                cout << "<tok_extern>" << endl;
                break;
            case tok_identifier:
                cout << "<identifier: " << IdentifierStr << ">" << endl;
                break;
            case tok_number:
                cout << "<number: " << NumVal << ">" << endl;
                break;
            case tok_string:
                cout << "<string: " << StringVal << ">" << endl;
                break;
            case tok_comment:
                cout << "<comment skipped>" << endl;
                break;
            case tok_beginInc:
                cout << "<startOne>" << endl;
                break;
            case tok_endInc:
                cout << "<stopOne>" << endl;
                break;
            case tok_beginBody:
                cout << "<startTwo>" << endl;
                break;
            case tok_endBody:
                cout << "<stopTwo>" << endl;
                break;
            default:
                // Unknown single-character token (operators, punctuation)
                cout << "<char: " << char(Tok) << ">" << endl;
                break;
        }
    }

    cout << "Lexer test finished." << endl;
    return 0;
}
