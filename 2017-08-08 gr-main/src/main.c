#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "parser-support.h"
#include "ast.h"
#include "eval.h"
#include "c-gen.h"

int32_t parseFile(char *filename) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("Error: Cannot read file `%s'.\n", filename);
        return EXIT_FAILURE;
    }

    struct ast_node *returnAstNode;
    int32_t parseStatus = parser_parseStream(filename, f, &returnAstNode);

    printf("\nParse status = %s\n", parser_getParseStatusName(parseStatus));

    //ast_print(returnAstNode, 2, 4);
    
    // Eval (run the program).
    struct eval_context *evalContext = eval_newContext(EVAL_DEFAULT_STACK_MAX_DEPTH);
    eval_ast(evalContext, returnAstNode);
    eval_freeContext(evalContext);
    
    // C-Gen (generate C code).
    cgen_print(returnAstNode);
        
    fclose(f);

    return parseStatus;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s <input-file> ...\n", argv[0]);
        return EXIT_FAILURE;
    }

    for (uint32_t i = 1; i < argc; i++) {
        parseFile(argv[i]);
    }

    return EXIT_SUCCESS;
}

