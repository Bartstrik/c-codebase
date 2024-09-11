#include <stdio.h>
#include "base/base.h"
#include "base/uinput.h"

int main(void) {
    //test of the get functions
    char c;
    double d;
    float f;
    int i;
    long l;
    char *s;
    c = get_char("enter char : \n");
    printf("char = %c\n", c);
    d = get_double("enter double : \n");
    printf("double = %lf\n", d);
    f = get_float("enter float : \n");
    printf("float = %f\n", f);
    i = get_int("enter int : \n");
    printf("int = %i\n", i);
    l = get_long("enter long : \n");
    printf("long = %li\n", l);
    s = get_string("enter string : \n", 5);
    printf("string = %s\n", s);


    printf("OS = "STRINGIFY(OS)"\n");
    printf("Compiler = "STRINGIFY(COMPILER)"\n");
}