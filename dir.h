#ifndef DIR_H
#define DIR_H

#include "fat.h"
#include "drive.h"

#define MAX_FILENAME_SIZE 12
#define MAX_FILES (CYLINDER_SIZE - FAT_SIZE) / sizeof(struct dir_ent)
struct dir_ent
{
    char filename[MAX_FILENAME_SIZE];
    unsigned short file_addr;
};

struct dir
{
    struct dir_ent file_entries[MAX_FILES];
};

int get_dir_ent(struct dir *, char *, struct dir_ent *);

int set_dir_ent(struct dir *, char *, unsigned short addr);

#endif
