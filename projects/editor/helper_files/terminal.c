#include "terminal.h"
#include <string.h>

int read_key(char* key) {
    int nread;
    char buf[256];
    int index = 0;

    nread = read(STDIN_FILENO, buf, sizeof(buf));
    if(nread == 0) return 0;
    if (nread == -1) return -1;

    for (int i = 0; i < nread; i++) {
        if (buf[i] == '\e') index = 0;
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
    
    int len = strlen(key);
    if (len == 0) return 0;
    if (len == 1) {
        //maybe create a new function for handling single char inputs
        if (iscntrl(key[0])) {
            switch (key[0]) {
                case CTRL_KEY('q'):
                case CTRL_KEY('w'):
                case CTRL_KEY('c'):
                    write(STDOUT_FILENO, "\e[2J", 4);
                    write(STDOUT_FILENO, "\e[H", 3);
                    exit_loop = 1;
                    break;
                //case for backspace and enters
            }
        } else {
            if (update_dataset(key[0], editor.cursor_y, editor.cursor_x) == -1) die("update_dataset");
            move_cursor('C');
            // editor.cursor_x++;
        }
        
        return 0;
    }
    //handling ANSI escape sequences
    if (key[0] == '\e' && key[1] == '[') {
        switch (key[2]) {
            case 'A':
            case 'B':
            case 'C':
            case 'D':
                move_cursor(key[2]);
                break;
        }
        return 0;
    }
    return -1;
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
    editor.window_x = 0;
    editor.window_y = 0;
}

void move_cursor(char key) {
    switch(key) {
        case 'A':
            if (editor.cursor_y > 2) {
                editor.cursor_y--;
                write(STDOUT_FILENO, "\e[A", 3);
            } else if (editor.window_y > 0){
                editor.window_y--;
            }

            break;

        case 'B':
            if(editor.cursor_y < editor.window_rows) {
                editor.cursor_y++;
                write(STDOUT_FILENO, "\e[B", 3);
            } else {
                editor.window_y++;
            }

            break;

        case 'C':
            if (editor.cursor_x < editor.window_cols) {
                editor.cursor_x++;
                write(STDOUT_FILENO, "\e[C", 3);
            } else {
                editor.window_x++;
            }

            break;

        case 'D':
            if (editor.cursor_x > 1) {
                editor.cursor_x--;
                write(STDOUT_FILENO, "\e[D", 3);
            } else if (editor.window_x > 0){
                editor.window_x--;
            }

            break;
    }
}