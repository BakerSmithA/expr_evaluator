#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

// Indicates whether parsing so far has been succcessful or failed.
typedef enum ParseType {
    SUCCESS, FAIL
} ParseType;

// Either the remaining tokens on the input or an error message if parsing failed.
typedef struct ParseResult {
    ParseType type;
    union {
        // Remaining tokens on the input stream.
        // No AST is produced because a syntax-directed grammar is used to
        // generate output while parsing.
        char *tokens;
        // Error message detailing what went wrong.
        char *err;
    };
} ParseResult;

ParseResult from_tokens(void *tokens) {
    return (ParseResult) { SUCCESS, tokens };
}

ParseResult fail(char *err) {
    return (ParseResult) { FAIL, err };
}

ParseResult then(ParseResult p, ParseResult(*f)(char*)) {
    if (p.type == SUCCESS) {
        return f(p.tokens);
    }
    return p;
}

ParseResult thens(ParseResult acc, int n, ...) {
    va_list fs;
    va_start(fs, n);

    for (int i=0; i<n; i++) {
        ParseResult(*f)(char*) = va_arg(fs, ParseResult(*)(char*));
        acc = then(acc, f);
    }

    va_end(fs);
    return acc;
}

ParseResult try(ParseResult(*a)(char*), ParseResult(*b)(char*), char *tokens) {
    ParseResult r_a = a(tokens);
    if (r_a.type == SUCCESS) {
        return r_a;
    }
    return b(tokens);
}

ParseResult then_try(ParseResult p, ParseResult(*a)(char*), ParseResult(*b)(char*)) {
    ParseResult _try(char *tokens) {
        return try(a, b, tokens);
    }
    return then(p, _try);
}

ParseResult next(char *tokens) {
    return from_tokens(tokens+1);
}

char *append_char(char *szString, size_t strsize, char c) {
    size_t len = strlen(szString);
    if(len+1 < strsize) {
        szString[len++] = c;
        szString[len] = '\0';
        return szString;
    }
    return NULL;
}

ParseResult match(char expected, char *tokens) {
    if (*tokens == expected) {
        return next(tokens);
    }
    printf("Got %c expected %c\n", *tokens, expected);
    return fail("Unexpected");
}

ParseResult print(char *tokens, char msg) {
    printf("%c", msg);
    return from_tokens(tokens);
}

// Syntax-Directed Grammar:
//  expr : term rest
//  rest : '+' term { print('+') rest }
//       | '-' term { print('-') rest }
//       | ε
//  term : '0' { print('0') }
//       | '1' { print('1') }
//       ...
//       | '9' { print('9') }

ParseResult term(char *tokens) {
    if (isdigit(*tokens)) {
        putchar(*tokens);
        return next(tokens);
    }
    return fail("Failed to parse term");
}

ParseResult bin_op(char op, char *tokens) {
    ParseResult p(char *ts) {
        return print(ts, op);
    }

    ParseResult plus = match(op, tokens);
    return thens(plus, 2, term, p);
}

ParseResult plus(char *tokens) {
    return bin_op('+', tokens);
}

ParseResult minus(char *tokens) {
    return bin_op('-', tokens);
}

ParseResult expr(char *tokens) {
    ParseResult t = term(tokens);
    return then_try(t, minus, plus);
}

void check_fail(ParseResult p) {
    if (p.type == FAIL) {
        printf("\nError: %s", p.err);
    }
}

int main(int argc, char *argv[argc]) {
    if (argc != 2) {
        printf("Expected expression to parse\n");
        return 0;
    }

    printf("%s\n", argv[1]);

    ParseResult p = expr(argv[1]);
    check_fail(p);

    printf("\n");
}
