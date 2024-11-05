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

#include "../base/str.h"
#include "../base/types.h"
#include "helper_files/terminal.h"
#include "helper_files/file_handler.h"
#include "helper_files/renderer.h"

typedef struct node {
    char c;
    struct node* next;
} node;

typedef struct editor_config {
    struct termios old_termios, new_termios;
    int window_rows;
    int window_cols;
    int cursor_x;
    int cursor_y;
    char* filename;

} editor_config;

extern node* base;
extern editor_config editor;

#endif //EDITOR_H