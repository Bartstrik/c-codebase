#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "../editor.h"
#include "../../base/types.h"
#include "renderer.h"

#define MAX_FILENAME_SIZE 256
#define BACKUP_INTERVAL_MS 60000

int load_file(FILE *file);

int write_backup(char* filename);

int save_file(FILE* file);

int save_quit_file(FILE* file);

int write_file(FILE* file, bool del);

int save_quit();

int init_files(int argc, char **argv);

int update_dataset(char c, int row, int col);

int input_node(char c, node** prev);


#endif //FILE_HANDLER_H