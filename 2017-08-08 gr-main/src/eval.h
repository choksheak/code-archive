#ifndef EVAL_H
#define EVAL_H

#include <inttypes.h>

#include "ast.h"
#include "hashmap.h"

#define EVAL_DEFAULT_STACK_MAX_DEPTH 1024

struct eval_context {
    uint32_t stackMaxDepth;
    uint32_t stackDepth;
    struct hashmap **stack;
};

extern struct eval_context *eval_newContext(uint32_t stackMaxDepth);
extern void eval_freeContext(struct eval_context *context);
extern union primitive_value eval_ast(struct eval_context *context, struct ast_node *astNode);

#endif /* EVAL_H */
