#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/*
Function Prototypes
*/

/* Function to get the name of the newest directory */
void getDir(char* newestDirName);

void main() {
	char dirName[256];
	getDir(dirName);
	char pathname[54];
	sprintf(pathname, "%s/first.txt", dirName);
	
	char line[128];
	char file[10][128];
	int i = 0;
	FILE* plist;
	plist = fopen(pathname, "r");
	while (fgets(line, sizeof(line), plist) != NULL) {
		strcpy(file[i], line);
		i++;
	}
	fclose(plist);
	int numlines = i;
	
	for (i = 0; i < numlines; i++) {
		printf("%s", file[i]);
	}
}
/* 
Function that returns the name of the most recently created directory. 
Preconditions: There is a directory that's been created. 
Postconditions: The name of the most recently created directory will
	be returned. 
*/
void getDir(char* newestDirName) {

	int newestDirTime = -1;
	char targetDirPrefix[32] = "perryke.rooms.";
	memset(newestDirName, '\0', sizeof(newestDirName));

	DIR* dirToCheck;
	struct dirent* fileInDir;
	struct stat dirAttributes;

	dirToCheck = opendir(".");

	if (dirToCheck > 0) {
		while ((fileInDir = readdir(dirToCheck)) != NULL) {
			if (strstr(fileInDir->d_name, targetDirPrefix) != NULL) {
				stat(fileInDir->d_name, &dirAttributes);
				if ((int)dirAttributes.st_mtime > newestDirTime) {
					newestDirTime = (int)dirAttributes.st_mtime;
					memset(newestDirName, '\0', sizeof(newestDirName));
					strcpy(newestDirName, fileInDir->d_name);
				}
			}
		}
	}
	closedir(dirToCheck);
}
