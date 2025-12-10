#include "model.h"

#include <stdio.h>
#include <stdlib.h>

void puzzleAddRange(Puzzle *puzzle, long start, long end) {
    RangeNode *node = malloc(sizeof(RangeNode));
    node->start = start;
    node->end = end;
    node->next = NULL;

    if (puzzle->rangeHead == NULL) {
        // initialize
        puzzle->rangeHead = node;
        puzzle->rangeTail = node;
    } else {
        puzzle->rangeTail->next = node;
        puzzle->rangeTail = node;
    }
}

void puzzleAddNumber(Puzzle *puzzle, long value) {
    NumberNode *node = malloc(sizeof(NumberNode));
    node->value = value;
    node->next = NULL;

    if (puzzle->numberHead == NULL) {
        // initialize
        puzzle->numberHead = node;
        puzzle->numberTail = node;
    } else {
        puzzle->numberTail->next = node;
        puzzle->numberTail = node;
    }
}

void deletePuzzle(Puzzle *puzzle) {
    // free range nodes
    {
        RangeNode *current = puzzle->rangeHead;
        while (current != NULL) {
            RangeNode *next = current->next;
            free(current);
            current = next;
        }
    }
    // free number nodes
    {
        NumberNode *current = puzzle->numberHead;
        while (current != NULL) {
            NumberNode *next = current->next;
            free(current);
            current = next;
        }
    }
    // free wrapper
    free(puzzle);
}

Puzzle *createPuzzle() {
    Puzzle *input = malloc(sizeof(Puzzle));
    input->rangeHead = NULL;
    input->rangeTail = NULL;
    input->numberHead = NULL;
    input->numberTail = NULL;
    return input;
}

