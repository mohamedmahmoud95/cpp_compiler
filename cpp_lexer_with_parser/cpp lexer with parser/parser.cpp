#include <string>
#include <deque>
#include <fstream>
#include <iostream>
#include "lexer.hpp"
#include "lexer.cpp"
#include "lexer_regex.hpp"
#include "lexer_regex.cpp"
#include "function_to_print_token_type.hpp"
#include "function_to_print_token_type.cpp"
#include "token_types.h"
using namespace std;




class parse_tree_node {
public:
    bool is_terminal;
    std::string label;
    std::deque<parse_tree_node*> children;

    parse_tree_node(std::string l, bool t) : is_terminal(t), label(l) {}
};

// A function to uniquely identify the node in graphviz dot style
std::ostream& operator<<(std::ostream& out, parse_tree_node* node) {
    out << "\"" << (void*) node << "\" [label=\"" << node->label << "\"]";
    return out;
}
class Parser2 {
    Lexer lexer;
    Token current_token;

public:
    Parser2(const std::string& input) : lexer(input) {}

    parse_tree_node* recursively_descend_with_lookahead();
    

private:
    bool match_input(int token_type, std::string* name =nullptr, std::string* value =nullptr);
    parse_tree_node* enumerator_with_lookahead();
    parse_tree_node* enumeratorvalueexpr_with_lookahead();
    parse_tree_node* enumlistbody_with_lookahead();
    parse_tree_node* enumlistoptional_with_lookahead();
    parse_tree_node* enumlist_with_lookahead();
    parse_tree_node* enumexpr_with_lookahead();
    parse_tree_node* enumexprbody_with_lookahead();

    parse_tree_node* parse_simple_expression_with_lookahead();
    parse_tree_node* parse_if_statement_with_lookahead();
    
    /*full recursive*/
    parse_tree_node* program_with_lookahead();
    parse_tree_node* declaration_list_with_lookahead();
    parse_tree_node* declaration_with_lookahead();
    parse_tree_node* var_declaration_with_lookahead();
    parse_tree_node* var_decl_list_with_lookahead();
    parse_tree_node* var_decl_init_with_lookahead();
    parse_tree_node* fun_declaration_with_lookahead();
    parse_tree_node* parameter_list_with_lookahead();
    parse_tree_node* parm_type_list_with_lookahead();
    parse_tree_node* parm_id_list_with_lookahead();
    parse_tree_node* parm_id_with_lookahead();
    parse_tree_node* compound_stmt_with_lookahead();
    parse_tree_node* local_declarations_with_lookahead();
    parse_tree_node* scoped_var_declaration_with_lookahead();
    parse_tree_node* statement_list_with_lookahead();
    parse_tree_node* statement_with_lookahead();
    parse_tree_node* expression_stmt_with_lookahead();
    parse_tree_node* selection_stmt_with_lookahead();
    parse_tree_node* iteration_stmt_with_lookahead();
    parse_tree_node* return_stmt_with_lookahead();
    parse_tree_node* break_stmt_with_lookahead();
    parse_tree_node* expression_with_lookahead();
    parse_tree_node* simple_expression_with_lookahead();
    parse_tree_node* and_expression_with_lookahead();
    parse_tree_node* unary_rel_expression_with_lookahead();
    parse_tree_node* rel_expression_with_lookahead();
    parse_tree_node* minmax_expression_with_lookahead();
    parse_tree_node* sum_expression_with_lookahead();
    parse_tree_node* mul_expression_with_lookahead();
    parse_tree_node* unary_expression_with_lookahead();
    parse_tree_node* factor_with_lookahead();
    parse_tree_node* mutable_with_lookahead();
    parse_tree_node* immutable_with_lookahead();
    parse_tree_node* call_with_lookahead();
    parse_tree_node* args_with_lookahead();
    parse_tree_node* arg_list_with_lookahead();
    parse_tree_node* constant_with_lookahead();
    parse_tree_node* body_with_lookahead();
    parse_tree_node* single_statement_with_lookahead();
    parse_tree_node* sub_body_with_lookahead();
    parse_tree_node* if_statement_with_lookahead();
    parse_tree_node* statements_with_lookahead();
    parse_tree_node* conditional_statements_with_lookahead();
    parse_tree_node* else_part_with_lookahead();
    parse_tree_node* switch_expr_with_lookahead();
    parse_tree_node* case_expr_with_lookahead();
    parse_tree_node* default_expr_with_lookahead();
    parse_tree_node* iterative_statements_with_lookahead();
    parse_tree_node* for_loop_with_lookahead();
    parse_tree_node* while_loop_with_lookahead();
    parse_tree_node* do_while_loop_with_lookahead();
     

   
};



// Parse Tree visualizer, and as usual with recursive tree visualizers we need an auxiliary function
void visualize_parse_tree(parse_tree_node* root);
void visualize_parse_tree_aux(parse_tree_node* node, std::ostream& out);


bool Parser2::match_input(int token_type, std::string* name , std::string* value ) {
    current_token = lexer.getNextToken();
    if (current_token.type != token_type) return false;
    if (name != nullptr && current_token.name != *name) return false;
    return true;

}

parse_tree_node* Parser2::recursively_descend_with_lookahead() { 
   return program_with_lookahead();
}


void visualize_parse_tree(parse_tree_node* root) {

    std::ofstream dot_file_out("parse_tree.dot", std::ios::trunc);

    // TODO: Would be nice if you decorated your parse tree, lookup how to do so in graphviz dot notation
    dot_file_out << "digraph G {\n";
    visualize_parse_tree_aux(root, dot_file_out);
    dot_file_out << "}";
    dot_file_out.close();

    // Convert the dot file into a SVG vector image
    system("dot -Tsvg ./parse_tree.dot -oparse_tree.svg");

    // Open the vector file
    // TODO: Integrate this with your GUI...
    // You'll need to lookup how to open an .svg file inside Qt or whatever GUI framework you are using
    system("parse_tree.svg");

}

void visualize_parse_tree_aux(parse_tree_node* node, std::ostream& out) {

    // Need to uniquely identify each node in graphviz
    out << "  " << node << (node->is_terminal ? "[fontcolor=\"red\"][color=\"red\"];\n" : ";\n");

    for (auto child : node->children) {

        bool child_has_children = child->children.size() > 0;
        if (child->is_terminal || (!child->is_terminal && child_has_children)) {

            // Need to uniquely identify each child node too
            out << "  " << child << ";\n";

            // Create edge between node and child unique addresses
            out << "  \"" << (void*) node << "\" -> \"" << (void*) child << "\";\n";

            // Recursively build rest of tree
            visualize_parse_tree_aux(child, out);

        }

    }

}
parse_tree_node* Parser2::parse_simple_expression_with_lookahead() {
    parse_tree_node* current_node = new parse_tree_node("simple-expression", false);

    // Parse the left operand (X)
    if (match_input(TOKEN_IDENTIFIER)) {
        current_node->children.push_back(new parse_tree_node("operand: " + current_token.lexeme, true));
    } else {
        delete current_node;
        return nullptr;
    }

    // Parse the operator (+)
    if (match_input(TOKEN_ADDOP)) {
        current_node->children.push_back(new parse_tree_node("operator: +", true));
    } else {
        delete current_node;
        return nullptr;
    }

    // Parse the right operand (Y)
    if (match_input(TOKEN_IDENTIFIER)) {
        current_node->children.push_back(new parse_tree_node("operand: " + current_token.lexeme, true));
    } else {
        delete current_node;
        return nullptr;
    }

    // Parse the equal sign (=)
    if (match_input(TOKEN_ASSIGNOP)) {
        current_node->children.push_back(new parse_tree_node("operator: =", true));
    } else {
        delete current_node;
        return nullptr;
    }

    // Parse the constant (3)
    if (match_input(TOKEN_NUMBER)) {
        current_node->children.push_back(new parse_tree_node("constant: " + current_token.lexeme, true));
    } else {
        delete current_node;
        return nullptr;
    }

    return current_node;
}

