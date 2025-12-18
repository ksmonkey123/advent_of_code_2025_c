#ifndef AOC_VECTORS_H
#define AOC_VECTORS_H

struct VecLong {
    int size;
    int capacity;
    long* data;
};
void vec_long_add(struct VecLong* vector, long data);
void vec_long_clear(struct VecLong* vector);

struct VecString {
    int size;
    int capacity;
    char** data;
};
// add string. char* is copied.
void vec_string_add(struct VecString* vector, char* data);
void vec_string_clear(struct VecString* vector);

#endif //AOC_VECTORS_H