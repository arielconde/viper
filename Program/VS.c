#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void loadPTList(char *);
void addPTList(char *);
void printlistPT();

struct listNode {
	char name[20];
	char nodeType[10];
	char value[50]; // @base = 2, 2 is the value
	char type[10]; // @base: integer; integer is the type
	char lexval[50]; // @base = 2, 2 is the lexval original from the symbol table
	char expect_type[10];
	char varname[30];
	char optr[30];
	struct listNode * next;
	struct listNode * child;
	struct listNode * childEnd;
	struct listNode * sibling;
	struct listNode * derive;
};

void traverseChildren(struct listNode *);

struct listNode * head = (struct listNode *) NULL;
struct listNode * end = (struct listNode *) NULL;

void loadPTList(char * fname) {
	FILE * fpt = fopen(fname, "r");
	char reader[100];
	char pass[100];
	while (fgets(reader, 100, fpt) != NULL) {
		reader[strlen(reader)-1] = '\0';
		if (strlen(reader) <= 0)
			return;
		// printf("calling addPTList\n");
		// strcpy(pass, strtok(reader, "\n"));
		// printf("len: %d ;;; %s\n", strlen(reader), pass);
		addPTList(reader);
	}
	fclose(fpt);
	return;
}

// add an item to the parse tree list
void addPTList(char * item) {
	struct listNode * temp = (struct listNode *) calloc(1, sizeof(struct listNode));
	// parse the item, get type, text value :)
	char nodeType[10];
	char name[20];
	strcpy(nodeType, strtok(item, " "));
	strcpy(name, strtok(NULL, " "));
	char value[10];
	strcpy(temp->nodeType, nodeType);
	strcpy(temp->name, name);

	// => is a producing node, set the value to " "
	if (strcmp(nodeType, "=>") == 0) {
		strcpy(value, strtok(NULL, " "));
		strcpy(temp->value, value);
		strcpy(temp->lexval, value);
	}

	if (head == NULL) {
		head = temp;
		end = temp;
		end->next = NULL;
	} else {
		end->next = temp;
		end = temp;
		end->next = NULL;
	}
}

void printlistPT() {
	struct listNode * traverser = head;
	printf("Traversing list:\n");
	while (traverser != NULL) {
		if (strcmp(traverser->nodeType, "=>") == 0)
			printf("nodetype: %s ::: name: %s value: %s\n", traverser->nodeType, traverser->name, traverser->value);
		else
			printf("nodetype: %s ::: name: %s\n", traverser->nodeType, traverser->name);
		traverser = traverser->next;
	}
}

struct listNode * scanner = (struct listNode *) NULL;

void makeTree(struct listNode * root) {
	// printf("makeTree(root->name) %s:%s\n", root->nodeType, root->name);
	printf("Making tree for %s\n", root->name);
	struct listNode * temp;
	int nOfChildren = 0;
	if (strcmp(root->nodeType, "->") == 0) {
		scanner = scanner->next; // moves to the next which is the first child
		root->child = scanner; // set the first child
		printf("Set of the child of %s to %s\n", root->name, scanner->name);
		nOfChildren++; // increase the cound of children
		temp = root->child; // temporary to go to traverse child siblings
		scanner = scanner->next; // points to the next item, whether to be -->, -> or =>
		while (strcmp(scanner->nodeType, "-->") == 0) {
			printf("Child of %s is %s\n", root->name, scanner->name);
			temp->sibling = scanner;
			root->childEnd = temp->sibling;
			temp = temp->sibling;
			scanner = scanner->next;
			nOfChildren++;
		}
		int i = 0;
		temp = root->child; // temp is ther traverser for the child

		for (i = 0; i < nOfChildren && scanner != NULL; i++) {
			if (strcmp(scanner->nodeType, "=>") == 0 && i < nOfChildren) {
				printf("Found value node of %s from \troot: \t%s\n", scanner->value, root->name);
				strcpy(temp->value, scanner->value);
				if (i >= nOfChildren) {

				}
				temp = temp->sibling;
				scanner = scanner->next;
			} else if (strcmp(scanner->nodeType, "->") == 0) {
				temp->derive = scanner;

				// -> is a parent node, calls makeTree on it
				printf("Found prod node of %s from \troot: \t%s\n", scanner->name, root->name);
				makeTree(temp->derive);
				if (temp->sibling != NULL) {

				} else {
					break;
				}

			} else if (strcmp(scanner->nodeType, "-->") == 0) {
				// this is not possible unless an something is wrong :(
				printf("Found this weird shit %s\n", scanner->name);
			} else {
				// printf("OHHHH NO!!!!!!!");
				// printf("%d, %d: %s: evaluating\n", nOfChildren, i, root->name);	
				// scanner = scanner->next;
			}
		}
	}
}

