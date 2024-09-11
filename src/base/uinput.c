#include "uinput.h"
#include "base.h"
#include <stdio.h>
#include <stdlib.h>

//todo 
//make a template for this

char get_char(const char *prompt) {
    int result = 0;
    char answer;
    while(result != 1) {
        printf("%s", prompt);
        result = scanf("%c", &answer);
        while (getchar() != '\n');
    }
    return answer;
}

double get_double(const char *prompt) {
    int result = 0;
    double answer;
    while(result != 1) {
        printf("%s", prompt);
        result = scanf("%lf", &answer);
        while (getchar() != '\n');
    }
    return answer;
}

float get_float(const char *prompt) {
    int result = 0;
    float answer;
    while(result != 1) {
        printf("%s", prompt);
        result = scanf("%f", &answer);
        while (getchar() != '\n');
    }
    return answer;
}

int get_int(const char *prompt) {
    int result = 0;
    int answer;
    while(result != 1) {
        printf("%s", prompt);
        result = scanf("%i", &answer);
        while (getchar() != '\n');
    }
    return answer;
}

long get_long(const char *prompt) {
    int result = 0;
    long answer;
    while(result != 1) {
        printf("%s", prompt);
        result = scanf("%ld", &answer);
        while (getchar() != '\n');
    }
    return answer;
}

//limited to strings with a max length of 99 characters
char* get_string(const char *prompt, int length) {
    int result = 0;
    char format[8];
    char *answer = malloc(length);
    while(result != 1) {
        printf("%s", prompt);

        snprintf(format, sizeof(format), "%%%d[^\n]", length);

        result = scanf(format, answer);

        if (result != 1) {
            for(int i = 0; i < length; i ++) {
                answer[i] = 0;
            }
            while (getchar() != '\n');
        }
    }
    return answer;
}