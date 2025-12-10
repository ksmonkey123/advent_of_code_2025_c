#include "util.h"

int positionOfLimited(const char *string, char search, char terminator) {
    int pos = 0;
    while (string[pos] != '\0' || string[pos] != terminator) {
        if (string[pos] == search) {
            return pos;
        }
        pos++;
    }
    return -1;
}

int positionOf(const char *string, char search) {
    return positionOfLimited(string, search, '\0');
}

long parseNumber(const char *string, int start, int end) {
    long number = 0;

    for (int i = start; i < end; i++) {
        number = number * 10 + (string[i] - '0');
    }

    return number;
}
