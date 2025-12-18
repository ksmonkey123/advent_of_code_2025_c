#include <stdio.h>
#include <stdlib.h>

#include "utils/vectors.h"
#include "utils/linked_list.h"

struct calculation {
    struct VecLong numbers;
    char operation;
};

enum TokenType { NUMBER, OPERATION, END_OF_LINE };

struct Token {
    enum TokenType type;

    union {
        long number;
        char operation;
    };
};

struct Token tokenize(const char *buffer, int length) {
    if (buffer[0] == '+' || buffer[0] == '*') {
        return (struct Token){.type = OPERATION, .operation = buffer[0]};
    }
    if (buffer[0] >= '0' && buffer[0] <= '9') {
        // parse number
        long number = 0;
        for (int i = 0; i < length; i++) {
            number = number * 10 + (buffer[i] - '0');
        }
        return (struct Token){.type = NUMBER, .number = number};
    }
    printf("unable to parse token");
    exit(-1);
}

/**
 * read and tokenize the file.
 *
 * @return the string "array". caller owns the char** as well as all contained char*
 */
struct LinkedList readFile(FILE *fd) {
    struct LinkedList tokens = {0};

    int bufferUsed = 0;
    char buffer[32];

    int c = 0;
    while ((c = fgetc(fd)) != EOF) {
        if (c != ' ' && c != '\n') {
            buffer[bufferUsed++] = (char) c;
        } else {
            if (bufferUsed > 0) {
                // word is done
                struct Token *token = malloc(sizeof(struct Token));
                *token = tokenize(buffer, bufferUsed);
                bufferUsed = 0;
                ll_append(&tokens, token);
            }

            if (c == '\n') {
                struct Token *token = malloc(sizeof(struct Token));
                token->type = END_OF_LINE;
                ll_append(&tokens, token);
            }
        }
    }

    return tokens;
}


int main() {
    FILE *fd = fopen("../inputs/day06.txt", "r");

    struct LinkedList tokens = readFile(fd);

    struct ll_node *next_token = tokens.head;

    int calculation_count = 0;
    while (next_token != NULL) {
        if (((struct Token *) next_token->data)->type != END_OF_LINE) {
            calculation_count++;
            next_token = next_token->next;
        } else {
            break;
        }
    }

    struct calculation calculations[calculation_count];
    for (int i = 0; i < calculation_count; i++) {
        calculations[i] = (struct calculation){0};
    }

    int cursor = 0;
    next_token = tokens.head;
    while (next_token != NULL) {
        struct Token *token = next_token->data;
        if (token->type == END_OF_LINE) {
            cursor = 0;
        } else if (token->type == OPERATION) {
            calculations[cursor++].operation = token->operation;
        } else {
            vec_long_add(&calculations[cursor++].numbers, token->number);
        }
        next_token = next_token->next;
    }

    ll_destroy(&tokens);

    long grand_total = 0;
    for (int i = 0; i < calculation_count; i++) {
        struct calculation calc = calculations[i];

        long local_result = 0;
        for (int j = 0; j < calc.numbers.size; j++) {
            if (calc.operation == '+') {
                local_result += calc.numbers.data[j];
            } else {
                if (local_result == 0) {
                    local_result = 1;
                }
                local_result *= calc.numbers.data[j];
            }
        }

        grand_total += local_result;
    }

    printf("part 1: %ld", grand_total);

    for (int i = 0; i < calculation_count; i++) {
        struct calculation calc = calculations[i];
        vec_long_clear(&calc.numbers);
    }
}
