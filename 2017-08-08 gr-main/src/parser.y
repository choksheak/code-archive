/* Bison grammar actions definitions */

%token AST_INT_LITERAL AST_IDENTIFIER AST_STATEMENTS AST_PRINT AST_PRINTLN

%{

#include "parser-support.h"
#include "ast.h"

%}

%parse-param {struct ast_node **returnAstNode}

%start program

%%

primary_expression
    : AST_INT_LITERAL
        { $$ = $1; }
    | AST_IDENTIFIER
        { $$ = $1; }
    | '(' expression ')'
        { $$ = parser_copyLocation($2, &(@1)); }
    ;

unary_expression
    : primary_expression
        { $$ = $1; }
    | '-' primary_expression
        { $$ = parser_copyLocation(ast_newUnaryNode('-', $2), &(@1)); }
    | '+' primary_expression
        { $$ = parser_copyLocation($2, &(@1)); }
    ;

multiplicative_expression
    : unary_expression
        { $$ = $1; }
    | multiplicative_expression '*' unary_expression
        { $$ = parser_copyLocation(ast_newBinaryNode('*', $1, $3), &(@1)); }
    | multiplicative_expression '/' unary_expression
        { $$ = parser_copyLocation(ast_newBinaryNode('/', $1, $3), &(@1)); }
    | multiplicative_expression '%' unary_expression
        { $$ = parser_copyLocation(ast_newBinaryNode('%', $1, $3), &(@1)); }
    ;

additive_expression
    : multiplicative_expression
        { $$ = $1; }
    | additive_expression '+' multiplicative_expression
        { $$ = parser_copyLocation(ast_newBinaryNode('+', $1, $3), &(@1)); }
    | additive_expression '-' multiplicative_expression
        { $$ = parser_copyLocation(ast_newBinaryNode('-', $1, $3), &(@1)); }
    ;

assignment_expression
    : AST_IDENTIFIER '=' additive_expression
        { $$ = parser_copyLocation(ast_newBinaryNode('=', $1, $3), &(@1)); }
    | AST_IDENTIFIER '=' assignment_expression
        { $$ = parser_copyLocation(ast_newBinaryNode('=', $1, $3), &(@1)); }
    ;

expression
    : additive_expression
        { $$ = $1; }
    | assignment_expression
        { $$ = $1; }
    ;

print_statement
    : AST_PRINT expression
        { $$ = parser_copyLocation(ast_newUnaryNode(AST_PRINT, $2), &(@1));
        printf("Print at %i.%i\n", $$->lineno, $$->column);
        }
    | AST_PRINTLN expression
        { $$ = parser_copyLocation(ast_newUnaryNode(AST_PRINTLN, $2), &(@1)); }
    ;

statement
    : assignment_expression
        { $$ = $1; }
    | print_statement
        { $$ = $1; }
    ;

statement_list
    : statement
        { $$ = $1; }
    | statement_list statement
        {
            struct ast_listNode *listNode;
            
            if ($1->nodeCategory != AST_LIST_NODE) {
                listNode = ast_newListNode(AST_STATEMENTS);
                arraylist_add(listNode->list, primitive_getPointer($1));
                arraylist_add(listNode->list, primitive_getPointer($2));
                parser_copyLocation((struct ast_node *) listNode, &(@1));
            }
            else {
                listNode = (struct ast_listNode *) ($1);
                arraylist_add(listNode->list, primitive_getPointer($2));
            }
                
            $$ = (struct ast_node *) listNode;
        }
    ;

program
    : /* empty */
        { *returnAstNode = NULL; }
    | statement_list
        { *returnAstNode = $1;
                printf ("Program location %d.%d-%d.%d\n",
                   @$.first_line, @$.first_column,
                   @1.last_line, @1.last_column); }
    ;

%%
