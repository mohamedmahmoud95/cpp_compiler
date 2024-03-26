#ifndef lexer_h
#define lexer_h

#include "lexer_regex.h"
#include "token_types.cpp"


struct Token {
    TokenType type;
    std::string lexeme;
};



class Lexer {
public:
    Lexer(const std::string& input);
    Token getNextToken() ;
    
private:
    const std::string input;
    size_t position;
    std::string currentBuffer;
    std::string nextBuffer;
    const size_t bufferSize;

    void swapBuffers();

    std::string extractLexeme(const std::string& buffer);
};
