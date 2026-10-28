#include "stdlib.h"
#include "math.h"


void main() {

	srand(time(0)); //Random Number Seed
	int min = 1, max = 8;
	int finished = 1;

	intBoard();

	//Set alarm pin
	//setUPDOWN_OUTPUT(0);
	//setALARM(1);
	
	//flashLEDActionUPDOWN(6);
	
	
	//lightLED(1); THIS SETS THE ALARM PIN TO 0.35V
	//while (1) {
	//	Sleep(500);   
	//	getALARMInput();
	//}
	
	/*------------------------------------------------------------------*/
	/*FIRE ALARM*/
	/*------------------------------------------------------------------*/

	int solving = 1;
	
	printf("SOLVING 'FIRE ALARM'\n");

	while (solving) {

		//When not pulled 14, when IS pulled 15

		int input = 6;

		while (input == 6) { //Wait for input
			input = getUPDOWN_INPUTInput();
		}

		printf("%d\n", input);
		
		if (input == 7) {

			printf("Fire alarm complete!\n");
			solving = 0;
		}
		

	}

	printf("FINISHED 'FIRE ALARM'\n\n");


	/*------------------------------------------------------------------*/
	/*ROLLING BALL*/
	/*------------------------------------------------------------------*/

	solving = 1;
	printf("\n");

	printf("SOLVING 'ROLLING BALL'\n");
	
	while (solving) { //Ball rolling input part

		int input = 7;

		while (input == 7) { //Wait for input
			input = getUPDOWN_INPUTInput();
		}

		printf("%d\n", input);
		
		if (input == 6) {

			printf("Ball Rolling complete!");
			solving = 0;
		}
		

	}
	

	printf("FINISHED 'ROLLING BALL'\n\n");


	/*------------------------------------------------------------------*/
	/*CALL ELEVATOR PANEL*/
	/*------------------------------------------------------------------*/
	
	solving = 1;

	printf("SOLVING 'CALL ELEVATOR PANEL'\n");

	while (solving) {

		//13 is up, 11 is down
		int sequence[] = {4, 4, 2, 4, 2, 2, 2, 2, 4, 2};

		for (int i = 0; i <= 9; i++) {

			int currentVal = sequence[i];
			int input = 6; //Should be 6 or 7 depending on ball position

			while (input == 6 || input == 7) { //Wait for input
				input = getUPDOWN_INPUTInput();
			}

			printf("%d", input);
			
			if (currentVal == input) {

				if (input == 4) { //Up input is 4

					flashLEDActionUPDOWN(2);

				} else { //Down input is 2

					flashLEDActionUPDOWN(4);
				}

			} else {

				i = -1;
				printf("RESTART SECQUENCE\n");
				flashLEDActionUPDOWN(6);
			}
			

			Sleep(500);

		}

		solving = 0;

	}

	printf("FINISHING 'CALL ELEVATOR PANEL'");

	/*------------------------------------------------------------------*/
	/*ELEVATOR PANEL*/
	/*------------------------------------------------------------------*/

	solving = 1;
	printf("\n");

	printf("SOLVING 'CALL ELEVATOR PANEL'");

	while (solving) {

		int input = 255;
		
		while (input == 255) { //Wait for input
			input = getButtonInput();
			flashLED(7);
			Sleep(250);
		}

		printf("%d", input);

		if (input == 191) {
			//TBD INSERT SHAKING CODE THAT SHAKES ELEVATOR ROOM

			solving = 0;
		}

	}

	while (finished) { //While solving sequence
		int sequence[8]; //The button # to be flashed (ex. 1, 3, 6, 8, etc.)

		restart: //If wrong input code will restart from here
		printf("\n");
		printf("\n");

		for (int i = 1; i <= 8; i++) { //Set sequence

			sequence[i - 1] = (rand() % max) + min;
			printf("%d, ", sequence[i - 1]);
		}

		printf("\n");

		for (int i = 1; i <= 8; i++) { //Go through sequence

			for (int y = 1; y <= i; y++) { //Display sequence to LEDs
				flashLED(sequence[y - 1]);
			}

			int input = 255;

			for (int y = 1; y <= i; y++) { //Take input from buttons
				int input = 255;
				
				while (input == 255) { //Wait for input
					input = getButtonInput();
				} 
				
				//printf("%d", 255-((int)pow(2, (sequence[y - 1])-1)));
				//printf(" %d ", input);
				//printf("\n");

				if (input == buttonInputChecker(sequence[y - 1]) ) { //Check for correct input AND if all inputs are over

					lightLED(255- input);
					printf("Correct ");
				} else { //Check for incorrect input
					
					printf("Incorrect ");
					flashLED(9);
					Sleep(10000);
					flashLED(0);

					goto restart;
				}
				Sleep(250); //Wait time between buttons
			}
			//Flash all LED buttons twice to indicate correct input sequence for round
			flashLED(9);
			Sleep(333);
			flashLED(0); 
			Sleep(333);
			flashLED(9);
			Sleep(333);
			flashLED(0);

			printf("\n");
			printf("\n");
		}

	}

	printf("FINISHING 'CALL ELEVATOR PANEL'");

	printf("\n");
	flashLED(0); //Reset board input

	return;
}

int buttonInputChecker(checkingvalue) { //Input an array value for conversion

	switch (checkingvalue) {
		case 6:
			return 254;
		case 5:
			return 253;
		case 4:
			return 251;
		case 2:
			return 247;
		case 1:
			return 239;
		case 3:
			return 223;
		case 7: //Lobby
			return 191;
		case 8: //Parking
			return 127;
		default:
			printf("Invalid Input");
			return 0;
		}
}