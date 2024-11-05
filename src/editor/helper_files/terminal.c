#include "terminal.h"

int read_key(char* key) {
    int nread;
    char buf[256];
    int index;

    nread = read(STDIN_FILENO, buf, sizeof(buf));
    if(nread == 0) return 0;
    if (nread == -1) return -1;

    for (int i = 0; i < nread; i++) {
        if (buf[i] == '\e') {
            index = 0;
        }
        key[index] = buf[i];
        index++;
    }
    key[index] = '\0';

    return 0;
}

int read_input() {
    //key needs to be nulled to prevent garbage values from interfering, on second thougth a single '\0' is enough
    char key[32];
    key[0] = '\0';
    if(read_key(key) == -1) die("read_key");

    int len = str_len(key);
    if (len == 0) return 0;
    if (len == 1) {
        if (iscntrl(key[0])) {
            switch (key[0]) {
                case CTRL_KEY('q'):
                    write(STDOUT_FILENO, "\e[2J", 4);
                    write(STDOUT_FILENO, "\e[H", 3);
                    reset_terminal();

                    exit(0);
                    break;
            }
        } else {
            //add char to data linked list

            //if (get_cursor_position(editor.cursor_y, editor.cursor_x) == -1) die("get_cursor_position");
            //if (update_dataset(key[0], editor.cursor_y, editor.cursor_x) == -1) die("update_dataset");
        }
        
    //handling ANSI escape sequences
    } else if (key[0] == '\e' && key[1] == '[') {
        switch (key[2]) {
            case 'A':
            case 'B':
            case 'C':
            case 'D':
                move_cursor(key[2]);
                break;
        }
    } else {
        return -1;
    }
    
    return 0;
}
