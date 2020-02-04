#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// The struct for the rooms
typedef struct {
	char *RoomName;
	char *RoomType;
	int NumConnections;
	char** Connections;
}Room;

// Function to set the names of the rooms
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

	// Getting 7 random numbers between 0 and 9
	int nums[10];
	for (int i = 0; i < 10; i++) {
		nums[i] = i;
	}
	for (int i = 0; i < 10; i++) {
		int tmp = nums[i];
		int idx = rand() % 7;
		nums[i] = nums[idx];
		nums[idx] = tmp;
	}

	// Setting the room names
	for (int i = 0; i < 7; i++) {
		r[i].RoomName = RoomNames[nums[i]];
	}
}

// Function to assign room types to all the rooms
void setTypes(Room* r) {
	r[0].RoomType = "START_ROOM";
	r[6].RoomType = "END_ROOM";
	for (int i = 1; i < 6; i++) {
		r[i].RoomType = "MID_ROOM";
	}
}


// Main function
void main() {
	// The command to enable random numbers
	srand(time(NULL));

	// Declaring the array of structs
	Room* r = malloc(7 * sizeof(Room));
	for (int i = 0; i < 6; i++) {
		r[i].Connections = malloc(6 * sizeof(char*));
	}

	// Setting the names of the rooms
	setNames(r);

	// Setting the room types of the rooms
	setTypes(r);

	// Setting the initial number of connections for each room
	for (int i = 0; i < 10; i++) {
		r[i].NumConnections = 0;
	}
	
	printf("Room Names: ");
	for (int i = 0; i < 7; i++) {
		printf("%s, ", r[i].RoomName);
	}
	printf("\nRoom Types: ");
	for (int i = 0; i < 7; i++) {
		printf("%s, ", r[i].RoomType);
	}
}
