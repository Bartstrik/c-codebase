#include <stdio.h>
#include "str.h"

int str_len(str s) {
    int n = 0;
    while (s[n] != '\0') {
        n++;
    }
    return n;
}

str str_toupper(str s, int len) {
    for (int i = 0; i < len; i++) {
        if (s[i] >= 'a' && s[i] <= 'z') {
            s[i] -= 32;
        }
    }
    return s;
}

str str_tolower(str s, int len) {
    for (int i = 0; i < len; i++) {
        if (s[i] >= 'A' && s[i] <= 'Z') {
            s[i] += 32;
        }
    }
    return s;
}

