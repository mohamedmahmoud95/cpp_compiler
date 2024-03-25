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
    TOKEN_ADDOP,
    TOKEN_SUBOP,
    TOKEN_MULOP,
    TOKEN_DIVOP,
    TOKEN_MODOP,
    TOKEN_INCOP,
    TOKEN_DECOP,
    TOKEN_ANDOP,
    TOKEN_OROP,
    TOKEN_NOTOP,
    TOKEN_EQOP,
    TOKEN_NEQOP,
    TOKEN_GTOP,
    TOKEN_LTOP,
    TOKEN_GTEOP,
    TOKEN_LTEOP,
    TOKEN_ASSIGNOP,
    TOKEN_ADDASSIGNOP,
    TOKEN_SUBASSIGNOP,
    TOKEN_MULASSIGNOP,
    TOKEN_DIVASSIGNOP,
    TOKEN_MODASSIGNOP,
    TOKEN_ANDASSIGNOP,
    TOKEN_ORASSIGNOP,
    TOKEN_XORASSIGNOP,
    TOKEN_LEFTASSIGNOP,
    TOKEN_RIGHTASSIGNOP,
//     TOKEN_BOPERATOR,
//     TOKEN_UOPERATOR,
//     TOKEN_LOGICALOPERATOR,
//     TOKEN_RELATIONALOPERATORS,
//     TOKEN_ASSIGNMENTOPERATOR,
    TOKEN_TERNARYOPERATOR,
    TOKEN_KEYWORD,
    TOKEN_DATATYPE,
    TOKEN_UNKNOWN,
    PUNCTUATION,

    //=========================
    // Bitwise tokens:
    TOKEN_Bitwise_AND,     // &
    TOKEN_Bitwise_OR,      // |
    TOKEN_Bitwise_XOR,     // ^
    TOKEN_Bitwise_NOT,     // ~
    //=========================

    //=========================
    // PUNCTUATIONAL tokens:
    TOKEN_LEFT_PAREN,      // (
    TOKEN_RIGHT_PAREN,     // )
    TOKEN_LEFT_BRACE,      // {
    TOKEN_RIGHT_BRACE,     // }
    TOKEN_LEFT_BRACKET,    // [
    TOKEN_RIGHT_BRACKET,   // ]
    TOKEN_COMMA,           // ,
    TOKEN_PERIOD,          // .
    TOKEN_SEMICOLON,       // ;
    TOKEN_COLON,           // :
    TOKEN_QUESTION,        // ?
    TOKEN_QUOTE,           // '
    TOKEN_DOUBLE_QUOTE,    // "
    TOKEN_PREPROCESSOR_HASH, // #
    TOKEN_BACKSLASH,       // '\'
    TOKEN_NEWLINE,         // Newline
    //=========================
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
    return std::regex_match(str, unaryOperatorPattern);;
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
    // Regular expression pattern for binary operators:
//<<<<<<< Yasminas
    static const std::regex binaryoperatorPattern("[\\+\\-\\*%]");
// =======
//     static const std::regex binaryoperatorPattern("[\\+\\-\\*]");
// >>>>>>> Mohamed-Raslan
    return std::regex_match(str, binaryoperatorPattern);
}

bool LexerRegex::matchTernaryOperator(const std::string& str) {
    static const std::regex ternaryOpPattern("\\?\\:");
    return std::regex_match(str, ternaryOpPattern);
}

bool LexerRegex::matchKeyword(const std::string& str) {
    // Regular expression pattern for keywords:
    static const std::regex keywordPattern("\\b(auto|break|case|char|const|continue|default|do|double|else|enum|extern|float|for|goto|if|int|long|register|return|short|signed|sizeof|static|struct|switch|typedef|union|unsigned|void|volatile|while)\\b");
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
    // static const std::regex PuncPattern("\\(|\\)|,|;|;\\{|\\}");
    static const std::regex PuncPattern("\\(|\\)|\\{|\\}|\\[|\\]|,|\\.|;|:|\\?|'|\"|`|\\\\|\\n");
    return std::regex_match(str, PuncPattern);
}

class Lexer {
public:
    Lexer(const string& input) : input(input), position(0), bufferSize(4096) {
        // Initialize buffers
        currentBuffer = input.substr(0, min(bufferSize, input.length()));
        if (input.length() > bufferSize) {
            nextBuffer = input.substr(bufferSize, min(bufferSize, input.length() - bufferSize));
        }
        else {
            nextBuffer = "";
        }
    }

