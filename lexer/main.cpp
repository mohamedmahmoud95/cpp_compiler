#include <iostream>
#include <string>
#include <regex>
#include <vector>

using namespace std;

enum TokenType {
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_BOPERATOR,
    TOKEN_UOPERATOR,
    TOKEN_LOGICALOPERATOR,
    TOKEN_KEYWORD,
    TOKEN_DATATYPE,
    TOKEN_UNKNOWN
};

struct Token {
    TokenType type;
    string lexeme;
};

class LexerRegex {
public:
    static bool matchBinaryOperator(const std::string& str);
    static bool matchUnaryOperator(const std::string& str);
    static bool matchlogicalOperator(const std::string& str);
    static bool matchKeyword(const std::string& str);
    static bool matchDatatype(const std::string& str);

};

bool LexerRegex::matchBinaryOperator(const std::string& str) {
    // Regular expression pattern for operators:
    static const std::regex binaryoperatorPattern("[\\+\\-\\*\\/=]");
    return std::regex_match(str, binaryoperatorPattern);
}
bool LexerRegex::matchUnaryOperator(const std::string& str) {
    // Regular expression pattern for unary operators:
    static const std::regex unaryOperatorPattern("\\+\\+|\\-\\-");
    return std::regex_match(str, unaryOperatorPattern);
}
bool LexerRegex::matchlogicalOperator(const std::string& str) {
    static const std::regex logicalOperatorPattern("\\&\\&|\\|\\||!");
    return std::regex_match(str, logicalOperatorPattern);
}

bool LexerRegex::matchKeyword(const std::string& str) {
    // Regular expression pattern for keywords:
    static const std::regex keywordPattern("\\b(auto|break|case|char|const|continue|default|do|double|else|enum|extern|float|for|goto|if|long|register|return|short|signed|sizeof|static|struct|switch|typedef|union|unsigned|void|volatile|while)\\b");
    return std::regex_match(str, keywordPattern);
}

bool LexerRegex::matchDatatype(const std::string& str) {
    // Regular expression pattern for datatypes:
    static const std::regex datatypePattern("\\b(int|float|double)\\b");
    return std::regex_match(str, datatypePattern);

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
        if (isdigit(buffer[0])) {
            // Find the end of the number
            while (end < buffer.length() && isdigit(buffer[end]))
                end++;
        }
        else if (isalpha(buffer[0]) || buffer[0] == '_') {
            // Find the end of the identifier
            end = 1;
            while (end < buffer.length() && isalnum(buffer[end]) && !isDelimiter(buffer[end]) || buffer[end] == '_')
                end++;
        }

        else if (LexerRegex::matchUnaryOperator(buffer.substr(0, 2))) {
            end = 2;
        }
        else if (LexerRegex::matchlogicalOperator(buffer.substr(0, 2))) {
            end = 2;
        }
        else {
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
        if (isalpha(token.lexeme[0]) || token.lexeme[0] == '_') {

            if (LexerRegex::matchKeyword(token.lexeme)) {

                token.type = TOKEN_KEYWORD;
            }
            else if (LexerRegex::matchDatatype(token.lexeme)) {
                token.type = TOKEN_DATATYPE;
            }
            else if (!LexerRegex::matchKeyword(token.lexeme) && !isdigit(token.lexeme[0])) {
                token.type = TOKEN_IDENTIFIER;
            }


        }
        else if (isdigit(token.lexeme[0])) {

            token.type = TOKEN_NUMBER;

        }
        else if (LexerRegex::matchUnaryOperator(token.lexeme.substr(0, token.lexeme.length()))) {

            token.type = TOKEN_UOPERATOR;
        }
        else if (LexerRegex::matchBinaryOperator(token.lexeme.substr(0, token.lexeme.length()))) {

            token.type = TOKEN_BOPERATOR;
        }
        else if (LexerRegex::matchlogicalOperator(token.lexeme.substr(0, token.lexeme.length()))) {

            token.type = TOKEN_LOGICALOPERATOR;
        }

        else {
            token.type = TOKEN_UNKNOWN;
        }
        position += token.lexeme.length();
    }
};

int main() {
    // Sample input string
    string input = " if x == y return 1; else rerrturn 0; while _cycle = 9; int frawla = 2098 ; int btates = --8++ ; float zrka23elyamama ; Ibrahim !Donia && ||;";

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
        case TOKEN_UOPERATOR:
            cout << "Unary Operator" << endl;
            break;
        case TOKEN_LOGICALOPERATOR:
            cout << "Logical Operator" << endl;
            break;
        case TOKEN_BOPERATOR:
            cout << "Binary Operator" << endl;
            break;
        case TOKEN_DATATYPE:
            cout << "Datatype" << endl;
            break;
        case TOKEN_UNKNOWN:
            cout << "Unknown" << endl;
            break;
        }
    } while (token.lexeme != "");

    return 0;
}
