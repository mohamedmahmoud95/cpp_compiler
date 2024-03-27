#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include "lexer_regex.hpp"
#include "lexer.hpp"
#include "function_to_print_token_type.hpp"

using namespace std;


int main() {
    // Sample input string
    string input = "3.14e5 if x == y return 1; else return 0; while _cycle = 9; int frawla = 2098 ; int = --8++ ; [] [ ]  float zrka23elyamama = 0.221; 0b1010 12.345 0xABCD 0777 ;Ibrahim !Donia && ||; ()) === != % > < >= 8.98-- *= %= += -= <<= ^= ?: &= + - () [] {} \\ ? . , ; : # \n ' \" & | ^ ~";

    Lexer lexer(input);
    Token token;

    do {
        token = lexer.getNextToken();
        cout << "Token: " << token.lexeme << ", Type: ";
        printTokenType(token);
    } while (token.lexeme != "");

    return 0;
}