// enum-expr → enum enum-expr-body
parse_tree_node*Parser2:: enumexpr_with_lookahead() {

    parse_tree_node* current_node = new parse_tree_node("enum-expr", false);

    // Lookahead won't help here since we don't have choices to pick from based on the lookahead anyway

    std::string enum_str = std::string("enum");
    if (match_input(TOKEN_KEYWORD, &enum_str)) current_node->children.push_back(new parse_tree_node("enum", true));
    else return nullptr;

    parse_tree_node* enumexprbody = enumexprbody_with_lookahead();
    if (enumexprbody) current_node->children.push_back(enumexprbody);
    else return nullptr;

    return current_node;

}

// enum-expr-body → identifier { enum-list } 
//                | { enum-list }
parse_tree_node*Parser2:: enumexprbody_with_lookahead() {

    parse_tree_node* current_node = new parse_tree_node("enum-expr-body", false);

    // Although we have a choice here, since the choice is whether to omit or keep "identifier", it still doesn't matter

    if (match_input(TOKEN_IDENTIFIER)) current_node->children.push_back(new parse_tree_node("identifier:\\n" + current_token.name, true));

    if (match_input(TOKEN_LEFT_BRACE)) current_node->children.push_back(new parse_tree_node("{", true));
    else return nullptr;

    parse_tree_node* enumlist = enumlist_with_lookahead();
    if (enumlist) current_node->children.push_back(enumlist);
    else return nullptr;

    if (match_input(TOKEN_RIGHT_BRACE)) current_node->children.push_back(new parse_tree_node("}", true));
    else return nullptr;

    return current_node;

}

// enum-list → enumerator enum-list-body
parse_tree_node*Parser2:: enumlist_with_lookahead() {

    parse_tree_node* current_node = new parse_tree_node("enum-list", false);

    // No choices here, lookahead useless again

    parse_tree_node* enumerator = enumerator_with_lookahead();

    if (enumerator) current_node->children.push_back(enumerator);
    else return nullptr;

    parse_tree_node* enumlistbody = enumlistbody_with_lookahead();
    if (enumlistbody) current_node->children.push_back(enumlistbody);
    else return nullptr;

    return current_node;

}

// enum-list-body → ε
//                | , enum-list-optional
parse_tree_node*Parser2:: enumlistbody_with_lookahead() {

    parse_tree_node* current_node = new parse_tree_node("enum-list-body", false);

    // Here, we have choices, but only one terminal in the choices (the other is "epsilon")
    // So, the lookahead here can't help much either.. if you don't see a comma, simply return, no problem.

    if (match_input(TOKEN_COMMA)) {
        current_node->children.push_back(new parse_tree_node(",", true));
        parse_tree_node* enumlistoptional = enumlistoptional_with_lookahead();
        if (enumlistoptional) current_node->children.push_back(enumlistoptional);
        else return nullptr;
    }
    return current_node;

}

// enum-list-optional → ε
//                    | enum-list
parse_tree_node*Parser2::enumlistoptional_with_lookahead() {

    parse_tree_node* current_node = new parse_tree_node("enum-list-optional", false);

    parse_tree_node* enumlist = enumlist_with_lookahead();
    if (enumlist) current_node->children.push_back(enumlist);
    else { /* do nothing */ }

    return current_node;

}

// enumerator → enumeration-constant enumerator-value-expr
parse_tree_node*Parser2:: enumerator_with_lookahead() {

    parse_tree_node* current_node = new parse_tree_node("enumerator", false);

    // No choices here, lookahead useless, AGAIN!

    if (match_input(TOKEN_IDENTIFIER)) current_node->children.push_back(new parse_tree_node("enumeration-constant:\\n" + current_token.name, true));
    else return nullptr;

    parse_tree_node* enumeratorvalueexpr = enumeratorvalueexpr_with_lookahead();
    if (enumeratorvalueexpr) current_node->children.push_back(enumeratorvalueexpr);
    else return nullptr;

    return current_node;

}

// enumerator-value-expr → ε
//                       | = constant-expression
parse_tree_node*Parser2::enumeratorvalueexpr_with_lookahead() {

    parse_tree_node* current_node = new parse_tree_node("enumerator-value-expr", false);

    // Finally, a case that lookahead helps in.. kinda?
    // If we lookahead and see an '=', we proceed with its branch
    // Otherwise, we return the node (since that is the other branch; epsilon "matched")
    if (match_input(TOKEN_ASSIGNOP)) {
        current_node->children.push_back(new parse_tree_node("=", true));
        if (match_input(TOKEN_NUMBER)) {
        
            current_node->children.push_back(new parse_tree_node("constant-expression:\\n" + current_token.lexeme, true));
        } else return nullptr;
    }
    return current_node;

}




/*ZEYAD'S*/


// program → declaration_list
parse_tree_node*Parser2:: program_with_lookahead() {
    return declaration_list_with_lookahead();
}

// declaration_list → declaration_list declaration | declaration
parse_tree_node*Parser2:: declaration_list_with_lookahead() {
    parse_tree_node* current_node = new parse_tree_node("declaration_list", false);

    parse_tree_node* declaration = declaration_with_lookahead();
    if (!declaration)
        return nullptr; // No declaration to parse

    current_node->children.push_back(declaration);

    // Try to parse more declarations
    parse_tree_node* more_declarations = declaration_list_with_lookahead();
    if (more_declarations)
        current_node->children.push_back(more_declarations);

    return current_node;
}

// declaration → var_declaration | fun_declaration
parse_tree_node*Parser2:: declaration_with_lookahead() {
    parse_tree_node* var_declaration = var_declaration_with_lookahead();
    if (var_declaration)
        return var_declaration;

    return fun_declaration_with_lookahead();
}

// var_declaration → type_specifier var_decl_list SEMICOLON | STATIC type_specifier var_decl_list SEMICOLON
parse_tree_node*Parser2:: var_declaration_with_lookahead() {
    parse_tree_node* current_node = new parse_tree_node("var_declaration", false);
    std::string static_str = "static";
    if (match_input(TOKEN_KEYWORD, &static_str, nullptr)) {
        current_node->children.push_back(new parse_tree_node("static", true));
    }

    parse_tree_node* type_specifier = expression_with_lookahead();
    if (!type_specifier)
        return nullptr;

    current_node->children.push_back(type_specifier);

    parse_tree_node* var_decl_list = var_decl_list_with_lookahead();
    if (!var_decl_list)
        return nullptr;

    current_node->children.push_back(var_decl_list);

    std::string semicolon_str = ";";
    if (!match_input(TOKEN_SEMICOLON, &semicolon_str, nullptr))
        return nullptr;

    return current_node;
}

// var_decl_list → var_decl_list COMMA var_decl_init | var_decl_init
parse_tree_node*Parser2:: var_decl_list_with_lookahead() {
    parse_tree_node* current_node = new parse_tree_node("var_decl_list", false);

    parse_tree_node* var_decl_init = var_decl_init_with_lookahead();
    if (!var_decl_init)
        return nullptr;

    current_node->children.push_back(var_decl_init);

    std::string comma_str = ",";
    if (!match_input(TOKEN_COMMA, &comma_str, nullptr))
        return current_node;

    parse_tree_node* more_var_decl_list = var_decl_list_with_lookahead();
    if (!more_var_decl_list)
        return nullptr;

    current_node->children.push_back(more_var_decl_list);

    return current_node;
}

