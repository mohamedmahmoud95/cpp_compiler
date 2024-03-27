//
//  function_to_print_token_type.cpp
//  lex
//
//  Created by Mohamed Raslan on 27/03/2024.
//

#include "function_to_print_token_type.hpp"

void printTokenType(Token token) {
    
 switch (token.type) {
        case TOKEN_KEYWORD:
            std::cout << "Keyword" << std::endl;
            break;
        case TOKEN_IDENTIFIER:
            std::cout << "Identifier" << std::endl;
            break;
        case TOKEN_NUMBER:
            std::cout << "Number" << std::endl;
            break;
        case TOKEN_FLOAT:
            std::cout << "Float" << std::endl;
            break;
        case TOKEN_BINARY:
            std::cout << "Binary" << std::endl;
            break;
        case TOKEN_HEX:
            std::cout << "Hexadecimal" << std::endl;
            break;
        case TOKEN_OCTAL:
            std::cout << "Octal" << std::endl;
            break;
        case TOKEN_INCOP:
            std::cout << "INCOP" << std::endl;
            break;
        case TOKEN_DECOP:
            std::cout << "DECOP" << std::endl;
            break;
        case TOKEN_ANDOP:
            std::cout << "ANDOP" << std::endl;
            break;
        case TOKEN_OROP:
            std::cout << "OROP" << std::endl;
            break;
        case TOKEN_NOTOP:
            std::cout << "NOTOP" << std::endl;
            break;
        case TOKEN_ADDOP:
            std::cout << "ADDOP" << std::endl;
            break;
        case TOKEN_SUBOP:
            std::cout << "SUBOP" << std::endl;
            break;
        case TOKEN_MULOP:
            std::cout << "MULOP" << std::endl;
            break;
        case TOKEN_DIVOP:
            std::cout << "DIVOP" << std::endl;
            break;
        case TOKEN_MODOP:
            std::cout << "MODOP" << std::endl;
            break;

        case TOKEN_EQOP:
            std::cout << "EQOP" << std::endl;
            break;
        case TOKEN_NEQOP:
            std::cout << "NEQOP" << std::endl;
            break;
        case TOKEN_GTOP:
            std::cout << "GTOP" << std::endl;
            break;
        case TOKEN_LTOP:
            std::cout << "LTOP" << std::endl;
            break;
        case TOKEN_GTEOP:
            std::cout << "GTEOP" << std::endl;
            break;
        case TOKEN_LTEOP:
            std::cout << "LTEOP" << std::endl;
            break;
        case TOKEN_ASSIGNOP:
            std::cout << "ASSIGNOP" << std::endl;
            break;
        case TOKEN_ADDASSIGNOP:
            std::cout << "ADDASSIGNOP" << std::endl;
            break;
        case TOKEN_SUBASSIGNOP:
            std::cout << "SUBASSIGNOP" << std::endl;
            break;
        case TOKEN_MULASSIGNOP:
            std::cout << "MULASSIGNOP" << std::endl;
            break;
        case TOKEN_DIVASSIGNOP:
            std::cout << "DIVASSIGNOP" << std::endl;
            break;
        case TOKEN_MODASSIGNOP:
            std::cout << "MODASSIGNOP" << std::endl;
            break;
        case TOKEN_ANDASSIGNOP:
            std::cout << "ANDASSIGNOP" << std::endl;
            break;
        case TOKEN_ORASSIGNOP:
            std::cout << "ORASSIGNOP" << std::endl;
            break;
        case TOKEN_XORASSIGNOP:
            std::cout << "XORASSIGNOP" << std::endl;
            break;
        case TOKEN_LEFTASSIGNOP:
            std::cout << "LEFTASSIGNOP" << std::endl;
            break;
        case TOKEN_RIGHTASSIGNOP:
            std::cout << "RIGHTASSIGNOP" << std::endl;
            break;

        case TOKEN_TERNARYOPERATOR:
            std::cout << "Ternary Operator" << std::endl;
            break;
        case TOKEN_UNKNOWN:
            std::cout << "Unknown" << std::endl;
            break;
        case TOKEN_DATATYPE:
            std::cout << "Datatype" << std::endl;
            break;

        //==================================================
        // PUNCTUATIONAL tokens:
        case TOKEN_LEFT_PAREN:
            std::cout << "Left parenthesis" << std::endl;
            break;
        case TOKEN_RIGHT_PAREN:
            std::cout << "Right parenthesis" << std::endl;
            break;
        case TOKEN_LEFT_BRACE:
            std::cout << "Left brace" << std::endl;
            break;
        case TOKEN_RIGHT_BRACE:
            std::cout << "Right brace" << std::endl;
            break;
        case TOKEN_LEFT_BRACKET:
            std::cout << "Left bracket" << std::endl;
            break;
        case TOKEN_RIGHT_BRACKET:
            std::cout << "Right bracket" << std::endl;
            break;
        case TOKEN_COMMA:
            std::cout << "Comma" << std::endl;
            break;
        case TOKEN_PERIOD:
            std::cout << "Period" << std::endl;
            break;
        case TOKEN_SEMICOLON:
            std::cout << "Semi-colon" << std::endl;
            break;
        case TOKEN_COLON:
            std::cout << "Colon" << std::endl;
            break;
        case TOKEN_QUESTION:
            std::cout << "Question" << std::endl;
            break;
        case TOKEN_QUOTE:
            std::cout << "Quote" << std::endl;
            break;
        case TOKEN_DOUBLE_QUOTE:
            std::cout << "Double quote" << std::endl;
            break;
        case TOKEN_PREPROCESSOR_HASH:
            std::cout << "Preprocessor hash" << std::endl;
            break;
        case TOKEN_BACKSLASH:
            std::cout << "Backslash" << std::endl;
            break;
        case TOKEN_NEWLINE:
            std::cout << "Newline" << std::endl;
            break;
        case PUNCTUATION:
            std::cout << "Punctuation" << std::endl;
            break;
        
        //==================================================


        //==================================================
        // BITWISE_OPERATORS:
        case TOKEN_Bitwise_AND:
            std::cout << "Bitwise AND" << std::endl;
            break;
        case TOKEN_Bitwise_OR:
            std::cout << "Bitwise OR" << std::endl;
            break;
        case TOKEN_Bitwise_XOR:
            std::cout << "Bitwise XOR" << std::endl;
            break;
        case TOKEN_Bitwise_NOT:
            std::cout << "Bitwise NOT" << std::endl;
            break;
        //==================================================

        }
}


