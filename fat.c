#include <string.h>
#include <stdlib.h>

#include "fat.h"
#include "drive.h"
#include "mem_utils.h"

int is_sector_restricted(unsigned short addr)
{
    return to_cylinder_number(addr) == 0;
}

/*
 * Sets the value in struct fat_entry in struct fat at the first int to the second
 * int. the int must either be EMPTY, END_OF_FILE, or a valid address in memory.
 * 
 * Returns 0 if a valid index and value was given, and 1 otherwise
 */
int set_fat_entry_value(struct fat *the_fat, unsigned short index, unsigned short value)
{
    if(is_sector_restricted(index)) {
        return 1;
    
    } else if(is_sector_restricted(value) && value != EMPTY && value != END_OF_FILE) {
        return 1;
    }

    the_fat->table[index] = value;

    return 0;
}


int next_free_sector(struct fat *the_fat, unsigned short *dest)
{
    return next_free_sector_from_start(the_fat, dest, 0);
}


int next_free_sector_from_start(struct fat *the_fat, unsigned short *dest, unsigned short start)
{
    if(is_sector_restricted(start)) {
        start = to_mem_addr(1, 0);
    
    } else if(start >= TOTAL_SECTORS) {
        return 1;
    }

    for(unsigned short cur_addr = start; cur_addr < TOTAL_SECTORS; ++cur_addr) {
        if(the_fat->table[cur_addr] == EMPTY) {
            *dest = cur_addr;
            return 0;
        }
    }

    return 1;
}


int getn_free_sectors(struct fat *the_fat, unsigned short n, unsigned short *dest)
{
    if(n >= TOTAL_SECTORS) {
        return 1;
    }

    unsigned short free_sect = 0;
    int ret = 0;
    for(int i = 0; i < n && !ret; ++i) {
        ret = next_free_sector_from_start(the_fat, &free_sect, free_sect);
        dest[i] = free_sect;
        // free_sect contains the next address we can start searching from
        free_sect++;
    }

    return ret;
}






























