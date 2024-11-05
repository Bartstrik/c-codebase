#include "../editor.h"
#include "file_handler.h"



u8 load_file(FILE* file) {
    fseek(file, 0, SEEK_END);
    i64 file_size = ftell(file);
    char c;

    for (i64 i = file_size - 1; i >= 0; i--) {
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
u8 write_backup(char* filename) {
      
    char buffer[MAX_FILENAME_SIZE];
    int res = snprintf(buffer, MAX_FILENAME_SIZE, "%s.tmp", filename);
    if (res < 0 || res > MAX_FILENAME_SIZE) {
        printf("Could not create string properly\n");
        return 1;
    }
    
    FILE *tmp_file = fopen(buffer, "w");
    if (tmp_file == NULL) {
        printf("Could not create file\n");
        return 1;
    }

    u8 result = write_file(tmp_file, false);
    if (result != 0) {
        return 1;
    }

    fclose(tmp_file);
    return 0;
}

// needs to be done when user closes the editor
u8 save_quit_file(FILE* file) {
    rewind(file);

    u8 result = write_file(file, true);
    if (result != 0) {
        return 1;
    }

    fclose(file);
    return 0;
}

u8 save_file(FILE* file) {
    rewind(file);

    u8 result = write_file(file, false);
    if (result != 0) {
        return 1;
    }

    return 0;
}

u8 write_file(FILE* file, bool del) {
    rewind(file);
    node* tmp = base;
    node* next;
    while (tmp != NULL) {
        next = tmp->next;
        fwrite(&tmp->c, sizeof(tmp->c), 1, file);

        if (del) free(tmp);
        tmp = next;
    }

    return 0;
}