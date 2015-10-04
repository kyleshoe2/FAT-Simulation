#include<stddef.h>

#define NAME_CONFLICT 1
#define NO_SPACE 2
#define NOT_FOUND 3


/* Parameters:
 * 	char*, filename (must be null terminated)
 * 	void*, data to save in file
 * 	size_t, amount of data to save
 * When invoked, this function will read the amount of data indicated by the third 
 * parameter from the memory area indicated by the second, and save the data on
 * the hard drive if there is room.  If room exists and no file with the same name
 * exists, and the save is successful, the command should return 0.  If there is 
 * another file with the same name, the return value is NAME_CONFLICT.  If there is
 * no more space on the hard drive, the return value is NO_SPACE. */
int save(char*, void*, size_t);

/* Parameters:
 * 	char*, filename (must be null terminated)
 * 	void*, location to store data from file
 * 	size_t, size of the area indicated by the second parameter
 * When invoked, this function will read the indicated file form the hard drive, 
 * and copy the data from the file into the area indicated by the second parameter.
 * The third parameter indicates the maximum amount which can be written to the 
 * designated memory area without causing a buffer overflow, and this function should
 * not write more than this amount.  If the space is inadequate, as much of the file
 * as can be read should be read, and the return value will be NO_SPACE.  If the 
 * file does not exist, the return value will be NOT_FOUND.  If the load was successful,
 * and the entire file fit into the allocated space, the return value should be 0.  */
int load(char*, void*, size_t);

/* Parameters:
 * 	char*, filename (must be null terminated)
 * When invoked, this function will remove the indicated file.  If the file does
 * not exist, the return value is NOT_FOUND.  Otherwise, the return value should 
 * be 0. */
int fdelete(char*);

/* Formats the filesystem.  This should set up an initial file allocation table and
 * free space table, and anything else you need.  It will be called before any of
 * the other functions in this file.  It will also remove all files on the 
 * filesystem if called later. */
void format();

