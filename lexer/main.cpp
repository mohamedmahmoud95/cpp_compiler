#include <iostream>
#include <string>
#include <regex>
#include <vector>

using namespace std;

enum TokenType {
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_OPERATOR,
    TOKEN_KEYWORD,
    TOKEN_UNKNOWN
};

struct Token {
    TokenType type;
    string lexeme;
};

class LexerRegex {
public:
    static bool matchOperator(const std::string& str);
    static bool matchKeyword(const std::string& str);
};

bool LexerRegex::matchOperator(const std::string& str) {
    // Regular expression pattern for operators:
    static const std::regex operatorPattern("[\\+\\-\\*\\/=]");
    return std::regex_match(str, operatorPattern);
}

bool LexerRegex::matchKeyword(const std::string& str) {
    // Regular expression pattern for keywords:
    static const std::regex keywordPattern("\\b(auto|break|case|char|const|continue|default|do|double|else|enum|extern|float|for|goto|if|int|long|register|return|short|signed|sizeof|static|struct|switch|typedef|union|unsigned|void|volatile|while)\\b");
    return std::regex_match(str, keywordPattern);
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

        // Buffer size (4KB)
        const size_t bufferSize = 4096;

        // Calculate the end position of the buffer
        size_t endPosition = position + bufferSize;
        if (endPosition > input.length())
            endPosition = input.length();

        // Extract the buffer
        string buffer = input.substr(position, endPosition - position);

        // Extract lexeme
        token.lexeme = extractLexeme(buffer);

        // Handle identifiers, keywords, numbers, operators, and unknown tokens
        handleToken(token);

        return token;
    }

private:
    const string input;
    size_t position;


    string extractLexeme(const string& buffer) {
        size_t end = 0;
        if (isalpha(buffer[0]) || buffer[0] == '_') {
            // Find the end of the identifier
            end = 1;
            while (end < buffer.length() && isalnum(buffer[end]) && !isDelimiter(buffer[end]) || buffer[end] == '_')
                end++;
        }
        else {
            // Single character token
            end = 1;
        }
        return buffer.substr(0, end);
    }

    bool isDelimiter(char c) {
        // Define your delimiters here
        string delimiters = " \t\n\r";
        return delimiters.find(c) != string::npos;
    }

    void handleToken(Token& token) {
        if (isalpha(token.lexeme[0])) {
            if (LexerRegex::matchKeyword(token.lexeme)) {
                token.type = TOKEN_KEYWORD;
            }
            else if (!LexerRegex::matchKeyword(token.lexeme) && !isdigit(token.lexeme[0])) {
                token.type = TOKEN_IDENTIFIER;
            }
        }
        else if (isdigit(token.lexeme[0])) {
            token.type = TOKEN_NUMBER;
        }
        else if (LexerRegex::matchOperator(token.lexeme.substr(0, token.lexeme.length()))) {
            token.type = TOKEN_OPERATOR;
        }
        else {
            token.type = TOKEN_UNKNOWN;
        }
        position += token.lexeme.length();
    }
};

int main() {
    // Sample input string
    string input = " if x == y return 1; else rerrturn 0;";

    Lexer lexer(input);
    Token token;

    do {
        token = lexer.getNextToken();
        cout << "Token: " << token.lexeme << ", Type: ";
        switch (token.type) {
        case TOKEN_KEYWORD:
            cout << "Keyword" << endl;
            break;
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
    } while (token.lexeme != "");

    return 0;
}
