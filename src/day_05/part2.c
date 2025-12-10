#include "parts.h"

long part2(Puzzle *input) {
    long counter = 0;

    RangeNode *node = input->rangeHead;

    // range nodes are already sorted, but not yet merged
    while (node != NULL) {
        counter += node->end - node->start + 1;
        node = node->next;
    }

    return counter;
}
