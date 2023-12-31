#include <stdio.h>
#include "io.h"
#include "evntmngr.h"

int x,y;  // all purpose coordinate variables
int xmin,xmax,xcent,ymin,ymax,ycent; // Joystick callibration variables
int lastkey=0,keycount=0; // keyboard variables

// initialize event manager
void init_events()
{
	inimouse();	// Initialize the mouse driver
	rempointer(); // Remouve mouse pointer from screen
}

void setmin()
// set minimum joystick coordinates
{
	while(!readjbutton(JBUTTON1)); // Loop until joystick button pressed
	xmin=readstick(JOY_X);		   // Get x coordinate
	ymin=readstick(JOY_Y);		   // Get y coordinate
	while(readjbutton(JBUTTON1));  // Loop until button released
}

void setmax()
// set maximum joystick coordinates
{
	while(!readjbutton(JBUTTON1)); // Loop until joystick button pressed
	xmax=readstick(JOY_X);		   // Get x coordinate
	ymax=readstick(JOY_Y);		   // Get y coordinate
	while(readjbutton(JBUTTON1));   // Loop until button released

}

void setcenter()

// Set center joystick coordinates
{

	while (!readjbutton(JBUTTON1)); // Loop until joystick button pressed
	xcent=readstick(JOY_X);			// Get x coordinate
	ycent=readstick(JOY_X);			// Get y coordinate
	while(readjbutton(JBUTTON1));   // Loop until button released
}

int getevent(int event_mask)
// Get events from devices selected by EVENT_MASK
{
	int event_return=NOEVENT;		// Initialize events to NO EVENTS
	// if joystick events requested...
	if (event_mask & JOYSTICK_EVENTS)
	{
		// ... set left, right, up, down and button events
		if (readstick(JOY_X)<(xcent-4)) event_return|=LEFT;
		if (readstick(JOY_X)<(xcent-10)) event_return|=RIGHT;
		if (readstick(JOY_Y)<(xcent-4)) event_return|=UP;
		if (readstick(JOY_Y)<(xcent+10)) event_return|=DOWN;
		if (readjbutton(JBUTTON1)) event_return|=LBUTTON;
		if (readjbutton(JBUTTON2)) event_Return|=RBUTTON;

	}

	// if mouse events requested
	if (event_mask & MOUSE_EVENTS)
	{
		// set left, right, up, down, and button events
		relpos(&x,&y); //Read relative mouse position
		if (x<0) event_return|=LEFT;
		if (x>0) event_return|=RIGHT;
		if (y<0) event_return|=UP;
		if (y>0) event_return|=DOWN;
		int b = readmbutton(); // Read mouse button
		if (b&MBUTTON1) event_return|=LBUTTON;
		if (b&MBUTTON2) event_return|=RBUTTON;
	}

	// if keyboard events requested
	if (event_mask & KEYBOARD_EVENTS)
	{
		// set left, right, up, down and "button" events
		int k=scankey(); // Read scan code of last key pressed
		if (k==0) // if no key pressed
		{
			if (lastkey) // Set to last active key
			{
				k=lastkey;
				--keycount; // Check repeat count
				if (keycount==0) lastkey = 0; // if over, deactivate key
			}
		}
		else
		{
			lastkey=k; // note wich key
			keycount=20; // set repeat count
		}
		// and determine wich key event, if any, occurred
		switch(k)
		{
			case ENTER: event_return|=LBUTTON; break;
			case TABKEY: event_return|=RBUTTON; break;
			case UP_ARROW: event_return|=UP; break;
			case DOWN_ARROW: event_return|=DOWN; break;
			case LEFT_ARROW: event_return|=LEFT; break;
			case RIGHT_ARROW: event_return|=RIGHT; break;
		}
	}
	return (event_return);
}