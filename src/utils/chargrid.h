#ifndef AOC_CHARGRID_H
#define AOC_CHARGRID_H

struct chargrid {
    int width;
    int height;
    char *data;
};

char chargrid_get(const struct chargrid *grid, int x, int y);

void chargrid_set(struct chargrid *grid, int x, int y, char value);

struct chargrid chargrid_load(const char *filename);

void chargrid_free(struct chargrid *grid);

void chargrid_subgrid(struct chargrid *dest, const struct chargrid *src, int x, int y, int width, int height);

#endif //AOC_CHARGRID_H