// var_decl_init → IDENTIFIER | IDENTIFIER LBRACKET NUMBER RBRACKET | IDENTIFIER ASSIGN expression
parse_tree_node*Parser2:: var_decl_init_with_lookahead() {
    parse_tree_node* current_node = new parse_tree_node("var_decl_init", false);
    if (!match_input(TOKEN_IDENTIFIER))
        return nullptr;

    current_node->children.push_back(new parse_tree_node("identifier", true));

    std::string leftbrack_str = "[";
    std::string assignop_str = "=";

    if (match_input(TOKEN_LEFT_BRACKET, &leftbrack_str, nullptr)) {
        current_node->children.push_back(new parse_tree_node("[", true));

        if (!match_input(TOKEN_NUMBER))
            return nullptr;

        current_node->children.push_back(new parse_tree_node(current_token.lexeme, true)); 

        std::string rightbrack_str = "]";
        if (!match_input(TOKEN_RIGHT_BRACKET, &rightbrack_str, nullptr))
            return nullptr;

        current_node->children.push_back(new parse_tree_node("]", true));
    }

    
    else if (match_input(TOKEN_ASSIGNOP, &assignop_str, nullptr)) {

        current_node->children.push_back(new parse_tree_node("=", true));

        parse_tree_node* expression = expression_with_lookahead();
        if (!expression)
            return nullptr;

        current_node->children.push_back(expression);
    }

    return current_node;
}

// fun_declaration → type_specifier IDENTIFIER LPAREN parameter_list RPAREN compound_stmt | IDENTIFIER LPAREN parameter_list RPAREN compound_stmt
parse_tree_node*Parser2:: fun_declaration_with_lookahead() {
    parse_tree_node* current_node = new parse_tree_node("fun_declaration", false);
    parse_tree_node* type_specifier = nullptr;
    if (match_input(TOKEN_DATATYPE, nullptr)) {
        type_specifier = new parse_tree_node(current_token.name, true);
        current_node->children.push_back(type_specifier);
    }

    if (!match_input(TOKEN_IDENTIFIER))
        return nullptr;

    current_node->children.push_back(new parse_tree_node(current_token.name, true));

    if (!match_input(TOKEN_LEFT_PAREN, nullptr))
        return nullptr;

    parse_tree_node* parameter_list = parameter_list_with_lookahead();
    if (!parameter_list)
        return nullptr;

    current_node->children.push_back(parameter_list);

    if (!match_input(TOKEN_RIGHT_PAREN, nullptr))
        return nullptr;

    parse_tree_node* compound_stmt = compound_stmt_with_lookahead();

    if (!compound_stmt)
        return nullptr;

    current_node->children.push_back(compound_stmt);

    return current_node;
}

// parameter_list → parameter_list COMMA parm_type_list | parm_type_list | /* epsilon */;
parse_tree_node*Parser2:: parameter_list_with_lookahead() {
    parse_tree_node* current_node = new parse_tree_node("parameter_list", false);

    parse_tree_node* parm_type_list = parm_type_list_with_lookahead();
    if (!parm_type_list)
        return nullptr;

    current_node->children.push_back(parm_type_list);

    std::string comma_str = ",";
    if (match_input(TOKEN_COMMA, &comma_str, nullptr)) {
        current_node->children.push_back(new parse_tree_node(",", true));

        parse_tree_node* more_parameter_list = parameter_list_with_lookahead();
        if (!more_parameter_list)
            return nullptr;

        current_node->children.push_back(more_parameter_list);
    }

    return current_node;
}

// parm_type_list → type_specifier parm_id_list
parse_tree_node*Parser2:: parm_type_list_with_lookahead() {

    parse_tree_node* current_node = new parse_tree_node("parm_type_list", false);

    parse_tree_node* type_specifier = expression_with_lookahead();
    if (!type_specifier)
        return nullptr;

    current_node->children.push_back(type_specifier);

    parse_tree_node* parm_id_list = parm_id_list_with_lookahead();
    if (!parm_id_list)
        return nullptr;

    current_node->children.push_back(parm_id_list);

    return current_node;
}

// parm_id_list → parm_id_list COMMA parm_id | parm_id;
parse_tree_node*Parser2:: parm_id_list_with_lookahead() {
    parse_tree_node* current_node = new parse_tree_node("parm_id_list", false);

    parse_tree_node* parm_id = parm_id_with_lookahead();
    if (!parm_id)
        return nullptr;

    current_node->children.push_back(parm_id);

    std::string comma_str = ",";
    if (match_input(TOKEN_COMMA, &comma_str, nullptr)) {
        current_node->children.push_back(new parse_tree_node(",", true));

        parse_tree_node* more_parm_id_list = parm_id_list_with_lookahead();
        if (!more_parm_id_list)
            return nullptr;

        current_node->children.push_back(more_parm_id_list);
    }

    return current_node;
}

// parm_id → IDENTIFIER | IDENTIFIER LBRACKET RBRACKET;
parse_tree_node*Parser2:: parm_id_with_lookahead() {
    parse_tree_node* current_node = new parse_tree_node("parm_id", false);

    if (!match_input(TOKEN_IDENTIFIER))
        return nullptr;

    current_node->children.push_back(new parse_tree_node(current_token.name, true));

    std::string leftbrack_str = "[";
    if (match_input(TOKEN_LEFT_BRACKET, &leftbrack_str, nullptr)) {
        current_node->children.push_back(new parse_tree_node("[", true));

        std::string rightbrack_str = "]";
        if (!match_input(TOKEN_RIGHT_BRACKET, &rightbrack_str, nullptr))
            return nullptr;

        current_node->children.push_back(new parse_tree_node("]", true));
    }

    return current_node;
}

// compound_stmt → LBRACE local_declarations statement_list RBRACE;
parse_tree_node*Parser2:: compound_stmt_with_lookahead() {
    parse_tree_node* current_node = new parse_tree_node("compound_stmt", false);

    std::string leftbrack_str = "[";
    if (!match_input(TOKEN_LEFT_BRACKET, &leftbrack_str, nullptr))
        return nullptr;

    parse_tree_node* local_declarations = local_declarations_with_lookahead();
    if (local_declarations)
        current_node->children.push_back(local_declarations);

    parse_tree_node* statement_list = statement_list_with_lookahead();
    if (statement_list)
        current_node->children.push_back(statement_list);

    std::string rightbrack_str = "]";
    if (!match_input(TOKEN_RIGHT_BRACKET, &rightbrack_str, nullptr))
        return nullptr;

    return current_node;
}

parse_tree_node*Parser2:: local_declarations_with_lookahead() {
    parse_tree_node* current_node = new parse_tree_node("local_declarations", false);

    parse_tree_node* scoped_var_declaration = scoped_var_declaration_with_lookahead();
    if (scoped_var_declaration)
        current_node->children.push_back(scoped_var_declaration);

    if (current_token.type == TOKEN_DATATYPE) {
        parse_tree_node* more_local_declarations = local_declarations_with_lookahead();
        if (more_local_declarations)
            current_node->children.push_back(more_local_declarations);
    }

    return current_node;
}


// scoped_var_declaration → type_specifier var_decl_list SEMICOLON;
parse_tree_node*Parser2:: scoped_var_declaration_with_lookahead() {
    parse_tree_node* current_node = new parse_tree_node("scoped_var_declaration", false);

    parse_tree_node* type_specifier = expression_with_lookahead();
    if (!type_specifier)
        return nullptr;

    current_node->children.push_back(type_specifier);

    parse_tree_node* var_decl_list = var_decl_list_with_lookahead();
    if (!var_decl_list)
        return nullptr;

    current_node->children.push_back(var_decl_list);

    std::string semicolon_str = ";";
    if (!match_input(TOKEN_SEMICOLON, &semicolon_str, nullptr))
        return nullptr;

    return current_node;
}

