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
 * Sets the value in struct fat_entry in struct fat at the first ushort to the second
 * ushort. the second ushort must either be EMPTY, END_OF_FILE, or a valid address in memory.
 * 
 * Returns 0 if a valid index and value was given, and 1 otherwise
 */
int set_fat_entry_value(struct fat *, unsigned short, unsigned short);


/*
 * Finds the next empty sector in the fat and puts it in the first unsigned short.
 * starts at the first valid address where the files can be stored
 * 
 * returns 0 if a free space was successfully found, and 1 if the whole filesystem is
 * full
 */
int next_free_sector(struct fat *, unsigned short *);


/*
 * Finds the next empty sector in the fat and puts it in the first unsigned short
 * starts searching at the address indicatd by the second unsigned short, or just
 * starts at the first valid address where the files can be stored
 * 
 * returns 0 if a free space was successfully found, and 1 if the whole filesystem is
 * full
 */
int next_free_sector_from_start(struct fat *, unsigned short *, unsigned short);


int getn_free_sectors(struct fat *, unsigned short, unsigned short *);
#endif
