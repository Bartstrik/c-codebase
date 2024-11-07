//TODO
//- create an append buffer to not have to do single write function calls
//- make it so that when the program is closed, the previous terminal history is still there


#include "editor.h"
#include "../base/str.h"
#include "../base/types.h"
#include "helper_files/terminal.h"
#include "helper_files/file_handler.h"
#include "helper_files/renderer.h"

int exit_loop = 0;
node* base = NULL;
editor_config editor;

int main(int argc, char** argv) {

    init_files(argc, argv);
    configure_terminal();
    init_editor();
    signal(SIGINT, signal_handler);

    while(!exit_loop) {
        refresh_screen();
        read_input();
    }

    reset_terminal();
    
    if (write_backup(editor.filename) == -1) die("write_backup");

    if (save_quit() == -1) die("save_quit");

    return 0;
}