// statement_list → statement_list statement | /* epsilon */;
parse_tree_node*Parser2:: statement_list_with_lookahead() {
    parse_tree_node* current_node = new parse_tree_node("statement_list", false);

    parse_tree_node* statement = statement_with_lookahead();
    if (statement)
        current_node->children.push_back(statement);

    //if (current_token_index < tokens.size() && tokens[current_token_index].type == "IDENTIFIER") {
    //    parse_tree_node* more_statement_list = statement_list_with_lookahead();
    //    if (more_statement_list)
    //        current_node->children.push_back(more_statement_list);
    //}

    return current_node;
}

// statement → expression_stmt | compound_stmt | selection_stmt | iteration_stmt | return_stmt | break_stmt | CONTINUE SEMICOLON;
parse_tree_node*Parser2:: statement_with_lookahead() {
    parse_tree_node* current_node = new parse_tree_node("statement", false);
    std::string if_str = "if";
    std::string while_str = "while";
    std::string do_str = "do";
    std::string for_str = "for";
    std::string return_str = "return";
    std::string break_str = "break";
    std::string continue_str = "continue";
    std::string semicolon_str = ";";


    if (match_input(TOKEN_IDENTIFIER, nullptr)) {
        parse_tree_node* expression_stmt = expression_stmt_with_lookahead();
        if (expression_stmt)
            current_node->children.push_back(expression_stmt);
    }

    
    else if (match_input(TOKEN_KEYWORD, &if_str, nullptr)) {
        parse_tree_node* selection_stmt = selection_stmt_with_lookahead();
        if (selection_stmt)
            current_node->children.push_back(selection_stmt);
    }
    else if (match_input(TOKEN_KEYWORD, &while_str, nullptr) || (match_input(TOKEN_KEYWORD, &do_str, nullptr)) || (match_input(TOKEN_KEYWORD, &for_str, nullptr))) {
        parse_tree_node* iteration_stmt = iteration_stmt_with_lookahead();
        if (iteration_stmt)
            current_node->children.push_back(iteration_stmt);
    }
    else if (match_input(TOKEN_KEYWORD, &return_str, nullptr)) {
        parse_tree_node* return_stmt = return_stmt_with_lookahead();
        if (return_stmt)
            current_node->children.push_back(return_stmt);
    }

    else if (match_input(TOKEN_KEYWORD, &break_str, nullptr)) {
        parse_tree_node* break_stmt = break_stmt_with_lookahead();
        if (break_stmt)
            current_node->children.push_back(break_stmt);
    }
    else if (match_input(TOKEN_KEYWORD, &continue_str, nullptr)) {
        current_node->children.push_back(new parse_tree_node("CONTINUE", true));

        if (!match_input(TOKEN_SEMICOLON, &semicolon_str, nullptr))
            return nullptr;
        current_node->children.push_back(new parse_tree_node(";", true));
    }
    else {
        // No matching statement
        return nullptr;

    }

    return current_node;
}

// expression_stmt → expression SEMICOLON | SEMICOLON;
parse_tree_node*Parser2:: expression_stmt_with_lookahead() {
    parse_tree_node* current_node = new parse_tree_node("expression_stmt", false);
    std::string semicolon_str = ";";
    if (match_input(TOKEN_SEMICOLON, &semicolon_str, nullptr)) {
        current_node->children.push_back(new parse_tree_node(";", true));
        return current_node;
    }

    parse_tree_node* expression = expression_with_lookahead();
    if (!expression)
        return nullptr;

    current_node->children.push_back(expression);

    if (!match_input(TOKEN_SEMICOLON, &semicolon_str, nullptr))
        return nullptr;

    current_node->children.push_back(new parse_tree_node(";", true));

    return current_node;
}

// selection_stmt → (DONE BEFORE)
parse_tree_node*Parser2:: selection_stmt_with_lookahead() {
    parse_tree_node* current_node = new parse_tree_node("selection_stmt", false);
    parse_tree_node* single_statement_with_lookahead();


    return current_node;
}

// iteration_stmt → (DONE BEFORE)
parse_tree_node*Parser2:: iteration_stmt_with_lookahead() {
    parse_tree_node* current_node = new parse_tree_node("iteration_stmt", false);
    parse_tree_node* single_statement_with_lookahead();

        return current_node;
}

// return_stmt → RETURN SEMICOLON | RETURN expression SEMICOLON;
parse_tree_node*Parser2:: return_stmt_with_lookahead() {
    parse_tree_node* current_node = new parse_tree_node("return_stmt", false);
    std::string semicolon_str = ";";
    std::string return_str = "return";

    if (!match_input(TOKEN_KEYWORD, &return_str, nullptr))
        return nullptr;

    current_node->children.push_back(new parse_tree_node("return", true));

    if (match_input(TOKEN_SEMICOLON, &semicolon_str, nullptr)) {
        current_node->children.push_back(new parse_tree_node(";", true));
        return current_node;
    }

    parse_tree_node* expression = expression_with_lookahead();
    if (!expression)
        return nullptr;

    current_node->children.push_back(expression);

    if (!match_input(TOKEN_SEMICOLON, &semicolon_str, nullptr))
        return nullptr;


    current_node->children.push_back(new parse_tree_node(";", true));

    return current_node;
}

// break_stmt → BREAK SEMICOLON;
parse_tree_node*Parser2:: break_stmt_with_lookahead() {
    parse_tree_node* current_node = new parse_tree_node("break_stmt", false);
    std::string return_str = "return";
    std::string break_str = "break";
    std::string continue_str = "continue";
    std::string semicolon_str = ";";

    if (!match_input(TOKEN_KEYWORD, &break_str, nullptr))
        return nullptr;

    current_node->children.push_back(new parse_tree_node("break", true));

    if (!match_input(TOKEN_SEMICOLON, &semicolon_str, nullptr))
        return nullptr;

    current_node->children.push_back(new parse_tree_node(";", true));
    return current_node;
}

// expression → mutable ASSIGN expression | mutable PLUS_ASSIGN expression | mutable MINUS_ASSIGN expression | mutable TIMES_ASSIGN expression | mutable DIV_ASSIGN expression | mutable MOD_ASSIGN expression | mutable INCREMENT | mutable DECREMENT | simple_expression;
parse_tree_node*Parser2:: expression_with_lookahead() {

    parse_tree_node* current_node = new parse_tree_node("expression", false);

    parse_tree_node* mutable_node = mutable_with_lookahead();
    if (!mutable_node)
        return nullptr;

    std::string semicolon_str = ";";
    std::string assignop_str = "=";
    std::string addassignop_str = "+=";
    std::string subassignop_str = "-=";
    std::string mulassignop_str = "-=";
    std::string divassignop_str = "-=";
    std::string modassignop_str = "-=";
    std::string incop_str = "++";
    std::string decop_str = "--";


    current_node->children.push_back(mutable_node);

    if (match_input(TOKEN_ASSIGNOP, &assignop_str , nullptr) || match_input(TOKEN_ADDASSIGNOP, &addassignop_str, nullptr) || match_input(TOKEN_SUBASSIGNOP, &subassignop_str, nullptr) || match_input(TOKEN_MULASSIGNOP, &mulassignop_str, nullptr) || match_input(TOKEN_DIVASSIGNOP, &divassignop_str, nullptr) || match_input(TOKEN_MODASSIGNOP, &modassignop_str, nullptr)) {
        current_node->children.push_back(new parse_tree_node(current_token.name, true));

        parse_tree_node* expression = expression_with_lookahead();
        if (!expression)
            return nullptr;

        current_node->children.push_back(expression);
    }
    else if (match_input(TOKEN_INCOP, &incop_str, nullptr) || match_input(TOKEN_DECOP, &decop_str, nullptr)) {
        current_node->children.push_back(new parse_tree_node(current_token.name, true));
    }
    else {
        parse_tree_node* simple_expression = simple_expression_with_lookahead();
        if (!simple_expression)
            return nullptr;

        current_node->children.push_back(simple_expression);
    }

    return current_node;
}

