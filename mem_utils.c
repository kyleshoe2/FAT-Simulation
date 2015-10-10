#include "drive.h"
#include "fat.h"

#include <stdlib.h>
#include <string.h>

/*
 * The following functions use a modified version of Logical block addressing
 * described here: https://en.wikipedia.org/wiki/Logical_block_addressing#CHS_conversion
 */

int to_mem_addr(int cyl, int sect)
{
    return cyl * SECTORS_PER_CYLINDER + sect;
}

int to_cylinder_number(int mem_addr)
{
    return mem_addr / SECTORS_PER_CYLINDER;
}

int to_sector_number(int mem_addr) 
{
    return mem_addr % SECTORS_PER_CYLINDER;
}

int store_fat(struct fat *the_fat)
{
    size_t size = FAT_SIZE;
    char *data = malloc(sizeof(char) * size);
    memcpy(data, the_fat, size);
    
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


int load_fat(struct fat *the_fat)
{
    size_t size = FAT_SIZE;
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
    memcpy(the_fat, data, size);
    free(data);
    return 0;
}
