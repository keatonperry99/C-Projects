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

/* Struct for the player */
typedef struct {
	int numTurns;
	char** Rooms;
	Room CurrentRoom;
}Player;

/*
Function Prototypes
*/

/* Function to get the name of the newest directory */
void getDir(char* newestDirName);

/* Function to set the room info */
void setRoomInfo(int idx, Room* r);

/* Function to print the current room */
void getCurrentRoom(Player* p);

/* Function to print the possible room connections */
void getConnections(Player* p);

/* Function that acts as a hub for the game */
int startGame(Player* p, Room* r) {
	/* Checking to see if the current room is the end room */
	int i;
	char type[128] = "END_ROOM";
	if (strcmp(type, p->CurrentRoom.RoomType) == 0) {
		printf("YOU HAVE FOUND THE END ROOM. CONGRATULATIONS!\n");
		printf("YOU TOOK %d STEPS. YOUR PATH TO VICTORY WAS:\n", p->numTurns);
		for (i = 0; i < p->numTurns; i++) {
			printf("%s", p->Rooms[i]);
		}
		return 0;
	}

	/* Printing the current room and possible connections */
	getCurrentRoom(p);
	getConnections(p);

	/* Getting the user's input */
	char buffer[32];
	char* b = buffer;
	size_t bufsize = 32;
	size_t characters;
	printf("WHERE TO? >");
	characters = getline(&b, &bufsize, stdin);
	
	/* Checking if the user's input matches any valid connections */
	char conect[128];
	int valid = 0;
	for (i = 0; i < p->CurrentRoom.NumConnections; i++) {
		sprintf(conect, "%s\n", p->CurrentRoom.Connections[i]);
		if (strcmp(conect, buffer) == 0) {
			valid = 1;
			break;
		}
	}
	if (valid == 0) {
		printf("\nHUH? I DON'T UNDERSTAND THAT ROOM. TRY AGAIN.\n\n");
		return 1;
	}

	/* If the user's input is valid */
	p->Rooms[p->numTurns] = conect;
	printf("\n\n%s\n\n", p->Rooms[p->numTurns]);
	p->numTurns++;

	/* Moving the user to the next room */
	char tmpstr[128];
	for (i = 0; i < 7; i++) {
		sprintf(tmpstr, "%s\n", r[i].RoomName);
		if (strcmp(buffer, tmpstr) == 0)
			p->CurrentRoom = r[i];
	}

	printf("\n");
	return 1;
}

/*
Main Function
*/

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
	/* Setting the room info */
	for (i = 0; i < 7; i++)
		setRoomInfo(i, r);

	/* Declaring the player struct */
	Player* p;
	p = malloc(sizeof(Player));
	
	p->Rooms = malloc(12 * sizeof(char*));
	
	/* Getting the starting room */
	p->CurrentRoom = r[0];
	
	/*
	Starting the game
	*/
	p->numTurns = 0;
	while (startGame(p, r) == 1) {

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

/* Function to set the room name */
void setRoomInfo(int idx, Room* r) {
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

	/* Getting the room name */
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

	/* Determining what the room name is */
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

	/* Setting the number of connection */
	r[idx].NumConnections = numlines - 2;

	/* Getting the room connections */
	char connecName[128];
	for (i = 1; i < numlines - 1; i++) {
		sprintf(connecName, "CONNECTION %d: Train\n", i);
		if (strcmp(connecName, file[i]) == 0)
			r[idx].Connections[i - 1] = "Train";
		sprintf(connecName, "CONNECTION %d: Woody\n", i);
		if (strcmp(connecName, file[i]) == 0)
			r[idx].Connections[i - 1] = "Woody";
		sprintf(connecName, "CONNECTION %d: Freezer\n", i);
		if (strcmp(connecName, file[i]) == 0)
			r[idx].Connections[i - 1] = "Freezer";
		sprintf(connecName, "CONNECTION %d: Fridge\n", i);
		if (strcmp(connecName, file[i]) == 0)
			r[idx].Connections[i - 1] = "Fridge";
		sprintf(connecName, "CONNECTION %d: Wombat\n", i);
		if (strcmp(connecName, file[i]) == 0)
			r[idx].Connections[i - 1] = "Wombat";
		sprintf(connecName, "CONNECTION %d: Aqua\n", i);
		if (strcmp(connecName, file[i]) == 0)
			r[idx].Connections[i - 1] = "Aqua";
		sprintf(connecName, "CONNECTION %d: Metal\n", i);
		if (strcmp(connecName, file[i]) == 0)
			r[idx].Connections[i - 1] = "Metal";
		sprintf(connecName, "CONNECTION %d: Buffalo\n", i);
		if (strcmp(connecName, file[i]) == 0)
			r[idx].Connections[i - 1] = "Buffalo";
		sprintf(connecName, "CONNECTION %d: Stones\n", i);
		if (strcmp(connecName, file[i]) == 0)
			r[idx].Connections[i - 1] = "Stones";
		sprintf(connecName, "CONNECTION %d: Dark\n", i);
		if (strcmp(connecName, file[i]) == 0)
			r[idx].Connections[i - 1] = "Dark";
	}

	/* Getting the room type */
	char roomType1[128] = "ROOM TYPE: START_ROOM\n";
	char roomType2[128] = "ROOM TYPE: MID_ROOM\n";
	char roomType3[128] = "ROOM TYPE: END_ROOM\n";
	if (strcmp(roomType1, file[numlines - 1]) == 0)
		r[idx].RoomType = "START_ROOM";
	if (strcmp(roomType2, file[numlines - 1]) == 0)
		r[idx].RoomType = "MID_ROOM";
	if (strcmp(roomType3, file[numlines - 1]) == 0)
		r[idx].RoomType = "END_ROOM";

	return;
}

/* Function to print the current room */
void getCurrentRoom(Player* p) {
	printf("CURRENT LOCATION: %s\n", p->CurrentRoom.RoomName);
}

/* Function to print the possible room connections */
void getConnections(Player* p) {
	int i;
	printf("POSSIBLE CONNECTIONS: ");
	for (i = 0; i < p->CurrentRoom.NumConnections; i++) {
		if (i != (p->CurrentRoom.NumConnections - 1))
			printf("%s, ", p->CurrentRoom.Connections[i]);
		else
			printf("%s.\n", p->CurrentRoom.Connections[i]);
	}
}
