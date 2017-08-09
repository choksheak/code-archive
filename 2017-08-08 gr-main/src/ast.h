#ifndef AST_H
#define AST_H

#include <stdio.h>

#include "primitive.h"
#include "arraylist.h"

enum ast_nodeCategory {
    AST_BASE_NODE,
    AST_LITERAL_NODE,
    AST_NAMED_NODE,
    AST_UNARY_NODE,
    AST_BINARY_NODE,
    AST_TRINARY_NODE,
    AST_LIST_NODE
};

struct ast_node {
    uint32_t nodeCategory;
    uint32_t nodeType;
    uint32_t lineno;
    uint32_t column;
};

struct ast_literalNode {
    struct ast_node base;
	union primitive_value value;
};

struct ast_namedNode {
    struct ast_node base;
	char *name;
};

struct ast_unaryNode {
    struct ast_node base;
	struct ast_node *node1;
};

struct ast_binaryNode {
    struct ast_node base;
	struct ast_node *node1;
	struct ast_node *node2;
};

struct ast_trinaryNode {
    struct ast_node base;
	struct ast_node *node1;
	struct ast_node *node2;
    struct ast_node *node3;
};

struct ast_listNode {
    struct ast_node base;
	struct arraylist *list;
};

extern const char *ast_getNodeCategoryName(uint32_t nodeCategory);
extern const char *ast_getNodeTypeName(uint32_t nodeType);

extern struct ast_node *ast_newNode(uint32_t nodeType);
extern struct ast_node *ast_newLiteralNode(uint32_t nodeType, union primitive_value value);
extern struct ast_node *ast_newNamedNode(uint32_t nodeType, char *name);
extern struct ast_node *ast_newUnaryNode(uint32_t nodeType, struct ast_node *node);
extern struct ast_node *ast_newBinaryNode(uint32_t nodeType, struct ast_node *node1, struct ast_node *node2);
extern struct ast_node *ast_newTrinaryNode(uint32_t nodeType, struct ast_node *node1, struct ast_node *node2, struct ast_node *node3);
extern struct ast_listNode *ast_newListNode(uint32_t nodeType);
extern void ast_free(struct ast_node *node);

extern void ast_print(struct ast_node *node, uint32_t initialIndent, uint32_t levelIndent);
extern void ast_fprint(FILE *stream, struct ast_node *node, uint32_t initialIndent, uint32_t levelIndent);

#endif /* AST_H */
