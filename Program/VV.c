#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>


struct node {
	char lexeme[30];
	char token[30];
	int row;
	int isUsed;
	struct node * next;
};

struct node * head = (struct node *) NULL;
struct node * end = (struct node *) NULL;
FILE * fpTable;

void add(char * item) {
	// initialize
	struct node * temp = (struct node *) malloc(sizeof(struct node));
	char * tempLex, * tempTok, * tempRow, * tempCol;
	tempLex = strtok(item, " ~ ");
	tempTok = strtok(NULL, " ~ ");
	tempRow = strtok(NULL, " ~ ");
	
	strcpy(temp->token, tempTok);
	strcpy(temp->lexeme, tempLex);
	temp->row = atoi(tempRow);

	// add
	// printf("Adding\n");
	if (head == NULL) {
		head = temp;
		end = temp;
		end->next = NULL;
		return;
	} else {
		end->next = temp;
		end = temp;
		end->next = NULL;
		return;
	}
}

void printList() {
	struct node * traverser = head;
	while (traverser) {
		printf("%s %s\n", traverser->lexeme, traverser->token);
		traverser = traverser->next;
	}
}


void loadSymbolTable(char *fname) {
	fpTable = fopen(fname, "r");
	char reader[100];
	while (fgets(reader, 100, fpTable) != NULL) {
		reader[strlen(reader)-1] = '\0';
		add(reader);
	}
}

int scope = 0;
char stack[100][100][100];
int stackCtr[100];

void checkVariables() {
	struct node * checker = head;
	while (checker) {
		if (strcmp(checker->token, "VAR_ID") == 0 && strcmp(checker->next->token, "COLON") == 0) {
			printf("New variable declaration: %s\n", checker->lexeme);
			addToList(checker->lexeme);
		}
		else if (strcmp(checker->token, "L_BRC") == 0 || strcmp(checker->token, "IS") == 0) {
			newList();
		}
		else if (strcmp(checker->token, "R_BRC") == 0 || strcmp(checker->token, "END") == 0) {
			destroyList(); // show the unused variables here
		}
		else if (strcmp(checker->token, "VAR_ID") == 0) {
			if (checkIfValid(checker->lexeme) == 1) {
			 // check against the stack
			// say if used
				printf("%s is valid\n", checker->lexeme);
				checker = checker->next;
				continue;
			} else {
				printf("Undeclared variable: %s\n", checker->lexeme);
			}
		}
		else {
			
		}
		checker = checker->next;
	}
}

//int scope = 0;
//char stack[100][100][100];
//int stackCtr[100];

void addToList(char * var) {
	strcpy(stack[scope][stackCtr[scope]], var);
	stackCtr[scope]++;
}

void newList() {
	scope++;
}

void destroyList() {
	stackCtr[scope] = 0;
	scope--;
}

int checkIfValid(char * var) {
	int i = 0;
	int j = 0;
	// printf("Checking if %s is valid.\n", var);
	for (i = 0; i < scope; i++) {
		for (j = 0; j < stackCtr[scope]; j++) {
			// printf("Comparing: %s:%s\n", var, stack[i][j]);
			if (strcmp(stack[i][j], var) == 0) {
				// printf("%s is valid\n", var);
				return 1;
			}
		}
	}
	return 0;
}

int main(int argc, char *argv[]) {
	
	char command[100];
	char symbolTableFile[100];
	// sprintf(symbolTableFile, "symbolTable_%s", argv[1]);
	loadSymbolTable(argv[1]);
	// printList();
	// check for variable declaration, scope, 
	checkVariables();
	printf("Done checking variables.\n");
	// done checking variables
	getch();

	return 0;	
}
