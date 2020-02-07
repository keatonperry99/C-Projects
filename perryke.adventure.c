#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/* Struct for the rooms */
typedef struct {
	char* RoomName;
	char* RoomType;
	int NumConnections;
	char** Connections;
}Room;

/*
Function Prototypes
*/

/* Function to get the name of the newest directory */
void getDir(char* newestDirName);

/* Function to get the information of the rooms */
void setRoom(int idx, Room* r) {
	/* Getting the directory name */
	char dirName[256];
	getDir(dirName);
	/* Getting the path name */
	char pathname[54];
	if (idx == 0) 
		sprintf(pathname, "%s/first.txt", dirName);
	else if (idx == 1)
		sprintf(pathname, "%s/second.txt", dirName);
	else if (idx == 2)
		sprintf(pathname, "%s/third.txt", dirName);
	else if (idx == 3)
		sprintf(pathname, "%s/fourth.txt", dirName);
	else if (idx == 4)
		sprintf(pathname, "%s/fifth.txt", dirName);
	else if (idx == 5)
		sprintf(pathname, "%s/sixth.txt", dirName);
	else if (idx == 6)
		sprintf(pathname, "%s/seventh.txt", dirName);

	/* Reading the file and storing it in an array */
	char line[128];
	char file[10][128];
	int i = 0;
	FILE* plist;
	plist = fopen(pathname, "r");
	/* Storing the file, line by line */
	while (fgets(line, sizeof(line), plist) != NULL) {
		strcpy(file[i], line);
		i++;
	}
	fclose(plist);
	int numlines = i;

	/* Setting the room name */
	char name1[128] = "ROOM NAME: Train\n";
	char name2[128] = "ROOM NAME: Woody\n";
	char name3[128] = "ROOM NAME: Freezer\n";
	char name4[128] = "ROOM NAME: Fridge\n";
	char name5[128] = "ROOM NAME: Wombat\n";
	char name6[128] = "ROOM NAME: Aqua\n";
	char name7[128] = "ROOM NAME: Metal\n";
	char name8[128] = "ROOM NAME: Buffalo\n";
	char name9[128] = "ROOM NAME: Stones\n";
	char name10[128] = "ROOM NAME: Dark\n";
	
	if (strcmp(name1, file[0]) == 0)
		r[idx].RoomName = "Train";
	else if (strcmp(name2, file[0]) == 0)
		r[idx].RoomName = "Woody";
	else if (strcmp(name3, file[0]) == 0)
		r[idx].RoomName = "Freezer";
	else if (strcmp(name4, file[0]) == 0)
		r[idx].RoomName = "Fridge";
	else if (strcmp(name5, file[0]) == 0)
		r[idx].RoomName = "Wombat";
	else if (strcmp(name6, file[0]) == 0)
		r[idx].RoomName = "Aqua";
	else if (strcmp(name7, file[0]) == 0)
		r[idx].RoomName = "Metal";
	else if (strcmp(name8, file[0]) == 0)
		r[idx].RoomName = "Buffalo";
	else if (strcmp(name9, file[0]) == 0)
		r[idx].RoomName = "Stones";
	else if (strcmp(name10, file[0]) == 0)
		r[idx].RoomName = "Dark";

	return;
}


void main() {
	/* Declaring the array of room structs */
	Room* r = malloc(7 * sizeof(Room));
	int i;
	int j;
	/* Declaring the connections within the rooms */
	r->Connections = malloc(7 * sizeof(char*));
	for (i = 0; i < 7; i++) {
		r[i].Connections = malloc(6 * sizeof(char*));
	}
	/* Setting the initial number of connections for each room */
	for (i = 0; i < 7; i++) {
		r[i].NumConnections = 0;
	}

	setRoom(0, r);
	printf("Room name is: %s\n", r[0].RoomName);
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
