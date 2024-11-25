#ifndef EDITOR_H
#define EDITOR_H

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <errno.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/ioctl.h>
#include <signal.h>

typedef struct node {
    char c;
    struct node* next;
} node;

typedef struct editor_config {
    struct termios old_termios, new_termios;
    int window_rows;
    int window_cols;
    int window_x;
    int window_y;
    int cursor_x;
    int cursor_y;
    char* filename;

} editor_config;

extern int exit_loop;
extern node* base;
extern editor_config editor;

#endif //EDITOR_H