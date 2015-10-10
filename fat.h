#ifndef FAT_H
#define FAT_H

#include "drive.h"

#define END_OF_FILE 0xFFFF
#define EMPTY 0x0

#define FAT_SIZE sizeof(struct fat)

struct fat
{
    unsigned short table[TOTAL_SECTORS];
};


/*
 * Sets the value in struct fat_entry in struct fat at the first int to the second
 * int. the int must either be EMPTY, END_OF_FILE, or a valid address in memory.
 * 
 * Returns 0 if a valid index and value was given, and 1 otherwise
 */
int set_fat_entry_value(struct fat *, int, int);

#endif
