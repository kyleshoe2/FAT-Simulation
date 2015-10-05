
#include "drive.h"

#define END_OF_FILE 0xFFFF
#define EMPTY 0x0


struct fat_entry
{
    int value;
};

struct fat
{
    struct fat_entry table[TOTAL_SECTORS];
};

/*
 * Will find the next fat_entry that has a free space available
 * 
 * Takes a struct fat_entry * for storing the struct fat_entry that 
 * has free space.
 * 
 * Returns 0 on successful completion or NO_SPACE if no space is available
 */
int next_free_entry(struct fat_entry *);

/*
 * Sets the value in struct fat_entry in struct fat at the first int to the second
 * int. the int must either be EMPTY, END_OF_FILE, or a valid address in memory.
 * 
 * Returns 0 if a valid index and value was given, and 1 otherwise
 */
int set_fat_entry_value(struct fat *, int, int);
