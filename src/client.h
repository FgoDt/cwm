#pragma once
#include "event.h"
#include <X11/Xlib.h>

class client
{
private:
	/* data */
	int width, height;
	//pos
	int x, y;

	bool configureNotify(XConfigureEvent xconfig);
	bool mapNotify(XMapEvent xmap);
	Window titleBar;
	Window leftSide;
	Window rightSide;
	Window bottomSide;
	Window leftBottomCorner;
	Window rightBottomCorner;
	Window handleWindow;

	bool mapped;

public:
	client(Window id);
	~client();

	bool processEvent(shared_ptr<lemonEventData> ev);

	bool canHandleEvent(shared_ptr<lemonEventData> ev);

	Window window();
};
