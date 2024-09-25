#include "uinput.h"
#include "base.h"
#include <stdio.h>
#include <stdlib.h>
#include "str.h"


//todo 
//make a template for this

char get_char(const str prompt) {
    int result = 0;
    char answer;
    while(result != 1) {
        printf("%s", prompt);
        result = scanf("%c", &answer);
        while (getchar() != '\n');
    }
    return answer;
}

double get_double(const str prompt) {
    int result = 0;
    double answer;
    while(result != 1) {
        printf("%s", prompt);
        result = scanf("%lf", &answer);
        while (getchar() != '\n');
    }
    return answer;
}

float get_float(const str prompt) {
    int result = 0;
    float answer;
    while(result != 1) {
        printf("%s", prompt);
        result = scanf("%f", &answer);
        while (getchar() != '\n');
    }
    return answer;
}

int get_int(const str prompt) {
    int result = 0;
    int answer;
    while(result != 1) {
        printf("%s", prompt);
        result = scanf("%i", &answer);
        while (getchar() != '\n');
    }
    return answer;
}

long get_long(const str prompt) {
    int result = 0;
    long answer;
    while(result != 1) {
        printf("%s", prompt);
        result = scanf("%ld", &answer);
        while (getchar() != '\n');
    }
    return answer;
}

//limited to strs with a max length of 999 characters
str get_str(const str prompt, int length) {
    int result = 0;
    char format[9];
    str answer = malloc(length);
    while(result != 1) {
        printf("%s", prompt);

        snprintf(format, sizeof(format), "%%%d[^\n]", length);

        result = scanf(format, answer);
        while (getchar() != '\n');

    }
    return answer;
}