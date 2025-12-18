#include "vectors.h"

#include <stdlib.h>
#include <string.h>

void vec_long_add(struct VecLong *vector, long data) {
    if (vector->size >= vector->capacity) {
        // capacity limit reached. need to grow
        long *reallocated = realloc(vector->data, sizeof(long) * (vector->capacity + 16));
        if (reallocated == NULL) {
            exit(-1);
        }
        vector->data = reallocated;
        vector->capacity += 16;
    }

    // we have space, simply add
    vector->data[vector->size] = data;
    vector->size++;
}

void vec_long_clear(struct VecLong *vector) {
    free(vector->data);
    vector->size = 0;
    vector->capacity = 0;
}

void vec_string_add(struct VecString *vector, char *data) {
    if (vector->size >= vector->capacity) {
        // capacity limit reached. need to grow
        char **reallocated = realloc(vector->data, sizeof(char *) * (vector->capacity + 16));
        if (reallocated == NULL) {
            exit(-1);
        }
        vector->data = reallocated;
    }

    // copy the data
    int data_length = 0;
    while (1) {
        if (data[data_length++] == '\0') {
            break;
        }
    }

    char *internal_data = malloc(sizeof(char) * data_length);
    memcpy(internal_data, data, data_length);

    // we have space, simply add
    vector->data[vector->size] = internal_data;
    vector->size++;
}

void vec_string_clear(struct VecString *vector) {
    // free data
    for (int i = 0; i < vector->size; i++) {
        free(vector->data[i]);
    }
    // clear vector
    free(vector->data);
    vector->size = 0;
    vector->capacity = 0;
}
