#ifndef UINPUT_H
#define UINPUT_H

#include "str.h"

char get_char(const str prompt);

double get_double(const str prompt);

float get_float(const str prompt);

int get_int(const str prompt);

long get_long(const str prompt);

str get_str(const str prompt, int length);

#endif //INPUT_H