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
        mvprintw(1, 1,"%s: Press 'q' to end program", argv[0]);
        if (initio_IrLeft()==0 && initio_IrRight()==0) {
                // no obstacle ahead, so follow line
                int lfL = initio_IrLineLeft();
                int lfR = initio_IrLineRight();
                if (lfL == 0 && lfR == 0) { 
                mvprintw(3, 1,"Action 2: Straight (Line sensors: %d, %d)    ", lfL, lfR);
                // todo: move straight forward
                initio_DriveForward (100); 
                }
                else if (lfL == 0 && lfR == 1) {
                // car is too much on the right
                mvprintw(3, 1,"Action 3: Spin left (Line sensors: %d, %d)    ", lfL, lfR);
                // todo: turn left
                initio_SpinLeft(100);   
                //initio_TurnForward(0, 100);
                }
                else if (lfL == 1 && lfR == 0) {
                // car is too much on the left
                mvprintw(3, 1,"Action 4: Spin right (Line sensors: %d, %d)    ", lfL, lfR);
                initio_SpinRight(100);  
                }
                else {
                mvprintw(3, 1,"Lost my line (Line sensors: %d, %d)        ", lfL, lfR);
                // todo: Stop
                initio_DriveReverse(30);
                }
        }
        else {
                initio_DriveForward (0); // Stop
        } // if
        ch = getch();
        if (ch != ERR){
                mvprintw(2, 1,"Key code: '%c' (%d)", ch, ch);
                refresh();
                delay (50); // pause 100ms
        } // while
        ch = getch();
}
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


