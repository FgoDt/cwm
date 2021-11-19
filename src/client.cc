#include "client.h"
#include <iostream>

using namespace std;

client::client(Window id)
{
	handleWindow = id;
}

client::~client()
{
}

bool client::configureNotify(XConfigureEvent xconfig)
{
	if (xconfig.override_redirect)
	{
		cout << "override redirect" << endl;
		return true;
	}
	if (xconfig.above != None)
	{
		cout << "above window" << xconfig.above << endl;
		return true;
	}
	x = xconfig.x;
	y = xconfig.y;
	width = xconfig.width;
	height = xconfig.height;
	cout << "got configure notify event width " << xconfig.width << " height " << xconfig.height << " x " << xconfig.x << " y " << xconfig.y << endl;
	return false;
}

bool client::mapNotify(XMapEvent xmap)
{
	cout << "got map notify" << endl;

	XWindowAttributes attrs;
	XGetWindowAttributes(xmap.display, xmap.window, &attrs);

	if (attrs.override_redirect || attrs.map_state != IsViewable)
	{
		return;
	}

	XMapWindow(xmap.display, xmap.window);

	return false;
}

bool client::processEvent(shared_ptr<lemonEventData> ev)
{

	switch (ev->xevent.type)
	{
	case ConfigureNotify:
		configureNotify(ev->xevent.xconfigure);
		break;

	case MapNotify:
		mapNotify(ev->xevent.xmap);
		break;

	default:
		return true;
	}
	ev->handled = true;
	return false;
}

bool client::canHandleEvent(shared_ptr<lemonEventData> ev)
{
	auto target = ev->xevent.xmap.window;
	if (target == handleWindow)
	{
		ev->target = event_target_handle_window;
	}
	else if (target == titleBar)
	{
		ev->target = event_target_title_bar;
	}
	else if (target == leftSide)
	{
		ev->target = event_target_left_side;
	}
	else if (target == rightSide)
	{
		ev->target = event_target_right_side;
	}
	else if (target == bottomSide)
	{
		ev->target = event_target_bottom_side;
	}
	else if (target == leftBottomCorner)
	{
		ev->target = event_target_left_bottom_corner;
	}
	else if (target == rightBottomCorner)
	{
		ev->target = event_target_right_bottom_corner;
	}
	else
	{
		ev->target = event_target_unknow;
	}
	if (ev->target == event_target_unknow)
	{
		return false;
	}
	return true;
}

Window client::window()
{
	return handleWindow;
}