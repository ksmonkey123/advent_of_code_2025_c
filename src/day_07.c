#include <stdio.h>

#include "utils/chargrid.h"

int main() {
    struct chargrid grid = chargrid_load("../inputs/day07.txt");

    // grid of "path counters" for each point in the chargrid. initialized to 0.
    long pathCounters[grid.height * grid.width];
    for (int y = 0; y < grid.height; y++) {
        for (int x = 0; x < grid.width; x++) {
            pathCounters[x + y * grid.width] = 0;
        }
    }

    long splitCount = 0;
    // single pass through the grid is enough. Start on second line.
    for (int y = 1; y < grid.height; y++) {
        for (int x = 0; x < grid.width; x++) {
            char c = chargrid_get(&grid, x, y);
            switch (c) {
                case '|':
                case '.': {
                    switch (chargrid_get(&grid, x, y - 1)) {
                        case 'S': {
                            // propagate beam down
                            chargrid_set(&grid, x, y, '|');
                            pathCounters[x + y * grid.width]++;
                            break;
                        }
                        case '|': {
                            // propagate beam down
                            chargrid_set(&grid, x, y, '|');
                            pathCounters[x + y * grid.width] += pathCounters[x + (y - 1) * grid.width];
                            break;
                        }
                        default: break;
                    }
                    break;
                }
                case '^': {
                    if (chargrid_get(&grid, x, y - 1) == '|') {
                        // split beam
                        chargrid_set(&grid, x - 1, y, '|');
                        pathCounters[x - 1 + y * grid.width] += pathCounters[x + (y - 1) * grid.width];
                        chargrid_set(&grid, x + 1, y, '|');
                        pathCounters[x + 1 + y * grid.width] += pathCounters[x + (y - 1) * grid.width];
                        splitCount++;
                    }
                    break;
                }
                default: break;
            }
        }
    }

    long pathSum = 0;
    for (int x = 0; x < grid.width; x++) {
        pathSum += pathCounters[x + (grid.height - 1) * grid.width];
    }

    printf("part 1: %ld\n", splitCount);
    printf("part 2: %ld\n", pathSum);
}
