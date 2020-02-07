#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>


/* The struct for the rooms */
typedef struct {
	char *RoomName;
	char *RoomType;
	int NumConnections;
	char** Connections;
}Room;

/*
Function prototypes
*/

/* Function to set the names of the rooms */
void setNames(Room* r);
/* Function to set the room types of the rooms */
void setTypes(Room* r);
/* Function to check if all rooms meet the requirements */
int isGraphFull(Room* r);
/* Function that returns a random room */
Room* getRandomRoom(Room* r);
/* Function that checks if a rooms has available connections */
int canAddConnectionFrom(Room* x);
/* Function that checks if two rooms are already connected */
int connectionAlreadyExists(Room* x, Room* y);
/* Function that connects two given rooms */
void connectRooms(Room* x, Room* y);
/* Function that checks to see if two rooms are the same */
int isSameRoom(Room* x, Room* y);
/* Function that adds a random connection between two rooms */
void addRandomConnection(Room* r);

/*
Main function
*/

void main() {
	/* The command to enable random numbers */
	srand(time(NULL));

	/* Declaring the array of structs */
	Room* r = malloc(7 * sizeof(Room));
	int i;
	int j;
	/* Declaring the connections within the rooms */
	r->Connections = malloc(7 * sizeof(char*));
	for (i = 0; i < 7; i++) {
		r[i].Connections = malloc(6 * sizeof(char*));
	}
	/* Setting the connections of the rooms to empty */
	for (i = 0; i < 7; i++) {
		for (j = 0; j < 6; j++) {
			r[i].Connections[j] = "NULL";
		}
	}
	/* Setting the initial number of connections for each room */
	for (i = 0; i < 10; i++) {
		r[i].NumConnections = 0;
	}

	/* Calling the function to set the room names */
	setNames(r);

	/* Calling the function to set the room types */
	setTypes(r);

	/* Creating all the connections */
	while (isGraphFull(r) == 0) {
		addRandomConnection(r);
	}

	/* Creating the directory */
	char prefix[] = "perryke.rooms.";
	int pid = getpid();
	char dirname[36];
	sprintf(dirname, "%s%d", prefix, pid);
	mkdir(dirname, 0755);

	/* Declaring the file pointer and data variables */
	FILE* fptr;
	char pathname[54];
	char alldata[356];
	/* Writing each room to a different file */
	for (j = 0; j < 7; j++) {
		/* Depending on what j is, the room filename changes */
		if (j == 0)
			sprintf(pathname, "%s/first.txt", dirname);
		else if (j == 1)
			sprintf(pathname, "%s/second.txt", dirname);
		else if (j == 2)
			sprintf(pathname, "%s/third.txt", dirname);
		else if (j == 3)
			sprintf(pathname, "%s/fourth.txt", dirname);
		else if (j == 4)
			sprintf(pathname, "%s/fifth.txt", dirname);
		else if (j == 5)
			sprintf(pathname, "%s/sixth.txt", dirname);
		else if (j == 6)
			sprintf(pathname, "%s/seventh.txt", dirname);

		/* Opening the file */
		fptr = fopen(pathname, "w");

		/* Writing the room name */
		sprintf(alldata, "ROOM NAME: %s\n", r[j].RoomName);
		fprintf(fptr, alldata);

		/* Writing the room connections */
		for (i = 1; i <= r[j].NumConnections; i++) {
			sprintf(alldata, "CONNECTION %d: %s\n", i, r[j].Connections[i - 1]);
			fprintf(fptr, alldata);
		}

		/* Writing the room type */
		sprintf(alldata, "ROOM TYPE: %s\n", r[j].RoomType);
		fprintf(fptr, alldata);

		/* Closing the first file */
		fclose(fptr);
	}
	
}


/*
Function to set the names of the rooms. It randomly generates
	7 numbers between 0 and 9, and assigns the room names based
	off of those numbers. 
Preconditions: The program has started.
Postconditions: Each room will now have a name associated with it. 
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

	/* Getting 7 random numbers between 0 and 9 */
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

	/* Setting the room names based on the random numbers */
	for (i = 0; i < 7; i++) {
		r[i].RoomName = RoomNames[nums[i]];
	}
}

