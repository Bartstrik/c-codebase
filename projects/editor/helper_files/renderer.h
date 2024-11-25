#ifndef RENDERER_H
#define RENDERER_H

#include "../editor.h"
#include "terminal.h"



void die(const char* s);

void refresh_screen();
int draw_screen();
int draw_topbar();
int draw_text();
int draw_tildes();
int draw_cursor();

#endif //RENDERER_H