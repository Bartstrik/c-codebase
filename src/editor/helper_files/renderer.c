#include "renderer.h"


void die(const char* s) {
    reset_terminal();

    perror(s);
    sleep(100);
    exit(1);
}

void configure_terminal() {
    if (tcgetattr(STDIN_FILENO, &editor.old_termios) == -1) die("tcgetattr");
    // atexit(reset_terminal);
    editor.new_termios = editor.old_termios;

    //TODO figure out which flags i need to set
    editor.new_termios.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    editor.new_termios.c_oflag &= ~(OPOST);
    editor.new_termios.c_cflag |= (CS8);
    editor.new_termios.c_lflag &= ~(ICANON | ECHO | IEXTEN | ISIG); //turn off echo and use non-canonical mode | ISIG to disable CTRL + C 
    
    editor.new_termios.c_cc[VMIN] = 0;
    editor.new_termios.c_cc[VTIME] = 10;

    if (tcsetattr(STDIN_FILENO, TCSANOW, &editor.new_termios) == -1) die("tcsetattr");
}

void reset_terminal() {
    printf("\e[m");
    printf("\e[?25h");
    printf("\e[2J");
    printf("\e[H");
    fflush(stdout);
    if (tcsetattr(STDIN_FILENO, TCSANOW, &editor.old_termios) == -1) die("tcsetattr");
}

void signal_handler(int signum) {
    exit_loop = 1;
    printf("signal %i received, exiting\n", signum);
}

void refresh_screen() {
    write(STDOUT_FILENO, "\e[H", 3);
    write(STDOUT_FILENO, "\e[?25l", 6);

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
    int filename_len = str_len(editor.filename);
    if (filename_len > editor.window_cols - 1) return -1;
    
    write(STDOUT_FILENO, "\e[48;5;2m", 9);
    write(STDOUT_FILENO, editor.filename, filename_len);

    for (int i = 0; i < editor.window_cols - filename_len; i++) {
        write(STDOUT_FILENO, " ", 1);
    }
    
    write(STDOUT_FILENO, "\r\n", 2);
    write(STDOUT_FILENO, "\e[m", 3);
    return 0;
}

//-write databuffer(needs to check to make sure not to write more lines than the window has)
//ugly
int draw_text() {
    int i = 0;
    node* tmp = base;
    while(tmp != NULL) {
        if (tmp->c == '\n') {
            write(STDOUT_FILENO, "\e[K", 3);
            write(STDOUT_FILENO, "\r\n", 2);
            i = 0;        
        } else {
            if (i < editor.window_cols) write(STDOUT_FILENO, &tmp->c, sizeof(char));
            i++;
        }
        tmp = tmp->next;
    }

    write(STDOUT_FILENO, "\e[K", 3);
    write(STDOUT_FILENO, "\r\n", 2);
    return 0;
}

int draw_tildes() {
    int tmp_y, tmp_x;
    if (get_cursor_position(&tmp_y, &tmp_x) == -1) die("get_cursor_position");
    //could also use a while loop for this, might be pretier
    for (int y = tmp_y; y < editor.window_rows; y++) {
        write(STDOUT_FILENO, "~", 1);
        write(STDOUT_FILENO, "\e[K", 3);

        if (y < editor.window_rows) {
            write(STDOUT_FILENO, "\r\n", 2);
        }
        
    }
    return 0;
}

int draw_cursor() {
    char buf[11];
    //using snprintf's return value as str_len
    int n = snprintf(buf, sizeof(buf), "\e[%d;%dH", editor.cursor_y, editor.cursor_x);
    write(STDOUT_FILENO, "\e[?25h", 6);
    write(STDOUT_FILENO, buf, n);
    return 0;
}


int get_window_size(int* rows, int* cols) {
    struct winsize ws;

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
        if (write(STDOUT_FILENO, "\e[999C\e[999B", 12) != 12)   return -1;
        return get_cursor_position(rows, cols);
    } else {
        *cols = ws.ws_col;
        *rows = ws.ws_row;
        return 0;
    }
}

int get_cursor_position(int* rows, int* cols) {
    while(1) {
        char buf[32];    
        write(STDOUT_FILENO, "\e[6n", 4);

        if (read_key(buf) == -1) die("read_key");

        if (buf[0] != '\e' || buf[1] != '[') continue;
        if (sscanf(&buf[2], "%d;%d", rows, cols) != 2) continue;
        return 0;
    }
}

void init_editor() {
    write(STDOUT_FILENO, "\e[2J", 4);
    editor.cursor_x = 1;
    editor.cursor_y = 2;
    if (get_window_size(&editor.window_rows, &editor.window_cols) == -1) die("get_window_size");
}

void move_cursor(char key) {
    switch(key) {
        case 'A':
            if (editor.cursor_y > 2) {
                editor.cursor_y--;
                write(STDOUT_FILENO, "\e[A", 3);
            }  
            break;

        case 'B':
            if(editor.cursor_y < editor.window_rows) {
                editor.cursor_y++;
                write(STDOUT_FILENO, "\e[B", 3);
            }
            break;

        case 'C':
            if (editor.cursor_x < editor.window_cols) {
                editor.cursor_x++;
                write(STDOUT_FILENO, "\e[C", 3);
            }
            break;

        case 'D':
            if (editor.cursor_x > 1) {
                editor.cursor_x--;
                write(STDOUT_FILENO, "\e[D", 3);
            }
            break;
        
    }
}