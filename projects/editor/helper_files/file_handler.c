#include "file_handler.h"

//right now the file is loaded into a linked list of chars. 
//I could change this to a linked list of char array, where each array is a single line.
//this would have some advantages for making the coding easier, however, performance wize i think this would be worse.
//it would mean:
//each edit would be creating a new node, copying the array with one char added/removed and swapping the nodes
//otherwise editing would mean:
//looping through the linked list until the right node is reached(which is way more steps) and adding/removing a node

static FILE *input;

int load_file(FILE* file) {
    fseek(file, 0, SEEK_END);
    i64 file_size = ftell(file);
    char c;

    for (i64 i = file_size; i >= 0; i--) {
        fseek(file, i, SEEK_SET);

        fread(&c, sizeof(c), 1, file);
        node* tmp = malloc(sizeof(node));
        tmp->c = c;
        if (!(base == NULL)) {
            tmp->next = base;
        }
        base = tmp;
    }
    return 0;
}


 //needs to be done once every set amount of time, for example every 1 minute
int write_backup(char* filename) {
      
    char buffer[MAX_FILENAME_SIZE];
    int res = snprintf(buffer, MAX_FILENAME_SIZE, "%s.tmp", filename);
    if (res < 0 || res > MAX_FILENAME_SIZE) {
        printf("Could not create string properly\n");
        return -1;
    }
    
    FILE *tmp_file = fopen(buffer, "w");
    if (tmp_file == NULL) {
        printf("Could not create file\n");
        return -1;
    }

    u8 result = write_file(tmp_file, false);
    if (result != 0) {
        return -1;
    }

    fclose(tmp_file);
    return 0;
}

int save_quit_file(FILE* file) {
    rewind(file);

    u8 result = write_file(file, true);
    if (result != 0) {
        return -1;
    }

    fclose(file);
    return 0;
}

int save_file(FILE* file) {
    rewind(file);

    u8 result = write_file(file, false);
    if (result != 0) {
        return -1;
    }

    return 0;
}

int write_file(FILE* file, bool del) {
    rewind(file);
    node* tmp = base;
    node* next;
    while (tmp->c != '\0' ) {
        next = tmp->next;
        fwrite(&tmp->c, sizeof(tmp->c), 1, file);

        if (del) free(tmp);
        tmp = next;
    }

    return 0;
}
//ugly
int save_quit() {
    fclose(input);
    FILE *output = fopen(editor.filename, "wb");
    save_quit_file(output);
    return 0;
}

int init_files(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: ./editor [file]\n");
        return -1;
    }


    editor.filename = argv[1];
    input = fopen(editor.filename, "r");
    if (input == NULL) {
        printf("Could not open file\n"); 
        return -1;
    }

    if (load_file(input) == -1) die("load_file");
    return 0;
}

//need to take into account the values of editor.window_y and x
int update_dataset(char c, int row, int col) {
    int i = 0;
    node* tmp = base;
    node* prev = NULL;

    row = row + editor.window_y - 2;
    col = col + editor.window_x - 1;

    while(true) {
        if (row == 0 && col == i) {
            input_node(c, &prev);
            return 0;
        }
        if ((tmp->c == '\0' && row == 0) || (tmp->c == '\n' && row == 0)) {
            input_node(' ', &prev);
            i++;
            continue;
        }
        if (tmp->c == '\0') {
            input_node('\n', &prev);
            i = 0;
            row--;
            continue;
        }
        if (tmp->c == '\n') {
            i = -1;
            row--;
        }

        i++;
        prev = tmp;
        tmp = tmp->next;
    }

    return 0;
}

int input_node(char c, node** prev) {
    node* new = malloc(sizeof(node));
    if(new == NULL) {
        printf("Could not allocate memory\n");
        die("malloc");
        return -1;
    }

    new->c = c;
    if (*prev != NULL) {
        new->next = (*prev)->next;
        (*prev)->next = new;
    } else {
        new->next = base;
        base = new;
    }
    *prev = new;
    return 0;
}