/* C code generator */

#include <inttypes.h>
#include <stdio.h>

#include "c-gen.h"
#include "ast.h"
#include "parser-support.h"

void cgen_print(struct ast_node *astNode) {
    cgen_fprint(stdout, astNode);
}

void cgen_fprint(FILE *stream, struct ast_node *astNode) {
    fprintf(stream, "/* Auto-generated C code by C-Gen */\n");
    fprintf(stream, "\n");
    fprintf(stream, "#include <stdio.h>\n");
    fprintf(stream, "\n");
    fprintf(stream, "int main(void) {\n");
    
    cgen_fprint_recurse(stream, astNode, 4);
    
    fprintf(stream, "    return 0;\n");
    fprintf(stream, "}\n");
}

void cgen_fprint_recurse(FILE *stream, struct ast_node *astNode, uint32_t indent) {
    switch (astNode->nodeType) {
    case '!':
        fputc('!', stream);
        break;
    case '#':
        fputc('#', stream);
        break;
    case '$':
        fputc('$', stream);
        break;
    case '%':
        fputc('%', stream);
        break;
    case '&':
        fputc('&', stream);
        break;
    case '*':
        {
            struct ast_binaryNode *node = (struct ast_binaryNode *) astNode;
            fputc('(', stream);
            cgen_fprint_recurse(stream, node->node1, indent);
            fprintf(stream, " * ");
            cgen_fprint_recurse(stream, node->node2, indent);
            fputc(')', stream);
        }
        break;
    case '+':
        {
            struct ast_binaryNode *node = (struct ast_binaryNode *) astNode;
            fputc('(', stream);
            cgen_fprint_recurse(stream, node->node1, indent);
            fprintf(stream, " + ");
            cgen_fprint_recurse(stream, node->node2, indent);
            fputc(')', stream);
        }
        break;
    case ',':
        break;
    case '-':
        {
            if (astNode->nodeCategory == AST_UNARY_NODE) {
                struct ast_unaryNode *node = (struct ast_unaryNode *) astNode;
                fprintf(stream, "(-");
                cgen_fprint_recurse(stream, node->node1, indent);
                fprintf(stream, ")");
            }
            else {
                struct ast_binaryNode *node = (struct ast_binaryNode *) astNode;
                fputc('(', stream);
                cgen_fprint_recurse(stream, node->node1, indent);
                fprintf(stream, " - ");
                cgen_fprint_recurse(stream, node->node2, indent);
                fputc(')', stream);
            }
        }
        break;
    case '.':
        fputc('.', stream);
        break;
    case '/':
        {
            struct ast_binaryNode *node = (struct ast_binaryNode *) astNode;
                fputc('(', stream);
                cgen_fprint_recurse(stream, node->node1, indent);
                fprintf(stream, " / ");
                cgen_fprint_recurse(stream, node->node2, indent);
                fputc(')', stream);
        }
        break;
    case ':':
        fputc(':', stream);
        break;
    case ';':
        fputc(';', stream);
        break;
    case '<':
        fputc('<', stream);
        break;
    case '=':
        {
            struct ast_binaryNode *node = (struct ast_binaryNode *) astNode;
            cgen_fprint_recurse(stream, node->node1, indent);
            fprintf(stream, " = ");
            cgen_fprint_recurse(stream, node->node2, indent);
        }
        break;
    case '>':
        fputc('>', stream);
        break;
    case '?':
        fputc('?', stream);
        break;
    case '@':
        fputc('@', stream);
        break;
    case '\\':
        fputc('\\', stream);
        break;
    case '^':
        fputc('^', stream);
        break;
    case '`':
        fputc('`', stream);
        break;
    case '|':
        fputc('|', stream);
        break;
    case '~':
        fputc('~', stream);
        break;
    case AST_INT_LITERAL:
        {
            struct ast_literalNode *node = (struct ast_literalNode *) astNode;
            fprintf(stream, "%" PRIi32, node->value.intValue);
        }
        break;
    case AST_IDENTIFIER:
        {
            struct ast_namedNode *node = (struct ast_namedNode *) astNode;
            fprintf(stream, "%s", node->name);
        }
        break;
    case AST_STATEMENTS:
        {
            struct ast_listNode *listNode = (struct ast_listNode *) astNode;
            union primitive_value *listValues = listNode->list->values;
            
            for (uint32_t i = 0, len = listNode->list->size; i < len; i++) {
                struct ast_node *nodeI = (struct ast_node *) (listValues[i].pointerValue);
                fprintf(stream, "%*s", indent, "");
                cgen_fprint_recurse(stream, nodeI, indent);
                fprintf(stream, ";\n");
            }
        }
        break;
    case AST_PRINT:
        {
            struct ast_unaryNode *node = (struct ast_unaryNode *) astNode;
            fprintf(stream, "printf(\"%%" PRIi32 "\", ");
            cgen_fprint_recurse(stream, node->node1, indent);
            fputc(')', stream);
        }
        break;
    case AST_PRINTLN:
        {
            struct ast_unaryNode *node = (struct ast_unaryNode *) astNode;
            fprintf(stream, "printf(\"%%" PRIi32 "\\n\", ");
            cgen_fprint_recurse(stream, node->node1, indent);
            fputc(')', stream);
        }
        break;
    default:
        printf("C-Gen error: Unknown node type %" PRIu32 "\n", astNode->nodeType);
        break;
    }    
}
