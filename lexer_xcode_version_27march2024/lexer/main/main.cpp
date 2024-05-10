#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include "function_to_print_token_type.hpp"
#include "lexer.hpp"
#include "lexer_regex.hpp"
#include <fstream>


using namespace std;
int main() {
    
    // File to read the source code from
    //If it says: "Error opening file: ", you probably need to change the path to the path where the file exists on your machine
    string filename = "/Users/mohamedraslan/Downloads/cpp_compiler-main/lexer_xcode_version_27march2024/lexer/input.txt";

    
    ifstream inputFile(filename);

    // Error handling: Check if the file opened successfully
    if (!inputFile.is_open()) {
      cerr << "Error opening file: " << filename << endl;
      return 1;
    }

    // Read the entire file content into a string
    string inputString;
    getline(inputFile, inputString, static_cast<char>(EOF));
    
    inputFile.close();

    // Create the lexer with the input string
    Lexer lexer(inputString);
   
//    // Sample input string
//    string input = "bool private public protected class template :: 3.14e5 if x == y return 1; else return 0; while _cycle = 9; int frawla = 2098 ; int = --8++ ; [] [ ]  float zrka23elyamama = 0.221; 0b1010 12.345 0xABCD 0777 ;Ibrahim !Donia && ||; ()) === != % > < >= 8.98-- *= %= += -= <<= ^= ?: &= + - () [] {} \\ ? . , ; : # \n ' \" & | ^ ~";

   // Lexer lexer(input);
    Token token;

    do {
        token = lexer.getNextToken();
        cout << "Token: " << token.lexeme << ", Type: ";
        printTokenType(token);
    } while (token.lexeme != "");

    return 0;
}


