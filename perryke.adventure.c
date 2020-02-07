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
	if (file[0] == "ROOM NAME: Train")
		r[idx].RoomName = "Train";
	else if (file[0] == "ROOM NAME: Woody")
		r[idx].RoomName = "Woody";
	else if (file[0] == "ROOM NAME: Freezer")
		r[idx].RoomName = "Freezer";
	else if (file[0] == "ROOM NAME: Fridge")
		r[idx].RoomName = "Fridge";
	else if (file[0] == "ROOM NAME: Wombat")
		r[idx].RoomName = "Wombat";
	else if (file[0] == "ROOM NAME: Aqua")
		r[idx].RoomName = "Aqua";
	else if (file[0] == "ROOM NAME: Metal")
		r[idx].RoomName = "Metal";
	else if (file[0] == "ROOM NAME: Buffalo")
		r[idx].RoomName = "Buffalo";
	else if (file[0] == "ROOM NAME: Stones")
		r[idx].RoomName = "Stones";
	else if (file[0] == "ROOM NAME: Dark")
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
