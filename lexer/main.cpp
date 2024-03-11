
#include <iostream>
#include <string>

using namespace std;

enum TokenType {
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_OPERATOR,
    TOKEN_UNKNOWN
};

struct Token {
    TokenType type;
    string lexeme;
};

class Lexer {
public:
    Lexer(const string& input) : input(input), position(0) {}

Token getNextToken() {
    Token token;

    // Skip whitespace
    while (isWhitespace(input[position]))
        position++;

    // Check for end of input
    if (position >= input.length() ) {
        token.type = TOKEN_UNKNOWN;
        return token;
    }

    // Handle identifiers
    if (isAlpha(input[position])) {
        token.type = TOKEN_IDENTIFIER;
        token.lexeme = readIdentifier();
    }
    // Handle numbers
    else if (isDigit(input[position])) {
        token.type = TOKEN_NUMBER;
        token.lexeme = readNumber();
    }
    // Handle operators
    else if (isOperator(input[position])) {
        token.type = TOKEN_OPERATOR;
        token.lexeme = readOperator();
    }
    // Skip unknown characters
    else {
        token.type = TOKEN_UNKNOWN;
        token.lexeme = input[position];
        position++;
        return token; // Skip to the next character
    }

    return token;
}


private:
    const string input;
    size_t position;

    bool isWhitespace(char ch) {
        return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r';
    }

    bool isAlpha(char ch) {
        return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
    }

    bool isDigit(char ch) {
        return ch >= '0' && ch <= '9';
    }

    bool isOperator(char ch) {
        return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=';
    }

    string readIdentifier() {
        string identifier;
        while (isAlphaNumeric(input[position])) {
            identifier += input[position];
            position++;
        }
        return identifier;
    }

    bool isAlphaNumeric(char ch) {
        return isAlpha(ch) || isDigit(ch);
    }

    string readNumber() {
        string number;
        while (isDigit(input[position])) {
            number += input[position];
            position++;
        }
        return number;
    }

    string readOperator() {
        string op;
        op += input[position];
        position++;
        return op;
    }
};

int main() {
    string input = "x = 10 + 20 * y";

    Lexer lexer(input);
    Token token;

    do {
        token = lexer.getNextToken();
        cout << "Token: " << token.lexeme << ", Type: ";
        switch (token.type) {
            case TOKEN_IDENTIFIER:
                cout << "Identifier" << endl;
                break;
            case TOKEN_NUMBER:
                cout << "Number" << endl;
                break;
            case TOKEN_OPERATOR:
                cout << "Operator" << endl;
                break;
            case TOKEN_UNKNOWN:
                cout << "Unknown" << endl;
                break;
        }
    } while (token.type != TOKEN_UNKNOWN && token.lexeme != "\0");

    return 0;
}
