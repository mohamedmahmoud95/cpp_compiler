
#include <iostream>
#include <string>
#include <regex>

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


class LexerRegex {
public:
    static bool matchOperator(const std::string& str);
};

bool LexerRegex::matchOperator(const std::string& str) {
    // Regular expression pattern for operators:
    static const std::regex operatorPattern("[\\+\\-\\*\\/=]");
    return std::regex_match(str, operatorPattern);
}


class Lexer {
public:
    Lexer(const string& input) : input(input), position(0) {}

    Token getNextToken() {
        Token token;

        // Skip whitespace
        while (position < input.length() && isspace(input[position]))
            position++;

        // Check for end of input
        if (position >= input.length()) {
            token.type = TOKEN_UNKNOWN;
            return token;
        }

        // Handle identifiers
        if (isalpha(input[position])) {
            // Find the end of the identifier
            size_t end = position + 1;
            while (end < input.length() && isalnum(input[end]))
                end++;
            token.lexeme = input.substr(position, end - position);
            token.type = TOKEN_IDENTIFIER;
            position = end;
        }
        // Handle numbers
        else if (isdigit(input[position])) {
            // Find the end of the number
            size_t end = position + 1;
            while (end < input.length() && isdigit(input[end]))
                end++;
            token.lexeme = input.substr(position, end - position);
            token.type = TOKEN_NUMBER;
            position = end;
        }
        // Handle operators
        else if (LexerRegex::matchOperator(input.substr(position, 1))) {
            token.lexeme = input.substr(position, 1);
            token.type = TOKEN_OPERATOR;
            position++;
        }
        // Skip unknown characters
        else {
            token.lexeme = input.substr(position, 1);
            token.type = TOKEN_UNKNOWN;
            position++;
        }

        return token;
    }

private:
    const string input;
    size_t position;
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
    } while (token.type != TOKEN_UNKNOWN);

    return 0;
}
