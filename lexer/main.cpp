#include <iostream>
#include <string>
#include <regex>
#include <vector>

using namespace std;

enum TokenType {
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_FLOAT,
    TOKEN_BINARY,
    TOKEN_HEX,
    TOKEN_OCTAL,
    TOKEN_BOPERATOR,
    TOKEN_UOPERATOR,
    TOKEN_LOGICALOPERATOR,
    TOKEN_RELATIONALOPERATORS,
    TOKEN_ASSIGNMENTOPERATOR,
    TOkEN_TERNARYOPERATOR,
    TOKEN_KEYWORD,
    TOKEN_DATATYPE,
    TOKEN_UNKNOWN,
    PUNCTUATION
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
    static bool matchRelationalOperator(const std::string& str);
    static bool matchAssignmentOperator(const std::string& str);
    static bool matchTernaryOperator(const std::string& str);
    static bool matchKeyword(const std::string& str);
    static bool matchDatatype(const std::string& str);
    static bool matchFloat(const std::string& str);
    static bool matchBinary(const std::string& str);
    static bool matchHex(const std::string& str);
    static bool matchOctal(const std::string& str);
    static bool matchPunc(const std::string& str);


};


bool LexerRegex::matchUnaryOperator(const std::string& str) {
    // Regular expression pattern for unary operators:
    static const std::regex unaryOperatorPattern("\\+\\+|\\-\\-");
    return std::regex_match(str, unaryOperatorPattern);
}
bool LexerRegex::matchRelationalOperator(const std::string& str) {
    static const std::regex relationalOpPattern("<=?|>=?|==|!=");
    return std::regex_match(str, relationalOpPattern);
}

