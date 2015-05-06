/*
* Jake Poirier
* CS157 HW2 
* The purpose of this homework is to get a better understanding of 
* how the command line arguments work with both files and inputs along
* with how structs are used and passed from function to function. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE_LINE 100 // Total maximum size of a data file line
#define MAX_SIZE_NAME 20  // max size of the name of a room
#define MAX_SIZE_DESC 60  // max size of the description of a room
#define MAX_NUM_ROOMS 25  // max number of rooms
int roomCount;
struct Room {
	char north, south, east, west;
	char id;
	char description[MAX_SIZE_DESC];
	char name[MAX_SIZE_NAME];
};

// function prototypes
int buildRooms(char filename[], struct Room rooms[]);
void runGame(struct Room rooms[]);
void printRoom(struct Room *r);

int main(int argc, char *argv[])
{
	struct Room rooms[MAX_NUM_ROOMS];   // list of all the rooms
	if (argc != 2) {
		fprintf(stderr, "usage: %s <room-file>\n", argv[0]);
		return 1;
	}
	if (buildRooms(argv[1], rooms) != 0)
		return 2;
	
	return 0;
}
//Buildrooms takes in the file and the struct[] we created above,
//And sets the struct[] with each room we have within the file 
int buildRooms(char filename[], struct Room list[])
{
	FILE *f = fopen(filename, "r");
	if (f == NULL) {
		fprintf(stderr, "Error opening game file %s.\n", filename);
		return 42;              // failure
	}
	char idStr[2];
	char name[MAX_SIZE_NAME], desc[MAX_SIZE_DESC], news[5];
	
	roomCount = 0;
	while(fscanf(f, "%s %s %s %[^\n]s", idStr, name, news, desc)==4){
		struct Room room;
		room.id = idStr[0];
		strcpy(room.name, name);
		room.north = news[0];
		room.south = news[1];
		room.east = news[2];
		room.west = news[3];
		strcpy(room.description, desc);
		list[roomCount] = room;
		roomCount++;
	}
	//each iteration through the file for each line we add another count
	// for the size of the struct[]
	runGame(list);

	return 0;
	                   // success
}
//print rooms will return the room name and description and the direction
// for whether or not there is a room to the north, south, east or west of 
//the current room
void printRoom(struct Room *r){	
	printf("Location: %s: %s\n", r->name, r->description);
	printf("Directions: ");
	if(r->north != '-')
		printf("north ");
	if(r->south != '-')
		printf("south ");
	if(r->east != '-')
		printf("east ");
	if(r->west != '-')
		printf("west ");
	if(r->north == '-' && r->south =='-'&&r->east=='-'&&r->west=='-')
		printf("none");
	printf("\n");
}


//changeRoom uses the desired direction, the current room int, the struct[] of rooms and the 
//struct[] count to determine whether or not it is feasible to change rooms, or if rooms are 
//changed then the new room name and location will be printed, and the current room int will
//be changed.

int changeRoom(char direction, int current, struct Room rooms[], int count){
 
	for(int i = 0; i<count; i++){
		if(direction =='n'){
			if(rooms[current].north == rooms[i].id){
				current = i;
				printRoom(&rooms[current]);
				return current;
			}			
		}
		if(direction =='s'){
			if(rooms[current].south == rooms[i].id){
				current = i;
				printRoom(&rooms[current]);
				return current;
			}
		}
		if(direction =='e'){
			if(rooms[current].east == rooms[i].id){
				current = i;
				printRoom(&rooms[current]);
				return current;
			}
		}
		if(direction =='w'){
			if(rooms[current].west == rooms[i].id){
				current = i;
				printRoom(&rooms[current]);
				return current;
			}
		}		
	}
	return current;
}
//Rungame takes the struct[] and the size count of the array and starts the game loop.
//The switch statement checks what the input char is for a direction or current or quit.
//using each char, the room that will be changed will be printed and changed or not depending
//if there is a room to the direction desired.
void runGame(struct Room rooms[]){
	char command = 't';
	char enter = 't';
		int current = 0;
		int current2 = 0;
		int running = 1;
		if(running == 1){
		printf("Welcome to Reconfigurable Rooms!\n");
		printf("Type c for current room, n/e/w/s, or q.\n");
		printf("> ");}
		//printRoom(&rooms[current]);
		while(running == 1){
			scanf("%c%c", &command, &enter);
			switch(command){
				case 'c':
				printRoom(&rooms[current]);			
				break;
				case 'n':
				current2 = changeRoom(command, current, rooms, roomCount);
				if(current2 == current)
					printf("Sorry can't.\n");
				current = current2;
				break;
				case 'e':
				current2 =changeRoom(command,current,rooms,roomCount);
				if(current2 ==current)
					printf("Sorry can't.\n");
				current = current2;
				break;
				case 'w':
				current2 = changeRoom(command,current,rooms,roomCount);
				if(current2 == current)
					printf("Sorry can't.\n");
				current = current2;
				break;
				case 's':
				current2 = changeRoom(command,current,rooms,roomCount);
				if(current2 == current)
					printf("Sorry can't.\n");
				current = current2;
				break;
				case 'q':
				running = 0;
				break;
				default:
				printf("Bad command \"%c\".\n", command);
				break;
			}
			command = 't';
		}

}

