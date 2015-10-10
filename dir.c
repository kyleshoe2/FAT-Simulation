#include "dir.h"

#include <stdlib.h>
#include <string.h>

int get_dir_ent(struct dir *root_dir, char *filename, struct dir_ent *dest)
{
    for(int i = 0; i < MAX_FILES; ++i) {
        struct dir_ent cur = root_dir->file_entries[i];
        if(!strncmp(filename, cur.filename, MAX_FILENAME_SIZE)) {
            *dest = cur;
            return 0;
        }
    }
    return 1;
}
