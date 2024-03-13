#ifndef LEXER_REGEX_H
#define LEXER_REGEX_H

#include <string>

class LexerRegex {
public:
    static bool matchIdentifier(const std::string& str);
    static bool matchNumber(const std::string& str);
    static bool matchOperator(const std::string& str);

private:
    static bool matchPattern(const std::string& str, const std::string& pattern);
};

#endif // LEXER_REGEX_H
