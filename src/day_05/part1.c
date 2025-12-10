#include "parts.h"

static int test(Puzzle *puzzle, long value) {
    RangeNode *range = puzzle->rangeHead;
    while (range != NULL) {
        if (range->start <= value && value <= range->end) {
            return 1;
        }
        range = range->next;
    }
    return 0;
}

long part1(Puzzle *puzzle) {
    int counter = 0;

    NumberNode *number = puzzle->numberHead;
    while (number != NULL) {
        if (test(puzzle, number->value)) {
            counter++;
        }
        number = number->next;
    }

    return counter;
}
