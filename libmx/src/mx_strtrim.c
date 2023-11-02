#include "../inc/libmx.h"

char *mx_strtrim(const char *str) {
	if (str == NULL) {
        return NULL;
    }

    const char *start = str;
    while (*start != '\0' && mx_isspace(*start)) {
        start++;
    }

    const char *end = str;
    const char *lastNonSpace = NULL;
    while (*end != '\0') {
        if (!mx_isspace(*end)) {
            lastNonSpace = end;
        }
        end++;
    }

    size_t trimmedLength = 0;
    if (lastNonSpace != NULL) {
        trimmedLength = lastNonSpace - start + 1;
    }

    char *trimmedStr = mx_strnew(trimmedLength);
    if (trimmedStr == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < trimmedLength; i++) {
        trimmedStr[i] = start[i];
    }

    return trimmedStr;
}
