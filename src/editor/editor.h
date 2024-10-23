#ifndef EDITOR_H
#define EDITOR_H

#include "../base/types.h"
#include <stdlib.h>


#define MAX_FILENAME_SIZE 256
#define BACKUP_INTERVAL_MS 60000

typedef struct node {
    char c;
    struct node* next;
} node;

u8 load_file(FILE *file);
u8 write_backup(char* filename);
u8 save_file(FILE* file);
u8 save_quit_file(FILE* file);
u8 write_file(FILE* file, bool del);

#endif //EDITOR_H