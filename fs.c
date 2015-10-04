
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

#include "fs.h"
#include "drive.h"


int fdelete(char* fn){
	return 5;	
}

int load(char* fn, void* data, size_t ds){
	return 5;
}

void format() {
}

int save(char* fn, void* data, size_t ds){
	return 5;
}
