//TODO
//- create an append buffer to not have to do single write function calls
//- make it so that when the program is closed, the previous terminal history is still there


#include "editor.h"

node* base = NULL;
editor_config editor;

int main(int argc, str* argv) {
    if (argc != 2) {
        printf("Usage: ./editor [file]\n");
        return 1;
    }


    editor.filename = argv[1];
    FILE *input = fopen(editor.filename, "r");
    if (input == NULL) {
        printf("Could not open file\n"); 
        return 1;
    }

    u8 result = load_file(input);

    //open files 
    //load files into memory
    //configure terminal
    //configure renderer
    configure_terminal();
    init_editor();
    signal(SIGINT, signal_handler);

    //while exit_loop
    //read user input
    //process user input
    while(1) {
        refresh_screen();
        read_input();
    }
    
    

    //load file into linked list of char's
    //reading file backwards because it creates the linked list in order. 
    //could choose not to do this and keep the linked list in reversed order,
    //but i chose not to do this for simplicity's sake
    result = load_file(input);
   
    result = write_backup(editor.filename);
    if (result != 0) {
        printf("error writing backup");
        return 1;
    }

    result = save_quit_file(input);
    if (result != 0) {
        printf("error writing backup");
        return 1;
    }
    return 0;
}
