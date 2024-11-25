#include "uinput.h"
#include "base.h"
#include <stdio.h>
#include <stdlib.h>




char get_char(const char* prompt) {
    int result = 0;
    char answer;
    while(result != 1) {
        printf("%s", prompt);
        result = scanf("%c", &answer);
        while (getchar() != '\n');
    }
    return answer;
}

double get_double(const char* prompt) {
    int result = 0;
    double answer;
    while(result != 1) {
        printf("%s", prompt);
        result = scanf("%lf", &answer);
        while (getchar() != '\n');
    }
    return answer;
}

float get_float(const char* prompt) {
    int result = 0;
    float answer;
    while(result != 1) {
        printf("%s", prompt);
        result = scanf("%f", &answer);
        while (getchar() != '\n');
    }
    return answer;
}

int get_int(const char* prompt) {
    int result = 0;
    int answer;
    while(result != 1) {
        printf("%s", prompt);
        result = scanf("%i", &answer);
        while (getchar() != '\n');
    }
    return answer;
}

long get_long(const char* prompt) {
    int result = 0;
    long answer;
    while(result != 1) {
        printf("%s", prompt);
        result = scanf("%ld", &answer);
        while (getchar() != '\n');
    }
    return answer;
}

//limited to stringss with a max length of 999 characters
//issue where prompt can not use %i the same way printf can to pass variables
//also needs to change so length isn't used 
char* get_str(const char* prompt, int length) {
    int result = 0;
    char format[9];
    char* answer = malloc(length);
    while(result != 1) {
        printf("%s", prompt);

        snprintf(format, sizeof(format), "%%%d[^\n]", length);

        result = scanf(format, answer);
        while (getchar() != '\n');

    }
    return answer;
}