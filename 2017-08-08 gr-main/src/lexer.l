/* Flex regex actions definitions */

DIGIT       [0-9]
WORD        [a-zA-Z_]
ALNUM       [0-9a-zA-Z_]
HEX         [0-9A-F]
INTTAIL     (u?(b|s|i|l)?)

%option noyywrap

%{

#include "parser-support.h"
#include "strbuf.h"
#include "ast.h"

%}

%%

"/*"[^*]*[*]+([^*/][^*]*[*]+)*[/]
"//"[^\n]*
"#"[^\n]*

"print"                         { return AST_PRINT; }
"println"                       { return AST_PRINTLN; }

{WORD}{ALNUM}*                  { return lexer_newToken(ast_newNamedNode(AST_IDENTIFIER, string_dup(yytext))); }

[1-9]({DIGIT}|_)*{INTTAIL}      { return lexer_newToken(ast_newLiteralNode(AST_INT_LITERAL, primitive_getInt(lexer_parseInt(0, 10)))); }
0x({HEX}|_)+{INTTAIL}           { return lexer_newToken(ast_newLiteralNode(AST_INT_LITERAL, primitive_getInt(lexer_parseInt(2, 16)))); }
0b[01_]+{INTTAIL}?              { return lexer_newToken(ast_newLiteralNode(AST_INT_LITERAL, primitive_getInt(lexer_parseInt(2, 2)))); }
0o[0-7_]+{INTTAIL}?             { return lexer_newToken(ast_newLiteralNode(AST_INT_LITERAL, primitive_getInt(lexer_parseInt(2, 8)))); }
0[0-7_]+{INTTAIL}?              { return lexer_newToken(ast_newLiteralNode(AST_INT_LITERAL, primitive_getInt(lexer_parseInt(1, 8)))); }

"("                             { return '('; }
")"                             { return ')'; }
"="                             { return '='; }
"-"                             { return '-'; }
"+"                             { return '+'; }
"*"                             { return '*'; }
"/"                             { return '/'; }
"%"                             { return '%'; }

[ \t\r\n]+

%%
