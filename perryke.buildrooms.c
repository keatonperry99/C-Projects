#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>

/*
The struct for the rooms
*/
typedef struct {
	char *RoomName;
	char *RoomType;
	int NumConnections;
	char** Connections;
}Room;

/*
Function prototypes
*/
void setNames(Room* r);

void setTypes(Room* r);

int isGraphFull(Room* r);

Room* getRandomRoom(Room* r);

int canAddConnectionFrom(Room* x);

int connectionAlreadyExists(Room* x, Room* y);

void connectRooms(Room* x, Room* y);

int isSameRoom(Room* x, Room* y);

void addRandomConnection(Room* r);

/*
Main function
*/
void main() {
	/*
	The command to enable random numbers
	*/
	srand(time(NULL));

	/*
	Declaring the array of structs
	*/
	Room* r = malloc(7 * sizeof(Room));
	int i;
	int j;
	r->Connections = malloc(7 * sizeof(char*));
	for (i = 0; i < 7; i++) {
		r[i].Connections = malloc(6 * sizeof(char*));
	}
	for (i = 0; i < 7; i++) {
		for (j = 0; j < 6; j++) {
			r[i].Connections[j] = "NULL";
		}
	}

	/*
	Setting the names of the rooms
	*/
	setNames(r);

	/*
	Setting the names of the rooms
	*/
	setTypes(r);

	/*
	Setting the initial number of connections for each room
	*/
	for (i = 0; i < 10; i++) {
		r[i].NumConnections = 0;
	}
	
	/*
	Creating all the connections
	*/
	while (isGraphFull(r) == 0) {
		addRandomConnection(r);
	}

	/*
	// Creating the directory
	*/
	char prefix[] = "perryke.rooms.";
	int pid = getpid();
	char dirname[36];
	sprintf(dirname, "%s%d", prefix, pid);
	mkdir(dirname, 0755);

	/*
	Creating and writing the first file
	*/

	FILE *fptr;
	char pathname[54];
	sprintf(pathname, "%s/first.txt", dirname);
	fptr = fopen(pathname, "w");

	/* Writing to room name */
	char alldata[356];
	sprintf(alldata, "ROOM NAME: %s\n", r[0].RoomName);
	fprintf(fptr, alldata);

	/* Writing the room connections */
	for (i = 1; i <= r[0].NumConnections; i++) {
		sprintf(alldata, "CONNECTION %d: %s\n", i, r[0].Connections[i-1]);
		fprintf(fptr, alldata);
	}
	
	/* Writing the room type */
	sprintf(alldata, "ROOM TYPE: %s\n", r[0].RoomType);
	fprintf(fptr, alldata);
	
	/* Closing the first file */
	fclose(fptr);
	

	/*
	char tmpstr[50];
	char pathname[54];
	char alldata[356];
	for (i = 0; i < 7; i++) {
		if (i == 0) *tmpstr = "/first.txt";
		else if (i == 1) *tmpstr = "/second.txt";
		else if (i == 2) *tmpstr = "/third.txt";
		else if (i == 3) *tmpstr = "/fourth.txt";
		else if (i == 4) *tmpstr = "/fifth.txt";
		else if (i == 5) *tmpstr = "/sixth.txt";
		else if (i == 6) *tmpstr = "/seventh.txt";

		sprintf(pathname, "%s%s", dirname, tmpstr);
		fptr = fopen(pathname, "w");

		sprintf(alldata, "ROOM NAME: %s\n", r[i].RoomName);
		fprintf(fptr, alldata);

		for (j = 1; j <= r[i].NumConnections; j++) {
			sprintf(alldata, "CONNECTION %d: %s\n", j, r[i].Connections[j - 1]);
			fprintf(fptr, alldata);
		}

		sprintf(alldata, "ROOM TYPE: %s\n", r[i].RoomType);
		fprintf(fptr, alldata);
		fclose(fptr);
	}
	*/
}


/*
Function to set the names of the rooms
*/
void setNames(Room* r) {
	char* RoomNames[10];
	RoomNames[0] = "Train";
	RoomNames[1] = "Woody";
	RoomNames[2] = "Freezer";
	RoomNames[3] = "Fridge";
	RoomNames[4] = "Wombat";
	RoomNames[5] = "Aqua";
	RoomNames[6] = "Metal";
	RoomNames[7] = "Buffalo";
	RoomNames[8] = "Stones";
	RoomNames[9] = "Dark";

	/*
	Getting 7 random numbers between 0 and 9
	*/
	int nums[10];
	int i;
	for (i = 0; i < 10; i++) {
		nums[i] = i;
	}
	for (i = 0; i < 10; i++) {
		int tmp = nums[i];
		int idx = rand() % 7;
		nums[i] = nums[idx];
		nums[idx] = tmp;
	}

	/*
	Setting the room names
	*/
	for (i = 0; i < 7; i++) {
		r[i].RoomName = RoomNames[nums[i]];
	}
}

/*
Function to assign room types to all the rooms
*/
void setTypes(Room* r) {
	r[0].RoomType = "START_ROOM";
	r[6].RoomType = "END_ROOM";
	int i;
	for (i = 1; i < 6; i++) {
		r[i].RoomType = "MID_ROOM";
	}
}

/*
Function to check to see if the graph is full. Returns 1 if
it's full, 0 if it's not.
*/
int isGraphFull(Room* r) {
	int i;
	for (i = 0; i < 7; i++) {
		if (r[i].NumConnections < 3) {
			return 0;
		}
	}
	return 1;
}

/*
Function to return a pointer to a random room
*/
Room* getRandomRoom(Room* r) {
	int idx = rand() % 7;
	return &(r[idx]);
}

/*
Function that returns 1 if a connection can be added, 0 if not
*/
int canAddConnectionFrom(Room* x) {
	if (x->NumConnections < 6) {
		return 1;
	}
	return 0;
}

/*
Function that checks if there's already a connection between
two rooms
*/
int connectionAlreadyExists(Room* x, Room* y) {
	int i;
	int j;
	for (i = 0; i < y->NumConnections; i++) {
		if (x->RoomName == y->Connections[i]) {
			return 1;
		}
	}
	for (j = 0; j < x->NumConnections; j++) {
		if (y->RoomName == x->Connections[j]) {
			return 1;
		}
	}
	return 0;
}

/*
Function to create a connection between room x and y
*/
void connectRooms(Room* x, Room* y) {
	int idx;
	idx = x->NumConnections;
	x->Connections[idx] = y->RoomName;
	x->NumConnections = idx + 1;
	idx = y->NumConnections;
	y->Connections[idx] = x->RoomName;
	y->NumConnections = idx + 1;
	return;
}

/*
Function to determine if two given rooms are the same room
*/
int isSameRoom(Room* x, Room* y) {
	if (x->RoomName == y->RoomName) {
		return 1;
	}
	return 0;
}

/*
Function to add a random connection between two rooms
*/
void addRandomConnection(Room* r) {
	Room* A;
	Room* B;
	while (1) {
		A = getRandomRoom(r);
		if (canAddConnectionFrom(A) == 1)
			break;
	}
	do
	{
		B = getRandomRoom(r);
	} while (canAddConnectionFrom(B) == 0 ||
		isSameRoom(A, B) == 1 ||
		connectionAlreadyExists(A, B) == 1);

	connectRooms(A, B);
}
