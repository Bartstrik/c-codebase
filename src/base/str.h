#ifndef str_H
#define str_H

typedef char* str;

int str_len(str s);
str str_toupper(str s, int len);
str str_tolower(str s, int len);
#endif // str_H