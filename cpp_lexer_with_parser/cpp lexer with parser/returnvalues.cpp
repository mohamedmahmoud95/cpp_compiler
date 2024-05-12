
#include "returnvalues.hpp"
using namespace std;
std::string returnTokenType( Token token) {
    switch (token.type) {
        case TOKEN_KEYWORD:
        case TOKEN_IDENTIFIER:
            return token.lexeme; // Return the actual name if it's a keyword or identifier
        case TOKEN_NUMBER:
        case TOKEN_FLOAT:
        case TOKEN_BINARY:
        case TOKEN_HEX:
        case TOKEN_OCTAL:
            return token.lexeme; // Return the actual value if it's a number
        case TOKEN_INCOP:
            return "INCOP";
        case TOKEN_DECOP:
            return "DECOP";
        case TOKEN_ANDOP:
            return "ANDOP";
        case TOKEN_OROP:
            return "OROP";
        case TOKEN_NOTOP:
            return "NOTOP";
        case TOKEN_ADDOP:
            return "ADDOP";
        case TOKEN_SUBOP:
            return "SUBOP";
        case TOKEN_MULOP:
            return "MULOP";
        case TOKEN_DIVOP:
            return "DIVOP";
        case TOKEN_MODOP:
            return "MODOP";
        case TOKEN_EQOP:
            return "EQOP";
        case TOKEN_NEQOP:
            return "NEQOP";
        case TOKEN_GTOP:
            return "GTOP";
        case TOKEN_LTOP:
            return "LTOP";
        case TOKEN_GTEOP:
            return "GTEOP";
        case TOKEN_LTEOP:
            return "LTEOP";
        case TOKEN_ASSIGNOP:
            return "ASSIGNOP";
        case TOKEN_ADDASSIGNOP:
            return "ADDASSIGNOP";
        case TOKEN_SUBASSIGNOP:
            return "SUBASSIGNOP";
        case TOKEN_MULASSIGNOP:
            return "MULASSIGNOP";
        case TOKEN_DIVASSIGNOP:
            return "DIVASSIGNOP";
        case TOKEN_MODASSIGNOP:
            return "MODASSIGNOP";
        case TOKEN_ANDASSIGNOP:
            return "ANDASSIGNOP";
        case TOKEN_ORASSIGNOP:
            return "ORASSIGNOP";
        case TOKEN_XORASSIGNOP:
            return "XORASSIGNOP";
        case TOKEN_LEFTASSIGNOP:
            return "LEFTASSIGNOP";
        case TOKEN_RIGHTASSIGNOP:
            return "RIGHTASSIGNOP";
        case TOKEN_TERNARYOPERATOR:
            return "Ternary Operator";
        case TOKEN_UNKNOWN:
            return "Unknown";
        case TOKEN_DATATYPE:
            return "Datatype";
        // Add cases for other token types as needed
        default:
            return "Undefined";
    }
}
