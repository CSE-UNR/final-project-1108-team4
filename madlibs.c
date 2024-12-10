// dreyden aubert
// 11/26/24
// madlibs

#include <stdio.h>
#define FN "madlib1.txt"
#define AD "an adjective"
#define NO "a noun"
#define VE "a verb"
#define ROWS 200
#define STRCAP 200

void getFile(int argc, char *argv[]);
int store(FILE* p, int rows, int cols, char str[][STRCAP]);
int stringLength(char str[]);
void prompt(char str[][STRCAP], int rows, int cols);
int stringCompare(char str1[], char compared[]);
void equivalency(char str[][STRCAP], int row, char strb[], char strc[]);
void output(char str[][STRCAP], int rows, int cols);
int space(char str[][STRCAP], int row, int cols);

int main(int argc, char *argv[]){
	FILE* fp = fopen(FN, "r"); // file io for reading madlib into program
	if(fp == NULL){
		printf("Can't open %s.\n", FN);
		return 0;
	}
	else{
		char madlibStr[ROWS][STRCAP]; // rows arbitrarily large
		getFile(argc, argv);
		int rows = store(fp, ROWS, STRCAP, madlibStr);
	 	prompt(madlibStr, rows, STRCAP);
	 	output(madlibStr, rows, STRCAP);
		fclose(fp);
		return 0;
	}
}
void getFile(int argc, char *argv[]){
	if(argc > 1){//no arguments passed makes argc = 1, so >1 to prevent segfault
		char name[9] = {"filename"};//argument
		if(stringCompare(name, argv[1]) == 0){
			printf("\nThe madlib file name is: %s.\n", FN);
		}
		else{
			printf("\nInvalid argument.\n");
		}
	}//might put into separate function
}
int store(FILE* p, int rows, int cols, char str[][STRCAP]){
	int numRows = 0;
	for(int i = 0; i < rows; i++){
		fgets(str[i], STRCAP, p);
		str[i][stringLength(str[i]) - 1] = '\0'; // removes endline character fgets inserts
		numRows = i;
		if(stringLength(str[i]) == 0){
			break; // exits loop once blank line encountered
		}
	}
	return numRows;
}
int stringLength(char str[]){
	int count = 0;
	for(int i = 0; str[i] != '\0'; i++){
		count++;
	}
	return count;
} // my (dreyden) length fxn from project 6
void prompt(char str[][STRCAP], int rows, int cols){
	char stra[2] = {'A', '\0'}, strn[2] = {'N', '\0'}, strv[2] = {'V', '\0'};
	for(int i = 0; i < rows; i++){
		equivalency(str, i, stra, AD);
		equivalency(str, i, strn, NO);
		equivalency(str, i, strv, VE);
	}
	
}
int stringCompare(char str1[], char compared[]){
	int diff = 0;
	for(int i = 0; str1[i] != '\0'; i++){
		if(str1[i] > compared[i] || stringLength(str1) > stringLength(compared)){
			diff = 1;
		}
		if(str1[i] < compared[i] || stringLength(str1) < stringLength(compared)){
			diff = -1;
		}
	}

	return diff;
} // dreyden compare fxn (project 6)
void equivalency(char str[][STRCAP], int row, char strb[], char strc[]){
		switch(stringCompare(str[row], strb)){
			case 0:
				printf("Enter %s: ", strc);
				scanf("%s", str[row]);
				break;
		}
}
void output(char str[][STRCAP], int rows, int cols){
	for (int i = 0; i < rows; i++){
	 	printf("%s", str[i]);
	 		if(space(str, i + 1, cols) == 0){
	 			printf(" ");
	 		}
	 	}
	 	printf("\n");
}
int space(char str[][STRCAP], int row, int cols){
	int val = 0;
	char first = str[row][0];
	switch(first){
		case '.':
		case ',':
		case '?':
		case '!':
			val = 1;
			break;
	}
	return val;
}

