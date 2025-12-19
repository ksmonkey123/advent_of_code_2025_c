#include <stdio.h>

#include "utils/chargrid.h"

struct calculation {
    char operation;
    int numbersCount;
    long numbers[10];
};

void parseSubgridPart1(struct calculation *dest, const struct chargrid *src) {
    dest->numbersCount = 0;
    for (int y = 0; y < src->height - 1; y++) {
        long value = 0;
        for (int x = 0; x < src->width; x++) {
            char c = chargrid_get(src, x, y);
            if (c != ' ') {
                value = 10 * value + (c - '0');
            }
        }
        dest->numbers[dest->numbersCount++] = value;
    }
    dest->operation = chargrid_get(src, 0, src->height - 1);
}

void parseSubgridPart2(struct calculation *dest, const struct chargrid *src) {
    dest->numbersCount = 0;
    for (int x = 0; x < src->width; x++) {
        long value = 0;
        for (int y = 0; y < src->height - 1; y++) {
            char c = chargrid_get(src, x, y);
            if (c != ' ') {
                value = 10 * value + (c - '0');
            }
        }
        dest->numbers[dest->numbersCount++] = value;
    }
    dest->operation = chargrid_get(src, 0, src->height - 1);
}

long doWork(const struct chargrid *grid, void (*parser)(struct calculation *, const struct chargrid *)) {
    long grand_total = 0;
    int startX = 0;
    struct chargrid currentCalculation = {0};
    for (int x = 0; x <= grid->width; x++) {
        // check if this column is a separator
        int separator = 1;
        if (x < grid->width) {
            for (int y = 0; y < grid->height; y++) {
                if (chargrid_get(grid, x, y) != ' ') {
                    separator = 0;
                    break;
                }
            }
        }
        if (!separator) {
            continue;
        }
        chargrid_subgrid(&currentCalculation, grid, startX, 0, x - startX, grid->height);
        startX = x + 1;

        struct calculation calculation = {0};
        parser(&calculation, &currentCalculation);

        long acc = calculation.operation == '+' ? 0 : 1;
        for (int i = 0; i < calculation.numbersCount; i++) {
            if (calculation.operation == '+') {
                acc += calculation.numbers[i];
            } else {
                acc *= calculation.numbers[i];
            }
        }

        grand_total += acc;
    }
    chargrid_free(&currentCalculation);
    return grand_total;
}

int main() {
    struct chargrid grid = chargrid_load("../inputs/day06.txt");

    printf("part 1: %ld\n", doWork(&grid, parseSubgridPart1));
    printf("part 2: %ld\n", doWork(&grid, parseSubgridPart2));

    chargrid_free(&grid);
}
