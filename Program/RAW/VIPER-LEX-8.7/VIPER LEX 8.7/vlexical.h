#include<stdio.h>


char krTerminal[] = {' ', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '=', '_', '+', '~', '`', '{', '}', '[', ']', ':', ';', '\'', '\"', '|', '\\', '<', ',', '>', '.', '\?', '/', '\n', '\t'};
int finalState[] = {7,15,20,22,25,30,35,38,41,47,50,53,77,60,62,67,71,76,81,87,91,97,102,107,109,113,119,125,144,207,127,132,135,138,213,147,150,152,154,156,158,160,162,164,166,168,171,174,176,178,181,183,185,187,189,191,194,195,196,197,198,199,200,202};						
char idTerminal[] = {' ', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '=', '+', '~', '`', '{', '}', '[', ']', ':', ';', '\'', '\"', '|', '\\', '<', ',', '>', '.', '\?', '/', '\n', '\t'};
char flTerminal[] = {' ', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '=', '+', '~', '`', '{', '}', '[', ']', ':', ';', '\'', '\"', '|', '\\', '<', ',', '>', '\?', '/', '\n', '\t'};

struct Node {

    char value;				// character
    int state;				// number
    int final;				// 1 or 0
    struct Node *nextChar;	// node

};


	int _isDelimiter(char ch) {
		
		int index, delim =0;
		
		for(index = 0; krTerminal[index] != '\0'; index++) {
			
			if( ch == krTerminal[index] ) {
				
				delim = 1;
				break;
				
			} // if( ch == krTerminal[index] )
			
		} // for(index = 0; krTerminal[index] != '\0'; index++)
		
		return delim;
		
	} // int isDelimiter(char ch)


   int _checkState(int state) {
		
		int index;
		int final = 0;
		
		for(index = 0; finalState[index] != '\0'; index++) {
			
			if( state == finalState[index] ) {
				
				final = 1;
				break;
				
			} // if( state == finalState[index] )
			
		} // for(index = 0; finalState[index]; index++)
		
   } // void checkState(int state)


   int _isIdDelimiter(char ch) {
		
		int index, delim =0;
		
		for(index = 0; idTerminal[index] != '\0'; index++) {
			
			if( ch == idTerminal[index] ) {
				
				delim = 1;
				break;
				
			} // if( ch == krTerminal[index] )
			
		} // for(index = 0; krTerminal[index] != '\0'; index++)
		
		return delim;
		
	} // int isDelimiter(char ch)
	
	int _isFloatDelimiter(char ch) {
		
		int index, delim =0;
		
		for(index = 0; flTerminal[index] != '\0'; index++) {
			
			if( ch == flTerminal[index] ) {
				
				delim = 1;
				break;
				
			} // if( ch == krTerminal[index] )
			
		} // for(index = 0; krTerminal[index] != '\0'; index++)
		
		return delim;
		
	} // int isDelimiter(char ch)
