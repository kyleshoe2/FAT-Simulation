
/* Project 2 rules:
 *		ALL data must be stored on the simulated hard drive!
 *			- No global variables
 *			- No static variables
 *			- No other contrived method to preserve data between function calls
 */

/*
 * This is the only file you need to modify.  You might want to add printing or 
 * changes stuff in tester.c, but the program should work at the end with the 
 * initial versions of all files except this one.  Function stubs are included
 * so that the project will compile as-received.
 */

#include "fs.h"
#include "drive.h"
#include "fat.h"
#include "dir.h"
#include "mem_utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int store_fs(struct fs *the_fs)
{
    size_t size = sizeof(struct fs);
    char *data = malloc(sizeof(char) * size);
    memcpy(data, the_fs, size);
    
    size_t offset = 0;
    int cur_sect = 0;
    for(int i = 0; i < size / BYTES_PER_SECTOR; ++i) {
        write_sector(0, cur_sect, data + offset);
        cur_sect++;
        offset += BYTES_PER_SECTOR;
    }
    char leftover[BYTES_PER_SECTOR];
    memcpy(leftover, data + offset, size - offset);
    write_sector(1, cur_sect, leftover);
    free(data);
    return 0;
}


int load_fs(struct fs *the_fs)
{
    size_t size = sizeof(struct fs);
    char *data = malloc(sizeof(char) * size);
    
    size_t offset = 0;
    int cur_sect = 0;
    for(int i = 0; i < size / BYTES_PER_SECTOR; ++i) {
        read_sector(0, cur_sect, data + offset);
        cur_sect++;
        offset += BYTES_PER_SECTOR;
    }
    char leftover[BYTES_PER_SECTOR];
    read_sector(0, cur_sect, leftover);
    memcpy(data, leftover, size - offset);
    memcpy(the_fs, data, size);
    free(data);
    return 0;
}

int fdelete(char* fn){
    struct fs *the_fs = malloc(sizeof(struct fs));
    int ret = 5;
    load_fs(the_fs);
    struct dir_ent file_ent;
    if(get_dir_ent(&the_fs->root_dir, fn, &file_ent)) {
        ret = NOT_FOUND;
    };
    
    store_fs(the_fs);
    free(the_fs);
	return ret;
}


int load(char* fn, void* data, size_t ds){
    struct fs *the_fs = malloc(sizeof(struct fs));
    int ret = 5;
    load_fs(the_fs);
    struct dir_ent file_ent;
    if(get_dir_ent(&the_fs->root_dir, fn, &file_ent)) {
        ret = NOT_FOUND;
    };

    store_fs(the_fs);
    free(the_fs);
    return ret;
}


int save(char* fn, void* data, size_t ds){
    struct fs *the_fs = malloc(sizeof(struct fs));
    int ret = 5;
    load_fs(the_fs);
    struct dir_ent file_ent;
    if(!get_dir_ent(&the_fs->root_dir, fn, &file_ent)) {
        ret = NAME_CONFLICT;
    };

    store_fs(the_fs);
    free(the_fs);
	return ret;
}


void format() {
    // first we clear all the space in the drive
    int cyl, sect;
    char blank[BYTES_PER_SECTOR] = "";
    for(cyl = 0; cyl < CYLINDERS; ++cyl) {
        for(sect = 0; sect < SECTORS_PER_CYLINDER; ++sect) {
            int err = write_sector(cyl, sect, blank);
            if(err == BAD_CYLINDER) {
                printf("Bad cylinder: %d\n", cyl);

            } else if(err == BAD_SECTOR) {
                printf("Bad sector: %d\n", sect);
            }
        }
    }

    // now we set up the initial fat
    //struct fat *initial_fat = malloc(FAT_SIZE);
    //struct dir *root_dir = malloc(sizeof(struct dir));
    struct fs *init_fs = malloc(sizeof(struct fs));
    for(int i = 0; i < TOTAL_SECTORS; ++i) {
        init_fs->the_fat.table[i] = EMPTY;
    }
    memset(&init_fs->root_dir, 0, sizeof(struct dir));
    store_fs(init_fs);
    free(init_fs);
}


void mem_map()
{
    int cyl, sect;
    int blank[BYTES_PER_SECTOR+1] = {0};
    for(cyl = 0; cyl < CYLINDERS; ++cyl) {
        for(sect = 0; sect < SECTORS_PER_CYLINDER; ++sect) {
            char data[BYTES_PER_SECTOR];
            read_sector(cyl, sect, data);
//            printf("Cylinder: %d\nSector: %d\n\tData: %s\n\n", cyl, sect, data);
        }
    }
}




























