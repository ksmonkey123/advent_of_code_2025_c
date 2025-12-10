#include "model.h"

#include <stdio.h>
#include <stdlib.h>

static int overlap(RangeNode *node1, RangeNode *node2) {
    if (node1->start > node2->start) {
        return overlap(node2, node1);
    }

    // NODE 1 starts first. only check end index now.
    if (node1->end >= node2->start - 1) {
        // node 1 ends after node 2 starts, we have overlap
        return 1;
    }
    return 0;
}

static void merge(RangeNode *target, RangeNode *additional) {
    if (additional->start < target->start) {
        target->start = additional->start;
    }
    if (additional->end > target->end) {
        target->end = additional->end;
    }
}

void puzzleAddRange(Puzzle *puzzle, long start, long end) {
    RangeNode *node = malloc(sizeof(RangeNode));
    node->start = start;
    node->end = end;
    node->next = NULL;

    if (puzzle->rangeHead == NULL) {
        // initialize
        puzzle->rangeHead = node;
        puzzle->rangeTail = node;
        return;
    }

    RangeNode *compressionHead = NULL;
    // insert at the "right" point.
    if (node->start < puzzle->rangeHead->start) {
        // add to the front of the list
        node->next = puzzle->rangeHead;
        puzzle->rangeHead = node;
        compressionHead = node;
    } else {
        // find right point to insert
        RangeNode *candidate = puzzle->rangeHead;
        while (1) {
            if (candidate->next == NULL || node->start < candidate->next->start) {
                // we found the right point to insert: between candidate and "next"
                if (overlap(candidate, node)) {
                    // in case of overlap, start compression before new node
                    compressionHead = candidate;
                } else {
                    // no overlap with candidate, start compression at new node
                    compressionHead = node;
                }
                node->next = candidate->next;
                candidate->next = node;
                break;
            }
            candidate = candidate->next;
        }
    }
    // we added a new node. try to compress the now potentially overlapping ranges
    while (compressionHead->next != NULL && overlap(compressionHead, compressionHead->next)) {
        RangeNode *droppedNode = compressionHead->next;
        // there's an overlap, we should merge and drop the merged node
        merge(compressionHead, droppedNode);
        compressionHead->next = droppedNode->next;
        free(droppedNode);
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
