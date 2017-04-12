#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// #include <conio.h>

// to check if nonterminal, traverse the terminal linked list
int isNonTerminal(char * variable);
FILE * fparseTree;

// node for the object table, which is loaded in the program
struct node {
	char lexeme[100];
	char token[100];
	int row;
	int col;
	struct node * next;
};

//-----------------------------------------------------------------------
// terminals
int noOfTerminals = 0; 
struct nodeTerminal {
	char terminal[100];
	int count;
	struct nodeTerminal * next;
};

struct nodeTerminal * headTerminal = (struct nodeTerminal *) NULL;
struct nodeTerminal * endTerminal = (struct nodeTerminal *) NULL;

// initiliazation and adding of node is already in one function to save lines
struct nodeTerminal * ptrAddTNode;
void addTerminalNode(char * terminal) {
	// initialize
	ptrAddTNode = malloc(sizeof(struct nodeTerminal));
	if (ptrAddTNode == NULL) {
		printf("Something unexpected happens while loading the table.");
	} // if malloc fails :(
	else {
		strcpy(ptrAddTNode->terminal, terminal);
		ptrAddTNode->count = noOfTerminals++;
	}

	// add
	if (headTerminal == NULL) {
		headTerminal = ptrAddTNode;
		endTerminal = ptrAddTNode;
		endTerminal->next = NULL;
		return;
	} else {
		endTerminal->next = ptrAddTNode;
		endTerminal = ptrAddTNode;
		endTerminal->next = NULL;
		return;
	}
};

struct nodeTerminal * traverserT;
void traverseTerminal() {
	printf("TRAVERSING TERMINALS: \n");
	traverserT = headTerminal;
	while (traverserT != NULL) {
		printf("loaded[%d]: %s\n", traverserT->count, traverserT->terminal);
		traverserT = traverserT->next;
	}
}
//-----------------------------------------------------------------------

// non terminals
struct nodeNonTerminal {
	char nonTerminal[100];
	struct nodeNonTerminal * nextNT; // next non terminal
	struct nodeDerivation * headND; // next derivation
	struct nodeDerivation * endND;// end derivation
};

struct nodeNonTerminal * headNonTerminal = (struct nodeNonTerminal *) NULL;
struct nodeNonTerminal * endNonTerminal = (struct nodeNonTerminal *) NULL;

// node derivations
struct nodeDerivation {
	char derivation[100];
	char terminal[100];
	struct nodeDerivation * next;
};

// here the magic of logic happens
char * tempNonTerminal;
struct nodeNonTerminal * ptrNonTerminal;
struct nodeDerivation * ptrDerivation;
char * tempDerivation;
int derivationCtr = 0;
char tempTerminal = 0;
struct nodeTerminal * traverser;
void addNonTerminalNode(char * nonTerminalLine) {
	
	// save the non terminal, the following strtok are for the derivations
	tempNonTerminal = strtok(nonTerminalLine, ",");
	if (tempNonTerminal == NULL) {
		printf("tempNonTerminal is null");
	}

	// initialize
	ptrNonTerminal = malloc(sizeof(struct nodeNonTerminal));

	if (ptrNonTerminal == NULL) {
		printf("Something unexpected happens while loading the parse table.");
	} else {
		strcpy(ptrNonTerminal->nonTerminal, tempNonTerminal);
		ptrNonTerminal->headND = (struct nodeDerivation *) NULL;
		ptrNonTerminal->endND = (struct nodeDerivation *) NULL;
	}

	// add
	if (headNonTerminal == NULL) {
		headNonTerminal = ptrNonTerminal;
		endNonTerminal = ptrNonTerminal;
		endNonTerminal->nextNT = NULL;
	} else {
		endNonTerminal->nextNT = ptrNonTerminal;
		endNonTerminal = ptrNonTerminal;
		endNonTerminal->nextNT = NULL;
	}

	// add the derivations in the nodeNonTerminal
	tempDerivation = strtok(NULL, ",");
	traverser = headTerminal;
	while (tempDerivation != NULL) {
		if (strcmp(tempDerivation, "Ø") != 0) {
			ptrDerivation = malloc(sizeof(struct nodeDerivation));
			
			//printf("----%s::\t\t", ptrNonTerminal->nonTerminal);
			// printf("DERIVATION: %s\n", tempDerivation);

			if (ptrDerivation == NULL) {
				printf("Error in malloc of ptrDerivation");
			}
			else {
				strcpy(ptrDerivation->derivation, tempDerivation);
				strcpy(ptrDerivation->terminal, traverser->terminal);
			}

			// add "this hurts my eyes"
			if (ptrNonTerminal->headND == NULL) {
				ptrNonTerminal->headND = ptrDerivation;
				ptrNonTerminal->endND = ptrDerivation;
				ptrNonTerminal->endND->next = NULL;
			} else {
				ptrNonTerminal->endND->next = ptrDerivation;
				ptrNonTerminal->endND = ptrDerivation;
				ptrNonTerminal->endND->next = NULL;
			}

		}
		traverser = traverser->next;
		tempDerivation = strtok(NULL, ",");
	}
}

