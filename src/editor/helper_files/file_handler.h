#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <stdio.h>
#include <stdlib.h>
#include "../editor.h"
#include "../../base/types.h"

#define MAX_FILENAME_SIZE 256
#define BACKUP_INTERVAL_MS 60000

u8 load_file(FILE *file);
u8 write_backup(char* filename);
u8 save_file(FILE* file);
u8 save_quit_file(FILE* file);
u8 write_file(FILE* file, bool del);

#endif //FILE_HANDLER_H