#ifndef DIR_H
#define DIR_H

#include "fat.h"
#include "drive.h"

#define MAX_FILENAME_SIZE 12

struct dir_ent
{
    char filename[MAX_FILENAME_SIZE];
    short file_addr;
};

struct dir
{
    struct dir_ent file_entries[(CYLINDER_SIZE - FAT_SIZE) / sizeof(struct dir_ent)];
};

#endif