    Token getNextToken() {
        Token token;

        // Skip whitespace
        while (position < currentBuffer.length() && isspace(currentBuffer[position]))
            position++;

        // Check if current buffer is exhausted (lexer has consumed all the tokens)
        if (position >= currentBuffer.length() && nextBuffer.empty()) {
            token.lexeme = "";
            token.type = TOKEN_UNKNOWN;
            return token;
        }

        // Extract lexeme from current buffer
        token.lexeme = extractLexeme(&currentBuffer[position]);

        // Handle tokens and update position
        handleToken(token);
        position += token.lexeme.length();

        // Check if current buffer is empty and there are more characters in the input
        if (position >= currentBuffer.length() && !nextBuffer.empty()) {
            swapBuffers();

            position = 0; // Reset position after swapping buffers
        }

        return token;
    }


private:
    const string input;
    size_t position;
    string currentBuffer;
    string nextBuffer;
    const size_t bufferSize;
// <<<<<<< Yasminas

    void swapBuffers() {
        // Move content of next buffer to current buffer
        currentBuffer = nextBuffer;

// =======

//     void swapBuffers() {
//         // Move content of next buffer to current buffer
//         currentBuffer = nextBuffer;

// >>>>>>> Mohamed-Raslan
        // Load new content into next buffer
        size_t nextBufferStartPosition = position + currentBuffer.length();
        nextBuffer = input.substr(nextBufferStartPosition, bufferSize);
    }

