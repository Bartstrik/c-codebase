#include <stdio.h>
#include <stdlib.h>
#include "str.h"
#include "math.h"



int str_len(str s) {
    int n = 0;
    while (s[n] != '\0') {
        n++;
    }
    return n;
}

int str_cpy(str from, str to) {
    int i = 0;
    while (from[i] != '\0') {
        to[i] = from[i];
        i++;
    } 
    //also copy the null termitator
    to[i] = '\0';
    return 0;
}

str str_cmp(str s1, str s2) {
    int len = MAX(str_len(s1), str_len(s2));

    str s3 = malloc(len + 1);
    if (s3 == NULL) {
        printf("Could not allocate memory\n");
        return NULL;
    }

    for (int i = 0; i < len; i++) {
        s3[i] = s1[i] ^ s2[i];
    }
    return s3;
}

int str_bin_cmp(str s1, str s2) {
    int len = MAX(str_len(s1), str_len(s2));
    for (int i = 0; i < len; i++) {
        if (s1[i] != s2[i]) {
            return 1;
        }
    }
    return 0;
}

//needs error handling, for when malloc returns NULL
str str_alloc(str s) {
    str new_s;
    int len = str_len(s);
    new_s = malloc((len + 1));

    for (int i = 0; i <= len; i++) {
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

