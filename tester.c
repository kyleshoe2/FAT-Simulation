#include "fs.h"
#include "drive.h"

#include<string.h>
#include<stdio.h>
#include<stdlib.h>

/*
 * Tests in this file:
 * 	1.  Demo of read_sector and write_sector
 * 	2.  Call to format (should not crash, etc)
 * 	3.  Save and load a file (phrase.txt)
 * 	4.  Save a bigger (multi-sector) file
 * 	5.  Delete a file
 * 	6.  Try to load a file that does not exist
 * 	7.  Try to delete a file that does not exist
 * 	8.  Try to re-use an already-used filename
 * 	9.  Fill the entire drive and check function of NO_SPACE
 * 	10. Try to read from full drive
 * 	11. Delete everything in the drive and check save/load again
 * 	12. Format and check to make sure all files are "gone"
 *
 * 	If your program passes all these tests without hardcoding in
 * 	the answers, storing data places other than the simulated 
 * 	hard drive, or something else of that nature, it will receive
 * 	full credit.
 */

int main() {
	int ret;

	// Test 1
	char buf[1024];
	strcpy(buf, "This is a phrase!");
	write_sector(10, 20, buf);
	char abuf[1024];
	read_sector(10, 20, abuf);
	printf("Read from drive: %s\n", abuf);

	// Test 2
	format();

	// Test 3
	char phrase[] = "This is another phrase to be stored in a file!";
	if(ret = save("phrase.txt", phrase, strlen(phrase)))
		printf("** Received error value:  %d\n", ret);
	if(ret = load("phrase.txt", buf, 1024))
		printf("** Received error value:  %d\n", ret);
	if(!strcmp(phrase, buf))
		printf("File store and load correctly, good!\n");
	else 
		printf("** File returned with changes!  Not good.\n");
	
	// Test 4
	printf("Now a bigger file!  %d bytes\n", strlen(phrase)*200);
	char* longphrase = (char*)malloc(strlen(phrase)*200);
	for(int i = 0; i < 200; ++i)
		strcpy(longphrase + i * (strlen(phrase)), phrase);
	if(ret = save("longph.txt", longphrase, strlen(longphrase)))
		printf("** Received error value:  %d\n", ret);
	char* longphrasecpy = (char*)malloc(strlen(phrase)*200);
	if(ret = load("longph.txt", longphrasecpy, strlen(phrase)*200))
		printf("** Received error value:  %d\n", ret);
	if(!strcmp(longphrase, longphrasecpy))
		printf("Long file returned correctly, good!\n");
	else
		printf("** Long file returned with errors.\n");

	// Test 5
	if(ret = fdelete("phrase.txt"))
		printf("** Received error value:  %d\n", ret);

	// Test 6
	if(ret = load("phrase.txt", longphrasecpy, strlen(phrase)*200)) {
		printf("load returned %d\n", ret);
		if(ret == NOT_FOUND)
			printf("load returned the correct error, good!\n");
		else
			printf("** load did not return the expected error (NOT_FOUND)\n");
	} else
		printf("** Test 6 should produce an error (NOT_FOUND)\n");

	// Test 7
	if(ret = fdelete("phrase.txt")) {
		printf("fdelete returned %d\n", ret);
		if(ret == NOT_FOUND)
			printf("fdelete returned the correct error, good!\n");
		else
			printf("** fdelete did not return the expected error (NOT_FOUND)\n");
	} else
		printf("** Test 7 should produce an error (NOT_FOUND)\n");

	// Test 8
	if(ret = save("longph.txt", longphrase, strlen(longphrase))) {
		printf("Received error value:  %d\n", ret);
		if(ret == NAME_CONFLICT) 
			printf("Good, save produced the correct error!\n");
		else
			printf("** save did not produce the expected error (NAME_CONFLICT)\n");
	} else
		printf("** Test 8 should produce an error (NAME_CONFLICT)\n");

	// Test 9
	int count = 0;
	for(char name[11] = "bigt.txt";!(ret = save(name, longphrase, strlen(longphrase)));sprintf(name, "bigt%d.txt", ++count));
	printf("Received error value:  %d\n", ret);
	if(ret == NO_SPACE)
		printf("save returned NO_SPACE, good!\n");
	else
		printf("** save did not return the expected error (NO_SPACE)\n");
	if(count > 300)
		printf("%d copies were stored, that seems like enough!  It is %d bytes.\n", count, count * strlen(longphrase));
	else
		printf("** %d copies were stored, there's got to be more space somewhere!\n", count);

	// Test 10
	longphrasecpy[100]=0;
	if(ret = load("bigt50.txt", longphrasecpy, count * strlen(longphrase)))
		printf("** Received error value:  %d\n", ret);
	if(!strcmp(longphrase, longphrasecpy))
		printf("File correctly read from full drive, good!\n");
	else
		printf("** File read with errors from full drive\n");

	// Test 11
	int newcount = 0;
	for(char name[11] = "bigt.txt";!(ret = fdelete(name));sprintf(name, "bigt%d.txt", ++newcount));
	if(ret == NOT_FOUND)
		printf("Deleted %d files, ended with NOT_FOUND, good\n", newcount);
	else
		printf("** fdelete returned %d\n", ret);
	if(newcount != count)
		printf("** A different number of files were deleted than were written! %d != %d\n", count, newcount);
	if(ret = load("bigt50.txt", longphrasecpy, count * strlen(longphrase))) 
		printf("Could not load deleted file, good!\n");
	
	// Test 12
	format();
	if(ret == load("longph.txt", longphrasecpy, strlen(longphrase)))
		printf("Could not load files after formatting, good!\n");
	else
		printf("** Files are readable after formatting!  Data recovery is supposed to be hard.\n");

	free(longphrase);
	free(longphrasecpy);

	return 0;
}