/*
	The approach is to scan all child, then take the returns of what ever child
	is needed of the semantic rules
*/
void evaluate(struct listNode * root) {
	printf("\n\nEVALUATING:::::::::::\n");
	struct listNode * childTraverser;
	struct listNode * retCatch; // variable to catch the return of rules
	childTraverser = root->child;
	// root->name[strlen(root->name)-1] = '\0';
	printf("root->name: ");
	puts(root->name);
	// printf("len: %d size:%d\n", strlen(root->name), sizeof(root->name));

	/* --------------------------------------------------------- */
	/* -- CHECK THE FIRST CHILD THEN APPLY THE SEMANTIC RULES -- */
	/* --------------------------------------------------------- */
	
	// START - comment the semantic rules if there is time :)
	if (strcmp(root->name, "START") == 0) {
		// since this production (START) has no semantic rules
		// just evaluate is childrens
		childTraverser = root->child;
		while (childTraverser) {
			// printf("Checking child: %s\n", childTraverser->name);
			if (childTraverser->derive)
				evaluate(childTraverser->derive);
			puts(childTraverser->value);
			childTraverser = childTraverser->sibling;
		}
	}

	// STMT
	else if (strcmp(root->name, "STMT") == 0) {
		
		// FN_ID
		if (strcmp(root->child->name, "FN_ID") == 0) {
			childTraverser = root->child;
			while (childTraverser) {
				if (childTraverser->derive && strcmp(childTraverser->derive->name, "FN_ARG") == 0) {
					evaluate(childTraverser->derive);
					strcpy(root->child->type, childTraverser->derive->type);
				}
				if (childTraverser->derive && strcmp(childTraverser->derive->name, "STMTS") == 0) {
					evaluate(childTraverser->derive);
				}
				childTraverser = childTraverser->sibling;
			}	
		}
		
		// IN
		if (strcmp(root->child->name, "IN") == 0) {
			childTraverser = root->child;
			while (childTraverser) {
				if (childTraverser->derive && strcmp(childTraverser->derive->name, "STMTS") == 0) {
					evaluate(childTraverser->derive);
				}
			}
		}

		// OUT
		if (strcmp(root->child->name, "OUT") == 0) {
			
		}

		// LET 
		if (strcmp(root->child->name, "LET") == 0) {
			childTraverser = root->child;
			struct listNode * letVarID;
			while (childTraverser) {
				if (strcmp(childTraverser->name, "VAR_ID") == 0) {
					letVarID = childTraverser;
				}
				if (childTraverser->derive && strcmp(childTraverser->derive->name, "LITERAL") == 0) {
					evaluate(childTraverser->derive);
					strcpy(letVarID->value, childTraverser->derive->value);
				}
				if (childTraverser->derive && strcmp(childTraverser->derive->name, "STMTS") == 0) {
					evaluate(childTraverser->derive);
				}
			}
		}

		
		// if (VAR_ID) --- Declaration production
		// STMT -> VAR_ID.type == STMT2.type
		if (strcmp(root->child->name, "VAR_ID") == 0) {
			printf("Variable Declaration\n");
			childTraverser = root->child; // VAR_ID
			// STMT type is declaration
			strcpy(root->value, root->child->value);
			
			// loop while there is a child
			while (childTraverser) {
				printf("Checking child %s of %s\n", childTraverser->name, root->name);
				
				if (strcmp(childTraverser->name, "VAR_ID") == 0) {
					printf("Variable name is: %s\n", childTraverser->value);
				}
				
				if (childTraverser->derive && strcmp(childTraverser->derive->name, "STMT2") == 0) {
					printf("STMT2 Found: evaluating\n");
					evaluate(childTraverser->derive); // this give type to STMT2
					printf("Type: %s\n", childTraverser->derive->type);
					strcpy(root->type, childTraverser->derive->type);
				}
				childTraverser = childTraverser->sibling;
			}
		}
		
		// FOR
		if (strcmp(root->child->name, "FOR") == 0) {
			
		}
		

	}

	// STMTS
	else if (strcmp(root->name, "STMTS") == 0) {
		printf("Now at stmts");
		if (!root->child)
			return;
		if (strcmp(root->child->name, "STMT") == 0) {
			evaluate(root->child->derive);
		} else {
			return;
		}
	}
	
	
	// STMT2
	else if (strcmp(root->name, "STMT2") == 0) {
		printf("Here at stmt2::: %s\n", root->child->name);
		if (strcmp(root->child->name, "COLON") == 0) {
			printf("A colon is found!!!\n");
			childTraverser = root->child;
			
			// list the kids
			while (childTraverser) {
				printf("Kids of %s :: %s\n", root->name, childTraverser->name);
				childTraverser = childTraverser->sibling;
			}
			
			
			childTraverser = root->child;
			while (childTraverser) {
				// set the data type
				printf("Kids of STMT2: %s\n", childTraverser->name);	
				if (childTraverser->derive && strcmp(childTraverser->name, "DATA_TYPE") == 0) {
					// printf("%s has a derive\n", childTraverser->name);
					evaluate(childTraverser);
					strcpy(root->type, childTraverser->derive->type);
					printf("DATATYPE is: %s\n", childTraverser->derive->value);
				}
				if (childTraverser->derive && strcmp(childTraverser->name, "STMT3") == 0) {
					// printf("Found stmt3 from parent %s\n", root->name);
					evaluate(childTraverser->derive);
				}
				childTraverser = childTraverser->sibling;
			}
			printf(" is declared");
		}
	}
	
	// STMT3
	else if (strcmp(root->name, "STMT3") == 0) {
		// SCOLON
		printf("Here at stmt3");
		if (strcmp(root->child->name, "SCOLON") == 0) {
			printf("Fould a colon");
			return;
			childTraverser = root->child;
			while (childTraverser) {
				if (childTraverser->derive && strcmp(childTraverser->derive->name, "STMTS") == 0) {
					return;
					evaluate(childTraverser->derive);
				}
			}
		}
		
		//EQUALS
		if(strcmp(root->child->name, "EQUALS") == 0) {
			childTraverser = root->child;
			while(childTraverser) {
				if (childTraverser->derive && strcmp(childTraverser->derive->name, "LITERAL") == 0) {
					evaluate(childTraverser->derive); 
					printf("Type: %s\n", childTraverser->derive->type);
					strcpy(root->type, childTraverser->derive->expect_type);
				}

				if (childTraverser->derive && strcmp(childTraverser->derive->name, "STMTS") == 0) {
					evaluate(childTraverser->derive);
				}
			
			//	childTraverser = childTraverser->sibling;
			}
		}
		// ARRAY
		if(strcmp(root->child->name, "ARRAY") == 0) {
			childTraverser = root->child;
			//while(childTraverser) {
			//	if(childTraverser->derive && strcmp(childTraverser->derive->name, "") {}
			//}
			evaluate(childTraverser->derive);
			strcpy(root->type, childTraverser->derive->type); // ARRAY.type = STMT3.type
		}
	}
	 
	
	// STMT4
	else if (strcmp(root->name, "STMT4") == 0) {
		if (strcmp(root->child->name, "LITERAL") == 0) {
			childTraverser = root->child;
			while (childTraverser) {
				
			}
			evaluate(childTraverser->derive);
			if (strcmp(root->type, childTraverser->type) != 0) {
				printf("Data type mismatch");
			}
			
			//strcpy(root->type, childTraverser->expect_type);	// LITERAL.expected_type = STMT4.type
		}
		
		if (childTraverser->derive && strcmp(childTraverser->derive->name, "STMTS") == 0) {
			evaluate(childTraverser->derive);
		}
				
		if (strcmp(root->child->name, "FN_CALL") == 0) {
			childTraverser = root->child;
			evaluate(childTraverser->derive);
		}
	}
	
	// DATA_TYPE
	else if (strcmp(root->name, "DATA_TYPE") == 0) {
		return;
		if (strcmp(root->child->name, "INT") == 0) {
			strcpy(root->type, "integer");
		} else if (strcmp(root->child->name, "REAL") == 0) {
			strcpy(root->type, "real");
		} else if (strcmp(root->child->name, "CHAR") == 0) {
			strcpy(root->type, "char");
		} else if (strcmp(root->child->name, "CHARS") == 0) {
			strcpy(root->type, "chars");
		} else if (strcmp(root->child->name, "BOOL") == 0) {
			strcpy(root->type, "boolean");
		}
	}
	
	else {
		printf("%s has no rules.\n", root->name);
		return NULL;
	}
}

