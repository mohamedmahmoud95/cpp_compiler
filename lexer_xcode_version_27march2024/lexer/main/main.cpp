#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <set>
#include "function_to_print_token_type.hpp"
#include "lexer.hpp"
#include "lexer_regex.hpp"
#include <fstream>
#include "parser.hpp"
#include "token_types.h"
#include <memory>
#include "token_types.h"

using namespace std;

vector <Token> identifiers;
set<Token> listOfUniqeIdentifiers;
void extract_symbol_table_from_identifiers_list(vector<Token> identifiers);
void print_symbol_table();
string readSourceCode(const string& filename);
string getHardCoddedSourceCodeExample();
void print_token_stream(vector<Token> token_stream);

vector<Token> token_stream;
vector<Token> symbole_table;
void extract_token_stream_from_input_file(string source_code);
void extract_identifiers_from_token_stream(vector <Token> token_stream);

void export_symbol_table();
void export_token_stream();


// File to read the source code from
//If it says: "Error opening file: ", you probably need to change the path to the path where the file exists on your machine
string sourse_code_file_name_and_path = "/Users/mohamedraslan/Downloads/cpp_compiler-main/lexer_xcode_version_27march2024/lexer/input.txt";

string token_stream_output_file_name_and_path = "/Users/mohamedraslan/Downloads/cpp_compiler-main/lexer_xcode_version_27march2024/lexer/token_stream.txt";

string symbol_table_output_file_name_and_path = "/Users/mohamedraslan/Downloads/cpp_compiler-main/lexer_xcode_version_27march2024/lexer/symbol_table.txt";

int main() {
    
    string source_code = readSourceCode(sourse_code_file_name_and_path);
    //or, use the following hard codded source code example:
    //string inputString = getHardCoddedSourceCodeExample();
    
    Lexer lexer(source_code);
    Token token;
    extract_token_stream_from_input_file(source_code);
    extract_identifiers_from_token_stream(token_stream);
    extract_symbol_table_from_identifiers_list(identifiers);
    print_token_stream(token_stream);
    print_symbol_table();
    export_token_stream();
    export_symbol_table();
    return 0;
}

// Function to read source code from a file into a string
string readSourceCode(const string& filename) {
    ifstream inputFile(filename);

    // Error handling: Check if the file opened successfully
    if (!inputFile.is_open()) {
        cerr << "Error opening file: " << filename << endl;
               exit(1);
    }

    // Read the entire file content into a string
    string inputString;
    getline(inputFile, inputString, static_cast<char>(EOF));
    
    inputFile.close();
    
    return inputString;
}

string getHardCoddedSourceCodeExample(){
    return "bool private public protected class template :: 3.14e5 if x == y return 1; else return 0; while _cycle = 9; int frawla = 2098 ; int = --8++ ; [] [ ]  float zrka23elyamama zrka23elyamama zrka23elyamama = 0.221; 0b1010 12.345 0xABCD 0777 ;Ibrahim !Donia && ||; ()) === != % > < >= 8.98-- *= %= += -= <<= ^= ?: &= + - () [] {} \\ ? . , ; : # \n ' \" & | ^ ~";
}

void extract_symbol_table_from_identifiers_list(vector<Token> identifiers){
    // Insert elements from the vector into the set (duplicates will be automatically removed)
    for (int i = 0 ; i < identifiers.size() ; i++)
    {
        symbole_table.push_back(identifiers[i]);
    }
    
//    return listOfUniqeIdentifiers;
}

void print_token_stream(vector<Token> token_stream){
    cout<<"\n\n================================================\n";
    cout<<"printing token stream:\n";
    for (const Token& token : token_stream) {
        cout <<  "Token: " <<setw(10) << left << token.lexeme << setw(10) << right << "Type: " <<tokenTypeNames[token.type]<< endl;
    }
    cout<<"\n\n================================================\n";

}

void print_symbol_table(){
    cout<<"\n\n================================================\n";
    cout<<"printing sybmol table:\n";
    for (const Token& identifier : symbole_table) {
      cout << identifier.lexeme << endl;
    }
    cout<<"================================================\n";
}


void export_token_stream(){
    ofstream tokenStreamFile(token_stream_output_file_name_and_path);
    for (const Token& token : token_stream) {
        tokenStreamFile << "Token: " <<setw(10) << left << token.lexeme << setw(10) << right << "Type: " <<tokenTypeNames[token.type]<< endl;
    }
    tokenStreamFile.close();
}

void export_symbol_table(){
    ofstream symbolTableFile(symbol_table_output_file_name_and_path);
    for (const Token& identifier : symbole_table) {
        symbolTableFile << identifier.lexeme << endl;
    }
    symbolTableFile.close();
}



void extract_token_stream_from_input_file(string source_code)
{
    Token token;
    Lexer lexer(source_code);
    do {
        token = lexer.getNextToken();
        token_stream.push_back(token);
    } while (token.lexeme != "");
    
//    return token_stream;
}

void extract_identifiers_from_token_stream(vector <Token> token_stream){
    for (const Token& token : token_stream)
        {
            if((isalpha(token.lexeme[0]) || token.lexeme[0] == '_')){
                identifiers.push_back(token);
            }
        }
    }
    
