#ifndef MEM_UTILS_H
#define MEM_UTILS_H

#include "fat.h"
#include "dir.h"

unsigned short to_mem_addr(int cyl, int sect);

unsigned short to_cylinder_number(unsigned short mem_addr);

unsigned short to_sector_number(unsigned short mem_addr);

#endif
