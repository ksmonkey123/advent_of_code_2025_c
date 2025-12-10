#include <stdio.h>
#include <stdlib.h>
#include "model.h"
#include "parts.h"
#include "util.h"

Puzzle *readFile(Puzzle *puzzle) {
    FILE *fd = fopen("../inputs/day05.txt", "r");

    char buffer[256];
    while (fgets(buffer, 256, fd) != NULL) {
        int separatorIndex = positionOf(buffer, '-');
        int endIndex = positionOf(buffer, '\n');

        if (endIndex == 0) {
            // empty line
            continue;
        }

        if (separatorIndex > 0) {
            // range
            long start = parseNumber(buffer, 0, separatorIndex);
            long end = parseNumber(buffer, separatorIndex + 1, endIndex);
            puzzleAddRange(puzzle, start, end);
        } else {
            // value
            long value = parseNumber(buffer, 0, endIndex);
            puzzleAddNumber(puzzle, value);
        }
    }

    fclose(fd);
}

int main() {
    Puzzle *input = createPuzzle();
    readFile(input);

    printf("part 1: %ld\n", part1(input));
    printf("part 2: %ld\n", part2(input));

    deletePuzzle(input);
}
