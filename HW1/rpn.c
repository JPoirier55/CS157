/* Jake Poirier
*  CS 157 HW 1
*  PURPOSE: The purpose of this program is to familiarize
*  ourselves with the conversion between binary, hex, octal,
*  as well as learn to use the command line arguments for 
*  a terminal run command.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
*  PrintErr takes in the original pointer to cmdline args
*  prints the error message of the correct usage
*/
void printErr(char *argv[]){
	printf("usage: %s [H|O|D] <left> <right> <operator>\n", argv[0]);

}
/*
*  printOutput takes in int value of the number, the base,
*  and the original pointer to argv[]
*  prints out the value in whatever base required from the 
*  command line arg
*  Checks to see whether or not the value is negative or not
*  for hex so we dont get a ridic number
*/
void printOutput(int value, char base, char *argv[]){
	switch(base){
		case 'O':
		if(value<0){
			value *=-1;
			printf("-%o\n", value);
		}else
			printf("%o\n",value);
		break;
		case 'H':
		if(value<0){
			value *=-1;
			printf("-%x\n", value);
		}else
			printf("%x\n", value);
		break;
		case 'D':
		printf("%d\n", value);
		break;
		case 't':
		printf("%d\n",value);
		break;
		default:
		printErr(argv);
	}
}

int main(int argc, char *argv[]){
	char base;
	char command;
	char test0[10],test1[10],test2[10], test3[10];
	int arg1, arg2;

	//Checking for correct number of cmd line args, err if not 4/5
	if(argc > 5 || argc < 4){
		printErr(argv);
		return 0;
	}
	//takes the cmdline args and copies to strings to eval. if 5 args
	if(argc == 5){
		strcpy(test0, argv[4]);
		strcpy(test1, argv[2]);
		strcpy(test2, argv[3]);
		strcpy(test3, argv[1]);
		//if operator is not single +,/-* errors
		if(strlen(test0) >=2){
			printErr(argv);
			return 0;
		}else
			command = test0[0];
		//if base is not single char H,D,O errs
		if(strlen(test3) >=2){
			printErr(argv);
			return 0;
		}else
			base = test3[0];
	//if 4 args at cmd line, copy strings accordingly
	}else{
		strcpy(test0, argv[3]);
		strcpy(test1, argv[1]);
		strcpy(test2, argv[2]);
		if(strlen(test0) >=2){
			printErr(argv);
			return 0;
		}else
			command = test0[0];

		base = 't';
	}
	//Testing to see whether the input vals are Hex, oct, or dec
	if(test2[0] == '0' && test2[1] =='x'){
		arg2 = strtol(test2, NULL, 16);

	}else if(test2[0] == '0'){
		arg2 = strtol(test2,NULL,8);
	}else
		arg2 = strtol(test2,NULL,10);
	if(test1[0] =='0' && test1[1] =='x'){
		arg1 = strtol(test1, NULL,16);
	}else if(test1[0] == '0'){
		arg1 = strtol(test1, NULL, 8);
	}else
		arg1 = strtol(test1, NULL,10);
		
	//Switch to see what operator or command was inputted,
	//each case calls printoutput to be printed, passing in base
	int sum,diff,div,mult,diff2;
	switch(command){
		case '+':
		sum = arg1+arg2;
		printOutput(sum, base, argv);
		break;
		case '-':
		diff = arg1-arg2;
		printOutput(diff, base, argv);
		break;
		case '/':
		div = arg1/arg2;
		printOutput(div, base, argv);
		break;
		case '*':
		mult = arg1*arg2;
		printOutput(mult, base, argv);
		break;
		case ',':
		diff2 = abs(arg1-arg2);
		printOutput(diff2, base, argv);
		break;
		default:
		printErr(argv);
		break;

	}
	
	return 0;

}
