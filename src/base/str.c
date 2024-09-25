#include <stdio.h>
#include <stdlib.h>
#include "str.h"



int str_len(str s) {
    int n = 0;
    while (s[n] != '\0') {
        n++;
    }
    return n;
}

str str_alloc(str s) {
    str new_s;
    int len = str_len(s);
    new_s = malloc(len);

    for (int i = 0; i < len; i++) {
        new_s[i] = s[i];
    }
    return new_s;
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

