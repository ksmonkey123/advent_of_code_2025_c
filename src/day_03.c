#include <stdio.h>

int positionOf(const char query, const char *buffer) {
    for (int i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] == query) {
            return i;
        }
        i++;
    }
    return -1;
}

struct HighDigit {
    int digit;
    int position;
};

/**
 * Search the buffer for the largest digit within the range
 * @param start start of the range (inclusive)
 * @param end end of the range (exclusive)
 */
struct HighDigit searchLargesDigit(const char *buffer, int start, int end) {
    struct HighDigit result = {.digit = 0, .position = 0};

    for (int i = start; i < end; i++) {
        int digit = buffer[i] - '0';
        if (digit > result.digit) {
            result.digit = digit;
            result.position = i;
        }
    }

    return result;
}

long lineJolt(const char *buffer, int digits) {
    int length = positionOf('\n', buffer);

    long result = 0;
    int start = 0;

    for (int i = 0; i < digits; i++) {
        struct HighDigit max = searchLargesDigit(buffer, start, length - (digits - 1) + i);
        result = 10 * result + max.digit;
        start = max.position + 1;
    }

    return result;
}

int main() {
    FILE *file = fopen("../inputs/day03.txt", "r");

    long joltSum = 0;
    long largeJoltSum = 0;

    char buffer[1024];
    while (fgets(buffer, 1024, file) != NULL) {
        long jolt = lineJolt(buffer, 2);
        joltSum += jolt;
        long largeJolt = lineJolt(buffer, 12);
        largeJoltSum += largeJolt;
    }

    printf("part 1: %ld\n", joltSum);
    printf("part 2: %ld\n", largeJoltSum);

    fclose(file);
}
