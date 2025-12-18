//
// Created by Andreas on 18.12.2025.
//

#include "chargrid.h"

#include <stdlib.h>

char chargrid_get(const struct chargrid *grid, int x, int y) {
    return grid->data[x + y * grid->width];
}

static int max(int a, int b) {
    return a > b ? a : b;
}

void chargrid_set(struct chargrid *grid, int x, int y, char value) {
    if (x >= grid->width || y >= grid->height) {
        int new_height = max(grid->height, y + 1);
        int new_width = max(grid->width, x + 1);
        // extend grid
        char *stretched = malloc(sizeof(char) * (new_width * new_height + 1));
        // copy over old grid
        for (int xx = 0; xx < new_width; xx++) {
            for (int yy = 0; yy < new_height; yy++) {
                if (xx < grid->width && yy < grid->height) {
                    // copy old data
                    stretched[xx + yy * new_width] = grid->data[xx + yy * grid->width];
                } else {
                    stretched[xx + yy * new_width] = ' ';
                }
            }
        }
        // add null terminator out of bounds of grid, just to be sure
        stretched[new_width * new_height - 1] = value;
        grid->width = new_width;
        grid->height = new_height;
        free(grid->data);
        grid->data = stretched;
    }

    grid->data[x + y * grid->width] = value;
}

void chargrid_init(struct chargrid *grid, FILE *fd) {
    int x = 0, y = 0;

    int c = 0;
    while ((c = fgetc(fd)) != EOF) {
        if (c != '\n') {
            chargrid_set(grid, x++, y, (char) c);
        } else {
            x = 0;
            y++;
        }
    }
}

void chargrid_free(struct chargrid *grid) {
    free(grid->data);
    grid->data = NULL;
    grid->width = 0;
    grid->height = 0;
}

void chargrid_subgrid(struct chargrid *dest, const struct chargrid *src, int x, int y, int width, int height) {
    chargrid_free(dest);

    for (int xx = 0; xx < width; xx++) {
        for (int yy = 0; yy < height; yy++) {
            chargrid_set(dest, xx, yy, chargrid_get(src, xx + x, yy + y));
        }
    }
}