/*
Function to assign room types to all the rooms. It assigns the first
	struct as the start room, and the last struct as the end room. 
	All other structs are mid rooms.
Preconditions: All rooms have been assigned names.
Postconditions: All rooms will have a room type assigned. 
*/
void setTypes(Room* r) {
	/* Setting the first and last rooms */
	r[0].RoomType = "START_ROOM";
	r[6].RoomType = "END_ROOM";
	int i;
	/* Setting the middle rooms */
	for (i = 1; i < 6; i++) {
		r[i].RoomType = "MID_ROOM";
	}
}

/*
Function to check to see if the graph is full. It returns 1 if all of
	the rooms have three or more connections, returns 0 otherwise. 
Preconditions: The rooms have started to have connections assigned
	to them.
Postconditions: Whether or not the graph is full will be returned. 
*/
int isGraphFull(Room* r) {
	int i;
	for (i = 0; i < 7; i++) {
		/* If the number of connections are less than three, false */
		if (r[i].NumConnections < 3) {
			return 0;
		}
	}
	/* Otherwise true */
	return 1;
}

/*
Function to return a pointer to a random room. 
Preconditions: The rooms have started to have connections assigned.
Postconditions: A pointer to a random room will be returned. 
*/
Room* getRandomRoom(Room* r) {
	int idx = rand() % 7;
	return &(r[idx]);
}

/*
Function to check if a connection can be added from a given room. 
	Returns 1 if a connection can be added, and return 0 otherwise. 
Preconditions: The rooms have started to have connections assigned. 
Postconditions: Whether or not a connection can be added to room x
	will be returned. 
*/
int canAddConnectionFrom(Room* x) {
	if (x->NumConnections < 6) {
		return 1;
	}
	return 0;
}

/*
Function that checks if there's already a connection between two
	given rooms. Returns 1 if there is an existing connection, 
	returns 0 otherwise. 
Preconditions: The rooms have started to have connections assigned. 
Postconditions: Whether or not the two rooms have an existing
	connection will be returned. 
*/
int connectionAlreadyExists(Room* x, Room* y) {
	int i;
	int j;
	/* Checking if there's a connection between x and y */
	for (i = 0; i < y->NumConnections; i++) {
		if (x->RoomName == y->Connections[i]) {
			return 1;
		}
	}
	/* Checking if there's a connection between y and x */
	for (j = 0; j < x->NumConnections; j++) {
		if (y->RoomName == x->Connections[j]) {
			return 1;
		}
	}
	return 0;
}

/*
Function to create a connection between two given rooms. 
Preconditions: The two given rooms are both valid. 
Postconditions: The two given rooms will be connected. 
*/
void connectRooms(Room* x, Room* y) {
	int idx;
	/* Creating the connection between x and y */
	idx = x->NumConnections;
	x->Connections[idx] = y->RoomName;
	x->NumConnections = idx + 1;
	/* Creating the connection between y and x */
	idx = y->NumConnections;
	y->Connections[idx] = x->RoomName;
	y->NumConnections = idx + 1;
	return;
}

/*
Function to determine if two given rooms are the same room.
	Returns 1 if they're the same, and returns 0 otherwise. 
Preconditions: The rooms have started to have connections assigned. 
Postconditions: Whether or not the two given rooms are the same
	will be returned. 
*/
int isSameRoom(Room* x, Room* y) {
	if (x->RoomName == y->RoomName) {
		return 1;
	}
	return 0;
}

/*
Function to add a random connection between two rooms. If first gets
	two random rooms, then checks to see if they are valid. If they
	are, then a connection between them is created. If they aren't
	valid, then a new room will be grabbed. 
Preconditions: The rooms have names, types, and the initial number
	of connections set. 
Postconditions: All of the rooms will be completely set and satisfy
	all requirements. 
*/
void addRandomConnection(Room* r) {
	Room* A;
	Room* B;
	while (1) {
		/* Getting a random room */
		A = getRandomRoom(r);
		/* Seeing if a connection can be added */
		if (canAddConnectionFrom(A) == 1)
			break;
	}
	do
	{
		/* Getting another random room */
		B = getRandomRoom(r);
		/* Checking if the room is valid */
	} while (canAddConnectionFrom(B) == 0 ||
		isSameRoom(A, B) == 1 ||
		connectionAlreadyExists(A, B) == 1);

	/* Connecting the two rooms */
	connectRooms(A, B);
}
