#include "stdlib.h"
#include "math.h"


void main() {

	srand(time(0)); //Random Number Seed
	int min = 1, max = 8;
	int finished = 1;

	intBoard();

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

				if (input == (255-((int)pow(2, (sequence[y - 1])-1)))) { //Check for correct input AND if all inputs are over

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

	printf("\n");
	flashLED(0); //Reset board input

	return;
}