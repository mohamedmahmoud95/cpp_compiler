#include "regular_expressions.h"
#include <string>

bool LexerRegex::matchIdentifier(const std::string& str) {
    // Rregular expression pattern for identifiers:
    // starts with a letter, followed by zero or more alphanumeric characters
    static const std::string identifierPattern = "[a-zA-Z][a-zA-Z0-9]*";
    // Check if the given string matches the identifier pattern
    return matchPattern(str, identifierPattern);
}

bool LexerRegex::matchNumber(const std::string& str) {
    // Regular expression pattern for numbers:
    // matches one or more digit characters
    static const std::string numberPattern = "\\d+"; // matches a digit character
    return matchPattern(str, numberPattern);
}

bool LexerRegex::matchOperator(const std::string& str) {
    // Regular expression pattern for operators:
    static const std::string operatorPattern = "[\\+\\-\\*\\/=]";
    return matchPattern(str, operatorPattern);
}

bool LexerRegex::matchPattern(const std::string& str, const std::string& pattern) {
    // Initialize indices for traversing the input string and the pattern string that we are comparing with
    size_t strIndex = 0;
    size_t patternIndex = 0;

    // Iterate through both strings while comparing characters
    while (strIndex < str.length() && patternIndex < pattern.length()) {
        // Check for escaped characters in the pattern
        if (pattern[patternIndex] == '\\') {  // If the current character in pattern is a backslash
            patternIndex++;                   // Move to the next character in pattern
            // If the escaped character does not match the corresponding character in the input string, return false
            if (pattern[patternIndex] != str[strIndex])
                return false;
        } else if (pattern[patternIndex] != str[strIndex])
            return false;
        patternIndex++;
        strIndex++;
    }
    // If both strings have been completely traversed, return true indicating a match
    return patternIndex == pattern.length() && strIndex == str.length();
}
