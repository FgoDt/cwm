#pragma once
#include "display.h"
#include <memory>

enum targetType
{
	event_target_unknow,
	event_target_handle_window,
	event_target_title_bar,
	event_target_left_side,
	event_target_right_side,
	event_target_bottom_side,
	event_target_left_bottom_corner,
	event_target_right_bottom_corner,
};

struct lemonEventData
{
	targetType target;
	XEvent xevent;
	bool handled;
	shared_ptr<string> desc;
};

class lemonEvent
{
private:
	shared_ptr<lemonDisplay> lDisplay;
	/* data */
public:
	lemonEvent(shared_ptr<lemonDisplay> dp);
	~lemonEvent();

	shared_ptr<lemonEventData> poll();
};
