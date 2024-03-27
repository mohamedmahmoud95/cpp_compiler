//
//  token_types.h
//  lex
//
//  Created by Mohamed Raslan on 27/03/2024.
//

#ifndef token_types_h
#define token_types_h

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


#endif /* token_types_h */
