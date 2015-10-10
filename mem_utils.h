#ifndef MEM_UTILS_H
#define MEM_UTILS_H

#include "fat.h"
#include "dir.h"

int to_mem_addr(int cyl, int sect);

int to_cylinder_number(int mem_addr);

int to_sector_number(int mem_addr);

#endif
