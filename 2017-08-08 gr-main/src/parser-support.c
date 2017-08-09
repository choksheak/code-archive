/* Supporting functions for the lexer and parser */

#include <stdio.h>
#include <stdlib.h>

#include "parser-support.h"
#include "strbuf.h"
#include "ast.h"

char *lexer_filename = "";
int32_t lexer_linenum = 1;
int32_t lexer_colnum = 1;

void lexer_updateLocation(void) {
    yylloc.first_line = lexer_linenum;
    yylloc.first_column = lexer_colnum;

    int32_t c = yytext[0];
    uint32_t i = 0;
    
    while (c != '\0') {
        if (c == '\r') {
            if (yytext[i + 1] == '\n') {
                // ignore '\r'
            }
            else {
                // Treat '\r' as proper newline.
                lexer_colnum = 1;
                lexer_linenum++;
            }
        }
        else if (c == '\n') {
            lexer_colnum = 1;
            lexer_linenum++;
        }
        else if (c == '\t') {
            lexer_colnum += 8 - (lexer_colnum % 8);
        }
        else {
            lexer_colnum++;
        }
        
        c = yytext[++i];
    }
    
    yylloc.last_line = lexer_linenum;
    yylloc.last_column = lexer_colnum;
}

enum yytokentype lexer_newToken(struct ast_node *astNode) {
    astNode->lineno = yylloc.first_line;
    astNode->column = yylloc.first_column;
    yylval = astNode;
    return astNode->nodeType;
}

void yyerror(struct ast_node **returnAstNode, char const *errorMessage)
{
    fflush(stdout);

    printf("\nParse error near %s %i:%i - %s (last read token is `%s')\n",
        lexer_filename != NULL ? lexer_filename : "position",
        lexer_linenum,
        lexer_colnum,
        errorMessage,
        yytext);
}

// TODO: This algorithm is neither correct nor complete.
// Need to recognize by integer size and signed-ness.
// Best to not require conversion to string to get integral value.
int32_t lexer_parseInt(uint32_t skipNumChars, uint32_t radix) {
    char *s = &(yytext[skipNumChars]);

    for (uint32_t i = 0; s[i] != '\0'; i++) {
        char c = s[i];

        if (c == '_' || c == 'u' || c == 'b' || c == 's' || c == 'i' || c == 'l') {
            char *t = string_dup(s);

            do {
                if (c != '_') {
                    t[i] = '\0';
                    break;
                }

                uint32_t k = 0;

                for (uint32_t j = 0; s[j] != '\0'; j++) {
                    c = s[j];

                    if (c == 'u' || c == 'b' || c == 's' || c == 'i' || c == 'l') {
                        break;
                    }

                    if (s[j] != '_') {
                        t[k++] = s[j];
                    }
                }

                t[k] = '\0';
            }
            while (0);

            int32_t retval = (int32_t) strtol(t, NULL, radix);
            free(t);
            return retval;
        }
    }

    return (int32_t) strtol(s, NULL, radix);
}

struct ast_node *parser_copyLocation(struct ast_node *astNode, YYLTYPE *location) {
    astNode->lineno = location->first_line;
    astNode->column = location->first_column;
    return astNode;
}

int32_t parser_parseStream(char *name, FILE *stream, struct ast_node **returnAstNode) {
    lexer_filename = name;
    yyset_in(stream);
    return yyparse(returnAstNode);
}

const char *parser_getParseStatusName(int32_t status) {
    switch (status) {
    case 0:
        return "Success";
    case 1:
        return "Failure";
    default:
        return "Unknown";
    }
}
