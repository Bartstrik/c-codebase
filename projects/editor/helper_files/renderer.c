#include "renderer.h"
#include <string.h>

void die(const char* s) {
    reset_terminal();

    perror(s);
    sleep(100);
    exit(1);
}

void refresh_screen() {
    write(STDOUT_FILENO, "\e[H", 3);
    write(STDOUT_FILENO, "\e[?25l", 6);

    if (get_window_size(&editor.window_rows, &editor.window_cols) == -1) die("get_window_size");
    if (editor.cursor_x > editor.window_cols) editor.cursor_x = editor.window_cols;
    if (editor.cursor_y > editor.window_rows) editor.cursor_y = editor.window_rows;

    if (draw_screen() == -1) die("draw_screen");
}

int draw_screen() {
    if (draw_topbar() == -1) die("draw_topbar");
    if (draw_text() == -1) die("draw_text");
    if (draw_tildes() == -1) die("draw_tildes");
    if (draw_cursor() == -1) die("draw_cursor");    
    return 0;
}

int draw_topbar() {
    int filename_len = strlen(editor.filename);
    write(STDOUT_FILENO, "\e[48;5;2m", 9);

    for (int i = 0; i < editor.window_cols; i++) {
        if (i < filename_len) {
            write(STDOUT_FILENO, &editor.filename[i], 1);
        } else {
            write(STDOUT_FILENO, " ", 1);
        }
    }

    write(STDOUT_FILENO, "\r\n", 2);
    write(STDOUT_FILENO, "\e[m", 3);

    return 0;
}

int draw_text() {
    int row = 2;
    int col = 1;
    //flag used for cases where no text is writen, so that no newline is printed at the end of this function
    bool text_written = false;

    if (base == NULL) return -1;
    node* tmp = base;

    for (int i = 0; i < editor.window_y; i++) {
        char prev = '\0';
        while (prev != '\n' && tmp != NULL) {
            prev = tmp->c;
            tmp = tmp->next;
        }
    }

    if (tmp != NULL) text_written = true;

    while(tmp != NULL) {
        if (col == 1) {
            for (int i = 0; i < editor.window_x && tmp != NULL; i++) {
                if (tmp->c != '\n') {
                    tmp = tmp->next;
                }
            }
            if (tmp == NULL) break;
        }

        if (tmp->c == '\n') {
            if (row >= editor.window_rows) {
                write(STDOUT_FILENO, "\e[K", 3);
                return 0;
            }
            write(STDOUT_FILENO, "\e[K", 3);
            write(STDOUT_FILENO, "\r\n", 2);
            
            row++;
            col = 1;        
        } else {
            if (col <= editor.window_cols) write(STDOUT_FILENO, &tmp->c, sizeof(char));
            col++;
        }
        tmp = tmp->next;
    }

    write(STDOUT_FILENO, "\e[K", 3);
    // write(STDOUT_FILENO, "\r\n", 2);
    if (row < editor.window_rows && text_written == true) write(STDOUT_FILENO, "\r\n", 2);
    return 0;
}

int draw_tildes() {
    int tmp_y, tmp_x;
    if (get_cursor_position(&tmp_y, &tmp_x) == -1) die("get_cursor_position");
    //could also use a while loop for this, might be pretier
    if (tmp_x != 1) return 0;
    for (int y = tmp_y; y <= editor.window_rows; y++) {
        write(STDOUT_FILENO, "~", 1);
        write(STDOUT_FILENO, "\e[K", 3);
        //pretty sure i can remove this if statement
        if (y < editor.window_rows) {
            write(STDOUT_FILENO, "\r\n", 2);
        }
        
    }
    return 0;
}

int draw_cursor() {
    char buf[11];
    //using snprintf's return value as strlen
    int n = snprintf(buf, sizeof(buf), "\e[%d;%dH", editor.cursor_y, editor.cursor_x);
    write(STDOUT_FILENO, "\e[?25h", 6);
    write(STDOUT_FILENO, buf, n);
    return 0;
}

