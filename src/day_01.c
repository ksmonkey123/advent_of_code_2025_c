#include <stdio.h>
#include <stdlib.h>

int part1(const int lines, const int *data) {
    int state = 50;
    int counter = 0;

    for (int i = 0; i < lines; i++) {
        state = (state + data[i]) % 100;
        if (state == 0) {
            counter++;
        }
    }

    return counter;
}

int part2(const int lines, const int *data) {
    int state = 50;
    int counter = 0;

    for (int i = 0; i < lines; i++) {
        int step = data[i];
        if (step > 0) {
            for (int j = 0; j < step; j++) {
                state++;
                if (state == 100) {
                    state = 0;
                    counter++;
                }
            }
        } else {
            // treat 0 as 100
            if (state == 0) {
                state = 100;
            }
            for (int j = 0; j < -step; j++) {
                state--;
                if (state == 0) {
                    state = 100;
                    counter++;
                }
            }
            // treat 100 as 0
            if (state == 100) {
                state = 0;
            }
        }
    }

    return counter;
}

int lineToUInt(const char *line) {
    int value = 0;

    int i = 0;
    while (line[i] >= '0' && line[i] <= '9') {
        value = 10 * value + (line[i] - '0');
        i++;
    }

    return value;
}

int readFile(int **target) {
    FILE *fp = fopen("../inputs/day01.txt", "r");

    int lines = 0;
    int c;
    while ((c = fgetc(fp)) != EOF) {
        if (c == '\n') {
            lines++;
        }
    }
    rewind(fp);

    *target = malloc(lines * sizeof(int));

    int i = 0;
    char buffer[64];
    while (fgets(buffer, 64, fp) != NULL) {
        int value = lineToUInt(buffer + 1);
        if (buffer[0] == 'L') {
            value = -value;
        }
        (*target)[i++] = value;
    }
    fclose(fp);
    return lines;
}

int main() {
    int *data;
    const int lines = readFile(&data);

    printf("part 1: %d\n", part1(lines, data));
    printf("part 2: %d\n", part2(lines, data));

    free(data);
}
