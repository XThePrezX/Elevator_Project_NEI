/* Include files */
#include "..\cbw.h"
#include "Utilities.h"
#include "windows.h"
#include "Analog.h"
#include "Board.h"
#include "cbw.h"
#include "Counters.h"
#include "Digital.h"

/* Variable Declarations */
//Board Variables
float			RevLevel = (float)CURRENTREVNUM;
static char		BoardName[BOARDNAMELEN];
static int		BoardNum = 0;	//See InstaCal to identify board #; (ex. 0, 1, 2, ...)

//LED Variables
static char		portTypeStrLED[PORTTYPENAMELEN];
static int		PortNumLED = 10; //See user's guide for ports; #'s are something like (ex. 10 for A, 11, 12, 13, ...)
static int		DirectionLED = DIGITALOUT; //Port recieves input or output; (ex. DIGITALOUT, DIGITALIN)

//Button Variables
static char		portTypeStrBUTTON[PORTTYPENAMELEN];
static int		PortNumBUTTON = 11; //See user's guide for ports; #'s are something like (ex. 10 for A, 11, 12, 13, ...)
static int		DirectionBUTTON = DIGITALIN; //Port recieves input or output; (ex. DIGITALOUT, DIGITALIN)

// UPDOWN_INPUT variables
static char		portTypeStrUPDOWN_INPUT[PORTTYPENAMELEN];
static int		PortNumUPDOWN_INPUT = 12; //See user's guide for ports; #'s are something like (ex. 10 for A, 11, 12, 13, ...)
static int		DirectionUPDOWN_INPUT = DIGITALIN;

// UPDOWN_OUTPUT variables
static char		portTypeStrUPDOWN_OUTPUT[PORTTYPENAMELEN];
static int		PortNumUPDOWN_OUTPUT = 13; //See user's guide for ports; #'s are something like (ex. 10 for A, 11, 12, 13, ...)
static int		DirectionUPDOWN_OUTPUT = DIGITALOUT;

 void intBoard()
{
	/* Library and board intialization */
	cbDeclareRevision(&RevLevel); //Initializes the Universal Library with the revision number of the library used to write your program
	InitUL(); //Set up error handling

	/* Set board and port names */
	GetNameOfBoard(BoardNum, BoardName); //Set BoardName and some other things

	GetNameOfPortType(PortNumLED, portTypeStrLED); //LED
	GetNameOfPortType(PortNumBUTTON, portTypeStrBUTTON); //Button

	GetNameOfPortType(PortNumUPDOWN_INPUT, portTypeStrUPDOWN_INPUT); //UPDOWN_INPUT
	GetNameOfPortType(PortNumUPDOWN_OUTPUT, portTypeStrUPDOWN_OUTPUT); //UPDOWN_OUTPUT


	/* Set the display screen */
	printf("Name: %s, Board#: %d\n", BoardName, BoardNum);

	printf("LED Port: %s (%d)\n", portTypeStrLED, PortNumLED);
	printf("UPDOWN_INPUT: %s (%d)\n", portTypeStrUPDOWN_INPUT, PortNumUPDOWN_INPUT);
	printf("UPDOWN_OUTPUT: %s (%d)\n", portTypeStrUPDOWN_OUTPUT, PortNumUPDOWN_OUTPUT);
	printf("Button Port: %s (%d)\n", portTypeStrBUTTON, PortNumBUTTON);
	printf("\n");


	flashLEDAction(0);
}

 void flashLED(int LEDNumber) {

	 if (LEDNumber != 9 && LEDNumber != 0) {
		 printf("%d:", LEDNumber);
	 }


	 switch (LEDNumber) {
		 case 6:
			 flashLEDAction(1);
			 break;
		 case 5:
			 flashLEDAction(2);
			 break;
		 case 4:
			 flashLEDAction(4);
			 break;
		 case 2:
			 flashLEDAction(8);
			 break;
		 case 1:
			 flashLEDAction(16);
			 break;
		 case 3:
			 flashLEDAction(32);
			 break;
		 case 7: //Lobby
			 flashLEDAction(64);
			 break;
		 case 8: //Parking
			 flashLEDAction(128);
			 break;
		 case 9: //Set all
			 flashLEDAction(255);
			 break;
		 case 0: //Reset
			 flashLEDAction(0);
			 break;
		 default:
			 printf("Invalid Input");
			 break;
	 }
}

 static flashLEDAction(int pin) {

	 //Set device to output mode
	 setPortDirectionLED(DIGITALOUT, pin);

	 if (pin != 0 && pin != 255) {

		 Sleep(500); // 1/2 Second delay between button flashes
		 printf("The value %d was written to %s", pin, portTypeStrLED);
		 printf("\n");
		 flashLEDAction(0);
	 }
	 
 }

 void flashLEDActionUPDOWN(int pin) {

	 //Set device to output mode
	 setPortDirectionUPDOWN_OUTPUT(DIGITALOUT, pin);

	 if (pin != 0 && pin != 15) {

		 Sleep(500); // 1/2 Second delay between button flashes
		 printf("The value %d was written to %s", pin, portTypeStrUPDOWN_OUTPUT);
		 printf("\n");
		 flashLEDActionUPDOWN(0);
	 }

 }

 void lightLED(pin) {

	 setPortDirectionLED(DIGITALOUT, pin);
 }

 void setUPDOWN_OUTPUT(pin) { //value being written

	 setPortDirectionUPDOWN_OUTPUT(DIGITALOUT, pin);
 }

 static setPortDirectionLED(int direction, int portPin) {

	 DirectionLED = direction;
	 cbDConfigPort(BoardNum, PortNumLED, DirectionLED);
	 cbDOut(BoardNum, PortNumLED, portPin);
 }

 static setPortDirectionUPDOWN_OUTPUT(int direction, int portPin) {

	 DirectionUPDOWN_OUTPUT = direction;
	 cbDConfigPort(BoardNum, PortNumUPDOWN_OUTPUT, DirectionUPDOWN_OUTPUT);
	 cbDOut(BoardNum, PortNumUPDOWN_OUTPUT, portPin);
 }


 static setPortDirectionBUTTON(int direction, int pin) {

	 DirectionBUTTON = direction;
	 cbDConfigPort(BoardNum, PortNumBUTTON, DirectionBUTTON);
	 cbDOut(BoardNum, PortNumBUTTON, pin);
 }

 int getButtonInput() {

	 int output = 0;
	 int *ptr = &output;

	 //Set device to input mode
	 DirectionBUTTON = DIGITALIN;
	 cbDConfigPort(BoardNum, PortNumBUTTON, DirectionBUTTON);
	 cbDIn(BoardNum, PortNumBUTTON, ptr);

	 //printf("%d");
	 return output;
 }

 int getUPDOWN_INPUTInput() {

	 int output = 0;
	 int* ptr = &output;

	 //Set device to input mode
	 DirectionUPDOWN_INPUT = DIGITALIN;
	 cbDConfigPort(BoardNum, PortNumUPDOWN_INPUT, DirectionUPDOWN_INPUT);
	 cbDIn(BoardNum, PortNumUPDOWN_INPUT, ptr);

	 //printf("%d");
	 return output;
 }