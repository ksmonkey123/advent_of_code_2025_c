#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Get index of first occurrence of the char 'query' in the null-terminated string. -1 if none
 */
int positionOf(const char query, const char *buffer) {
    for (int i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] == query) {
            return i;
        }
    }
    return -1;
}

typedef struct {
    char *content;
    int width;
    int height;
} CharGrid;

/**
 * Read input file into char grid.
 * Caller owns grid and contained array.
 * (Array is allocated as a single block)
 */
CharGrid *readFile() {
    FILE *fd = fopen("../inputs/day04.txt", "r");
    char buffer[20000];
    int bytesRead = fread(buffer, sizeof(char), 19999, fd);
    buffer[bytesRead] = '\0';
    fclose(fd);

    // get width
    int width = positionOf('\n', buffer);
    int height = bytesRead / (width + 1);
    void *space = malloc(sizeof(CharGrid) + (width * height + 1) * sizeof(char));

    CharGrid *grid = space;
    char *gridContent = space + sizeof(CharGrid);
    grid->content = gridContent;
    grid->width = width;
    grid->height = height;

    // write file content into grid
    for (int y = 0; y < grid->height; y++) {
        memcpy(grid->content + grid->width * y, buffer + (grid->width + 1) * y, grid->width * sizeof(char));
    }
    grid->content[grid->width * grid->height] = '\0';

    return grid;
}

/**
 * get char at the given x/y coordinates. `\0` if out of bounds.
 * @param x horizontal coordinate
 * @param y vertical coordinate
 */
char getAbsolute(const CharGrid *grid, int x, int y) {
    if (x < 0 || y < 0 || x >= grid->width || y >= grid->height) {
        return '\0';
    }
    return grid->content[x + y * grid->width];
}

int testAbsolute(const CharGrid *grid, int x, int y, char test) {
    if (getAbsolute(grid, x, y) == test) {
        return 1;
    }
    return 0;
}

void setAbsolute(CharGrid *grid, int x, int y, char value) {
    grid->content[x + y * grid->width] = value;
}

/**
 * Counts the number of the 8 neighbors that match the tested char
 */
int getNeighborCount(const CharGrid *grid, int x, int y, char test) {
    return testAbsolute(grid, x - 1, y - 1, test)
           + testAbsolute(grid, x, y - 1, test)
           + testAbsolute(grid, x + 1, y - 1, test)
           + testAbsolute(grid, x - 1, y, test)
           + testAbsolute(grid, x + 1, y, test)
           + testAbsolute(grid, x - 1, y + 1, test)
           + testAbsolute(grid, x, y + 1, test)
           + testAbsolute(grid, x + 1, y + 1, test);
}

int part1(const CharGrid *grid) {
    int count = 0;

    for (int x = 0; x < grid->width; x++) {
        for (int y = 0; y < grid->height; y++) {
            if (testAbsolute(grid, x, y, '@') > 0
                && getNeighborCount(grid, x, y, '@') < 4) {
                count++;
            }
        }
    }

    return count;
}

int part2(CharGrid *grid) {
    int count = 0;
    while (1) {
        int iteration = 0;
        for (int x = 0; x < grid->width; x++) {
            for (int y = 0; y < grid->height; y++) {
                if (testAbsolute(grid, x, y, '@') > 0
                    && getNeighborCount(grid, x, y, '@') < 4) {
                    setAbsolute(grid, x, y, '-');
                    iteration++;
                }
            }
        }
        if (iteration > 0) {
            count += iteration;
        } else {
            return count;
        }
    }
}

int main() {
    CharGrid *grid = readFile();

    printf("part 1: %d\n", part1(grid));
    printf("part 2: %d\n", part2(grid));

    free(grid);
}