// simple_expression → simple_expression OR and_expression | and_expression;
parse_tree_node*Parser2:: simple_expression_with_lookahead() {
    parse_tree_node* current_node = new parse_tree_node("simple_expression", false);

    parse_tree_node* and_expression = and_expression_with_lookahead();
    if (!and_expression)
        return nullptr;

    current_node->children.push_back(and_expression);
    std::string orop_str = "OR";
    if (match_input(TOKEN_OROP, &orop_str, nullptr)) {
        current_node->children.push_back(new parse_tree_node("OR", true));

        parse_tree_node* more_simple_expression = simple_expression_with_lookahead();
        if (!more_simple_expression)
            return nullptr;

        current_node->children.push_back(more_simple_expression);
    }

    return current_node;
}

// and_expression → and_expression AND unary_rel_expression | unary_rel_expression;
parse_tree_node*Parser2:: and_expression_with_lookahead() {
    parse_tree_node* current_node = new parse_tree_node("and_expression", false);

    parse_tree_node* unary_rel_expression = unary_rel_expression_with_lookahead();
    if (!unary_rel_expression)
        return nullptr;

    current_node->children.push_back(unary_rel_expression);

    std::string andop_str = "AND";

    if (match_input(TOKEN_ANDOP, &andop_str, nullptr)) {
        current_node->children.push_back(new parse_tree_node("AND", true));

        parse_tree_node* more_and_expression = and_expression_with_lookahead();
        if (!more_and_expression)
            return nullptr;

        current_node->children.push_back(more_and_expression);
    }

    return current_node;
}

// unary_rel_expression → NOT unary_rel_expression | rel_expression;
parse_tree_node*Parser2:: unary_rel_expression_with_lookahead() {
    parse_tree_node* current_node = new parse_tree_node("unary_rel_expression", false);
    std::string notop_str = "NOT";

    if (match_input(TOKEN_NOTOP, &notop_str, nullptr)) {
        current_node->children.push_back(new parse_tree_node("NOT", true));

        parse_tree_node* unary_rel_expression = unary_rel_expression_with_lookahead();
        if (!unary_rel_expression)
            return nullptr;

        current_node->children.push_back(unary_rel_expression);
    }
    else {
        parse_tree_node* rel_expression = rel_expression_with_lookahead();
        if (!rel_expression)
            return nullptr;

        current_node->children.push_back(rel_expression);
    }

    return current_node;
}

parse_tree_node*Parser2:: rel_expression_with_lookahead() {
    parse_tree_node* current_node = new parse_tree_node("rel_expression", false);

    parse_tree_node* minmax_expression = minmax_expression_with_lookahead();
    if (!minmax_expression)
        return nullptr;

    current_node->children.push_back(minmax_expression);
    std::string ltop_str = "<";
    std::string lteop_str = "<=";
    std::string gtop_str = ">";
    std::string gteop_str = ">=";
    std::string eqop_str = "==";
    std::string neqop_str = "!=";

    if (match_input(TOKEN_LTOP, &ltop_str, nullptr) || match_input(TOKEN_LTEOP, &lteop_str, nullptr) || match_input(TOKEN_GTOP, &gtop_str, nullptr) || match_input(TOKEN_GTEOP, &gteop_str, nullptr) || match_input(TOKEN_EQOP, &eqop_str, nullptr) || match_input(TOKEN_NEQOP, &neqop_str, nullptr)) {
        current_node->children.push_back(new parse_tree_node(current_token.name, true));

        parse_tree_node* more_minmax_expression = minmax_expression_with_lookahead();
        if (!more_minmax_expression)
            return nullptr;


        current_node->children.push_back(more_minmax_expression);
    }

    return current_node;
}

parse_tree_node*Parser2:: minmax_expression_with_lookahead() {
    parse_tree_node* current_node = new parse_tree_node("minmax_expression", false);

    parse_tree_node* sum_expression = sum_expression_with_lookahead();
    if (!sum_expression)
        return nullptr;

    current_node->children.push_back(sum_expression);

    //if (match_input("MINMAXOP", nullptr)) {
    //    current_node->children.push_back(new parse_tree_node("MINMAXOP", true));

    //    parse_tree_node* more_minmax_expression = minmax_expression_with_lookahead();
    //    if (!more_minmax_expression)
    //        return nullptr;

    //    current_node->children.push_back(more_minmax_expression);
    //}
    return current_node;
}

parse_tree_node*Parser2:: sum_expression_with_lookahead() {
    parse_tree_node* current_node = new parse_tree_node("sum_expression", false);

    parse_tree_node* mul_expression = mul_expression_with_lookahead();
    if (!mul_expression)
        return nullptr;

    current_node->children.push_back(mul_expression);

    std::string add_str = "+";
    std::string sub_str = "-";
    if (match_input(TOKEN_ADDOP,&add_str, nullptr) || match_input(TOKEN_SUBOP, &sub_str,nullptr)) {
        current_node->children.push_back(new parse_tree_node(current_token.name, true));

        parse_tree_node* more_sum_expression = sum_expression_with_lookahead();
        if (!more_sum_expression)
            return nullptr;

        current_node->children.push_back(more_sum_expression);
    }

    return current_node;
}


// mul_expression → mul_expression TIMES unary_expression | mul_expression DIVIDE unary_expression | mul_expression MOD unary_expression | unary_expression;
parse_tree_node*Parser2:: mul_expression_with_lookahead() {
    parse_tree_node* current_node = new parse_tree_node("mul_expression", false);

    parse_tree_node* unary_expression = unary_expression_with_lookahead();
    if (!unary_expression)
        return nullptr;

    current_node->children.push_back(unary_expression);

    std::string mulop_str = "*";
    std::string divop_str = "/";
    std::string modop_str = "%";

    if (match_input(TOKEN_MULOP, &mulop_str, nullptr) || match_input(TOKEN_DIVOP, &divop_str, nullptr) || match_input(TOKEN_MODOP, &modop_str, nullptr)) {
        current_node->children.push_back(new parse_tree_node(current_token.name, true));

        parse_tree_node* more_mul_expression = mul_expression_with_lookahead();
        if (!more_mul_expression)
            return nullptr;

        current_node->children.push_back(more_mul_expression);
    }

    return current_node;
}

// unary_expression → unaryop unary_expression | factor;
parse_tree_node*Parser2:: unary_expression_with_lookahead() {
    parse_tree_node* current_node = new parse_tree_node("unary_expression", false);

    std::string mulop_str = "*";
    std::string subop_str = "-";
    std::string decop_str = "--";

    if (match_input(TOKEN_SUBOP, &subop_str, nullptr) || match_input(TOKEN_MULOP, &mulop_str, nullptr) || match_input(TOKEN_DECOP, &decop_str, nullptr)) {
        current_node->children.push_back(new parse_tree_node(current_token.name, true));

        parse_tree_node* unary_expression = unary_expression_with_lookahead();
        if (!unary_expression)
            return nullptr;

        current_node->children.push_back(unary_expression);
    }
    else {
        parse_tree_node* factor = factor_with_lookahead();
        if (!factor)
            return nullptr;

        current_node->children.push_back(factor);
    }

    return current_node;
}