    string extractLexeme(const string& buffer) {
        size_t end = 0;
        size_t bufferLength = buffer.length();

        // Check if buffer is empty
        if (bufferLength == 0) {
            return "";
        }

        // Check if the token is a number
        if (isdigit(buffer[0]) || (buffer[0] == '.' && isdigit(buffer[1])) || (buffer[0] == '0' && (tolower(buffer[1]) == 'x' || tolower(buffer[1]) == 'b'))) {
            bool hasDecimal = false;
            bool hasExponent = false;
            bool hasSuffix = false;

            // Find the end of the number literal
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
            }

            // Return the extracted lexeme
            return buffer.substr(0, end);
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
        // Check if the token is an operator
        else if (
            LexerRegex::matchAssignmentOperator(buffer.substr(0, 2)) ||
            LexerRegex::matchlogicalOperator(buffer.substr(0, 2)) ||
            LexerRegex::matchRelationalOperator(buffer.substr(0, 2)) ||
            LexerRegex::matchTernaryOperator(buffer.substr(0, 2)) ||
            LexerRegex::matchUnaryOperator(buffer.substr(0, 2)) ||
            LexerRegex::matchBinaryOperator(buffer.substr(0, 2))) {

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
            else {
                token.type = TOKEN_IDENTIFIER;
            }
        }
        else if (isdigit(token.lexeme[0])) {
            if (LexerRegex::matchBinary(token.lexeme)) {
                token.type = TOKEN_BINARY;
            }
            else if (LexerRegex::matchHex(token.lexeme)) {
                token.type = TOKEN_HEX;
            }
            else if (LexerRegex::matchOctal(token.lexeme)) {
                token.type = TOKEN_OCTAL;
            }
            else if (LexerRegex::matchFloat(token.lexeme)) {
                token.type = TOKEN_FLOAT;
            }
            else {
                token.type = TOKEN_NUMBER;
            }
        }
        else if (LexerRegex::matchAssignmentOperator(token.lexeme)) {
            if (token.lexeme == "=") {
                token.type = TOKEN_ASSIGNOP;
            }
            else if (token.lexeme == "+=") {
                token.type = TOKEN_ADDASSIGNOP;
            }
            else if (token.lexeme == "-=") {
                token.type = TOKEN_SUBASSIGNOP;
            }
            else if (token.lexeme == "*=") {
                token.type = TOKEN_MULASSIGNOP;
            }
            else if (token.lexeme == "/=") {
                token.type = TOKEN_DIVASSIGNOP;
            }
            else if (token.lexeme == "%=") {
                token.type = TOKEN_MODASSIGNOP;
            }
            else if (token.lexeme == "&=") {
                token.type = TOKEN_ANDASSIGNOP;
            }
            else if (token.lexeme == "|=") {
                token.type = TOKEN_ORASSIGNOP;
            }
            else if (token.lexeme == "^=") {
                token.type = TOKEN_XORASSIGNOP;
            }
            else if (token.lexeme == "<<=") {
                token.type = TOKEN_LEFTASSIGNOP;
            }
            else if (token.lexeme == ">>=") {
                token.type = TOKEN_RIGHTASSIGNOP;
            }
        }


        else if (LexerRegex::matchUnaryOperator(token.lexeme)) {

            if (token.lexeme == "++") {
                token.type = TOKEN_INCOP;
            }
            else if (token.lexeme == "--") {
                token.type = TOKEN_DECOP;
            }

        }

        else if (LexerRegex::matchBinaryOperator(token.lexeme)) {
            switch (token.lexeme[0]) {
            case '+':
                token.type = TOKEN_ADDOP;
                break;
            case '-':
                token.type = TOKEN_SUBOP;
                break;
            case '*':
                token.type = TOKEN_MULOP;
                break;
            case '/':
                token.type = TOKEN_DIVOP;
                break;
            case '%':
                token.type = TOKEN_MODOP;
                break;
            }

        }
        else if (LexerRegex::matchlogicalOperator(token.lexeme)) {

            if (token.lexeme == "&&") {
                token.type = TOKEN_ANDOP;
            }
            else if (token.lexeme == "||") {
                token.type = TOKEN_OROP;
            }
            else if (token.lexeme == "!") {
                token.type = TOKEN_NOTOP;
            }

        }
        else if (LexerRegex::matchRelationalOperator(token.lexeme)) {
            if (token.lexeme == "==") {
                token.type = TOKEN_EQOP;
            }
            else if (token.lexeme == "!=") {
                token.type = TOKEN_NEQOP;
            }
            else if (token.lexeme == ">") {
                token.type = TOKEN_GTOP;
            }
            else if (token.lexeme == "<") {
                token.type = TOKEN_LTOP;
            }
            else if (token.lexeme == ">=") {
                token.type = TOKEN_GTEOP;
            }
            else if (token.lexeme == "<=") {
                token.type = TOKEN_LTEOP;
            }
        }

//         }
//         else if (LexerRegex::matchAssignmentOperator(token.lexeme)) {
//             token.type = TOKEN_ASSIGNMENTOPERATOR;
//         }
//         else if (LexerRegex::matchUnaryOperator(token.lexeme)) {
//             token.type = TOKEN_UOPERATOR;
//         }
//         else if (LexerRegex::matchBinaryOperator(token.lexeme)) {
//             token.type = TOKEN_BOPERATOR;
//         }
//         else if (LexerRegex::matchlogicalOperator(token.lexeme)) {
//             token.type = TOKEN_LOGICALOPERATOR;
//         }
//         else if (LexerRegex::matchRelationalOperator(token.lexeme)) {
//             token.type = TOKEN_RELATIONALOPERATORS;
//         }
        else if (LexerRegex::matchTernaryOperator(token.lexeme)) {
            token.type = TOKEN_TERNARYOPERATOR;
        }
    
        else if (LexerRegex::matchPunc(token.lexeme)) {
             if (token.lexeme == "(") {
                token.type = TOKEN_LEFT_PAREN;
            }
            else if (token.lexeme == ")") {
                token.type = TOKEN_RIGHT_PAREN;
            }
            else if (token.lexeme == "{") {
                token.type = TOKEN_LEFT_BRACE;
            }
            else if (token.lexeme == "}") {
                token.type = TOKEN_RIGHT_BRACE;
            }
            else if (token.lexeme == "[") {
                token.type = TOKEN_LEFT_BRACKET;
            }
            else if (token.lexeme == "]") {
                token.type = TOKEN_RIGHT_BRACKET;
            }
            else if (token.lexeme == "'") {
                token.type = TOKEN_QUOTE;
            }
            else if (token.lexeme == "\"") {
                token.type = TOKEN_DOUBLE_QUOTE;
            }
            else if (token.lexeme == ".") {
                token.type = TOKEN_PERIOD;
            }
            else if (token.lexeme == ",") {
                token.type = TOKEN_COMMA;
            }
            else if (token.lexeme == ";") {
                token.type = TOKEN_SEMICOLON;
            }
            else if (token.lexeme == ":") {
                token.type = TOKEN_COLON;
            }
            else if (token.lexeme == ".") {
                token.type = TOKEN_PERIOD;
            }
            else if (token.lexeme == "?") {
                token.type = TOKEN_QUESTION;
            }
            else if (token.lexeme == "#") {
                token.type = TOKEN_PREPROCESSOR_HASH;
            }
            else if (token.lexeme == "\\") {
                token.type = TOKEN_BACKSLASH;
            }
            else if (token.lexeme == "\n") {
                token.type = TOKEN_NEWLINE;
            }
            else {
            token.type = PUNCTUATION;
            }
        }
        else {
            token.type = TOKEN_UNKNOWN;
        }
    }
};

