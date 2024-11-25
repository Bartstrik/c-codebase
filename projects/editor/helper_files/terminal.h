#ifndef TERMINAL_H
#define TERMINAL_H

#include "../editor.h"
#include "../../../src/base/types.h"
#include "file_handler.h"
#include "renderer.h"

#define CTRL_KEY(k) ((k) & 0x1f) 




int read_key();
int read_input();
void configure_terminal();
void reset_terminal();  
void signal_handler(int signum);
int get_window_size(int *rows, int *cols);
int get_cursor_position(int *rows, int *cols);
void init_editor();
void move_cursor(char key);


#endif //TERMINAL_H