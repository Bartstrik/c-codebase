#ifndef str_H
#define str_H


typedef char* str;

int str_len(str s);
str str_cmp(str s1, str s2);
int str_bin_cmp(str s1, str s2);
str str_alloc(str s);
str str_alloc_len(int len);
str str_toupper(str s, int len);
str str_tolower(str s, int len);
#endif // str_H