int main() {
    // Sample input string
    string input = "3.14e5 if x == y return 1; else return 0; while _cycle = 9; int frawla = 2098 ; int = --8++ ; [] [ ]  float zrka23elyamama = 0.221; 0b1010 12.345 0xABCD 0777 ;Ibrahim !Donia && ||; ()) === != % > < >= 8.98-- *= %= += -= <<= ^= ?: &= + - () [] {} \\ ? . , ; : # \n ' \" ";

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
        case TOKEN_INCOP:
            cout << "INCOP" << endl;
            break;
        case TOKEN_DECOP:
            cout << "DECOP" << endl;
            break;
        case TOKEN_ANDOP:
            cout << "ANDOP" << endl;
            break;
        case TOKEN_OROP:
            cout << "OROP" << endl;
            break;
        case TOKEN_NOTOP:
            cout << "NOTOP" << endl;
            break;
        case TOKEN_ADDOP:
            cout << "ADDOP" << endl;
            break;
        case TOKEN_SUBOP:
            cout << "SUBOP" << endl;
            break;
        case TOKEN_MULOP:
            cout << "MULOP" << endl;
            break;
        case TOKEN_DIVOP:
            cout << "DIVOP" << endl;
            break;
        case TOKEN_MODOP:
            cout << "MODOP" << endl;
            break;

        case TOKEN_EQOP:
            cout << "EQOP" << endl;
            break;
        case TOKEN_NEQOP:
            cout << "NEQOP" << endl;
            break;
        case TOKEN_GTOP:
            cout << "GTOP" << endl;
            break;
        case TOKEN_LTOP:
            cout << "LTOP" << endl;
            break;
        case TOKEN_GTEOP:
            cout << "GTEOP" << endl;
            break;
        case TOKEN_LTEOP:
            cout << "LTEOP" << endl;
            break;
        case TOKEN_ASSIGNOP:
            cout << "ASSIGNOP" << endl;
            break;
        case TOKEN_ADDASSIGNOP:
            cout << "ADDASSIGNOP" << endl;
            break;
        case TOKEN_SUBASSIGNOP:
            cout << "SUBASSIGNOP" << endl;
            break;
        case TOKEN_MULASSIGNOP:
            cout << "MULASSIGNOP" << endl;
            break;
        case TOKEN_DIVASSIGNOP:
            cout << "DIVASSIGNOP" << endl;
            break;
        case TOKEN_MODASSIGNOP:
            cout << "MODASSIGNOP" << endl;
            break;
        case TOKEN_ANDASSIGNOP:
            cout << "ANDASSIGNOP" << endl;
            break;
        case TOKEN_ORASSIGNOP:
            cout << "ORASSIGNOP" << endl;
            break;
        case TOKEN_XORASSIGNOP:
            cout << "XORASSIGNOP" << endl;
            break;
        case TOKEN_LEFTASSIGNOP:
            cout << "LEFTASSIGNOP" << endl;
            break;
        case TOKEN_RIGHTASSIGNOP:
            cout << "RIGHTASSIGNOP" << endl;
            break;

        case TOKEN_TERNARYOPERATOR:
            cout << "Ternary Operator" << endl;
            break;
        case TOKEN_UNKNOWN:
            cout << "Unknown" << endl;
            break;
        case TOKEN_DATATYPE:
            cout << "Datatype" << endl;
            break;

        //==================================================
        // PUNCTUATIONAL tokens:
        case TOKEN_LEFT_PAREN:
            cout << "Left parenthesis" << endl;
            break;
        case TOKEN_RIGHT_PAREN:
            cout << "Right parenthesis" << endl;
            break;
        case TOKEN_LEFT_BRACE:
            cout << "Left brace" << endl;
            break;
        case TOKEN_RIGHT_BRACE:
            cout << "Right brace" << endl;
            break;
        case TOKEN_LEFT_BRACKET:
            cout << "Left bracket" << endl;
            break;
        case TOKEN_RIGHT_BRACKET:
            cout << "Right bracket" << endl;
            break;
        case TOKEN_COMMA:
            cout << "Comma" << endl;
            break;
        case TOKEN_PERIOD:
            cout << "Period" << endl;
            break;
        case TOKEN_SEMICOLON:
            cout << "Semi-colon" << endl;
            break;
        case TOKEN_COLON:
            cout << "Colon" << endl;
            break;
        case TOKEN_QUESTION:
            cout << "Question" << endl;
            break;
        case TOKEN_QUOTE:
            cout << "Quote" << endl;
            break;
        case TOKEN_DOUBLE_QUOTE:
            cout << "Double quote" << endl;
            break;
        case TOKEN_PREPROCESSOR_HASH:
            cout << "Preprocessor hash" << endl;
            break;
        case TOKEN_BACKSLASH:
            cout << "Backslash" << endl;
            break;
        case TOKEN_NEWLINE:
            cout << "Newline" << endl;
            break;
        case PUNCTUATION:
            cout << "Punctuation" << endl;
            break;
        }
        //==================================================


    } while (token.lexeme != "");

    return 0;
}

