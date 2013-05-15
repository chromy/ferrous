#include "expression.h"
#include "parser.h"
#include "lexer.h"

#include <stdio.h>
#include <sys/stat.h>

int yyparse(SExpression **expression, yyscan_t scanner);

SExpression *getAST(void) {
    SExpression *expression;
    yyscan_t scanner;
    YY_BUFFER_STATE state;

    if (yylex_init(&scanner)) {
        // couldn't initialize
        return NULL;
    }

    if (yyparse(&expression, scanner)) {
        // error parsing
        return NULL;
    }

    yylex_destroy(scanner);
    return expression;
}

int evaluate(SExpression *e) {
    switch (e->type) {
        case eVALUE:
            return e->value;
        case eMULTIPLY:
            return evaluate(e->left) * evaluate(e->right);
        case ePLUS:
            return evaluate(e->left) + evaluate(e->right);
        default:
            // shouldn't be here
            return 0;
    }
}

void writeExe(int result) {
    const char* name = "a.out";
    FILE *fout;
    fout = fopen(name, "w");
    chmod(name, S_IRWXU);
    fprintf(fout, "#! /usr/bin/env bash\n");
    fprintf(fout, "echo %d\n", result);
    fclose(fout);
}

int main(void) {
    SExpression *e = NULL;
    int result = 0;

    e = getAST();
    result = evaluate(e);
    writeExe(result);

    deleteExpression(e);

    return 0;
}
