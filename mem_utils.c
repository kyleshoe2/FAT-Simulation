#include "drive.h"
#include "fat.h"

#include <stdlib.h>
#include <string.h>

/*
 * The following functions use a modified version of Logical block addressing
 * described here: https://en.wikipedia.org/wiki/Logical_block_addressing#CHS_conversion
 */

unsigned short to_mem_addr(int cyl, int sect)
{
    return cyl * SECTORS_PER_CYLINDER + sect;
}

unsigned short to_cylinder_number(unsigned short mem_addr)
{
    return mem_addr / SECTORS_PER_CYLINDER;
}

unsigned short to_sector_number(unsigned short mem_addr) 
{
    return mem_addr % SECTORS_PER_CYLINDER;
}

