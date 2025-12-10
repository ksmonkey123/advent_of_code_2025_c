#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char start[32];
    char end[32];
    int startLength;
    int endLength;
} RawRange;

typedef struct {
    long start;
    long end;
    long startPrefix;
    long endPrefix;
    long prefixMultiplier;
} Part1Range;


long parseNumber(const char *buffer, const int length) {
    long sum = 0;

    for (int i = 0; i < length; i++) {
        sum *= 10;
        sum += buffer[i] - '0';
    }

    return sum;
}

long exp(int base, int exponent) {
    long result = 1;
    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}

Part1Range part1_preprocess(const RawRange *range) {
    Part1Range result;

    result.start = parseNumber(range->start, range->startLength);
    result.end = parseNumber(range->end, range->endLength);
    result.startPrefix = parseNumber(range->start, range->startLength / 2);
    result.endPrefix = parseNumber(range->end, range->endLength / 2);
    result.prefixMultiplier = exp(10, (range->startLength - (range->startLength / 2)));

    if (range->startLength % 2 != 0) {
        // start is odd, we can directly raise to the start of the next 'even' block.
        result.startPrefix = exp(10, range->startLength / 2);
    }
    if (range -> endLength % 2 != 0) {
        // end is odd, we can cut the range to the end of the previous 'even' block.
        result.endPrefix = exp(10, range->endLength / 2) - 1;
    }

    return result;
}

long part1_process_range(const RawRange *range) {
    if (range->endLength - range->startLength > 1) {
        // we  don't support that yet
        exit(-1);
    }

    if (range->startLength == range->endLength && range->startLength % 2 == 1) {
        // entirely odd ranges within the same magnitude must always be empty
        return 0;
    }

    const Part1Range r = part1_preprocess(range);

    long sum = 0;

    for (long i = r.startPrefix; i <= r.endPrefix; i++) {
        long candidate = i * r.prefixMultiplier + i;
        if (candidate >= r.start && candidate <= r.end) {
            sum += candidate;
        }
    }

    return sum;
}

long part1(const int nranges, const RawRange *ranges) {
    long sum = 0;

    for (int i = 0; i < nranges; i++) {
        sum += part1_process_range(ranges + i);
    }

    return sum;
}

int main() {
    FILE *fp = fopen("../inputs/day02.txt", "r");

    int serials = 1;
    {
        // count commas to get amount of serials
        int c;
        while ((c = fgetc(fp)) != EOF) {
            if (c == ',') {
                serials++;
            }
        }
        rewind(fp);
    }

    // read ranges
    RawRange ranges[serials];
    {
        for (int i = 0; i < serials; i++) {
            ranges[i].startLength = 0;
            ranges[i].endLength = 0;

            int c = 0;
            // read start
            while ((c = fgetc(fp)) != EOF) {
                if (c != '-') {
                    ranges[i].start[ranges[i].startLength++] = (char) c;
                } else {
                    break;
                }
            }
            // read end;
            while ((c = fgetc(fp)) != EOF) {
                if (c != ',') {
                    ranges[i].end[ranges[i].endLength++] = (char) c;
                } else {
                    break;
                }
            }
            // null-terminate strings for safety
            ranges[i].start[ranges[i].startLength] = '\0';
            ranges[i].end[ranges[i].endLength] = '\0';
        }

        fclose(fp);
    }

    printf("part 1: %ld\n", part1(serials, ranges));
}
