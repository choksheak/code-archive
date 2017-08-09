#ifndef C_GEN_H
#define C_GEN_H

#include "ast.h"

extern void cgen_print(struct ast_node *astNode);
extern void cgen_fprint(FILE *stream, struct ast_node *astNode);
extern void cgen_fprint_recurse(FILE *stream, struct ast_node *astNode, uint32_t indent);

#endif /* C_GEN_H */
