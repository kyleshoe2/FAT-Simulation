#include <string.h>
#include <stdlib.h>

#include "fat.h"
#include "drive.h"


/*
 * Sets the value in struct fat_entry in struct fat at the first int to the second
 * int. the int must either be EMPTY, END_OF_FILE, or a valid address in memory.
 * 
 * Returns 0 if a valid index and value was given, and 1 otherwise
 */
int set_fat_entry_value(struct fat *the_fat, int index, int value)
{
    if(index < 0 || index >= TOTAL_SECTORS) {
        return 1;
    }

    return 0;
}




