FILE * fchildren;

void traverseChildren(struct listNode * parent) {
	struct listNode * temp = parent->child;
	printf("Children of ");
	fprintf(fchildren, "\n-----------\nChildren of %s\n", parent->name);
	puts(parent->name);
	char tempStr[100];
	while (temp != NULL) {
		strcpy(tempStr, temp->name);
		// tempStr[strlen(tempStr)-1] = '\0';
		printf("%s, ", tempStr);
		fprintf(fchildren, "%s, ", tempStr);
		temp = temp->sibling;
	}
	printf("\n");

	temp = parent->child;
	// will print the children and its derivations
	while (temp != NULL) {
		if (temp->derive != NULL && strcmp(temp->derive->nodeType, "->") == 0) {
			printf("\n\n");
			puts(parent->name);
			printf("has producing child %s\n", temp->derive->name);
			printf("traversing it now");
			traverseChildren(temp->derive);
			printf("end of traversing %s\n", temp->derive->name);
		} else {
			printf("\n\n\nParent: %s\n", parent->name);
			printf("Children: ");
			puts(temp->name);
			printf("value: ");
			puts(temp->value);
			printf("Node Type: ");
			puts(temp->nodeType);
		}
		// printf("moves to next sibling: %s to %s\n", temp->name, temp->sibling->name);
		temp = temp->sibling;
	}
	// puts(parent->name);
	// printf("%s\n", parent->child->name);
}

int checkIfTerminal(char name[]) {
	// load the terminals from the parse table
	// do some comparison here
	return 1;
}

int main(int argc, char *argv[]) {
	fchildren = fopen("CHILDREN.TXT", "w");
	loadPTList("PTREE.TXT");
	printlistPT();
	// printf("setting scanner to head\n");
	scanner = head;
	makeTree(head);
	printf("Traversing the root\n");
	traverseChildren(head);
	printf("\n\nend traversing\n");
	evaluate(head);
	getch();
	return 0;
}