// factor → immutable | mutable;
parse_tree_node*Parser2:: factor_with_lookahead() {
    parse_tree_node* current_node = new parse_tree_node("factor", false);

    parse_tree_node* immutable = immutable_with_lookahead();
    if (immutable) {
        current_node->children.push_back(immutable);
        return current_node;
    }

    parse_tree_node* imutable = mutable_with_lookahead();
    if (imutable) {
        current_node->children.push_back(imutable);
        return current_node;
    }

    return nullptr;
}

// mutable → IDENTIFIER | IDENTIFIER LBRACKET expression RBRACKET;
parse_tree_node*Parser2:: mutable_with_lookahead() {
    parse_tree_node* current_node = new parse_tree_node("mutable", false);

    if (!match_input(TOKEN_IDENTIFIER, nullptr))
        return nullptr;
    current_node->children.push_back(new parse_tree_node(current_token.name, true));

    std::string leftbrack_str = "[";
    std::string rightbrack_str = "]";

    if (match_input(TOKEN_LEFT_BRACKET, &leftbrack_str, nullptr)) {
        current_node->children.push_back(new parse_tree_node("[", true));

        parse_tree_node* expression = expression_with_lookahead();
        if (!expression)
            return nullptr;

        current_node->children.push_back(expression);

        if (!match_input(TOKEN_RIGHT_BRACKET,&rightbrack_str, nullptr))
            return nullptr;

        current_node->children.push_back(new parse_tree_node("]", true));
    }

    return current_node;
}

// immutable → LPAREN expression RPAREN | call | constant;
parse_tree_node*Parser2:: immutable_with_lookahead() {
    parse_tree_node* current_node = new parse_tree_node("immutable", false);

    std::string leftbrack_str = "[";
    std::string rightbrack_str = "]";

    if (match_input(TOKEN_LEFT_BRACKET, &leftbrack_str, nullptr)) {
        current_node->children.push_back(new parse_tree_node("[", true));

        parse_tree_node* expression = expression_with_lookahead();
        if (!expression)
            return nullptr;

        current_node->children.push_back(expression);

        if (!match_input(TOKEN_RIGHT_BRACKET, &rightbrack_str, nullptr))
            return nullptr;

        current_node->children.push_back(new parse_tree_node("]", true));
    }
    //else if (match_input(TOKEN_IDENTIFIER, nullptr) && (lookahead_token_index + 1 < tokens.size()) && tokens[lookahead_token_index + 1].type == "[") {
    //    parse_tree_node* call = call_with_lookahead();
    //    if (!call)
    //        return nullptr;

    //    current_node->children.push_back(call);
    //}
    else {
        parse_tree_node* constant = constant_with_lookahead();
        if (!constant)
            return nullptr;

        current_node->children.push_back(constant);
    }

    return current_node;
}

// call → IDENTIFIER LPAREN args RPAREN;
parse_tree_node*Parser2:: call_with_lookahead() {
    parse_tree_node* current_node = new parse_tree_node("call", false);

    if (!match_input(TOKEN_IDENTIFIER, nullptr))
        return nullptr;


    current_node->children.push_back(new parse_tree_node(current_token.name, true));


    std::string leftbrack_str = "[";
    std::string rightbrack_str = "]";

    if (!match_input(TOKEN_LEFT_BRACKET, &leftbrack_str, nullptr))
        return nullptr;

    parse_tree_node* args = args_with_lookahead();
    if (args)
        current_node->children.push_back(args);

    if (!match_input(TOKEN_RIGHT_BRACKET, &rightbrack_str, nullptr))
        return nullptr;

    current_node->children.push_back(new parse_tree_node("]", true));

    return current_node;
}

// args → arg_list | /* epsilon */;
parse_tree_node*Parser2:: args_with_lookahead() {
    parse_tree_node* current_node = new parse_tree_node("args", false);

    parse_tree_node* arg_list = arg_list_with_lookahead();
    if (arg_list)
        current_node->children.push_back(arg_list);

    return current_node;
}

// arg_list → arg_list COMMA expression | expression;
parse_tree_node*Parser2:: arg_list_with_lookahead() {
    parse_tree_node* current_node = new parse_tree_node("arg_list", false);

    parse_tree_node* expression = expression_with_lookahead();
    if (!expression)
        return nullptr;

    current_node->children.push_back(expression);

    if (match_input(TOKEN_COMMA, nullptr)) {
        current_node->children.push_back(new parse_tree_node(",", true));

        parse_tree_node* more_arg_list = arg_list_with_lookahead();
        if (!more_arg_list)
            return nullptr;

        current_node->children.push_back(more_arg_list);
    }

    return current_node;
}

// constant → TOKEN_NUMBER | TOKEN_CHARACTER | TOKEN_STRING | TRUE | FALSE;
parse_tree_node*Parser2:: constant_with_lookahead() {
    parse_tree_node* current_node = new parse_tree_node("constant", false);

    std::string char_str = "char";
    std::string string_str = "string";
    std::string true_str = "true";
    std::string false_str = "false";



    if (match_input(TOKEN_NUMBER, nullptr) || match_input(TOKEN_KEYWORD, &char_str ,nullptr) || match_input(TOKEN_KEYWORD, &string_str, nullptr) ||
        match_input(TOKEN_KEYWORD, &true_str, nullptr) || match_input(TOKEN_KEYWORD, &false_str, nullptr)) {

        if(current_token.type != TOKEN_NUMBER)
            current_node->children.push_back(new parse_tree_node(current_token.name, true));

        else
            current_node->children.push_back(new parse_tree_node(current_token.lexeme, true));



        return current_node;
    }

    return nullptr;
}


//===================================================================================================================//
//                                                       Parsing Statements                                         //
//==================================================================================================================//


//BELOW ARE THE GRAMMAR RULES USED//
/***********************************************************************************************************
body -> single_statement sub_body Done
sub_body -> body | ε Done

single_statement -> conditional_statements | iterative_statements

conditional_statements -> if_expr | switch_expr Done
if_expr -> if (boolean_expr) {body} else_expr | if (boolean_expr) single_statement else_expr Done
else_expr -> else {body} | else single_statement | ε Done

switch_expr -> switch(id) { case_expr default_expr }Done
case_expr -> case const : body break; | case const : body | case_expr | ε Done
default_expr -> default: body | default: body break; Done
const -> number | string | char  Done

Iterative_Statements-> for_loop | while_loop | do_while_loop
for_loop -> for (init_expr; condition_expr; update_expr) { body}

init_expr -> expression | ε
condition_expr -> boolean_expr | ε
update_expr -> assignment_expr | ε
while_loop -> while (condition_expr) { body }
do_while_loop -> do { body } while (condition_expr)
***********************************************************************************************************/

// Forward declarations


// body → single_statement sub_body
parse_tree_node*Parser2:: body_with_lookahead() {
    parse_tree_node* current_node = new parse_tree_node("body", false);

    parse_tree_node* single_stmt = single_statement_with_lookahead();
    if (single_stmt) {
        current_node->children.push_back(single_stmt);
    }
    else {
        return nullptr;
    }

    parse_tree_node* sub_body = sub_body_with_lookahead();
    if (sub_body) {
        current_node->children.push_back(sub_body);
    }
    else {
        return nullptr;
    }

    return current_node;
}

// sub_body → body | ε
parse_tree_node*Parser2:: sub_body_with_lookahead() {
    parse_tree_node* current_node = new parse_tree_node("sub_body", false);

    parse_tree_node* body_node = body_with_lookahead();
    if (body_node) {
        current_node->children.push_back(body_node);
    }
    else {
        return nullptr; // ε

    }

    return current_node;
}