bool LexerRegex::matchlogicalOperator(const std::string& str) {
    static const std::regex logicalOperatorPattern("\\&\\&|\\|\\||!");
    return std::regex_match(str, logicalOperatorPattern);
}
bool LexerRegex::matchAssignmentOperator(const std::string& str) {
    static const std::regex assignmentOpPattern("=|\\+=|\\-=|\\*=|/=|%=|&=|\\|=|\\^=|<<=|>>=");
    return std::regex_match(str, assignmentOpPattern);

}
bool LexerRegex::matchBinaryOperator(const std::string& str) {
    // Regular expression pattern for operators:
    static const std::regex binaryoperatorPattern("[\\+\\-\\*]");
    return std::regex_match(str, binaryoperatorPattern);
}
bool LexerRegex::matchTernaryOperator(const std::string& str) {
    static const std::regex ternaryOpPattern("\\?\\:");
    return std::regex_match(str, ternaryOpPattern);

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

bool LexerRegex::matchFloat(const std::string& str) {
    // Regular expression pattern for float numbers:
    static const std::regex floatPattern("\\b\\d+\\.\\d+(e[+-]?\\d+)?\\b");
    return std::regex_match(str, floatPattern);
}

bool LexerRegex::matchBinary(const std::string& str) {
    // Regular expression pattern for binary numbers:
    static const std::regex binaryPattern("\\b0[bB][01]+\\b");
    return std::regex_match(str, binaryPattern);
}

bool LexerRegex::matchHex(const std::string& str) {
    // Regular expression pattern for hexadecimal numbers:
    static const std::regex hexPattern("\\b0[xX][0-9a-fA-F]+\\b");
    return std::regex_match(str, hexPattern);
}

bool LexerRegex::matchOctal(const std::string& str) {
    // Regular expression pattern for octal numbers:
    static const std::regex octalPattern("\\b0[0-7]+\\b");
    return std::regex_match(str, octalPattern);
}
bool LexerRegex::matchPunc(const std::string& str) {
    // Regular expression pattern for punctuation:
    static const std::regex PuncPattern("\\(|\\)|,|;|\\{|\\}");
    return std::regex_match(str, PuncPattern);
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

        // Check if the token is a number
        if (isdigit(buffer[0]) || (buffer[0] == '.' && isdigit(buffer[1] || (buffer[0] == '0' && (tolower(buffer[1] == 'x'))) || (buffer[0] == '0' && (tolower(buffer[1] == 'b')))))) {
            bool hasDecimal = false;
            bool hasExponent = false;
            bool hasSuffix = false;

            // Find the end of the float number
            while (end < buffer.length() && (isdigit(buffer[end]) || buffer[end] == '.' || buffer[end] == 'e' || buffer[end] == 'E' || buffer[end] == 'f' || buffer[end] == 'F' || buffer[end] == 'l' || buffer[end] == 'L')) {
                if (buffer[end] == '.') {
                    if (hasDecimal) break; // More than one decimal point
                    hasDecimal = true;
                }
                else if (buffer[end] == 'e' || buffer[end] == 'E') {
                    if (hasExponent) break; // More than one exponent
                    hasExponent = true;
                }
                else if (buffer[end] == 'f' || buffer[end] == 'F' || buffer[end] == 'l' || buffer[end] == 'L') {
                    if (hasSuffix) break; // More than one suffix
                    hasSuffix = true;
                }
                end++;
                if (buffer[0] == '0' && (buffer[1] == 'x') || (buffer[0] == '0' && (tolower(buffer[1] == 'b')))) {
                    end = 2; // Skip the '0x' prefix
                    while (end < buffer.length() && isxdigit(buffer[end]))
                        end++;
                }

                else {
                    // Regular decimal number
                    while (end < buffer.length() && isdigit(buffer[end]))
                        end++;
                }

            }

            // Check for valid float lexeme
            if (!hasDecimal && !hasExponent && !hasSuffix)
                return buffer.substr(0, end); // Integer number
            else
                return buffer.substr(0, end); // Float number
        }





        // Check if the token is an identifier or keyword
        else if (isalpha(buffer[0]) || buffer[0] == '_') {
            // Find the end of the identifier
            while (end < buffer.length() && (isalnum(buffer[end]) || buffer[end] == '_'))
                end++;
            return buffer.substr(0, end);
        }
        else if (LexerRegex::matchAssignmentOperator(buffer.substr(0, 3)))
        {
            end = 3;
            return buffer.substr(0, end);
        }

        else if (LexerRegex::matchAssignmentOperator(buffer.substr(0, 2)))
        {
            end = 2;
            return buffer.substr(0, end);
        }
        // Check if the token is an operator
        else if (LexerRegex::matchUnaryOperator(buffer.substr(0, 2)) ||
            LexerRegex::matchlogicalOperator(buffer.substr(0, 2)) || LexerRegex::matchRelationalOperator(buffer.substr(0, 2)) ||
            LexerRegex::matchTernaryOperator(buffer.substr(0, 2))) {
            end = 2;
            return buffer.substr(0, end);
        }


        // Otherwise, return single-character token
        else {
            end = 1;
            return buffer.substr(0, end);
        }
    }



    bool isDelimiter(char c) {
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

            if (LexerRegex::matchBinary(token.lexeme.substr(0, token.lexeme.length()))) {
                token.type = TOKEN_BINARY;
            }
            else if (LexerRegex::matchHex(token.lexeme.substr(0, token.lexeme.length()))) {
                token.type = TOKEN_HEX;
            }
            else if (LexerRegex::matchOctal(token.lexeme.substr(0, token.lexeme.length()))) {
                token.type = TOKEN_OCTAL;
            }

            else if (LexerRegex::matchFloat(token.lexeme.substr(0, token.lexeme.length()))) {
                token.type = TOKEN_FLOAT;
            }
            else
                token.type = TOKEN_NUMBER;

        }


        else if (LexerRegex::matchAssignmentOperator(token.lexeme.substr(0, token.lexeme.length()))) {
            token.type = TOKEN_ASSIGNMENTOPERATOR;
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
        else if (LexerRegex::matchRelationalOperator(token.lexeme.substr(0, token.lexeme.length()))) {

            token.type = TOKEN_RELATIONALOPERATORS;
        }

        else if (LexerRegex::matchTernaryOperator(token.lexeme.substr(0, token.lexeme.length()))) {

            token.type = TOkEN_TERNARYOPERATOR;
        }

        else if (LexerRegex::matchPunc(token.lexeme)) {
            token.type = PUNCTUATION;
        }

        else {
            token.type = TOKEN_UNKNOWN;
        }
        position += token.lexeme.length();
    }
};

int main() {
    // Sample input string
    string input = " 3.14e5 if x == y return 1; else rerrturn 0; while _cycle = 9; int frawla = 2098 ; int = --8++ ; float zrka23elyamama = 0.221; 0b1010 12.345 0xABCD 0777 ;Ibrahim !Donia && ||; ()) === != > < >= 8.98-- *= %= += -= <<= ^= ?: &= + - ";

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
        case TOKEN_FLOAT:
            cout << "Float" << endl;
            break;
        case TOKEN_BINARY:
            cout << "Binary" << endl;
            break;
        case TOKEN_HEX:
            cout << "Hexadecimal" << endl;
            break;
        case TOKEN_OCTAL:
            cout << "Octal" << endl;
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
        case TOKEN_RELATIONALOPERATORS:
            cout << "Relational Operator" << endl;
            break;
        case TOKEN_ASSIGNMENTOPERATOR:
            cout << "Assignment Operator" << endl;
            break;

        case TOkEN_TERNARYOPERATOR:
            cout << "Ternary Operator" << endl;
            break;
        case TOKEN_UNKNOWN:
            cout << "Unknown" << endl;
            break;
        case PUNCTUATION:
            cout << "Punctuation" << endl;
            break;
        }

    } while (token.lexeme != "");

    return 0;
}