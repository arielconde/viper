#include <stdio.h>
#include <string.h>
FILE * fSignal ;
int willProceed = 0;
int main(int argc, char *argv[]) {
	
	char command[100];
	sprintf(command, "VL %s", argv[1]);
	system(command); // VL writes a okay or not to the signal.txt
	
	fSignal = fopen("signal.txt", "r");
	fscanf(fSignal, "%d", &willProceed);
	if (willProceed == 1) {
		printf("Can't continue compiling.");
		getch();
		fclose(fSignal);
		return 0;
	}
	fclose(fSignal);
	getch();
	
	sprintf(command, "VP symbolTable_%s", argv[1]);
	system(command);
	fSignal = fopen("signal.txt", "r");
	fscanf(fSignal, "%d", &willProceed);
	if (willProceed == 1) {
		printf("Can't continue compiling.\n");
		getch();
		fclose(fSignal);
		return 0;
	}
	fclose(fSignal);
	printf("\n\n\n\n");
	getch();
	
	printf("Checking variables:\n");
	sprintf(command, "VV symbolTable_%s", argv[1]);
	system(command);
//	fSignal = fopen("signal.txt", "r");
//	fscanf(fSignal, "%d", &willProceed);
//	if (willProceed == 1) {
//		printf("Can't continue compiling.");
//		getch();
//		fclose(fSignal);
//		return 0;
//	}
//	fclose(fSignal);
	getch();
	
	
	sprintf(command, "VS PTREE.TXT", argv[1]);
	system(command);
//	

	
	return 0;
}