// single_statement → conditional_statements | iterative_statements
parse_tree_node*Parser2:: single_statement_with_lookahead() {
    parse_tree_node* current_node = new parse_tree_node("single_statement", false);

    // parse conditional_statements
    parse_tree_node* conditional_stmt = conditional_statements_with_lookahead();
    if (conditional_stmt) {
        current_node->children.push_back(conditional_stmt);
        return current_node;
    }

    // Try to parse iterative_statements
    parse_tree_node* iterative_stmt = iterative_statements_with_lookahead();
    if (iterative_stmt) {
        current_node->children.push_back(iterative_stmt);
        return current_node;
    }

    return nullptr;
}


//=======================//
//CONDITIONAL STATEMENTS//
//=====================//


parse_tree_node*Parser2:: conditional_statements_with_lookahead() {
    parse_tree_node* current_node = new parse_tree_node("Conditional_Statements", false);

    parse_tree_node* if_statement_node = if_statement_with_lookahead();
    if (if_statement_node) {
        current_node->children.push_back(if_statement_node);
        return current_node;
    }

    parse_tree_node* switch_case_node = switch_expr_with_lookahead();
    if (switch_case_node) {
        current_node->children.push_back(switch_case_node);
        return current_node;
    }


    return nullptr; // Failed to parse Iterative_Statements
}

//------------//
//IF STATEMENT
//-----------//

// if_expr -> i


// if-statement → if ( expression ) statement else-part
parse_tree_node*Parser2:: if_statement_with_lookahead() {
    parse_tree_node* current_node = new parse_tree_node("if-statement", false);

    std::string if_str = "if";
   

    if (!match_input(TOKEN_KEYWORD, &if_str)) return nullptr;
    if (!match_input(TOKEN_LEFT_PAREN)) return nullptr;

    // Parse expression
    if (!match_input(TOKEN_RIGHT_PAREN)) return nullptr;

    parse_tree_node* statement = statements_with_lookahead();
    if (statement) current_node->children.push_back(statement);
    else

        return nullptr;

    parse_tree_node* else_part = else_part_with_lookahead();
    if (else_part) current_node->children.push_back(else_part);

    return current_node;
}

// else-part → ε | else statement
parse_tree_node*Parser2:: else_part_with_lookahead() {
    parse_tree_node* current_node = new parse_tree_node("else-part", false);
    std::string else_str = "else";
    if (match_input(TOKEN_KEYWORD, &else_str)) {
        parse_tree_node* statement = statements_with_lookahead();
        if (statement) current_node->children.push_back(statement);
        else return nullptr;
    }

    return current_node;
}

// statement → if-statement | other-statement
parse_tree_node*Parser2:: statements_with_lookahead() {

    // Check if it's an if-statement
    parse_tree_node* if_stmt = if_statement_with_lookahead();
    if (if_stmt) return if_stmt;

    // Otherwise, it's an other statement
    // For simplicity, let's assume other statements here
    if (!match_input(TOKEN_IDENTIFIER)) return nullptr;
    return new parse_tree_node("other statement", true);
}




//------------//
//SWITCH CASE//
//-----------//

// switch_expr → switch ( identifier ) { case_expr default_expr }
parse_tree_node*Parser2:: switch_expr_with_lookahead() {
    parse_tree_node* current_node = new parse_tree_node("switch_expr", false);

    std::string switch_str = "swtch";
    std::string rightparen_str = ")";
    std::string leftparen_str = "(";
    std::string semicolon_str = ";";
    std::string leftbraces_str = "{";
    std::string rightbraces_str = "}";

    if (!match_input(TOKEN_KEYWORD, &switch_str, nullptr)) // Check for "switch" keyword
        return nullptr;

    if (!match_input(TOKEN_LEFT_PAREN,&leftparen_str, nullptr)) // Check for "("
        return nullptr;

    if (!match_input(TOKEN_IDENTIFIER, nullptr)) // Check for identifier (id)
        return nullptr;

    if (!match_input(TOKEN_LEFT_PAREN, &rightparen_str, nullptr)) // Check for ")"
        return nullptr;

    if (!match_input(TOKEN_LEFT_BRACE,&leftbraces_str, nullptr)) // Check for "{"

        return nullptr;

    parse_tree_node* case_expr = case_expr_with_lookahead(); // Parse case expressions

    if (case_expr) {
        current_node->children.push_back(case_expr);
    }
    else {
        return nullptr; // Failed to parse case expressions
    }

    parse_tree_node* default_expr = default_expr_with_lookahead(); // Parse default expression
    if (default_expr) {
        current_node->children.push_back(default_expr);
    }
    else {
        return nullptr; // Failed to parse default expression
    }

    if (!match_input(TOKEN_RIGHT_BRACE, &rightbraces_str, nullptr)) // Check for "}"
       
        return nullptr;


    return current_node;

}

// case_expr → case const : body break; | case const : body | case_expr | ε
parse_tree_node*Parser2:: case_expr_with_lookahead() {

    std::string case_str = "case";
    std::string colon_str = ":";
    std::string semicolon_str = ";";
    std::string break_str = "break";
    parse_tree_node* current_node = new parse_tree_node("case_expr", false);

    while (true) {
        if (!match_input(TOKEN_KEYWORD, &case_str, nullptr)) // Check for "case" keyword
            return current_node->children.empty() ? nullptr : current_node;

        if (!match_input(TOKEN_IDENTIFIER, nullptr)) // Check for constant (const)
            return nullptr;

        if (!match_input(TOKEN_COLON, &colon_str, nullptr)) // Check for ":"
            return nullptr;

        parse_tree_node* body = body_with_lookahead(); // Parse body
        if (body) {
            current_node->children.push_back(body);
        }
        else {
            return nullptr; // Failed to parse body
        }

        if (match_input(TOKEN_KEYWORD, &break_str, nullptr)) { // Check for "break"
            if (!match_input(TOKEN_SEMICOLON, &semicolon_str, nullptr)) // Check for ";"
                return nullptr;
        }

        if (current_node->children.size() > 1) {
            return current_node; // Already parsed at least one case expression
        }
    }
}

// default_expr → default: body | default: body break;
parse_tree_node*Parser2:: default_expr_with_lookahead() {
    std::string default_str = "default";
    std::string colon_str = ":";
    std::string semicolon_str = ";";
    std::string break_str = "break";



    parse_tree_node* current_node = new parse_tree_node("default_expr", false);

    if (!match_input(TOKEN_KEYWORD, &default_str, nullptr)) // Check for "default" keyword
        return nullptr;

    if (!match_input(TOKEN_COLON, &colon_str, nullptr)) // Check for ":"
        return nullptr;

    parse_tree_node* body = body_with_lookahead(); // Parse body
    if (body) {
        current_node->children.push_back(body);
    }
    else {
        return nullptr; // Failed to parse body
    }

    if (match_input(TOKEN_KEYWORD, &break_str, nullptr)) { // Check for "break"
        if (!match_input(TOKEN_SEMICOLON, &semicolon_str, nullptr)) // Check for ";"
            return nullptr;
    }

    return current_node;
}



//=======================//
//ITERATIVE STATEMENTS//
//=====================//



// Iterative_Statements → for_loop | while_loop | do_while_loop
parse_tree_node*Parser2:: iterative_statements_with_lookahead() {
    parse_tree_node* current_node = new parse_tree_node("Iterative_Statements", false);

    parse_tree_node* for_loop_node = for_loop_with_lookahead();
    if (for_loop_node) {
        current_node->children.push_back(for_loop_node);
        return current_node;
    }

    parse_tree_node* while_loop_node = while_loop_with_lookahead();
    if (while_loop_node) {
        current_node->children.push_back(while_loop_node);
        return current_node;
    }

    parse_tree_node* do_while_loop_node = do_while_loop_with_lookahead();
    if (do_while_loop_node) {
        current_node->children.push_back(do_while_loop_node);
        return current_node;
    }

    return nullptr; // Failed to parse Iterative_Statements
}


