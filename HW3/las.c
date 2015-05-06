#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Hero{
	char name[30];
	char super[30];
	char appear[6];
};

int compare_name(const void *av, const void *bv){
	const struct Hero *a = av; 
	const struct Hero *b = bv;
	return strcmp(a->name,b->name);
}
int compare_super(const void *av, const void *bv){
	const struct Hero *a = av;
	const struct Hero *b = bv;
	return strcmp(a->super, b->super);
}
int compare_appear(const void *av, const void *bv){
	const struct Hero *a = av;
	const struct Hero *b = bv;
	return strcmp(a->appear, b->appear);
}
void printTable(struct Hero heroes[], char command[],int count){
	char plain[] = "Plain", super[] = "Super", appear[] = "Appear";
	char underLine[]="~~~~~";
	printf("%-30s %-30s %s\n%-30s %-30s %s.\n", plain,super,appear, underLine,underLine,underLine);	
	if(strcmp(command,"appear")==0){
		for(int i = count-1; i>=0; i--){
			printf("%-30s %-30s %s\n", heroes[i].name, heroes[i].super, heroes[i].appear);		
		}
	}else{
		for(int i = 0; i < count; i++){
			printf("%-30s %-30s %s\n", heroes[i].name, heroes[i].super, heroes[i].appear);
		}
	}

}
void printErr(char arg[]){
	printf("usage: %s file [plain|super|appear]\n", arg);
}


int main(int argc, char *argv[]){
	
	char fileName[30],heroName[30],super[30],appear[6];
	char slash[2],slash2[2], command[10] = "null";
	char newLine;
	
	if(argc == 3){
		strcpy(command, argv[2]);
		strcpy(fileName, argv[1]);
	}else if(argc ==2){
		strcpy(fileName, argv[1]);
	}else{
		printErr(argv[0]);
		return -1;
	}
	FILE *f = fopen(fileName, "r");
	if(f ==NULL){
		fprintf(stderr,"Error opening file %s.\n", fileName);
		return 42;
	}
	
	
	struct Hero heroes[100];
	int count = 0;
	while(fscanf(f,"%[^/]%[/]%[^/]%[/]%s%c",heroName,slash, super,slash2, appear,&newLine)==6){
		strcpy(heroes[count].name,heroName);
		strcpy(heroes[count].super,super);
		strcpy(heroes[count].appear,appear);
		count++;			
	}
	
	if(strcmp(command,"plain")==0){
		qsort(heroes,count,sizeof(struct Hero),compare_name);
		printTable(heroes,command,count);	
	}else if(strcmp(command,"super")==0){
		qsort(heroes,count,sizeof(struct Hero),compare_super);
		printTable(heroes,command,count);
	}else if(strcmp(command,"appear")==0){
		qsort(heroes,count,sizeof(struct Hero), compare_appear);
		printTable(heroes,command,count);	
	}else if(strcmp(command,"null")==0){
		printTable(heroes,command,count);
	}else{
		printErr(argv[0]);
	}
	
	fclose(f);
	return 0;

}