struct nodeDerivation * traverseND;
void traverseDerivation(struct nodeNonTerminal * toTraverse) {
	traverseND = toTraverse->headND;
	while (traverseND != NULL) {
		printf("Derivation[%s]: %s\n", traverseND->terminal, traverseND->derivation);
		traverseND = traverseND->next;
	} 
}

struct nodeNonTerminal * traverserNT;
void traverseNonTerminals() {
	traverserNT = headNonTerminal;
	while (traverserNT != NULL) {
		printf("NonTerminal: %s\n", traverserNT->nonTerminal);
		traverseDerivation(traverserNT);
		traverserNT = traverserNT->nextNT;
	}
}

//-----------------------------------------------------------------------

// for the object table
struct node * head = (struct node *) NULL;
struct node * end = (struct node *) NULL;
char stack[100][100];
int top = -1;
int hasError = 0;
int noOfErrors = 0;

int stackI = 0;
void printStack() {
	stackI = top;
	for (stackI = top; stackI >= 0; stackI--) {
		printf("STACK[%d]: %s\n", stackI, stack[stackI]);
	}
	
}

char readerPT[1000]; // to read the csv file
char * tempStrTok;
FILE * fparseTable;
void loadParseTable(char * fileName) {
	fparseTable = fopen(fileName, "r");

	if (fparseTable == NULL)
		printf("Cant open parse table");

	// load the terminals
	fgets(readerPT, 1000, fparseTable);
	// remove the \0 at the end
	readerPT[strlen(readerPT)-1] = '\0';
	tempStrTok = strtok(readerPT, ","); // discard the first value in csv && temporary storage for the terminals while being loaded
	while (tempStrTok != NULL) {
		tempStrTok = strtok(NULL, ",");
		if (tempStrTok == NULL)
			break;
		addTerminalNode(tempStrTok);
	} // end of loading the terminals


	// load the nonterminals and its derivations
	while (fgets(readerPT, 1000, fparseTable) != NULL) {
		readerPT[strlen(readerPT)-1] = '\0';
		addNonTerminalNode(readerPT);
	}
}

// functions for loading the contents of object table
struct node * ptr;
struct node * initNode(char * lexeme, char * token, int row, int col) {
	ptr = malloc(sizeof(struct node));
	if (ptr == NULL)
		return (struct node *) NULL;
	else {
		strcpy(ptr->lexeme, lexeme);
		strcpy(ptr->token, token);
		ptr->row = row;
		ptr->col = col;
	}
	return ptr;
}

void add(struct node * new) {
	if (head == NULL) {
		head = new;
		end = new;
		end->next = NULL;
	return;
	}
	end->next = new;
	end = new;
	end->next = NULL;
	return;
}

void push(char * param) {
	top++;
	strcpy(stack[top], param);
	return;
}

void pop() {
	top--;
	if (top < -1) {
		printf("Error reach end of stack.\n");
	}
	return;
}

struct nodeNonTerminal * traverserNT;
struct nodeDerivation * traverserND;
char storeTraverserND[100];
char tempDerivations[100][100];
					int i = 0;
char * derive;
char * derivationSep;
void T(char * nonTerminal, struct node * curNode) {
	// traverse the nonterminal until it find
	traverserNT = headNonTerminal;
	while (traverserNT != NULL) {
		if (strcmp(traverserNT->nonTerminal, nonTerminal) == 0) {
			traverserND = traverserNT->headND;
			while (traverserND != NULL) {
				if (strcmp(traverserND->terminal, curNode->token) == 0) {
					pop();
					strcpy(storeTraverserND, traverserND->derivation);
					
					if (strcmp(traverserND->derivation, "*") == 0) {
						printf("=> %s %s\n", nonTerminal, "/////");
						fprintf(fparseTree, "=> %s %s\n", nonTerminal, "/////");
						return;
					} else {
						// printf("%s -> %s\n", nonTerminal, traverserND->derivation);
						// fprintf(fparseTree, "%s -> %s\n", nonTerminal, traverserND->derivation);
						printf("-> %s\n", nonTerminal);
						fprintf(fparseTree, "-> %s\n", nonTerminal);
						// derivationSep = strtok(traverseND->derivation, " ");
						
						
					}
					
					derive = strtok(traverserND->derivation, " ");
					i = 0;
					while (derive != NULL) {
						strcpy(tempDerivations[i], derive);
						printf("--> %s\n", tempDerivations[i]);
						fprintf(fparseTree, "--> %s\n", tempDerivations[i]);
						i++;
						derive = strtok(NULL, " ");
					}

					strcpy(traverserND->derivation, storeTraverserND);
					for ( i = i - 1; i >= 0; i--) {
						if (strcmp(tempDerivations[i], "*") == 0) {
							break;
						}
						else {
							push(tempDerivations[i]);
						}
					}
					break;
				}
				traverserND = traverserND->next;
			}
			// traverseNonTerminals();
			if (traverserND == NULL) {
				// print the error message, & expected suggestions
				printf("Unexpected token: %s [%s] at line %d:%d\n", curNode->lexeme, curNode->token, curNode->row, curNode->col);
				traverserND = traverserNT->headND;
				printf("    Expects to a token to be: ");
				while (traverserND != NULL) {
					if (traverserND->next == NULL)
						break;
					printf("%s, ", traverserND->terminal);
					traverserND = traverserND->next;
				}
				printf("or %s.\n\n", traverserND->terminal);
				noOfErrors++; // increment no. of errors
				// pop(); // pop the top stack, to find until valid
			}
			break;
		}
		traverserNT = traverserNT->nextNT;
	}
}