//-------------//
//  FOR LOOP  //
//-----------//
// for_loop → for (init_expr; condition_expr; update_expr) { body}
parse_tree_node*Parser2:: for_loop_with_lookahead() {
    std::string rightparen_str = ")";
    std::string leftparen_str = "(";
    std::string for_str = "for";
    std::string semicolon_str = ";";
    parse_tree_node* current_node = new parse_tree_node("for_loop", false);

    if (!match_input(TOKEN_KEYWORD, &for_str, nullptr)) // Check for "for" keyword
        return nullptr;

    if (!match_input(TOKEN_LEFT_PAREN, &leftparen_str, nullptr)) // Check for "("
        return nullptr;

    parse_tree_node* init_expr = expression_with_lookahead(); // Parse init expression
    if (init_expr) {
        current_node->children.push_back(init_expr);
    } // else ε is valid

    if (!match_input(TOKEN_SEMICOLON, &semicolon_str, nullptr)) // Check for ";"
        return nullptr;

    parse_tree_node* condition_expr = expression_with_lookahead(); // Parse condition expression
    if (condition_expr) {
        current_node->children.push_back(condition_expr);
    } // else ε is valid

    if (!match_input(TOKEN_SEMICOLON, &semicolon_str, nullptr)) // Check for ";"
        return nullptr;

    parse_tree_node* update_expr = expression_with_lookahead(); // Parse update expression
    if (update_expr) {
        current_node->children.push_back(update_expr);
    } // else ε is valid

    if (!match_input(TOKEN_RIGHT_PAREN,&rightparen_str, nullptr)) // Check for ")"
        return nullptr;

    parse_tree_node* body = body_with_lookahead(); // Parse body
    if (body) {
        current_node->children.push_back(body);
    }
    else {
        return nullptr; // Failed to parse body
    }

    return current_node;
}


//---------------//
//  WHILE LOOP  //
//-------------//

// while_loop → while (condition_expr) { body }
parse_tree_node*Parser2:: while_loop_with_lookahead() {
    parse_tree_node* current_node = new parse_tree_node("while_loop", false);

    std::string rightparen_str = ")";
    std::string leftparen_str = "(";
    std::string while_str = "while";
    std::string semicolon_str = ";";

    if (!match_input(TOKEN_KEYWORD, &while_str, nullptr))
        return nullptr;

    if (!match_input(TOKEN_LEFT_PAREN, &leftparen_str, nullptr))
        return nullptr;

    parse_tree_node* condition_expr = expression_with_lookahead();
    if (condition_expr) {
        current_node->children.push_back(condition_expr);
    }
    else {
        return nullptr;
    }

    if (!match_input(TOKEN_RIGHT_PAREN, &rightparen_str, nullptr))
        return nullptr;

    parse_tree_node* body = body_with_lookahead();
    if (body) {
        current_node->children.push_back(body);
    }
    else {
        return nullptr;
    }

    return current_node;
}

//------------------//
//  DO-WHILE LOOP  //
//----------------//


// do_while_loop → do { body } while (condition_expr)
parse_tree_node*Parser2:: do_while_loop_with_lookahead() {
    parse_tree_node* current_node = new parse_tree_node("do_while_loop", false);
    std::string rightparen_str = ")";
    std::string leftparen_str = "(";
    std::string do_str = "do";
    std::string semicolon_str = ";";
    std::string while_str = "while";


    if (!match_input(TOKEN_KEYWORD, &do_str, nullptr))
        return nullptr;

    parse_tree_node* body = body_with_lookahead();
    if (body) {
        current_node->children.push_back(body);
    }
    else {
        return nullptr;
    }

    if (!match_input(TOKEN_KEYWORD, &while_str, nullptr))
        return nullptr;

    if (!match_input(TOKEN_LEFT_PAREN, &leftparen_str, nullptr))
        return nullptr;

    parse_tree_node* condition_expr = expression_with_lookahead();
    if (condition_expr) {
        current_node->children.push_back(condition_expr);
    }
    else {
        return nullptr;
    }

    if (!match_input(TOKEN_RIGHT_PAREN, &rightparen_str, nullptr))
        return nullptr;

    return current_node;
}

parse_tree_node* Parser2::parse_if_statement_with_lookahead() {
    parse_tree_node* current_node = new parse_tree_node("if_statement", false);

    // Parse 'if'
    std::string if_str = "if";
    if (!match_input(TOKEN_KEYWORD, &if_str, nullptr)) {
        delete current_node;
        return nullptr;
    }
    current_node->children.push_back(new parse_tree_node("if", true));

    // Parse '('
    std::string left_paren_str = "(";
    if (!match_input(TOKEN_LEFT_PAREN, &left_paren_str, nullptr)) {
        delete current_node;
        return nullptr;
    }
    current_node->children.push_back(new parse_tree_node("(", true));

    // Parse identifier
    if (!match_input(TOKEN_IDENTIFIER)) {
        delete current_node;
        return nullptr;
    }
    current_node->children.push_back(new parse_tree_node(current_token.lexeme, true));

    // Parse '='
    std::string assignop_str = "=";
    if (!match_input(TOKEN_ASSIGNOP, &assignop_str, nullptr)) {
        delete current_node;
        return nullptr;
    }
    current_node->children.push_back(new parse_tree_node("=", true));

    // Parse constant or identifier (0)
    if (!match_input(TOKEN_NUMBER) && !match_input(TOKEN_IDENTIFIER)) {
        delete current_node;
        return nullptr;
    }
    current_node->children.push_back(new parse_tree_node(current_token.lexeme, true));

    // Parse ')'
    std::string right_paren_str = ")";
    if (!match_input(TOKEN_RIGHT_PAREN, &right_paren_str, nullptr)) {
        delete current_node;
        return nullptr;
    }
    current_node->children.push_back(new parse_tree_node(")", true));

    // Parse '{'
    std::string left_brace_str = "{";
    if (!match_input(TOKEN_LEFT_BRACE, &left_brace_str, nullptr)) {
        delete current_node;
        return nullptr;
    }
    current_node->children.push_back(new parse_tree_node("{", true));

    // Parse identifier (y)
    if (!match_input(TOKEN_IDENTIFIER)) {
        delete current_node;
        return nullptr;
    }
    current_node->children.push_back(new parse_tree_node(current_token.lexeme, true));

    // Parse '='
    if (!match_input(TOKEN_ASSIGNOP, &assignop_str, nullptr)) {
        delete current_node;
        return nullptr;
    }
    current_node->children.push_back(new parse_tree_node("=", true));

    // Parse constant or identifier (1)
    if (!match_input(TOKEN_NUMBER) && !match_input(TOKEN_IDENTIFIER)) {
        delete current_node;
        return nullptr;
    }
    current_node->children.push_back(new parse_tree_node(current_token.lexeme, true));

    // Parse '}'
    std::string right_brace_str = "}";
    if (!match_input(TOKEN_RIGHT_BRACE, &right_brace_str, nullptr)) {
        delete current_node;
        return nullptr;
    }
    current_node->children.push_back(new parse_tree_node("}", true));

    return current_node;
}








int main() {
    string filename = "E:\\cpp_Yasmina's compiler\\input.txt";
    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return 1;
    }

    string inputString;
    getline(inputFile, inputString, static_cast<char>(EOF));
    inputFile.close();

    Parser2 parser(inputString);

    std::cout << "Recursive Descent with lookahead:\n" << std::endl;
    parse_tree_node* parse_tree_root_node = parser.recursively_descend_with_lookahead();

    cout << (parse_tree_root_node ? "Parsing successful.\n" : "Parsing failed.\n") << std::endl;
    if (parse_tree_root_node) visualize_parse_tree(parse_tree_root_node);


    return 0;
}
