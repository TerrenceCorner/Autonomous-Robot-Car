//======================================================================
// license: GNU LESSER GENERAL PUBLIC LICENSE
//          Version 2.1, February 1999
//          (for details see LICENSE file)
//
// Compilation: 
// gcc -o testIR -Wall -Werror -lcurses -lwiringPi -lpthread -linitio testIR.c
//
//======================================================================

#include <stdlib.h>
#include <initio.h>
#include <curses.h>

//======================================================================
// testIR():
// Simple program to test infrared obstacle sensors:
// Drive forward and stop whenever an obstacle is detected by either
// the left or right infrared (IR) sensor.
//======================================================================
void testIR(int argc, char *argv[]) 
{
	int ch = 0;
	while (ch != 'q') {
	mvprintw(1, 1,"%d", initio_IrLineLeft());
	if (initio_IrLineLeft() > initio_IrLineRight()){
		initio_TurnForward(100, 5);
	}
	if (initio_IrLineRight() > initio_IrLineLeft()){
		initio_TurnForward(5, 100);
	}
	if ((initio_IrLineRight() == 1) && (initio_IrLineLeft() == 1)){
		initio_DriveForward(100);
	}
	ch = getch();


	if (ch != ERR)
		mvprintw(2, 1,"Key code: '%c' (%d)", ch, ch);
		refresh();
		delay (100); // pause 100ms
		} // while

	return;
}


//======================================================================
// main(): initialisation of libraries, etc
//======================================================================
int main (int argc, char *argv[])
{
	WINDOW *mainwin = initscr();  // curses: init screen
	noecho ();                    // curses: prevent the key being echoed
	cbreak();                     // curses: disable line buffering 
	nodelay(mainwin, TRUE);       // curses: set getch() as non-blocking 
	keypad (mainwin, TRUE);       // curses: enable detection of cursor and other keys

	initio_Init (); // initio: init the library

	testIR(argc, argv);

	initio_Cleanup ();  // initio: cleanup the library (reset robot car)
	endwin();           // curses: cleanup the library
	return EXIT_SUCCESS;
}


