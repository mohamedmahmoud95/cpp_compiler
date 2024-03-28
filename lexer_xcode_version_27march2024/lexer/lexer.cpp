
#include "lexer.hpp"
#include "lexer_regex.hpp"
#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <stdio.h>

Lexer:: Lexer(const std::string& input) : input(input), position(0), bufferSize(4096) {
       // Initialize buffers
       currentBuffer = input.substr(0, std::min(bufferSize, input.length()));
       if (input.length() > bufferSize) {
           nextBuffer = input.substr(bufferSize, std::min(bufferSize, input.length() - bufferSize));
       }
       else {
           nextBuffer = "";
       }
   };

Token Lexer :: getNextToken() {
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



void Lexer :: swapBuffers() {
       // Move content of next buffer to current buffer
       currentBuffer = nextBuffer;
       // Load new content into next buffer
       size_t nextBufferStartPosition = position + currentBuffer.length();
       nextBuffer = input.substr(nextBufferStartPosition, bufferSize);
   }

   std:: string Lexer :: extractLexeme(const std::string& buffer) {
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
               if ((buffer[0] == '0' && (tolower(buffer[1] == 'x'))) || (buffer[0] == '0' && (tolower(buffer[1] == 'b')))) {
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
           LexerRegex::matchBitwiseOperator(buffer.substr(0, 2)) ||
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

   bool  Lexer :: isDelimiter(char c) {
       std::string delimiters = " \t\n\r";
       return delimiters.find(c) != std::string::npos;
   }



   void  Lexer :: handleToken(Token& token) {
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

        else if (LexerRegex::matchBitwiseOperator(token.lexeme)) {
           if (token.lexeme == "&") {
               token.type = TOKEN_Bitwise_AND;
           }
           else if (token.lexeme == "&") {
               token.type = TOKEN_Bitwise_AND;
           }
           else if (token.lexeme == "|") {
               token.type = TOKEN_Bitwise_OR;
           }
           else if (token.lexeme == "^") {
               token.type = TOKEN_Bitwise_XOR;
           }
           else if (token.lexeme == "~") {
               token.type = TOKEN_Bitwise_NOT;
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
