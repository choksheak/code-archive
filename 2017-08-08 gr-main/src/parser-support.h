#ifndef PARSER_SUPPORT_H
#define PARSER_SUPPORT_H

#include <stdint.h>
#include <stdio.h>

#define YY_USER_ACTION lexer_updateLocation();

#define YY_NO_INPUT
#define YY_NO_UNPUT

#define YYSTYPE struct ast_node *
extern YYSTYPE yylval;

// This include must come after YYSTYPE and YYLTYPE.
#include "gen.gr.tokens.h"

extern char *yytext;

extern void yyerror(struct ast_node **returnAstNode, char const *s);
extern void yyset_in(FILE *_in_str);
extern int32_t yylex(void);
extern int32_t yyparse(struct ast_node **returnAstNode);
extern int32_t yyget_lineno(void);

extern char *lexer_filename;
extern int32_t lexer_linenum;
extern int32_t lexer_colnum;

extern void lexer_updateLocation(void);
extern enum yytokentype lexer_newToken(struct ast_node *astNode);
extern int32_t lexer_parseInt(uint32_t skipNumChars, uint32_t radix);

extern struct ast_node *parser_copyLocation(struct ast_node *astNode, YYLTYPE *location);
extern int32_t parser_parseStream(char *name, FILE *stream, struct ast_node **returnAstNode);
extern const char *parser_getParseStatusName(int32_t status);

// Handle deprecated call to fileno in flex generated code.
extern int fileno(FILE *stream);

#endif /* PARSER_SUPPORT_H */
