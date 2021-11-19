#include "event.h"
#include <iostream>

using namespace std;

lemonEvent::lemonEvent(shared_ptr<lemonDisplay> dp) : lDisplay(dp)
{
}

lemonEvent::~lemonEvent()
{
}

shared_ptr<lemonEventData> lemonEvent::poll()
{

	auto event = make_shared<lemonEventData>();

	XEvent e;
	XNextEvent(lDisplay->xdisplay, &e);
	string desc;

	switch (e.type)
	{
	case KeyPress:
		desc = "KeyPress";
		break;
	case KeyRelease:
		desc = ("KeyRelease");
		break;
	case ButtonPress:
		desc = ("ButtonPress");
		break;
	case ButtonRelease:
		desc = ("ButtonRelease");
		break;
	case MotionNotify:
		desc = ("MotionNotify");
		break;
	case EnterNotify:
		desc = ("EnterNotify");
		break;
	case LeaveNotify:
		desc = ("LeaveNotify");
		break;
	case FocusIn:
		desc = ("FocusIn");
		break; //9
	case FocusOut:
		desc = "FocusOut";
		break; //10
	case KeymapNotify:
		desc = "KeymapNotify";
		break; //11
	case Expose:
		desc = "Expose";
		break; //12
	case GraphicsExpose:
		desc = "GraphicsExpose";
		break; //13
	case NoExpose:
		desc = "NoExpose";
		break; //14
	case VisibilityNotify:
		desc = "VisibilityNotify";
		break; //15
	case CreateNotify:
		desc = ("CreateNotify");
		break; //16
	case DestroyNotify:
		desc = ("DestroyNotify");
		break; //17
	case UnmapNotify:
		desc = ("UnmapNotify");
		break; //18
	case MapNotify:
		desc = ("MapNotify");
		break; //19
	case MapRequest:
		desc = ("MapRequest");
		break; //20
	case ReparentNotify:
		desc = "ReparentNotify";
		break; //21
	case ConfigureNotify:
		desc = ("ConfigureNotify");
		break; //22
	case ConfigureRequest:
		desc = "ConfigureRequest";
		break; //23
	case GravityNotify:
		desc = "GravityNotify";
		break; //24
	case ResizeRequest:
		desc = "ResizeRequest";
		break; //25
	case CirculateNotify:
		desc = "CirculateNotify";
		break; //26
	case CirculateRequest:
		desc = "CirculateRequest";
		break; //27
	case PropertyNotify:
		desc = "PropertyNotify";
		break; //28
	case SelectionClear:
		desc = "SelectionClear";
		break; //29
	case SelectionRequest:
		desc = "SelectionRequest";
		break; //30
	case SelectionNotify:
		desc = "SelectionNotify";
		break; //31
	case ColormapNotify:
		desc = "ColormapNotify";
		break; //32
	case ClientMessage:
		desc = "ClientMessage";
		break; //33
	case MappingNotify:
		desc = "MappingNotify";
		break; //34
	case GenericEvent:
		desc = "GenericEvent";
		break; //35
	case LASTEvent:
		desc = "LASTEvent";
		break; //36	/* must be bigger than any event # */

	default:
		desc = "UNKONW Event";
		break;
	}

	event->desc = make_shared<string>(desc);
	event->xevent = e;
	return event;
}
