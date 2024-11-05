#ifndef RENDERER_H
#define RENDERER_H

#include "../editor.h"



void die(const char* s);
void configure_terminal();
void reset_terminal();  
void signal_handler(__attribute__((unused)) int signum);
void refresh_screen();
int draw_rows();
int draw_topbar();
int draw_text();
int draw_tildes();
int draw_cursor();
int get_window_size(int *rows, int *cols);
int get_cursor_position(int *rows, int *cols);
void init_editor();
void move_cursor(char key);

#endif //RENDERER_H