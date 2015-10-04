/* 
 * Simulated hard drive implementation for CS430 at LCSC
 * Created Fall 2014
 */

#include "drive.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// This is a global variable used to store the filesystem.  It is the only
// global variable that should be in the program.
void* dmem = 0;

void init() {
	dmem = (void*)malloc(CYLINDERS*CYLINDER_SIZE);
}

#define TESTS \
	if(cylinder < 0 || cylinder >= CYLINDERS) return BAD_CYLINDER; \
	if(sector < 0 || sector >= SECTORS_PER_CYLINDER) return BAD_SECTOR; \
	if(!dmem) init();

int read_sector(int cylinder, int sector, void* data){
	TESTS
	size_t offset = CYLINDER_SIZE * cylinder + BYTES_PER_SECTOR * sector;
	memcpy(data, dmem + offset, BYTES_PER_SECTOR);
	return 0;
}

int write_sector(int cylinder, int sector, void* data){
	TESTS
	size_t offset = CYLINDER_SIZE * cylinder + BYTES_PER_SECTOR * sector;
	memcpy(dmem + offset, data, BYTES_PER_SECTOR);
	return 0;
}
