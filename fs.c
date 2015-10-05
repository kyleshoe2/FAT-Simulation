
/* Project 2 rules:
 *		ALL data must be stored on the simulated hard drive!
 *			- No global variables
 *			- No static variables
 *			- No other contrived method to preserve data between function calls
 */

/*
 * This is the only file you need to modify.  You might want to add printing or 
 * changes stuff in tester.c, but the program should work at the end with the 
 * initial versions of all files except this one.  Function stubs are included
 * so that the project will compile as-received.
 */

#include <stdlib.h>
#include <stdio.h>

#include "fs.h"
#include "drive.h"


int fdelete(char* fn){
	return 5;	
}

int load(char* fn, void* data, size_t ds){
	return 5;
}

void format() {
    int cyl, sect;
    char blank[BYTES_PER_SECTOR] = "";
    for(cyl = 0; cyl < CYLINDERS; ++cyl) {
        for(sect = 0; sect < SECTORS_PER_CYLINDER; ++sect) {
            int err = write_sector(cyl, sect, blank);
            if(err == BAD_CYLINDER) {
                printf("Bad cylinder: %d\n", cyl);

            } else if(err == BAD_SECTOR) {
                printf("Bad sector: %d\n", sect);
            }
        }
    }
}

int save(char* fn, void* data, size_t ds){
	return 5;
}


void mem_map()
{
    int cyl, sect;
    int blank[BYTES_PER_SECTOR+1] = {0};
    for(cyl = 0; cyl < CYLINDERS; ++cyl) {
        for(sect = 0; sect < SECTORS_PER_CYLINDER; ++sect) {
            char data[BYTES_PER_SECTOR];
            read_sector(cyl, sect, data);
            printf("Cylinder: %d\nSector: %d\n\tData: %s\n\n", cyl, sect, data);
        }
    }
}




























