/* Abstract syntax tree */

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include "ast.h"
#include "parser-support.h"
#include "arraylist.h"

const char *ast_getNodeCategoryName(uint32_t nodeCategory) {
    switch (nodeCategory) {
    case AST_BASE_NODE:
        return "AST_BASE_NODE";
    case AST_LITERAL_NODE:
        return "AST_LITERAL_NODE";
    case AST_NAMED_NODE:
        return "AST_NAMED_NODE";
    case AST_UNARY_NODE:
        return "AST_UNARY_NODE";
    case AST_BINARY_NODE:
        return "AST_BINARY_NODE";
    case AST_TRINARY_NODE:
        return "AST_TRINARY_NODE";
    case AST_LIST_NODE:
        return "AST_LIST_NODE";
    default:
        return "(unknown)";
    }
}

const char *ast_getNodeTypeName(uint32_t nodeType) {
    switch (nodeType) {
    case 0:
        return "(none)";
    case '!':
        return "!";
    case '#':
        return "#";
    case '$':
        return "$";
    case '%':
        return "%";
    case '&':
        return "&";
    case '(':
        return "(";
    case ')':
        return ")";
    case '*':
        return "*";
    case '+':
        return "+";
    case ',':
        return ",";
    case '-':
        return "-";
    case '.':
        return ".";
    case '/':
        return "/";
    case ':':
        return ":";
    case ';':
        return ";";
    case '<':
        return "<";
    case '=':
        return "=";
    case '>':
        return ">";
    case '?':
        return "?";
    case '@':
        return "@";
    case '[':
        return "]";
    case '\\':
        return "\\";
    case ']':
        return "]";
    case '^':
        return "^";
    case '`':
        return "`";
    case '{':
        return "{";
    case '|':
        return "|";
    case '}':
        return "}";
    case '~':
        return "~";
    case AST_INT_LITERAL:
        return "AST_INT_LITERAL";
    case AST_IDENTIFIER:
        return "AST_IDENTIFIER";
    case AST_STATEMENTS:
        return "AST_STATEMENTS";
    case AST_PRINT:
        return "AST_PRINT";
    case AST_PRINTLN:
        return "AST_PRINTLN";
    default:
        return "(unknown)";
    }
}

struct ast_node *ast_newNode(uint32_t nodeType) {
	struct ast_node *newNode = malloc(sizeof(struct ast_node));
    newNode->nodeCategory = AST_BASE_NODE;
	newNode->nodeType = nodeType;
	return (struct ast_node *) newNode;
}

struct ast_node *ast_newLiteralNode(uint32_t nodeType, union primitive_value value) {
	struct ast_literalNode *newNode = malloc(sizeof(struct ast_literalNode));
    newNode->base.nodeCategory = AST_LITERAL_NODE;
    newNode->base.nodeType = nodeType;
    newNode->value = value;
	return (struct ast_node *) newNode;
}

struct ast_node *ast_newNamedNode(uint32_t nodeType, char *name) {
	struct ast_namedNode *newNode = malloc(sizeof(struct ast_namedNode));
    newNode->base.nodeCategory = AST_NAMED_NODE;
	newNode->base.nodeType = nodeType;
	newNode->name = name;
	return (struct ast_node *) newNode;
}

struct ast_node *ast_newUnaryNode(uint32_t nodeType, struct ast_node *node) {
	struct ast_unaryNode *newNode = malloc(sizeof(struct ast_unaryNode));
    newNode->base.nodeCategory = AST_UNARY_NODE;
	newNode->base.nodeType = nodeType;
	newNode->node1 = node;
	return (struct ast_node *) newNode;
}

struct ast_node *ast_newBinaryNode(uint32_t nodeType, struct ast_node *node1, struct ast_node *node2) {
	struct ast_binaryNode *newNode = malloc(sizeof(struct ast_binaryNode));
    newNode->base.nodeCategory = AST_BINARY_NODE;
	newNode->base.nodeType = nodeType;
	newNode->node1 = node1;
	newNode->node2 = node2;
	return (struct ast_node *) newNode;
}

struct ast_node *ast_newTrinaryNode(uint32_t nodeType, struct ast_node *node1, struct ast_node *node2, struct ast_node *node3) {
	struct ast_trinaryNode *newNode = malloc(sizeof(struct ast_trinaryNode));
    newNode->base.nodeCategory = AST_TRINARY_NODE;
	newNode->base.nodeType = nodeType;
	newNode->node1 = node1;
	newNode->node2 = node2;
	newNode->node2 = node3;
	return (struct ast_node *) newNode;
}

struct ast_listNode *ast_newListNode(uint32_t nodeType) {
    struct ast_listNode *newNode = malloc(sizeof(struct ast_listNode));
    newNode->base.nodeCategory = AST_LIST_NODE;
    newNode->base.nodeType = nodeType;
	newNode->list = arraylist_create();
	return newNode;
}