FILE * fobjTable;
char reader[1000];
char * tempLex, * tempTok, * tempRow, * tempCol;
struct node * temp;
struct node * next;
int noOfErrorsTemp = 0;
char symbolTable[100];
int main(int argc, char *argv[]) {
	printf("Loading parse table");
	loadParseTable("TABLE.csv");
	// loadParseTable("PTABLE.csv");
	// traverseTerminal();
	// traverseNonTerminals();
	
//	printf("Enter name of symbol table: ");
//	
//	scanf("%s", symbolTable);

	strcpy(symbolTable, argv[1]);
	
	fobjTable = fopen(symbolTable, "r");

	fparseTree = fopen("PTREE.TXT", "w");

	if (fobjTable == NULL) {
		printf("Error in opening symbol table.\n");
		return -1; // to alert the calling program of error [ useful when lexical, parser, semantic is bundled ]
	}
		

	while (fgets(reader, 1000, fobjTable) != NULL) {
		reader[strlen(reader)-1] = '\0';
		tempLex = strtok(reader, "~");
		tempTok = strtok(NULL, " ~ ");
		tempRow = strtok(NULL, " ~ ");
		tempCol = strtok(NULL, " ~ ");
		temp = initNode(tempLex, tempTok, atoi(tempRow), atoi(tempCol));
		add(temp);
	}
	
	struct node * traverseOBJ = head;
	
	// printf("PRINTING:::::::::::::::::::::::::::::::::::::::::::::::::\n\n");
//	while (traverseOBJ != NULL) {
//		printf("TraverserOBJ %s --- %s\n", traverseOBJ->token, traverseOBJ->lexeme);
//		traverseOBJ = traverseOBJ->next;
//	}
	// printf("PRINTING:::::::::::::::::::::::::::::::::::::::::::::::::\n\n");
	
	// strcpy(stack[0], "E");
	strcpy(stack[0], "START");
	top++;

	next = head;

	while (next != NULL && top >= 0) {
		// check if there is an increased in error send by T function, if there is move to the next token
		if (noOfErrorsTemp != noOfErrors) {
			next = next->next;
			noOfErrorsTemp++;
			pop();
			continue;
		}

		// Check if terminal, can be refactored in a bool function isTerminal();
		if (isTerminal(stack[top]) == 0) {
			T(stack[top], next);
			printf("Calling t: %s --- %s\n", stack[top], next->token);
		} else {
			if (strcmp(stack[top], next->token) == 0) {
				next->lexeme[strlen(next->lexeme)-1] = '\0';
				printf("=> %s %s\n", next->token, next->lexeme);
				fprintf(fparseTree, "=> %s %s\n", next->token, next->lexeme);
				next = next->next; // increment the pointer
				pop();
				continue;
			} else {
				hasError = 1;
				next = next->next;
				pop();
				continue;
			}
		}
	}
	if (noOfErrors == 0 && top < 0) {
		printf("Parsing successful!\n");
	} else if (noOfErrors == 1) {
		// for the grammar, heil fuhrer!!!
		printf("Parsing ended with %d error.\n", noOfErrors);	
	} else {
		printf("Parsing ended with %d errors.\n", noOfErrors);
	}
	getch();
	return 0;
}

// Function to check if the STACK[TOP] is nonTerminal
struct nodeTerminal * isTerminalTemp; // the traverser variable
int isTerminal(char * variable) {
	isTerminalTemp = headTerminal;
	while (isTerminalTemp != NULL) {
		if (strcmp(variable, isTerminalTemp->terminal) == 0) {
			return 1;
		}
		isTerminalTemp = isTerminalTemp->next;
	}
	return 0;
}
