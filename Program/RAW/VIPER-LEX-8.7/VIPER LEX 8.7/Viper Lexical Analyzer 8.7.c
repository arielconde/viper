#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include"vlexical.h"

void lexicalAnalyzer(char file[]);
void stateMachine(char ch);
void createStartState(char ch);
void createNextState(char ch);
void displayTokenClass(int final, int state, int line);

int lineNumber = 1;
int hasError = 0;
FILE *ptr = NULL;
FILE *ptr2 = NULL;
FILE *fOutput = NULL;
char nextCh;

struct Node *currState;

int main() {
	
	char inputFile[100];
    int exist = 0;

    printf("\nInput .vpr file: ");
    scanf("%s", &inputFile);
    printf("\n");

    FILE *file = fopen(inputFile,"r");
    
    if( file != NULL ) {
        
    	fclose(file);
    	
		if( (strcmp(strrchr(inputFile,'.')+1,"vpr"))==0 ) {
			lexicalAnalyzer(inputFile);
		} else {
			printf("Not a Viper file.\n");
		} // if(viperExtension(fileInput))
		
    } else {
    	
        printf("File does not exist!");
    	fclose(file);
        
    } // if( f!=NULL )
	
    getch();

	return 0;
	
} // int main()


	void lexicalAnalyzer(char file[]) {
		
		char output[15] = "symbolTable_"; 
		fOutput = fopen(strcat(output,file),"w");
		
		ptr = fopen(file,"r");
		
		ptr2 = fopen(file,"r");
		nextCh = fgetc(ptr2); // lookahead pointer
		
		char ch;
		
		while( (ch = fgetc(ptr)) != EOF ) {
			
			stateMachine(ch);
			
		} // while( (ch = fgetc(ptr)) != EOF )
		
		fclose(ptr);
		
		if(hasError == 1) {
			printf("\n\n...\n\n\nINVALID LEXEME DETECTED. CANNOT CONTINUE TO PARSING PHASE.\n");
		}else{
			printf("\n\n...\n\n\nNO INVALID LEXEME DETECTED. CODE READY TO BE PARSE.\n");
			// INSERT FUNCTION CALL GOING TO PARSER
		}
		
	} // void lexicalAnalyzer(char file[])
	
	
	void createStartState(char ch) {
		
		currState = (struct Node*)malloc(sizeof(struct Node));
    	currState -> value = ch;
   		currState -> state = 1;
    	currState -> final = 0;
    	currState -> nextChar = NULL;
		
	} // void createStartState(char ch)
	
	
	void createNextState(char ch) {

    	struct Node *nextState = (struct Node*)malloc(sizeof(struct Node));
    	nextState -> value = ch;
    	nextState -> final = 0;
    	nextState -> nextChar = NULL;

    	currState -> nextChar = nextState;
    	currState = currState -> nextChar;

	} // void createNextState(char ch)
	
	
	void getNextInput() {
	
		char ch = fgetc(ptr);
		createNextState(ch);
		nextCh = fgetc(ptr2);
	
	} // void getNextChar()
	
	
	void stateMachine(char ch) {
		
		char e, eo;
		int n = 0;
		createStartState(ch);
		nextCh = fgetc(ptr2);
		
		switch( currState -> value ) {
			
			case 'a' : {
				
				n = 1;
				currState -> state = 2;
				printf("\n%c", currState -> value);
				fprintf(fOutput,"%c",currState -> value);
				
				if ( _isDelimiter(nextCh) ) {
					
					currState -> final  = _checkState( currState -> state );
					
				} else {
					
					getNextInput();
					
					switch( currState -> value ) {
						
						case 'r' : {
							
							currState -> state = 3;
							printf("%c", currState -> value);
							fprintf(fOutput,"%c",currState -> value);
							
							if( _isDelimiter(nextCh) ) {
					
								currState -> final  = _checkState( currState -> state );
					
							} else {
								
								getNextInput();
					
								switch( currState -> value ) {
						
									case 'r' : {
							
										currState -> state = 4;
										printf("%c", currState -> value);
										fprintf(fOutput,"%c",currState -> value);
							
										if( _isDelimiter(nextCh) ) {
					
											currState -> final  = _checkState( currState -> state );
								
										} else {
								
											getNextInput();
					
											switch( currState -> value ) {
						
												case 'a' : {
							
													currState -> state = 5;
													printf("%c", currState -> value);
													fprintf(fOutput,"%c",currState -> value);
							
													if( _isDelimiter(nextCh) ) {
					
														currState -> final  = _checkState( currState -> state );
								
													} else {
								
														getNextInput();
					
														switch( currState -> value ) {
						
															case 'y' : {
							
																currState -> state = 6;
																printf("%c", currState -> value);
																fprintf(fOutput,"%c",currState -> value);
														
																if( _isDelimiter(nextCh) || ((e=fgetc(ptr)) == EOF) ) {
																
																	currState -> state = 7;
																	currState -> final  = _checkState( currState -> state );
																	
																} // if( _isDelimiter(nextCh) || ((e=fgetc(ptr)) == EOF) )
																
																break;
						
															} // case 'y'
					
														} // switch( currState -> value )
								
													} // if( isDelimiter(nextCh) )
						
													break;
						
												} // case 'a'
					
											} // switch( currState -> value )
										
										} // if( isDelimiter(nextCh) )
						
										break;
						
									} // case 'r'
					
								} // switch( currState -> value )
								
							} // if( isDelimiter(nextCh) )
							
							break;
							
						} // case 'r'
						
					} // switch( currState -> value )
			
				} // if ( _isDelimiter(nextCh) )
				
				break;
			
			} // case 'a'
			
			
			case 'b' : {
				
				n = 1;
				currState -> state = 8;
				printf("\n%c", currState -> value);
				fprintf(fOutput,"%c",currState -> value);
				
				if( _isDelimiter(nextCh) ) {
					
					currState -> final  = _checkState( currState -> state );
					
				} else {
					
					getNextInput();
					
					switch( currState -> value ) {
						
						case 'o' : {
							
							currState -> state = 9;
							printf("%c", currState -> value);
							fprintf(fOutput,"%c",currState -> value);
							
							if( _isDelimiter(nextCh) ) {
					
								currState -> final  = _checkState( currState -> state );
					
							} else {
								
								getNextInput();
					
								switch( currState -> value ) {
						
									case 'o' : {
							
										printf("%c", currState -> value);
										fprintf(fOutput,"%c",currState -> value);
										currState -> state = 10;
							
										if( _isDelimiter(nextCh) ) {
					
											currState -> final  = _checkState( currState -> state );
								
										} else {
								
											getNextInput();
					
											switch( currState -> value ) {
						
												case 'l' : {
							
													currState -> state = 11;
													printf("%c", currState -> value);
													fprintf(fOutput,"%c",currState -> value);
							
													if( _isDelimiter(nextCh) ) {
					
														currState -> final  = _checkState( currState -> state );
								
													} else {
								
														getNextInput();
					
														switch( currState -> value ) {
						
															case 'e' : {
							
																currState -> state = 12;
																printf("%c", currState -> value);
																fprintf(fOutput,"%c",currState -> value);
														
																if( _isDelimiter(nextCh) ) {
					
																	currState -> final  = _checkState( currState -> state );
								
																} else {
								
																	getNextInput();
					
																	switch( currState -> value ) {
						
																		case 'a' : {
							
																			currState -> state = 13;
																			printf("%c", currState -> value);
																			fprintf(fOutput,"%c",currState -> value);
																	
																			if( _isDelimiter(nextCh) ) {
					
																				currState -> final  = _checkState( currState -> state );
								
																			} else {
								
																				getNextInput();
					
																				switch( currState -> value ) {
						
																					case 'n' : {
							
																						currState -> state = 14;
																						printf("%c", currState -> value);
																						fprintf(fOutput,"%c",currState -> value);
																	
																						if( _isDelimiter(nextCh) || ((e=fgetc(ptr)) == EOF) ) {
					
																							currState -> state = 15;
																							currState -> final  = currState -> final  = _checkState(currState -> state);
										
																						
																						} // if( isDelimiter(nextCh) )
																			
																					break;
						
																					} // case 'n'
								
																				} // switch( currState -> value )
								
																			} // if( isDelimiter(nextCh) )
														
															
																			break;
						
																		} // case 'a'
					
																	} // switch( currState -> value )
								
																} // if( isDelimiter(nextCh) )
																
																
																break;
						
															} // case 'e'
					
														} // switch( currState -> value )
								
													} // if( isDelimiter(nextCh) )
						
													break;
						
												} // case 'l'
					
											} // switch( currState -> value )
										
										} // if( isDelimiter(nextCh) )
						
										break;
						
									} // case 'o'
					
								} // switch( currState -> value )
								
							} // if( isDelimiter(nextCh) )
						
							break;
						
						} // case 'o'
					
					} // switch( currState -> value )
					
				} // if( isDelimiter(nextCh) )
				
				break;
			
			} // case 'b'
			
			
			case 'c' : {
				
				n = 1;
				currState -> state = 16;
				printf("\n%c", currState -> value);
				fprintf(fOutput,"%c",currState -> value);
				
				if( _isDelimiter(nextCh) ) {
					
					currState -> final  = _checkState( currState -> state );
					
				} else {
					
					getNextInput();
					
					switch( currState -> value ) {
						
						case 'h' : {
							
							currState -> state = 17;
							printf("%c", currState -> value);
							fprintf(fOutput,"%c",currState -> value);
							
							if( _isDelimiter(nextCh) ) {
					
								currState -> final  = _checkState( currState -> state );
					
							} else {
								
								getNextInput();
					
								switch( currState -> value ) {
						
									case 'a' : {
							
										currState -> state = 18;
										printf("%c", currState -> value);
										fprintf(fOutput,"%c",currState -> value);
							
										if( _isDelimiter(nextCh) ) {
					
											currState -> final  = _checkState( currState -> state );
								
										} else {
								
											getNextInput();
					
											switch( currState -> value ) {
						
												case 'r' : {
							
													currState -> state = 19;
													printf("%c", currState -> value);
													fprintf(fOutput,"%c",currState -> value);
							
													if( _isDelimiter(nextCh) || ((e=fgetc(ptr)) == EOF) ) {
					
														currState -> state = 20;
														currState -> final = _checkState( currState -> state );
													
													} else if ( nextCh == 's') {
								
														getNextInput();
					
														printf("s");
														fprintf(fOutput,"s",currState -> value);
														currState -> state = 21;
														
														if( _isDelimiter(nextCh) || ((eo=fgetc(ptr)) == EOF) ) {
					
															currState -> state = 22;
															currState -> final = _checkState( currState -> state );
															nextCh = fgetc(ptr2);
						
														} // if( isDelimiter(nextCh) )
																
														
													} // if( isDelimiter(nextCh) )
													
													break;
						
												} // case 'r'
					
											} // switch( currState -> value )
										
										} // if( isDelimiter(nextCh) )
						
										break;
						
									} // case 'a'
					
								} // switch( currState -> value )
								
							} // if( isDelimiter(nextCh) )
						
							break;
						
						} // case 'h'
					
					} // switch( currState -> value )
					
				} // if( isDelimiter(nextCh) )
				
				break;
			
			} // case 'c'
			 
			 
			case 'd' : {
				
				n = 1;
				currState -> state = 23;
				printf("\n%c", currState -> value);
				fprintf(fOutput,"%c",currState -> value);
				
				if( _isDelimiter(nextCh) ) {
					
					currState -> final = _checkState( currState -> state );
					
				} else {
					
					getNextInput();
					
					switch( currState -> value ) {
						
						case 'o' : {
							
							currState -> state = 24;
							printf("%c", currState -> value);
							fprintf(fOutput,"%c",currState -> value);
							
							if( _isDelimiter(nextCh) ) {
					
								currState -> state = 25;
								currState -> final = _checkState( currState -> state );
					
							} else {
								
								getNextInput();
								
								switch( currState -> value ) {
						
									case 'w' : {
							
										currState -> state = 26;
										printf("%c", currState -> value);
										fprintf(fOutput,"%c",currState -> value);
							
										if( _isDelimiter(nextCh) ) {
					
											currState -> final = _checkState( currState -> state );
								
										} else {
								
											getNextInput();
					
											switch( currState -> value ) {
						
												case 'n' : {
							
													currState -> state = 27;
													printf("%c", currState -> value);
													fprintf(fOutput,"%c",currState -> value);
							
													if( _isDelimiter(nextCh) ) {
					
														currState -> final = _checkState( currState -> state );
								
													} else {
								
														getNextInput();
					
														switch( currState -> value ) {
						
															case 't' : {
							
																currState -> state = 28;
																printf("%c", currState -> value);
																fprintf(fOutput,"%c",currState -> value);
														
																if( _isDelimiter(nextCh) ) {
					
																	currState -> final = _checkState( currState -> state );
								
																} else {
								
																	getNextInput();
					
																	switch( currState -> value ) {
						
																		case 'o' : {
							
																			currState -> state = 29;
																			printf("%c", currState -> value);
																			fprintf(fOutput,"%c",currState -> value);
																	
																			if( _isDelimiter(nextCh) || ((e=fgetc(ptr)) == EOF) ) {
					
																				currState -> state = 30;
																				currState -> final = _checkState( currState -> state );
							
																			} // if( isDelimiter(nextCh) )
														
																			break;
						
																		} // case 'r'
					
																	} // switch( currState -> value )
								
																} // if( isDelimiter(nextCh) )
																
																
																break;
						
															} // case 'r'
					
														} // switch( currState -> value )
								
													} // if( isDelimiter(nextCh) )
						
													break;
						
												} // case 'r'
					
											} // switch( currState -> value )
										
										} // if( isDelimiter(nextCh) )
						
										break;
						
									} // case 'r'
					
								} // switch( currState -> value )
								
							} // if( isDelimiter(nextCh) )
						
						
							break;
						
						} // case 'r'
					
					} // switch( currState -> value )
					
				} // if( isDelimiter(nextCh) )
				
				
				break;
			
			}
			
			
			case 'e' : {
				
				n = 1;
				currState -> state = 31;
				printf("\n%c", currState -> value);
				fprintf(fOutput,"%c",currState -> value);
				
				if( _isDelimiter(nextCh) ) {
					
					currState -> final = _checkState( currState -> state );
					
				} else {
					
					getNextInput();
					
					switch( currState -> value ) {
						
						case 'l' : {
							
							currState -> state = 32;
							printf("%c", currState -> value);
							fprintf(fOutput,"%c",currState -> value);
							
							if( _isDelimiter(nextCh) ) {
					
								currState -> final = _checkState( currState -> state );
					
							} else {
								
								getNextInput();
					
								switch( currState -> value ) {
						
									case 's' : {
							
										printf("%c", currState -> value);
										fprintf(fOutput,"%c",currState -> value);	
										currState -> state = 33;
							
										if( _isDelimiter(nextCh) ) {
					
											currState -> final = _checkState( currState -> state );
								
										} else {
								
											getNextInput();
					
											switch( currState -> value ) {
						
												case 'e' : {
							
													printf("%c", currState -> value);
													fprintf(fOutput,"%c",currState -> value);
													currState -> state = 34;
							
													if( _isDelimiter(nextCh) || (e=fgetc(ptr)==EOF)) {
					
														currState -> state = 35;
														currState -> final = _checkState( currState -> state );
								
													} // if( isDelimiter(nextCh) )
						
													break;
						
												} // case 'r'
												
												case 'i' : {
													
													printf("%c", currState -> value);
													fprintf(fOutput,"%c",currState -> value);
													currState -> state = 36;
													
													if( _isDelimiter(nextCh) ) {
					
														currState -> final = _checkState( currState -> state );
								
													} else {
								
														getNextInput();
								
														switch( currState -> value ) {
						
															case 'f' : {
							
																printf("%c", currState -> value);
																fprintf(fOutput,"%c",currState -> value);
																currState -> state = 37;
							
																if( _isDelimiter(nextCh) || (e=fgetc(ptr)==EOF)) {
					
																	currState -> state = 38;
																	currState -> final = _checkState( currState -> state );
								
																} // if( isDelimiter(nextCh) )
						
																break;
						
															} // case 'r'
														
														} // switch( currState -> value )
										
													} // if( isDelimiter(nextCh) )
						
													
													break;
													
												}
					
											} // switch( currState -> value )
										
										} // if( isDelimiter(nextCh) )
						
										break;
						
									} // case 'r'
					
								} // switch( currState -> value )
								
							} // if( isDelimiter(nextCh) )
						
							break;
						
						} // case 'r'
					
						case 'n' : {
							
							printf("%c", currState -> value);
							fprintf(fOutput,"%c",currState -> value);
							currState -> state = 39;
							
							if( _isDelimiter(nextCh) ) {
					
								currState -> final = _checkState( currState -> state );
					
							} else {
								
								getNextInput();
					
								switch( currState -> value ) {
						
									case 'd' : {
							
										printf("%c", currState -> value);
										fprintf(fOutput,"%c",currState -> value);
										currState -> state = 40;
							
										if( _isDelimiter(nextCh) || (e=fgetc(ptr)==EOF)) {
											
											currState -> state = 41;
											currState -> final = _checkState( currState->state );
											
										}
									}
								}
							}
							
							break;
						}
					
					} // switch( currState -> value )
					
				} // if( isDelimiter(nextCh) )
				
				break;
			
			} // case 'a'
			
			
			case 'f' : {
				
				n = 1;
				currState -> state = 42;
				printf("\n%c", currState -> value);
				fprintf(fOutput,"%c",currState -> value);
				
				if ( _isDelimiter(nextCh) ) {
					
					currState -> final  = _checkState( currState -> state );
					
				} else {
					
					getNextInput();
					
					switch( currState -> value ) {
						
						case 'a' : {
							
							currState -> state = 43;
							printf("%c", currState -> value);
							fprintf(fOutput,"%c",currState -> value);
							
							if( _isDelimiter(nextCh) ) {
					
								currState -> final  = _checkState( currState -> state );
					
							} else {
								
								getNextInput();
					
								switch( currState -> value ) {
						
									case 'l' : {
							
										currState -> state = 44;
										printf("%c", currState -> value);
										fprintf(fOutput,"%c",currState -> value);
							
										if( _isDelimiter(nextCh) ) {
					
											currState -> final  = _checkState( currState -> state );
								
										} else {
								
											getNextInput();
					
											switch( currState -> value ) {
						
												case 's' : {
							
													currState -> state = 45;
													printf("%c", currState -> value);
													fprintf(fOutput,"%c",currState -> value);
							
													if( _isDelimiter(nextCh) ) {
					
														currState -> final  = _checkState( currState -> state );
								
													} else {
								
														getNextInput();
					
														switch( currState -> value ) {
						
															case 'e' : {
							
																currState -> state = 46;
																printf("%c", currState -> value);
																fprintf(fOutput,"%c",currState -> value);
														
																if( _isDelimiter(nextCh) || ((e=fgetc(ptr)) == EOF) ) {
																
																	currState -> state = 47;
																	currState -> final  = _checkState( currState -> state );
																	
																} // if( _isDelimiter(nextCh) || ((e=fgetc(ptr)) == EOF) )
																
																break;
						
															} // case 'y'
					
														} // switch( currState -> value )
								
													} // if( isDelimiter(nextCh) )
						
													break;
						
												} // case 'a'
					
											} // switch( currState -> value )
										
										} // if( isDelimiter(nextCh) )
						
										break;
						
									} // case 'r'
					
								} // switch( currState -> value )
								
							} // if( isDelimiter(nextCh) )
							
							break;
							
						} // case 'r'
						
						case 'o' : {
							
							currState -> state = 48;
							printf("%c", currState -> value);
							fprintf(fOutput,"%c",currState -> value);
							
							if( _isDelimiter(nextCh) ) {
					
								currState -> final  = _checkState( currState -> state );
					
							} else {
								
								getNextInput();
					
								switch( currState -> value ) {
						
									case 'r' : {
							
										currState -> state = 49;
										printf("%c", currState -> value);
										fprintf(fOutput,"%c",currState -> value);
														
										if( _isDelimiter(nextCh) || ((e=fgetc(ptr2)) == EOF) ) {
																
											currState -> state = 50;
											currState -> final  = _checkState( currState -> state );
																	
										} // if( _isDelimiter(nextCh) || ((e=fgetc(ptr)) == EOF) )
										
									} // case 'l'
									
								} // switch( currState -> value )
									
							} // if( _isDelimiter(nextCh) )
							
							break;
						}
						
					} // switch( currState -> value )
			
				} // if ( _isDelimiter(nextCh) )
				
				break;
			
			} // case 'a'
			
			
			case 'i' : {
				
				n = 1;
				printf("\n%c", currState -> value);
				fprintf(fOutput,"%c",currState -> value);
				currState -> state = 51;
				
				if( _isDelimiter(nextCh) ) {
					
					currState -> final = _checkState( currState -> state );
					
				} else {
					
					getNextInput();
					
					switch( currState -> value ) {
						
						case 'n' : {
							
							printf("%c", currState -> value);
							fprintf(fOutput,"%c",currState -> value);
							currState -> state = 54;
							
							//if( _isDelimiter(nextCh) || ((e=fgetc(ptr)) == EOF) ) {
							if( _isDelimiter(nextCh) ) {
					
								currState -> state = 77;
								currState -> final = _checkState(currState -> state);
								
							} else {
								
								getNextInput();
								
								switch( currState -> value ) {
						
									case 't' : {
							
										printf("%c", currState -> value);
										fprintf(fOutput,"%c",currState -> value);
										currState -> state = 55;
							
										if( _isDelimiter(nextCh) ) {
					
											currState -> final = _checkState( currState -> state );
								
										} else {
								
											getNextInput();
					
											switch( currState -> value ) {
						
												case 'e' : {
							
													printf("%c", currState -> value);
													fprintf(fOutput,"%c",currState -> value);
													currState -> state = 56;
							
													if( _isDelimiter(nextCh) ) {
					
														currState -> final = _checkState( currState -> state );
								
													} else {
								
														getNextInput();
					
														switch( currState -> value ) {
						
															case 'g' : {
							
																printf("%c", currState -> value);
																fprintf(fOutput,"%c",currState -> value);
																currState -> state = 57;
														
																if( _isDelimiter(nextCh) ) {
					
																	currState -> final = _checkState( currState -> state );
								
																} else {
								
																	getNextInput();
					
																	switch( currState -> value ) {
						
																		case 'e' : {
							
																			printf("%c", currState -> value);
																			fprintf(fOutput,"%c",currState -> value);
																			currState -> state = 58;
																	
																			
																			if( _isDelimiter(nextCh) ) {
					
																				currState -> final = _checkState( currState -> state );
								
																			} else {
																				
																				getNextInput();
																				
																				switch( currState -> value ) {
						
																					case 'r' : {
																						
																						printf("%c", currState -> value);
																						fprintf(fOutput,"%c",currState -> value);
																						currState -> state = 59;
																						
																						if( _isDelimiter(nextCh) || ((e=fgetc(ptr)) == EOF) ) {
					
																							currState -> state = 60;
																							currState -> final = _checkState(currState -> state);
										
																						} // if( isDelimiter(nextCh) )
																			
																					break;
						
																					} // case 'r'
								
																				} // switch( currState -> value )
								
																			} // if( isDelimiter(nextCh) )
														
															
																			break;
						
																		} // case 'r'
					
																	} // switch( currState -> value )
								
																} // if( isDelimiter(nextCh) )
																
																
																break;
						
															} // case 'r'
					
														} // switch( currState -> value )
								
													} // if( isDelimiter(nextCh) )
						
													break;
						
												} // case 'r'
					
											} // switch( currState -> value )
										
										} // if( isDelimiter(nextCh) )
						
										break;
						
									} // case 'r'
					
								} // switch( currState -> value )
								
							} // if( isDelimiter(nextCh) )
						
							break;
						
						} // case 'r'
					
						case 'f' : {
							
							currState -> state = 52;
							printf("%c", currState -> value);
							fprintf(fOutput,"%c",currState -> value);
														
							if( _isDelimiter(nextCh) || ((e=fgetc(ptr)) == EOF) ) {
																
								currState -> state = 53;
								currState -> final  = _checkState( currState -> state );
																	
							} // if( _isDelimiter(nextCh) || ((e=fgetc(ptr)) == EOF) )
							
							break;
							
						} // case 'f'
					
						case 's' : {
							
							printf("%c", currState -> value);
							fprintf(fOutput,"%c",currState -> value);
							currState -> state = 61;
							
							if( _isDelimiter(nextCh) || ((e=fgetc(ptr2)) == EOF) ) {
					
								currState -> state = 62;
								currState -> final = _checkState(currState -> state);
								
							}
							
							break;
							
						}
					
					} // switch( currState -> value )
					
				} // if( isDelimiter(nextCh) )
				
				break;
			
			} // case 'i'
			

			case 'l' : {
				
				n = 1;
				printf("\n%c", currState -> value);
				fprintf(fOutput,"%c",currState -> value);
				currState -> state = 68;
				
				if( _isDelimiter(nextCh) ) {
					
					currState -> final = _checkState( currState -> state );
					
				} else {
					
					getNextInput();
					
					switch( currState -> value ) {
						
						case 'e' : {
							
							printf("%c", currState -> value);
							fprintf(fOutput,"%c",currState -> value);	
							currState -> state = 69;
							
							if( _isDelimiter(nextCh) ) {
					
								currState -> final = _checkState( currState -> state );
					
							} else {
								
								getNextInput();
					
								switch( currState -> value ) {
						
									case 't' : {
							
										printf("%c", currState -> value);
										fprintf(fOutput,"%c",currState -> value);
										currState -> state = 70;
							
										if( _isDelimiter || ((e=fgetc(ptr2)) == EOF) ) {
					
											currState -> state = 71;
											currState -> final = _checkState(currState -> state);
														
										} // if( isDelimiter(nextCh) )
										
										break;
						
									} // case 'r'
					
								} // switch( currState -> value )
								
							} // if( isDelimiter(nextCh) )
						
							break;
						
						} // case 'r'
					
					} // switch( currState -> value )
					
				} // if( isDelimiter(nextCh) )
				
				break;
			
			} // case 'l'


			case 'm' : {
				
				n = 1;
				currState -> state = 72;
				printf("\n%c", currState -> value);
				fprintf(fOutput,"%c",currState -> value);
				
				if ( _isDelimiter(nextCh) ) {
					
					currState -> final  = _checkState( currState -> state );
					
				} else {
					
					getNextInput();
					
					switch( currState -> value ) {
						
						case 'a' : {
							
							currState -> state = 73;
							printf("%c", currState -> value);
							fprintf(fOutput,"%c",currState -> value);
							
							if( _isDelimiter(nextCh) ) {
					
								currState -> final  = _checkState( currState -> state );
					
							} else {
								
								getNextInput();
					
								switch( currState -> value ) {
						
									case 'i' : {
							
										currState -> state = 74;
										printf("%c", currState -> value);
										fprintf(fOutput,"%c",currState -> value);
							
										if( _isDelimiter(nextCh) ) {
					
											currState -> final  = _checkState( currState -> state );
								
										} else {
								
											getNextInput();
					
											switch( currState -> value ) {
						
												case 'n' : {
							
													currState -> state = 75;
													printf("%c", currState -> value);
													fprintf(fOutput,"%c",currState -> value);
							
													if( _isDelimiter(nextCh) || ((e=fgetc(ptr2)) == EOF) ) {
																
														currState -> state = 76;
														currState -> final  = _checkState( currState -> state );
																	
													} // if( _isDelimiter(nextCh) || ((e=fgetc(ptr)) == EOF) )
						
													break;
						
												} // case 'a'
					
											} // switch( currState -> value )
										
										} // if( isDelimiter(nextCh) )
						
										break;
						
									} // case 'r'
					
								} // switch( currState -> value )
								
							} // if( isDelimiter(nextCh) )
							
							break;
							
						} // case 'r'
						
					} // switch( currState -> value )
			
				} // if ( _isDelimiter(nextCh) )
				
				break;
				
			} // case 'm'
			
			
			case 'o' : {
				
				n = 1;
				currState -> state = 78;
				printf("\n%c", currState -> value);
				fprintf(fOutput,"%c",currState -> value);
				
				if ( _isDelimiter(nextCh) ) {
					
					currState -> final  = _checkState( currState -> state );
					
				} else {
					
					getNextInput();
					
					switch( currState -> value ) {
						
						case 'u' : {
							
							currState -> state = 79;
							printf("%c", currState -> value);
							fprintf(fOutput,"%c",currState -> value);
							
							if( _isDelimiter(nextCh) ) {
					
								currState -> final  = _checkState( currState -> state );
					
							} else {
								
								getNextInput();
					
								switch( currState -> value ) {
						
									case 't' : {
							
										currState -> state = 80;
										printf("%c", currState -> value);
										fprintf(fOutput,"%c",currState -> value);
							
										if( _isDelimiter(nextCh) || ((e=fgetc(ptr2)) == EOF) ) {
																
											currState -> state = 81;
											currState -> final  = _checkState( currState -> state );
																	
										} // if( _isDelimiter(nextCh) || ((e=fgetc(ptr)) == EOF) )
										
										break;
						
									} // case 'r'
					
								} // switch( currState -> value )
								
							} // if( isDelimiter(nextCh) )
							
							break;
							
						} // case 'r'
						
					} // switch( currState -> value )
			
				} // if ( _isDelimiter(nextCh) )
				
				break;
				
			} // case 'o'
			
			
			case 'r' : {
				
				n = 1;		
				printf("\n%c", currState -> value);
				fprintf(fOutput,"%c",currState -> value);
				currState -> state = 82;
				
				if( _isDelimiter(nextCh) ) {
					
					currState -> final = _checkState( currState -> state );
					
				} else {
					
					getNextInput();
					
					switch( currState -> value ) {
						
						case 'a' : {
							
							printf("%c", currState -> value);
							fprintf(fOutput,"%c",currState -> value);
							currState -> state = 83;
							
							if( _isDelimiter(nextCh) ) {
					
								currState -> final = _checkState( currState -> state );
					
							} else {
								
								getNextInput();
					
								switch( currState -> value ) {
						
									case 'n' : {
							
										printf("%c", currState -> value);
										fprintf(fOutput,"%c",currState -> value);
										currState -> state = 84;
							
										if( _isDelimiter(nextCh) ) {
					
											currState -> final = _checkState( currState -> state );
								
										} else {
								
											getNextInput();
					
											switch( currState -> value ) {
						
												case 'g' : {
							
													printf("%c", currState -> value);
													fprintf(fOutput,"%c",currState -> value);
													currState -> state = 85;
							
													if( _isDelimiter(nextCh) ) {
					
														currState -> final = _checkState( currState -> state );
								
													} else {
								
														getNextInput();
					
														switch( currState -> value ) {
						
															case 'e' : {
							
																printf("%c", currState -> value);
																fprintf(fOutput,"%c",currState -> value);
																currState -> state = 86;
														
																if( _isDelimiter(nextCh) || ((e=fgetc(ptr2)) == EOF) ){
																
																	currState -> state = 87;
																	currState -> final = _checkState( currState -> state );
																	
																} 
																
																break;
						
															} // case 'r'
					
														} // switch( currState -> value )
								
													} // if( isDelimiter(nextCh) )
						
													break;
						
												} // case 'r'
					
											} // switch( currState -> value )
										
										} // if( isDelimiter(nextCh) )
						
										break;
						
									} // case 'r'
					
								} // switch( currState -> value )
								
							} // if( isDelimiter(nextCh) )
						
							break;
						
						} // case 'r'
			
						case 'e' : {
							
							printf("%c", currState -> value);
							fprintf(fOutput,"%c",currState -> value);
							currState -> state = 88;
				
							if( _isDelimiter(nextCh) ) {
					
								currState -> final = _checkState( currState -> state );
					
							} else {
					
								getNextInput();
					
								switch( currState -> value ) {
									
									case 'a' : {
										
										printf("%c", currState -> value);
										fprintf(fOutput,"%c",currState -> value);
										currState -> state = 89;
				
										if( _isDelimiter(nextCh) ) {
					
											currState -> final = _checkState( currState -> state );
					
										} else {
					
											getNextInput();
					
											switch( currState -> value ) {
												
												case 'l' : {
													
													printf("%c", currState -> value);
													fprintf(fOutput,"%c",currState -> value);
													currState -> state = 90;
														
													if( _isDelimiter(nextCh) || ((e=fgetc(ptr2)) == EOF) ){
																
														currState -> state = 91;
														currState -> final = _checkState( currState -> state );
																	
													} 
													
													break;
													
												}
												
											}
										}
										
										break;
										
									} // case 'a'
									
									
									case 't' : {
										
										printf("%c", currState -> value);
										fprintf(fOutput,"%c",currState -> value);
										currState -> state = 92;
							
										if( _isDelimiter(nextCh) ) {
					
											currState -> final = _checkState( currState -> state );
								
										} else {
								
											getNextInput();
					
											switch( currState -> value ) {
						
												case 'u' : {
							
													printf("%c", currState -> value);
													fprintf(fOutput,"%c",currState -> value);
													currState -> state = 93;
							
													if( _isDelimiter(nextCh) ) {
					
														currState -> final = _checkState( currState -> state );
								
													} else {
								
														getNextInput();
					
														switch( currState -> value ) {
						
															case 'r' : {
																
																printf("%c", currState -> value);
																fprintf(fOutput,"%c",currState -> value);
																currState -> state = 94;
							
																if( _isDelimiter(nextCh) ) {
					
																	currState -> final = _checkState( currState -> state );
								
																} else {
																
																	getNextInput();
					
																	switch( currState -> value ) {
																		
																		case 'n' : {
																			
																			printf("%c", currState -> value);
																			fprintf(fOutput,"%c",currState -> value);
																			currState -> state = 95;
							
																			if( _isDelimiter(nextCh) ) {
					
																				currState -> final = _checkState( currState -> state );
								
																			} else {
																
																				getNextInput();
					
																				switch( currState -> value ) {
																					
																					case 's' : {
																			
																						printf("%c", currState -> value);
																						fprintf(fOutput,"%c",currState -> value);
																						currState -> state = 96;
														
																						if( _isDelimiter(nextCh) || ((e=fgetc(ptr2)) == EOF) ){
																
																							currState -> state = 97;
																							currState -> final = _checkState( currState -> state );
																	
																						}
																			
																			
																						break;
																			
																					}
																					
																					
																				}
																			}
																			
																			break;
																			
																		}
																	
																	}
																	
																}
																
																break;
						
															} // case 'r'
					
														} // switch( currState -> value )
								
													} // if( isDelimiter(nextCh) )
						
													break;
						
												} // case 'r'
					
											} // switch( currState -> value )
										
										} // if( isDelimiter(nextCh) )
										
										break;
										
									} // case 't'
									
									
								}
								
							}
					
							break;
						}
						
			
					}
				}
				
				break;
			}	
			
			
			case 't' : {
				
				n = 1;
				currState -> state = 103;
				printf("\n%c", currState -> value);
				fprintf(fOutput,"%c",currState -> value);
				
				if ( _isDelimiter(nextCh) ) {
					
					currState -> final  = _checkState( currState -> state );
					
				} else {
					
					getNextInput();
					
					switch( currState -> value ) {
						
						case 'r' : {
							
							currState -> state = 104;
							printf("%c", currState -> value);
							fprintf(fOutput,"%c",currState -> value);
							
							if( _isDelimiter(nextCh) ) {
					
								currState -> final  = _checkState( currState -> state );
					
							} else {
								
								getNextInput();
					
								switch( currState -> value ) {
						
									case 'u' : {
							
										currState -> state = 105;
										printf("%c", currState -> value);
										fprintf(fOutput,"%c",currState -> value);
							
										if( _isDelimiter(nextCh) ) {
					
											currState -> final  = _checkState( currState -> state );
								
										} else {
								
											getNextInput();
					
											switch( currState -> value ) {
						
												case 'e' : {
							
													currState -> state = 106;
													printf("%c", currState -> value);
													fprintf(fOutput,"%c",currState -> value);
							
													if( _isDelimiter(nextCh) || ((e=fgetc(ptr2)) == EOF) ) {
																
														currState -> state = 107;
														currState -> final  = _checkState( currState -> state );
																	
													} // if( _isDelimiter(nextCh) || ((e=fgetc(ptr)) == EOF) )
						
													break;
						
												} // case 'a'
					
											} // switch( currState -> value )
										
										} // if( isDelimiter(nextCh) )
						
										break;
						
									} // case 'r'
					
								} // switch( currState -> value )
								
							} // if( isDelimiter(nextCh) )
							
							break;
							
						} // case 'r'
						
						case 'o' : {
							
							currState -> state = 108;
							printf("%c", currState -> value);
							fprintf(fOutput,"%c",currState -> value);
							
							if( _isDelimiter(nextCh) || ((e=fgetc(ptr2)) == EOF) ) {
																
								currState -> state = 109;
								currState -> final  = _checkState( currState -> state );
																	
							} // if( _isDelimiter(nextCh) || ((e=fgetc(ptr)) == EOF) )
							
							break;
							
						}
						
						case 'a' : {
							
							currState -> state = 110;
							printf("%c", currState -> value);
							fprintf(fOutput,"%c",currState -> value);
							
							if( _isDelimiter(nextCh) ) {
					
								currState -> final  = _checkState( currState -> state );
					
							} else {
								
								getNextInput();
					
								switch( currState -> value ) {
						
									case 'i' : {
							
										currState -> state = 111;
										printf("%c", currState -> value);
										fprintf(fOutput,"%c",currState -> value);
							
										if( _isDelimiter(nextCh) ) {
					
											currState -> final  = _checkState( currState -> state );
								
										} else {
								
											getNextInput();
					
											switch( currState -> value ) {
						
												case 'l' : {
							
													currState -> state = 112;
													printf("%c", currState -> value);
													fprintf(fOutput,"%c",currState -> value);
							
													if( _isDelimiter(nextCh) || ((e=fgetc(ptr2)) == EOF) ) {
																
														currState -> state = 113;
														currState -> final  = _checkState( currState -> state );
																	
													} // if( _isDelimiter(nextCh) || ((e=fgetc(ptr)) == EOF) )
						
													break;
						
												} // case 'a'
					
											} // switch( currState -> value )
										
										} // if( isDelimiter(nextCh) )
						
										break;
						
									} // case 'r'
					
								} // switch( currState -> value )
								
							} // if( isDelimiter(nextCh) )
							
							break;
						}
						
					} // switch( currState -> value )
			
				} // if ( _isDelimiter(nextCh) )
				
				break;
			}
			
			
			case 'h' : {
				
				n = 1;
				currState -> state = 140;
				printf("\n%c", currState -> value);
				fprintf(fOutput,"%c",currState -> value);
				
				if ( _isDelimiter(nextCh) ) {
					
					currState -> final  = _checkState( currState -> state );
					
				} else {
					
					getNextInput();
					
					switch( currState -> value ) {
						
						case 'e' : {
							
							currState -> state = 141;
							printf("%c", currState -> value);
							fprintf(fOutput,"%c",currState -> value);
							
							if( _isDelimiter(nextCh) ) {
					
								currState -> final  = _checkState( currState -> state );
					
							} else {
								
								getNextInput();
					
								switch( currState -> value ) {
						
									case 'a' : {
							
										currState -> state = 142;
										printf("%c", currState -> value);
										fprintf(fOutput,"%c",currState -> value);
							
										if( _isDelimiter(nextCh) ) {
					
											currState -> final  = _checkState( currState -> state );
								
										} else {
								
											getNextInput();
					
											switch( currState -> value ) {
						
												case 'd' : {
							
													currState -> state = 143;
													printf("%c", currState -> value);
													fprintf(fOutput,"%c",currState -> value);
							
													if( _isDelimiter(nextCh) || ((e=fgetc(ptr2)) == EOF) ) {
																
														currState -> state = 144;
														currState -> final  = _checkState( currState -> state );
																	
													} // if( _isDelimiter(nextCh) || ((e=fgetc(ptr)) == EOF) )
						
													break;
						
												} // case 'a'
					
											} // switch( currState -> value )
										
										} // if( isDelimiter(nextCh) )
						
										break;
						
									} // case 'r'
					
								} // switch( currState -> value )
								
							} // if( isDelimiter(nextCh) )
							
							break;
							
						} // case 'r'
						
					} // switch( currState -> value )
			
				} // if ( _isDelimiter(nextCh) )
				
				break;
				
			}
			
			
			case 'v' : {
				
				n = 1;
				currState -> state = 203;
				printf("\n%c", currState -> value);
				fprintf(fOutput,"%c",currState -> value);
				
				if ( _isDelimiter(nextCh) ) {
					
					currState -> final  = _checkState( currState -> state );
					
				} else {
					
					getNextInput();
					
					switch( currState -> value ) {
						
						case 'o' : {
							
							currState -> state = 204;
							printf("%c", currState -> value);
							fprintf(fOutput,"%c",currState -> value);
							
							if( _isDelimiter(nextCh) ) {
					
								currState -> final  = _checkState( currState -> state );
					
							} else {
								
								getNextInput();
					
								switch( currState -> value ) {
						
									case 'i' : {
							
										currState -> state = 205;
										printf("%c", currState -> value);
										fprintf(fOutput,"%c",currState -> value);
							
										if( _isDelimiter(nextCh) ) {
					
											currState -> final  = _checkState( currState -> state );
								
										} else {
								
											getNextInput();
					
											switch( currState -> value ) {
						
												case 'd' : {
							
													currState -> state = 206;
													printf("%c", currState -> value);
													fprintf(fOutput,"%c",currState -> value);
							
													if( _isDelimiter(nextCh) || ((e=fgetc(ptr2)) == EOF) ) {
																
														currState -> state = 207;
														currState -> final  = _checkState( currState -> state );
																	
													} // if( _isDelimiter(nextCh) || ((e=fgetc(ptr)) == EOF) )
						
													break;
						
												} // case 'a'
					
											} // switch( currState -> value )
										
										} // if( isDelimiter(nextCh) )
						
										break;
						
									} // case 'r'
					
								} // switch( currState -> value )
								
							} // if( isDelimiter(nextCh) )
							
							break;
							
						} // case 'r'
						
						case 'i' : {
							
							currState -> state = 115;
							printf("%c", currState -> value);
							fprintf(fOutput,"%c",currState -> value);
							
							if( _isDelimiter(nextCh) ) {
					
								currState -> final  = _checkState( currState -> state );
					
							} else {
								
								getNextInput();
					
								switch( currState -> value ) {
						
									case 'p' : {
							
										currState -> state = 116;
										printf("%c", currState -> value);
										fprintf(fOutput,"%c",currState -> value);
							
										if( _isDelimiter(nextCh) ) {
					
											currState -> final  = _checkState( currState -> state );
								
										} else {
								
											getNextInput();
					
											switch( currState -> value ) {
						
												case 'e' : {
							
													currState -> state = 117;
													printf("%c", currState -> value);
													fprintf(fOutput,"%c",currState -> value);
							
													if( _isDelimiter(nextCh) ) {
					
														currState -> final  = _checkState( currState -> state );
								
													} else {
								
														getNextInput();
					
														switch( currState -> value ) {
															
															case 'r' : {
																
																currState -> state = 118;
																printf("%c", currState -> value);
																fprintf(fOutput,"%c",currState -> value);
																
																if( _isDelimiter(nextCh) || ((e=fgetc(ptr2)) == EOF) ) {
																
																	currState -> state = 119;
																	currState -> final  = _checkState( currState -> state );
																}
																
																break;
															}
														}
																	
													} // if( _isDelimiter(nextCh) || ((e=fgetc(ptr)) == EOF) )
						
													break;
						
												} // case 'a'
					
											} // switch( currState -> value )
										
										} // if( isDelimiter(nextCh) )
						
										break;
						
									} // case 'r'
					
								} // switch( currState -> value )
								
							} // if( isDelimiter(nextCh) )
							
							break;
							
						} // case 'r'
						
					} // switch( currState -> value )
			
				} // if ( _isDelimiter(nextCh) )
				
				break;
				
			}
			
			
			case 'w' : {
				
				n = 1;		
				printf("\n%c", currState -> value);
				fprintf(fOutput,"%c",currState -> value);
				currState -> state = 120;
				
				if( _isDelimiter(nextCh) ) {
					
					currState -> final = _checkState( currState -> state );
					
				} else {
					
					getNextInput();
					
					switch( currState -> value ) {
						
						case 'h' : {
							
							printf("%c", currState -> value);
							fprintf(fOutput,"%c",currState -> value);
							currState -> state = 121;
							
							if( _isDelimiter(nextCh) ) {
					
								currState -> final = _checkState( currState -> state );
					
							} else {
								
								getNextInput();
					
								switch( currState -> value ) {
						
									case 'i' : {
							
										printf("%c", currState -> value);
										fprintf(fOutput,"%c",currState -> value);
										currState -> state = 122;
							
										if( _isDelimiter(nextCh) ) {
					
											currState -> final = _checkState( currState -> state );
								
										} else {
								
											getNextInput();
					
											switch( currState -> value ) {
						
												case 'l' : {
							
													printf("%c", currState -> value);
													fprintf(fOutput,"%c",currState -> value);
													currState -> state = 123;
							
													if( _isDelimiter(nextCh) ) {
					
														currState -> final = _checkState( currState -> state );
								
													} else {
								
														getNextInput();
					
														switch( currState -> value ) {
						
															case 'e' : {
							
																printf("%c", currState -> value);
																fprintf(fOutput,"%c",currState -> value);
																currState -> state = 124;
														
																if( _isDelimiter(nextCh) || ((e=fgetc(ptr2)) == EOF) ){
																
																	currState -> state = 125;
																	currState -> final = _checkState( currState -> state );
																	
																} 
																
																break;
						
															} // case 'r'
					
														} // switch( currState -> value )
								
													} // if( isDelimiter(nextCh) )
						
													break;
						
												} // case 'r'
					
											} // switch( currState -> value )
										
										} // if( isDelimiter(nextCh) )
						
										break;
						
									} // case 'r'
					
								} // switch( currState -> value )
								
							} // if( isDelimiter(nextCh) )
						
							break;
						
						} // case 'r'
			
						
					}
				}
				
				break;
			}	
			
			
			case '@' : {
				
				n = 1;
				printf("\n%c", currState->value);
				fprintf(fOutput,"%c",currState -> value);
				currState -> state = 145;
				
				while( (_isIdDelimiter(nextCh)) == 0 ){
					
					getNextInput();
					currState -> state = 146;
					printf("%c", currState->value);
					fprintf(fOutput,"%c",currState -> value);
					
				}
				
				currState -> state = 147;
				currState -> final = 1;
				
				break;
				
			} // case '@'
			
			
			case '#' : {
				
				printf("\n%c", currState -> value);
				fprintf(fOutput,"%c",currState -> value);
				currState -> state = 192;
				
				while( (nextCh != '#') || (nextCh != '\n') || (currState -> value != '\n') || (currState -> value != '#')){
					
					getNextInput();
					currState -> state = 193;
					printf("%c", currState->value);
					fprintf(fOutput,"%c",currState -> value);
				
					if( (currState -> value == '\n') || (currState -> value == '#') ) {
						
						break;
						
					}
					
					
				}
				
				currState -> state = 194;
				currState -> final = 1;
					
				break;
				
			} // case '#'
			
			
			case '$' : {
				
				printf("\n%c", currState->value);
				fprintf(fOutput,"%c",currState -> value);
				currState -> state = 148;
				
				while( !(_isIdDelimiter(nextCh)) ){
					
					getNextInput();
					currState -> state = 149;
					printf("%c", currState->value);
					fprintf(fOutput,"%c",currState -> value);
					
				}
				
				currState -> state = 150;
				currState -> final = 1;
				
				break;
				
			} // case '$
			
			
			case '\'' : {
			
				printf("\n%c", currState->value);
				fprintf(fOutput,"%c",currState -> value);
				currState -> state = 133;
				
				getNextInput();
				
				printf("%c", currState->value);
				fprintf(fOutput,"%c",currState -> value);
				currState -> state = 134;
				
				getNextInput();
				
				printf("%c", currState->value);
				fprintf(fOutput,"%c",currState -> value);
				
				if( currState -> value == '\'') {
					currState -> state = 135;
					currState -> final = 1;
				}
				
				break;
				
			}
			
			
			case '0' :
			case '1' :
			case '2' :
			case '3' :
			case '4' :
			case '5' :
			case '6' :
			case '7' :
			case '8' :
			case '9' : {
				
				int p = 0;
				
				printf("\n%c", currState->value);
				fprintf(fOutput,"%c",currState -> value);
				currState -> state = 127;
				
				while( !(_isFloatDelimiter(nextCh)) ) {
					
					getNextInput();
					
					printf("%c", currState->value);
					fprintf(fOutput,"%c",currState -> value);
					currState -> state = 127;
					
					if ( currState -> value == '.' ) {
						
					    currState -> state = 131;
						p = 1;
						
					}
					
				}
				
				if ( p != 0 ) {
					
					currState -> state = 132;
					currState -> final = 1;
					
				} else {
					
					currState -> state = 127;
					currState -> final = 1;
					
				}
				
				break;
			}
			
			
			case '(' : {
				
				printf("\n%c", currState->value);
				fprintf(fOutput,"%c",currState -> value);
				currState -> state = 199;
				currState -> final = 1;
				
				break;
			}
			
			
			case ')' : {
				
				printf("\n%c", currState->value);
				fprintf(fOutput,"%c",currState -> value);
				currState -> state = 200;
				currState -> final = 1;
				
				break;
			}

			
			case '[' : {
				
				printf("\n%c", currState->value);
				fprintf(fOutput,"%c",currState -> value);
				currState -> state = 195;
				currState -> final = 1;
				
				break;
			}
			
			
			case ']' : {
				
				printf("\n%c", currState->value);
				fprintf(fOutput,"%c",currState -> value);
				currState -> state = 196;
				currState -> final = 1;
				
				break;
			}
	
			
			case '{' : {
				
				printf("\n%c", currState->value);
				fprintf(fOutput,"%c",currState -> value);
				currState -> state = 197;
				currState -> final = 1;
				
				break;
			}
			
			
			case '}' : {
				
				printf("\n%c", currState->value);
				fprintf(fOutput,"%c",currState -> value);
				currState -> state = 198;
				currState -> final = 1;
				
				break;
			}
			
			
			case ':' : {
				
				printf("\n%c", currState->value);
				fprintf(fOutput,"%c",currState -> value);
				currState -> state = 300;
				currState -> final = 1;
				
				break;
			}
			
			
			case ';' : {
				
				printf("\n%c", currState->value);
				fprintf(fOutput,"%c",currState -> value);
				currState -> state = 301;
				currState -> final = 1;
				
				break;
			}
		
			
			case '*' : {
				
				printf("\n%c", currState->value);
				fprintf(fOutput,"%c",currState -> value);
				currState -> state = 160;
				currState -> final = 1;
				
				break;
			}
		
			
			case '%' : {
				
				printf("\n%c", currState->value);
				fprintf(fOutput,"%c",currState -> value);
				currState -> state = 166;
				currState -> final = 1;
				
				break;
			}
			
			
			case '^' : {
				
				printf("\n%c", currState->value);
				fprintf(fOutput,"%c",currState -> value);
				currState -> state = 168;
				currState -> final = 1;
				
				break;
			}
			
			
			case ',' : {
				
				printf("\n%c", currState->value);
				fprintf(fOutput,"%c",currState -> value);
				currState -> state = 302;
				currState -> final = 1;
				
				break;
			}
			
			
			case '|' : {
				
				printf("\n%c", currState->value);
				fprintf(fOutput,"%c",currState -> value);
				currState -> state = 172;
				
				if ( nextCh == '|') {
				
					getNextInput();
					
					printf("%c",currState->value);
					fprintf(fOutput,"%c",currState -> value);
					currState -> state = 174;
					currState -> final = 1;
					
				} 
				
				break;
			}
			
			
			case '&' : {
				
				printf("\n%c", currState->value);
				fprintf(fOutput,"%c",currState -> value);
				currState -> state = 168;
				
				if ( nextCh == '&') {
				
					getNextInput();
					
					printf("%c",currState->value);
					fprintf(fOutput,"%c",currState -> value);
					currState -> state = 171;
					currState -> final = 1;
					
				} 
				
				break;
			}
			
			
			case '=' : {
				
				printf("\n%c", currState->value);
				fprintf(fOutput,"%c",currState -> value);
				currState -> state = 191;
				currState -> final = 1;
				
				if ( nextCh == '=') {
				
					getNextInput();
					
					printf("%c",currState->value);
					fprintf(fOutput,"%c",currState -> value);
					currState -> state = 181;
					currState -> final = 1;
					
				} 
				
				break;
			}
			
			
			case '+' : {
				
				printf("\n%c", currState->value);
				fprintf(fOutput,"%c",currState -> value);
				currState -> state = 152;
				currState -> final = 1;
				
				if ( nextCh == '+') {
				
					getNextInput();
					
					printf("%c",currState->value);
					fprintf(fOutput,"%c",currState -> value);
					currState -> state = 154;
					currState -> final = 1;
					
				} 
				
				break;
			}
			
			
			case '-' : {
				
				printf("\n%c", currState->value);
				fprintf(fOutput,"%c",currState -> value);
				currState -> state = 156;
				currState -> final = 1;
				
				if ( nextCh == '-') {
				
					getNextInput();
					
					printf("%c",currState->value);
					fprintf(fOutput,"%c",currState -> value);
					currState -> state = 158;
					currState -> final = 1;
					
				} 
				
				break;
			}
		
			
			case '<' : {
				
				printf("\n%c", currState->value);
				fprintf(fOutput,"%c",currState -> value);
				currState -> state = 187;
				currState -> final = 1;
				
				if ( nextCh == '=') {
				
					getNextInput();
					
					printf("%c",currState->value);
					fprintf(fOutput,"%c",currState -> value);
					currState -> state = 189;
					currState -> final = 1;
					
				} 
				
				break;
			}
			
			
			case '/' : {
				
				printf("\n%c", currState->value);
				fprintf(fOutput,"%c",currState -> value);
				currState -> state = 162;
				currState -> final = 1;
				
				if ( nextCh == '/') {
				
					getNextInput();
					
					printf("%c",currState->value);
					fprintf(fOutput,"%c",currState -> value);
					currState -> state = 164;
					currState -> final = 1;
					
				} 
				
				break;
			}
			
			
			case '>' : {
				
				printf("\n%c", currState->value);
				fprintf(fOutput,"%c",currState -> value);
				currState -> state = 183;
				currState -> final = 1;
				
				if ( nextCh == '=') {
				
					getNextInput();
					
					printf("%c",currState->value);
					fprintf(fOutput,"%c",currState -> value);
					currState -> state = 185;
					currState -> final = 1;
					
				} 
				
				break;
			}
			
			
			case '!' : {
				
				printf("\n%c", currState->value);
				fprintf(fOutput,"%c",currState -> value);
				currState -> state = 176;
				currState -> final = 1;
				
				if ( nextCh == '=') {
				
					getNextInput();
					
					printf("%c",currState->value);
					fprintf(fOutput,"%c",currState -> value);
					currState -> state = 178;
					currState -> final = 1;
					
				} 
				
				break;
			}
			
			
			case '\"' : {
			
				printf("\n%c", currState->value);
				fprintf(fOutput,"%c",currState -> value);
				currState -> state = 136;
				
				getNextInput();
				
				while ( currState -> value != '\"') {
					
					printf("%c", currState->value);
					fprintf(fOutput,"%c",currState -> value);
					currState -> state = 137;
					
					getNextInput();
					
					if( currState -> value == '\n') {
						break;
					}
					
					if( currState -> value == '\"') {
						
						printf("%c", currState->value);
						fprintf(fOutput,"%c",currState -> value);
						currState -> state = 138;
						currState -> final = 1;
						break;
						
					}
					
					
				}
				
				break;
				
			}
			
			
			case '\n': {
				
				lineNumber++;
				currState -> final = 1;
				currState -> state = 202;
				break;
			}

			
			case '\t': {
				
				currState -> final = 1;
				currState -> state = 202;
				break;
			}
			
	
			case ' ': {
				
				currState -> final = 1;
				currState -> state = 202;
				break;
				
			} // case whitespace
			
			
		} // switch( currState -> value )
		
		
		// detected an invealid lexeme
		if( currState -> final == 0 ) {
			
			if( n == 0 ) {
				
				printf("\n%c",currState->value);
				fprintf(fOutput,"\n%c",currState -> value);
				currState -> final = 0;
				
			} else {
				
				printf("%c",currState->value);
				fprintf(fOutput,"%c",currState -> value);
				currState -> final = 0;
				
			}
			
			do{
				
				getNextInput();
				
				if ( (_isDelimiter(nextCh)) == 1 || nextCh == EOF) {
					
					printf("%c",currState->value);
					fprintf(fOutput,"%c",currState -> value);
					currState -> final = 0;
					break;
					
				}
				
				printf("%c",currState->value);
				fprintf(fOutput,"%c",currState -> value);
				currState -> final = 0;
				
			} while(1);
			
			
		}
		
		displayTokenClass(currState->final, currState->state, lineNumber);
		
	} // void stateMachine(char ch)
	
	
	void displayTokenClass(int final, int state, int line) {
		
		if ( final ) {
			
			if ( state == 7 ) {
				
				printf("\tARRAY\t%d\n", lineNumber);
				fprintf(fOutput," ~ ARRAY ~ %d\n", lineNumber);
				
			} else if ( state == 15 ) {
				
				printf("\tBOOL\t%d\n", lineNumber);
				fprintf(fOutput," ~ BOOL ~ %d\n", lineNumber);
				
			} else if ( state == 20 ) {
				
				printf("\tCHAR\t%d\n", lineNumber);
				fprintf(fOutput," ~ CHAR ~ %d\n", lineNumber);
				
			} else if ( state == 22 ) {
				
				printf("\tCHARS\t%d\n", lineNumber);
				fprintf(fOutput," ~ CHARS ~ %d\n", lineNumber);
				
			} else if ( state == 25 ) {
				
				printf("\tDO\t%d\n", lineNumber);
				fprintf(fOutput," ~ DO ~ %d\n", lineNumber);
				
			} else if ( state == 30 ) {
				
				printf("\tDOWNTO\t%d\n", lineNumber);
				fprintf(fOutput," ~ DOWNTO ~ %d\n", lineNumber);
				
			} else if ( state == 35 ) {
				
				printf("\tELSE\t%d\n", lineNumber);
				fprintf(fOutput," ~ ELSE ~ %d\n", lineNumber);
				
			} else if ( state == 38 ) {
				
				printf("\tELSIF\t%d\n", lineNumber);
				fprintf(fOutput," ~ ELSIF ~ %d\n", lineNumber);
				
			} else if ( state == 41 ) {
				
				printf("\tEND\t%d\n", lineNumber);
				fprintf(fOutput," ~ END ~ %d\n", lineNumber);
				
			} else if ( state == 47 ) {
				
				printf("\tFALSE\t%d\n", lineNumber);
				fprintf(fOutput," ~ BOOL_LIT ~ %d\n", lineNumber);
				
			} else if ( state == 50 ) {
				
				printf("\tFOR\t%d\n", lineNumber);
				fprintf(fOutput," ~ FOR ~ %d\n", lineNumber);
				
			} else if ( state == 53 ) {
				
				printf("\tIF\t%d\n", lineNumber);
				fprintf(fOutput," ~ IF ~ %d\n", lineNumber);
				
			} else if ( state == 77 ) {
				
				printf("\tIN\t%d\n", lineNumber);
				fprintf(fOutput," ~ IN ~ %d\n", lineNumber);
				
			} else if ( state == 60 ) {
				
				printf("\tINT\t%d\n", lineNumber);
				fprintf(fOutput," ~ INT ~ %d\n", lineNumber);
				
			} else if ( state == 62 ) {
				
				printf("\tIS\t%d\n", lineNumber);
				fprintf(fOutput," ~ IS ~ %d\n", lineNumber);
				
			} else if ( state == 67 ) {
				
				printf("\tJUMP\t%d\n", lineNumber);
				fprintf(fOutput," ~ JUMP ~ %d\n", lineNumber);
				
			} else if ( state == 71 ) {
				
				printf("\tLET\t%d\n", lineNumber);
				fprintf(fOutput," ~ LET ~ %d\n", lineNumber);
				
			} else if ( state == 76 ) {
				
				printf("\tMAIN\t%d\n", lineNumber);
				fprintf(fOutput," ~ MAIN ~ %d\n", lineNumber);
				
			} else if ( state == 81 ) {
				
				printf("\tOUT\t%d\n", lineNumber);
				fprintf(fOutput," ~ OUT ~ %d\n", lineNumber);
				
			} else if ( state == 87 ) {
				
				printf("\tRANGE\t%d\n", lineNumber);
				fprintf(fOutput," ~ RANGE ~ %d\n", lineNumber);
				
			} else if ( state == 91 ) {
				
				printf("\tREAL\t%d\n", lineNumber);
				fprintf(fOutput," ~ REAL ~ %d\n", lineNumber);
				
			} else if ( state == 97 ) {
				
				printf("\tRET\t%d\n", lineNumber);
				fprintf(fOutput," ~ RET ~ %d\n", lineNumber);
				
			} else if ( state == 102 ) {
				
				printf("\tSTOP\t%d\n", lineNumber);
				fprintf(fOutput," ~ STOP ~ %d\n", lineNumber);
				
			} else if ( state == 107 ) {
				
				printf("\tTRUE\t%d\n", lineNumber);
				fprintf(fOutput," ~ BOOL_LIT ~ %d\n", lineNumber);
				
			} else if ( state == 109 ) {
				
				printf("\tTO\t%d\n", lineNumber);
				fprintf(fOutput," ~ TO ~ %d\n", lineNumber);
				
			} else if ( state == 113 ) {
				
				printf("\tTAIL\t%d\n", lineNumber);
				fprintf(fOutput," ~ TAIL ~ %d\n", lineNumber);
				
			} else if ( state == 119 ) {
				
				printf("\tVIPER\t%d\n", lineNumber);
				fprintf(fOutput," ~ VIPER ~ %d\n", lineNumber);
				
			} else if ( state == 125 ) {
				
				printf("\tWHILE\t%d\n", lineNumber);
				fprintf(fOutput," ~ WHILE ~ %d\n", lineNumber);
				
			} else if ( state == 144 ) {
				
				printf("\tHEAD\t%d\n", lineNumber);
				fprintf(fOutput," ~ HEAD ~ %d\n", lineNumber);
				
			} else if ( state == 207 ) {
				
				printf("\tVOID\t%d\n", lineNumber);
				fprintf(fOutput," ~ VOID ~ %d\n", lineNumber);
				
			} else if ( state == 127 ) {
				
				printf("\tINT_LIT\t%d\n", lineNumber);
				fprintf(fOutput," ~ INT_LIT ~ %d\n", lineNumber);
				
			} else if ( state == 132 ) {
				
				printf("\tREAL_LIT\t%d\n", lineNumber);
				fprintf(fOutput," ~ REAL_LIT ~ %d\n", lineNumber);
				
			} else if ( state == 135 ) {
				
				printf("\tCHAR_LIT\t%d\n", lineNumber);
				fprintf(fOutput," ~ CHAR_LIT ~ %d\n", lineNumber);
				
			} else if ( state == 138 ) {
				
				printf("\tSTR_LIT\t%d\n", lineNumber);
				fprintf(fOutput," ~ STR_LIT ~ %d\n", lineNumber);
				
			} else if ( state == 213 ) {
				
				printf("\tEMP\t%d\n", lineNumber);
				fprintf(fOutput," ~ EMP ~ %d\n", lineNumber);
				
			} else if ( state == 147 ) {
				
				printf("\tVAR_ID\t%d\n", lineNumber);
				fprintf(fOutput," ~ VAR_ID ~ %d\n", lineNumber);
				
			} else if ( state == 150 ) {
				
				printf("\tFN_ID\t%d\n", lineNumber);
				fprintf(fOutput," ~ FN_ID ~ %d\n", lineNumber);
				
			} else if ( state == 194 ) {
				
				printf("\tCOMMENT\t%d\n", lineNumber);
				fprintf(fOutput," ~ COMMENT ~ %d\n", lineNumber);
				
			} else if ( state == 152 ) {
				
				printf("\tPLUS\t%d\n", lineNumber);
				fprintf(fOutput," ~ PLUS ~ %d\n", lineNumber);
				
			} else if ( state == 154 ) {
				
				printf("\tPLUSPLUS\t%d\n", lineNumber);
				fprintf(fOutput," ~ PLUSPLUS ~ %d\n", lineNumber);
				
			} else if ( state == 156 ) {
				
				printf("\tMINUS\t%d\n", lineNumber);
				fprintf(fOutput," ~ MINUS ~ %d\n", lineNumber);
				
			} else if ( state == 158 ) {
				
				printf("\tSUBTSUBT\t%d\n", lineNumber);
				fprintf(fOutput," ~ SUBTSUBT ~ %d\n", lineNumber);
				
			} else if ( state == 160 ) {
				
				printf("\tMULTI\t%d\n", lineNumber);
				fprintf(fOutput," ~ MULTI ~ %d\n", lineNumber);
				
			} else if ( state == 162 ) {
				
				printf("\tINT_DIV\t%d\n", lineNumber);
				fprintf(fOutput," ~ INT_DIV ~ %d\n", lineNumber);
				
			} else if ( state == 164 ) {
				
				printf("\tREAL_DIV\t%d\n", lineNumber);
				fprintf(fOutput," ~ REAL_DIV ~ %d\n", lineNumber);
				
			} else if ( state == 166 ) {
				
				printf("\tMOD\t%d\n", lineNumber);
				fprintf(fOutput," ~ MOD ~ %d\n", lineNumber);
				
			} else if ( state == 168 ) {
				
				printf("\tEXP\t%d\n", lineNumber);
				fprintf(fOutput," ~ EXP ~ %d\n", lineNumber);
				
			} else if ( state == 171 ) {
				
				printf("\tAND\t%d\n", lineNumber);
				fprintf(fOutput," ~ AND ~ %d\n", lineNumber);
				
			} else if ( state == 174 ) {
				
				printf("\tOR\t%d\n", lineNumber);
				fprintf(fOutput," ~ OR ~ %d\n", lineNumber);
				
			} else if ( state == 176 ) {
				
				printf("\tNOT\t%d\n", lineNumber);
				fprintf(fOutput," ~ NOT ~ %d\n", lineNumber);
				
			} else if ( state == 178 ) {
				
				printf("\tNOTEQUAL\t%d\n", lineNumber);
				fprintf(fOutput," ~ NOTEQUAL ~ %d\n", lineNumber);
				
			} else if ( state == 181 ) {
				
				printf("\tEQUAL_TO\t%d\n", lineNumber);
				fprintf(fOutput," ~ EQUAL_TO ~ %d\n", lineNumber);
				
			} else if ( state == 183 ) {
				
				printf("\tGRTR_THAN\t%d\n", lineNumber);
				fprintf(fOutput," ~ GRTR_THAN ~ %d\n", lineNumber);
				
			} else if ( state == 185 ) {
				
				printf("\tGRTR_THAN_OR_EQ\t%d\n", lineNumber);
				fprintf(fOutput," ~ GRTR_THAN_OR_EQ ~ %d\n", lineNumber);
				
			} else if ( state == 187 ) {
				
				printf("\tLESS_THAN\t%d\n", lineNumber);
				fprintf(fOutput," ~ LESS_THAN ~ %d\n", lineNumber);
				
			} else if ( state == 189 ) {
				
				printf("\tLESS_THAN_OR_EQ\t%d\n", lineNumber);
				fprintf(fOutput," ~ LESS_THAN_OR_EQ ~ %d\n", lineNumber);
				
			} else if ( state == 191 ) {
				
				printf("\tEQUALS\t%d\n", lineNumber);
				fprintf(fOutput," ~ EQUALS ~ %d\n", lineNumber);
				
			} else if ( state == 195 ) {
				
				printf("\tL_BRAC\t%d\n", lineNumber);
				fprintf(fOutput," ~ L_BRAC ~ %d\n", lineNumber);
				
			} else if ( state == 196 ) {
				
				printf("\tR_BRAC\t%d\n", lineNumber);
				fprintf(fOutput," ~ R_BRAC ~ %d\n", lineNumber);
				
			} else if ( state == 197 ) {
				
				printf("\tL_BRC\t%d\n",lineNumber);
				fprintf(fOutput," ~ L_BRC ~ %d\n", lineNumber);
				
			} else if ( state == 198 ) {
				
				printf("\tR_BRC\t%d\n",lineNumber);
				fprintf(fOutput," ~ R_BRC ~ %d\n", lineNumber);
				
			} else if ( state == 199 ) {
				
				printf("\tL_PAREN\t%d\n",lineNumber);
				fprintf(fOutput," ~ L_PAREN ~ %d\n", lineNumber);
				
			} else if ( state == 200 ) {
				
				printf("\tR_PAREN\t%d\n",lineNumber);
				fprintf(fOutput," ~ R_PAREN ~ %d\n", lineNumber);
				
			} else if ( state == 300 ) {
				
				printf("\tCOLON\t%d\n",lineNumber);
				fprintf(fOutput," ~ COLON ~ %d\n", lineNumber);
				
			} else if ( state == 301 ) {
				
				printf("\tSCOLON\t%d\n",lineNumber);
				fprintf(fOutput," ~ SCOLON ~ %d\n",lineNumber);
				
			} else if ( state == 302 ) {
				
				printf("\tCOMMA\t%d\n", lineNumber);
				fprintf(fOutput," ~ COMMA ~ %d\n", lineNumber);
				
			} // if (state == 7 )
			else {
				
				
			}
			
			
		} else {
			
			printf("\tINVALID_LEXEME\t%d\n", lineNumber);
			fprintf(fOutput," ~ INVALID_LEXEME ~ %d\n", lineNumber);
			hasError = 1;
			
		} // if ( final )
		
		
		
	} // void displayTokenClass(int final, int state)
