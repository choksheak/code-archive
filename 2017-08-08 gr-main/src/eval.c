/* AST evaluator */

#include <inttypes.h>
#include <stdlib.h>

#include "ast.h"
#include "parser-support.h"
#include "eval.h"

struct eval_context *eval_newContext(uint32_t stackMaxDepth) {
    struct eval_context *context = (struct eval_context *) malloc(sizeof(struct eval_context));
    if (context == NULL) {
        return NULL;
    }
    context->stackMaxDepth = stackMaxDepth;
    context->stackDepth = 0;
    context->stack = (struct hashmap **) calloc(sizeof(struct hashmap *), stackMaxDepth);
    return context;
}

void eval_freeContext(struct eval_context *context) {
    for (uint32_t i = 0; i < context->stackMaxDepth; i++) {
        if (context->stack[i] != NULL) {
            hashmap_free(context->stack[i]);
        }
    }

    free(context->stack);
    free(context);
}

union primitive_value eval_ast(struct eval_context *context, struct ast_node *astNode) {
    union primitive_value value = primitive_null;
    
    switch (astNode->nodeType) {
    case '!':
        break;
    case '#':
        break;
    case '$':
        break;
    case '%':
        break;
    case '&':
        break;
    case '*':
        {
            struct ast_binaryNode *node = (struct ast_binaryNode *) astNode;
            union primitive_value value1 = eval_ast(context, node->node1);
            union primitive_value value2 = eval_ast(context, node->node2);
            value.intValue = value1.intValue * value2.intValue;
        }
        break;
    case '+':
        {
            struct ast_binaryNode *node = (struct ast_binaryNode *) astNode;
            union primitive_value value1 = eval_ast(context, node->node1);
            union primitive_value value2 = eval_ast(context, node->node2);
            value.intValue = value1.intValue + value2.intValue;
        }
        break;
    case ',':
        break;
    case '-':
        {
            if (astNode->nodeCategory == AST_UNARY_NODE) {
                struct ast_unaryNode *node = (struct ast_unaryNode *) astNode;
                union primitive_value value1 = eval_ast(context, node->node1);
                value.intValue = -value1.intValue;
            }
            else {
                struct ast_binaryNode *node = (struct ast_binaryNode *) astNode;
                union primitive_value value1 = eval_ast(context, node->node1);
                union primitive_value value2 = eval_ast(context, node->node2);
                value.intValue = value1.intValue - value2.intValue;
            }
        }
        break;
    case '.':
        break;
    case '/':
        {
            struct ast_binaryNode *node = (struct ast_binaryNode *) astNode;
            union primitive_value value1 = eval_ast(context, node->node1);
            union primitive_value value2 = eval_ast(context, node->node2);
            value.intValue = value1.intValue / value2.intValue;
        }
        break;
    case ':':
        break;
    case ';':
        break;
    case '<':
        break;
    case '=':
        {
            struct ast_binaryNode *node = (struct ast_binaryNode *) astNode;
            struct ast_node *node1 = node->node1;
            struct ast_node *node2 = node->node2;
            
            if (node1->nodeType != AST_IDENTIFIER) {
                printf("Eval error: %" PRIu32 ".%" PRIu32 ": Expecting identifier but got %s.\n",
                    node1->lineno,
                    node1->column,
                    ast_getNodeTypeName(node1->nodeType));
                break;
            }
            
            struct ast_namedNode *id = (struct ast_namedNode *) node1;
            value = eval_ast(context, node2);
            
            struct hashmap *map = context->stack[context->stackDepth];
            if (map == NULL) {
                map = hashmap_createStringMap();
                context->stack[context->stackDepth] = map;
            }
            
            printf("Setting variable %s as %" PRIi32 "\n", id->name, value.intValue);
            hashmap_put(map, primitive_getString(id->name), value);
        }
        break;
    case '>':
        break;
    case '?':
        break;
    case '@':
        break;
    case '\\':
        break;
    case '^':
        break;
    case '`':
        break;
    case '|':
        break;
    case '~':
        break;
    case AST_INT_LITERAL:
        {
            struct ast_literalNode *node = (struct ast_literalNode *) astNode;
            value = node->value;
        }
        break;
    case AST_IDENTIFIER:
        {
            struct ast_namedNode *node = (struct ast_namedNode *) astNode;
            
            struct hashmap *map = context->stack[context->stackDepth];
            union primitive_value *valuePtr = (map != NULL)
                    ? hashmap_get(map, primitive_getString(node->name))
                    : NULL;
            
            if (valuePtr == NULL) {
                printf("Eval error: %" PRIu32 ".%" PRIu32 ": Variable `%s' not defined.\n",
                    astNode->lineno,
                    astNode->column,
                    node->name);
                break;
            }

            value = *valuePtr;
        }
        break;
    case AST_STATEMENTS:
        {
            struct ast_listNode *listNode = (struct ast_listNode *) astNode;
            union primitive_value *listValues = listNode->list->values;
            
            for (uint32_t i = 0, len = listNode->list->size; i < len; i++) {
                struct ast_node *nodeI = (struct ast_node *) (listValues[i].pointerValue);
                value = eval_ast(context, nodeI);
            }
        }
        break;
    case AST_PRINT:
        {
            struct ast_unaryNode *node = (struct ast_unaryNode *) astNode;
            value = eval_ast(context, node->node1);
            printf("PRINT %" PRIi32 "\n", value.intValue);
        }
        break;
    case AST_PRINTLN:
        {
            struct ast_unaryNode *node = (struct ast_unaryNode *) astNode;
            value = eval_ast(context, node->node1);
            printf("PRINTLN %" PRIi32 "\n", value.intValue);
        }
        break;
    default:
        printf("Eval error: Unknown node type %" PRIu32 "\n", astNode->nodeType);
        break;
    }

    return value;
}
