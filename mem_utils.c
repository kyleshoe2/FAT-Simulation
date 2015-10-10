
#include "drive.h"

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
