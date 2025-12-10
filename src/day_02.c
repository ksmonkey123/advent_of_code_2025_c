#include <stdio.h>

typedef struct {
    long start;
    long end;
} NumberRange;

long parseNumber(const char *buffer, const int length) {
    long sum = 0;

    for (int i = 0; i < length; i++) {
        sum *= 10;
        sum += buffer[i] - '0';
    }

    return sum;
}

int numberLength(long number) {
    int x = 0;
    while (number > 0) {
        x++;
        number /= 10;
    }
    return x;
}

void numberToString(long number, char *buffer) {
    const int l = numberLength(number);
    buffer[l] = '\0';

    for (int i = 0; i < l; i++) {
        buffer[l - 1 - i] = (char) ((number % 10) + '0');
        number /= 10;
    }
}

int isRepeating(long number, int times) {
    const int l = numberLength(number);
    if (l % times != 0) {
        // cannot be repeating if length is not a multiple of 'times'
        return 0;
    }

    char buffer[64];
    numberToString(number, buffer);
    for (int i = 1; i < times; i++) {
        for (int j = 0; j < l / times; j++) {
            if (buffer[j] != buffer[j + i * (l / times)]) {
                return 0;
            }
        }
    }
    return 1;
}

long repeated(long prefix, long multiplier, int repeats) {
    long sum = 0;
    for (int i = 0; i < repeats; i++) {
        sum *= multiplier;
        sum += prefix;
    }
    return sum;
}

long part1(const int nranges, const NumberRange *ranges) {
    long sum = 0;

    for (int i = 0; i < nranges; i++) {
        for (long j = ranges[i].start; j <= ranges[i].end; j++) {
            if (isRepeating(j, 2) != 0) {
                sum += j;
            }
        }
    }

    return sum;
}

long part2(const int nranges, const NumberRange *ranges) {
    long sum = 0;

    for (int i = 0; i < nranges; i++) {
        for (long j = ranges[i].start; j <= ranges[i].end; j++) {
            int l = numberLength(j);
            for (int t = 2; t <= l; t++) {
                if (isRepeating(j, t) != 0) {
                    sum += j;
                    break;
                }
            }
        }
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
    NumberRange ranges[serials];
    {
        for (int i = 0; i < serials; i++) {
            int startLength = 0;
            int endLength = 0;
            char start[20];
            char end[20];

            int c = 0;
            // read start
            while ((c = fgetc(fp)) != EOF) {
                if (c != '-') {
                    start[startLength++] = (char) c;
                } else {
                    break;
                }
            }
            // read end;
            while ((c = fgetc(fp)) != EOF) {
                if (c != ',') {
                    end[endLength++] = (char) c;
                } else {
                    break;
                }
            }
            // null-terminate strings for safety
            start[startLength] = '\0';
            end[endLength] = '\0';

            ranges[i].start = parseNumber(start, startLength);
            ranges[i].end = parseNumber(end, endLength);
        }

        fclose(fp);
    }

    printf("part 1: %ld\n", part1(serials, ranges));
    printf("part 2: %ld\n", part2(serials, ranges));
}
