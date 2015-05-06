#include "mod.h"
#include <stdio.h>

int main(){
	initialize();
	//for(int i = 0; i < 300;i++){
	readfile("test1.data");
	readfile("test.data");
	//}
	//readfile("test.data");
	printf("There are %d values.\n", count());
	printf("The largest value is %d.\n", largest());
	printf("The total is %d.\n", total());
	terminate();
	return 0;
}