void ast_free(struct ast_node *node) {
    switch (node->nodeCategory) {
    case AST_BASE_NODE:
    case AST_LITERAL_NODE:
        break;
    case AST_NAMED_NODE:
        free(((struct ast_namedNode *) node)->name);
        break;
    case AST_UNARY_NODE:
        ast_free((struct ast_node *) (((struct ast_unaryNode *) node)->node1));
        break;
    case AST_BINARY_NODE:
        ast_free((struct ast_node *) (((struct ast_binaryNode *) node)->node1));
        ast_free((struct ast_node *) (((struct ast_binaryNode *) node)->node2));
        break;
    case AST_TRINARY_NODE:
        ast_free((struct ast_node *) (((struct ast_trinaryNode *) node)->node1));
        ast_free((struct ast_node *) (((struct ast_trinaryNode *) node)->node2));
        ast_free((struct ast_node *) (((struct ast_trinaryNode *) node)->node3));
        break;
    case AST_LIST_NODE:
        {
            struct ast_listNode *listNode = (struct ast_listNode *) node;
            union primitive_value *listValues = listNode->list->values;
            
            for (uint32_t i = 0, len = listNode->list->size; i < len; i++) {
                void *ptr = listValues[i].pointerValue;
                ast_free((struct ast_node *) ptr);
            }
        }
    }
    
    free(node);
}

void ast_print(struct ast_node *node, uint32_t initialIndent, uint32_t levelIndent) {
    ast_fprint(stdout, node, initialIndent, levelIndent);
}

void ast_fprint(FILE *stream, struct ast_node *node, uint32_t initialIndent, uint32_t levelIndent) {
    fprintf(stream, "\n%*s{\n%*snodeCategory: \"%s\", nodeType: \"%s\", lineno: %" PRIu32 ", column: %" PRIu32,
        initialIndent, "",
        initialIndent + levelIndent, "",
        ast_getNodeCategoryName(node->nodeCategory),
        ast_getNodeTypeName(node->nodeType),
        node->lineno,
        node->column);
            
    switch (node->nodeCategory) {
    case AST_BASE_NODE:
        break;
    case AST_LITERAL_NODE:
        {
            fprintf(stream, ", value: ");
            
            switch (node->nodeType) {
            case AST_INT_LITERAL:
                fprintf(stream, "%" PRIi32,
                    ((struct ast_literalNode *) node)->value.intValue);
                break;
            default:
                fprintf(stream, "(unknown literal node type %" PRIu32 ")", node->nodeType);
                break;
            }
        }
        break;
    case AST_NAMED_NODE:
        {
            fprintf(stream, ", name: \"%s\"", ((struct ast_namedNode *) node)->name);
        }
        break;
    case AST_UNARY_NODE:
        {
            struct ast_unaryNode *n = (struct ast_unaryNode *) node;
            
            fprintf(stream, ",\n%*snode1:", initialIndent + levelIndent, "");
            ast_fprint(stream, n->node1, initialIndent + levelIndent, levelIndent);
        }
        break;
    case AST_BINARY_NODE:
        {
            struct ast_binaryNode *n = (struct ast_binaryNode *) node;
            
            fprintf(stream, ",\n%*snode1:", initialIndent + levelIndent, "");
            ast_fprint(stream, n->node1, initialIndent + levelIndent, levelIndent);
            
            fprintf(stream, ",\n%*snode2:", initialIndent + levelIndent, "");
            ast_fprint(stream, n->node2, initialIndent + levelIndent, levelIndent);
        }
        break;
    case AST_TRINARY_NODE:
        {
            struct ast_trinaryNode *n = (struct ast_trinaryNode *) node;
            
            fprintf(stream, ",\n%*snode1:", initialIndent + levelIndent, "");
            ast_fprint(stream, n->node1, initialIndent + levelIndent, levelIndent);
            
            fprintf(stream, ",\n%*snode2:", initialIndent + levelIndent, "");
            ast_fprint(stream, n->node2, initialIndent + levelIndent, levelIndent);
            
            fprintf(stream, ",\n%*snode3:", initialIndent + levelIndent, "");
            ast_fprint(stream, n->node3, initialIndent + levelIndent, levelIndent);
        }
        break;
    case AST_LIST_NODE:
        {
            struct ast_listNode *listNode = (struct ast_listNode *) node;
            union primitive_value *listValues = listNode->list->values;
            
            for (uint32_t i = 0, len = listNode->list->size; i < len; i++) {
                struct ast_node *nodeI = (struct ast_node *) (listValues[i].pointerValue);
                fprintf(stream, ",\n%*snode[%" PRIu32 "]:", initialIndent + levelIndent, "", i);
                ast_fprint(stream, nodeI, initialIndent + levelIndent, levelIndent);
            }
        }
        break;
    default:
        fprintf(stream, "(unknown node category %" PRIu32 ")", node->nodeCategory);
        break;
    }

    fprintf(stream, "\n%*s}", initialIndent, "");
}
