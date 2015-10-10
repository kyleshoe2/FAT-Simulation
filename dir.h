#ifndef DIR_H
#define DIR_H

#include "fat.h"
#include "drive.h"

struct root_dir_ent
{
    char filename[16];
    short file_addr;
};

struct root_dir
{
    root_dir_ent[(CYLINDER_SIZE - FAT_SIZE) / sizeof(root_dir_ent)] file_entries;
};

#endif
