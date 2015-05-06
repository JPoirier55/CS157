/*
 *Jake Poirier
 *CS157 HW4
 *5/1/15
 *
 *The purpose of this program is to work with 
 *Dynamically allocated data structures. Also 
 *We are working with our own header files and a 
 *main.c that is not within our mod.c class
*/
#include "mod.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int intsSize = 1000;		//global vars
int countInt = 0;
int *ints;

/*Reads in the file from test.c or main.c and scans the 
 * file for integers. When it comes to something that is
 * not an int its reutrns non zero, if it comes to the end of the 
 *file it will just end the while loop
*/
int readfile(const char *filename){
		
	FILE *f = fopen(filename, "r");
	if(f==NULL){
		fprintf(stderr, "Can't read '%s'\n",filename);
		return 42;
	}
	int currentInt;
	char errorChar;
	int running = 1;
	while(running){
		if(fscanf(f, "%d ", &currentInt)==1){
			ints[countInt]= currentInt;
			countInt++;
			
			/*this code snipped will change the amount of 
			 * allocated memory depending on how big the count gets
			 * just to be sure, the threshold is within 100 ints of 
		 	 * the total allocated memory, so we can realloc more
			 * when it gets to be intsSize-100
			*/
			if(countInt > intsSize -100){
				ints =realloc(ints, intsSize*2*sizeof(int));
				intsSize *=2;
			}
			
		}else if(fscanf(f, "%c ", &errorChar)==1){
			fprintf(stderr,"Hit non int value %c\n", errorChar);
			fclose(f);
			return 42;
		}else{
			running = 0;
		}
	}
	fclose(f);
	return 0;
}
//returns the total global var countInt for total count of ints
int count(){
	return countInt;
}
//adds each value of the ints from ints array to sum and returns sum
int total(){
	int sum = 0;
	for(int i =0;i<countInt;i++){
		sum +=ints[i];
	}
	return sum;
}
//compares each value in the ints array, if one is bigger it is set
//to max, and after the total array is scanned, max is returned
int largest(){
	int max = 0;
	int temp =0;
	for(int i =0; i<countInt;i++){
		temp = ints[i];		
		if(temp>max){			
			max = temp;
		}
	}
	return max;
}
//initializes the ints array by mallocating space by the inital size
//of intsSize
void initialize(){
	ints = (int*)malloc(intsSize * sizeof(int));
	if(ints == NULL){
		fprintf(stderr, "Failed to allocate ints array\n");
		exit(1);
	}
}
//terminates the ints array by freeing the memory allocated
void terminate(){
	free(ints);
}	


