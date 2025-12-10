#ifndef AOC_INPUT_H
#define AOC_INPUT_H
#include <stdlib.h>

typedef struct rangeNode {
    long start;
    long end;
    struct rangeNode *next;
} RangeNode;

typedef struct numberNode {
    long value;
    struct numberNode *next;
} NumberNode;

typedef struct {
    struct rangeNode *rangeHead;
    struct rangeNode *rangeTail;
    struct numberNode *numberHead;
    struct numberNode *numberTail;
} Puzzle;

Puzzle *createPuzzle();

void deletePuzzle(Puzzle *puzzle);

void puzzleAddRange(Puzzle *puzzle, long start, long end);

void puzzleAddNumber(Puzzle *puzzle, long value);

#endif //AOC_INPUT_H
