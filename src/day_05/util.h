#ifndef AOC_UTIL_H
#define AOC_UTIL_H

int positionOfLimited(const char *string, char search, char terminator);
int positionOf(const char *string, char search);

/**
 * parse the chars in the range of a string as a number
 * @param start inclusive
 * @param end exclusive
 */
long parseNumber(const char *string, int start, int end);

#endif //AOC_UTIL_H
