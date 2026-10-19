#include "string.h"

_Bool strEq(const char *str1, const char *str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }

    return *str1 == *str2;  // checks if they bth ended in '\0'
}

int strLen(const char *str) {
    int result = 0;
    while (*str != '\0') {
        result++;
        str++;
    }
    return result;
}