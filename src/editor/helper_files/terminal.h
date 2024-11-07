#ifndef TERMINAL_H
#define TERMINAL_H

#include "../editor.h"
#include "../../base/types.h"
#include "file_handler.h"
#include "renderer.h"

#define CTRL_KEY(k) ((k) & 0x1f) 




int read_key();
int read_input();


#endif //TERMINAL_H