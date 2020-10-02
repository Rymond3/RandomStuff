#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mytar.h"

extern char *use;

/** Copy nBytes bytes from the origin file to the destination file.
 *
 * origin: pointer to the FILE descriptor associated with the origin file
 * destination:  pointer to the FILE descriptor associated with the destination file
 * nBytes: number of bytes to copy
 *
 * Returns the number of bytes actually copied or -1 if an error occured.
 */
int
copynFile(FILE * origin, FILE * destination, int nBytes)
{
	/*	
	int copiedByte, count = 0;

	while ((copiedByte = getc(origin)) != EOF && (count < nBytes)) {
		putc((unsigned char) copiedByte, destination);
		count++;
	}

	return count;
	*/

int byte = 0;
	int count = 0;
	int line = 0;
	while ((line != EOF) && (count < nBytes)) {
		line = getc(origin);
		if (line != EOF) {
			byte = putc((unsigned char) line, destination);

			if (byte == EOF) {
				perror("putc() failed!!");
				return -1;
			}
			count++;
		}
	}
	return count;
}

/** Loads a string from a file.
 *
 * file: pointer to the FILE descriptor 
 * 
 * The loadstr() function must allocate memory from the heap to store 
 * the contents of the string read from the FILE. 
 * Once the string has been properly built in memory, the function returns
 * the starting address of the string (pointer returned by malloc()) 
 * 
 * Returns: !=NULL if success, NULL if error
 */
char*
loadstr(FILE * file)
{
	int count = 0;
	char *name = NULL;
	int line;

	while ((line = getc(file)) != '\0')
		count++;

	if (count > 0) {
		name = malloc(sizeof(char) * (count + 1));
		fseek(file, -(count+1), SEEK_CUR);
		for (int i = 0; i < count + 1; i++)
			name[i] = getc(file);
	}

	return name;
}

/** Read tarball header and store it in memory.
 *
 * tarFile: pointer to the tarball's FILE descriptor 
 * nFiles: output parameter. Used to return the number 
 * of files stored in the tarball archive (first 4 bytes of the header).
 *
 * On success it returns the starting memory address of an array that stores 
 * the (name,size) pairs read from the tar file. Upon failure, the function returns NULL.
 */
stHeaderEntry*
readHeader(FILE * tarFile, int *nFiles)
{
	stHeaderEntry* array = NULL;
	int numFiles = 0;
	unsigned int size;
	char *name;

	fread(&numFiles, sizeof(int), 1, tarFile);
	array = malloc(sizeof(stHeaderEntry) * numFiles);

	for(int i = 0; i < numFiles; ++i) {
		name = loadstr(tarFile);

		array[i].name = name;
		if(fread(&size,sizeof(unsigned int), 1, tarFile) > 0)
			array[i].size = size;
	}	
	
	(*nFiles) = numFiles;

	return array;
}

/** Creates a tarball archive 
 *
 * nfiles: number of files to be stored in the tarball
 * filenames: array with the path names of the files to be included in the tarball
 * tarname: name of the tarball archive
 * 
 * On success, it returns EXIT_SUCCESS; upon error it returns EXIT_FAILURE. 
 * (macros defined in stdlib.h).
 *
 * HINTS: First reserve room in the file to store the tarball header.
 * Move the file's position indicator to the data section (skip the header)
 * and dump the contents of the source files (one by one) in the tarball archive. 
 * At the same time, build the representation of the tarball header in memory.
 * Finally, rewind the file's position indicator, write the number of files as well as 
 * the (file name,file size) pairs in the tar archive.
 *
 * Important reminder: to calculate the room needed for the header, a simple sizeof 
 * of stHeaderEntry will not work. Bear in mind that, on disk, file names found in (name,size) 
 * pairs occupy strlen(name)+1 bytes.
 *
 */
int
createTar(int nFiles, char *fileNames[], char tarName[])
{
	FILE *tar = fopen(tarName,"w");
	stHeaderEntry* headerList = malloc(sizeof(stHeaderEntry) * nFiles);	
	int nameLength = 0, sizeBytes = 0, pointer, countBytes = 0;

	if (tar == NULL) 
		return EXIT_FAILURE;
	
	for(int i = 0; i < nFiles; ++i){
		nameLength = strlen(fileNames[i]) + 1;
		sizeBytes += nameLength;
		headerList[i].name = malloc(nameLength);
		strcpy(headerList[i].name, fileNames[i]);
	}

	pointer = sizeof(int) + (nFiles*sizeof(unsigned int)) + sizeBytes; ///

	fseek(tar, pointer, SEEK_SET);

	FILE *inputFile;
	
	for(int i = 0; i < nFiles; ++i){
		inputFile = fopen(fileNames[i], "r");
		if (inputFile == NULL) 
			return EXIT_FAILURE;
		countBytes = copynFile(inputFile, tar, INT_MAX);
		fclose(inputFile);
		headerList[i].size = countBytes;
	}
	
	fseek(tar, 0, SEEK_SET);
	
	if (fwrite(&nFiles, sizeof(int), 1, tar) !=-1) {
		for (int i = 0; i < nFiles; i++) {
			if((fwrite(headerList[i].name, strlen(headerList[i].name) + 1, 1, tar) != -1) && (fwrite(&headerList[i].size, sizeof(unsigned int), 1, tar) != -1))
				free(headerList[i].name);

			else return EXIT_FAILURE;
		}
	}

	free(headerList);
	fclose(tar);

	return EXIT_FAILURE;
}

/** Extract files stored in a tarball archive
 *
 * tarName: tarball's pathname
 *
 * On success, it returns EXIT_SUCCESS; upon error it returns EXIT_FAILURE. 
 * (macros defined in stdlib.h).
 *
 * HINTS: First load the tarball's header into memory.
 * After reading the header, the file position indicator will be located at the 
 * tarball's data section. By using information from the 
 * header --number of files and (file name, file size) pairs--, extract files 
 * stored in the data section of the tarball.
 *
 */
int
extractTar(char tarName[])
{
	FILE * tar = fopen(tarName, "r");
	stHeaderEntry* headerList;
	int numFiles = 0;
	char *name = NULL;

	if(tar != NULL){
		headerList = readHeader(tar, &numFiles);
		if(headerList != NULL){
			for(int i = 0; i < numFiles; i++) {
				FILE * outputFile;
				name = headerList[i].name;
				if((outputFile = fopen(name, "w")) != NULL){
					int bytes = copynFile(tar, outputFile, headerList[i].size);

					if(bytes == headerList[i].size)
						fclose(outputFile);
				}
				free(name);
			}
			free(headerList);
		}

		fclose(tar);
	}

	return EXIT_FAILURE;
}
