
/* You can assume these are number 0-49 and there is only one head */
#define CYLINDERS 50
/* This is true regardless of the circumfrence of each cylinder */
#define SECTORS_PER_CYLINDER 100
#define BYTES_PER_SECTOR 1024
#define CYLINDER_SIZE (SECTORS_PER_CYLINDER * BYTES_PER_SECTOR)
#define TOTAL_SECTORS (SECTORS_PER_CYLINDER * CYLINDERS)

#define BAD_CYLINDER 1 //TODO:  Fix comments below
#define BAD_SECTOR 2

/* Parameters:
 * 	int, cylinder to read from
 * 	int, sector number to read from designated cylinder
 * 	void*, pointer to memory area where data is to be written
 * Note:  Parameter #3 must be a pointer to an area where 
 * BYTES_PER_SECTOR can be written.  Otherwise memory errors 
 * will result!
 * Return value:  0 indicates success, also can return
 * BAD_CYLINDER or BAD_SECTOR if these are specified out of range.*/ 
int read_sector(int, int, void*);

/* Parameters:
 * 	int, cylinder to read from
 * 	int, sector number to read from designated cylinder
 * 	void*, pointer to memory area where data is to be written
 * Note:  This function will read BYTES_PER_SECTOR from the location
 * indicated by the third parameter, with no further checking! 
 * Return value:  0 indicates success, also can return
 * BAD_CYLINDER or BAD_SECTOR if these are specified out of range.*/ 
int write_sector(int, int, void*);

