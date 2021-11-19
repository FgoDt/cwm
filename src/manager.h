#pragma once
#include "client.h"
#include "display.h"
#include "event.h"
#include <list>
#include <memory>

class manager
{
private:
	shared_ptr<lemonDisplay> lDisplay;
	unique_ptr<lemonEvent> levent;
	bool exit;

	shared_ptr<lemonEventData> pollEvent();
	//bool parseEvent(shared_ptr<lemonEventData> ev);
	bool handleEvent(shared_ptr<lemonEventData> ev);
	bool dispatchEvent(shared_ptr<lemonEventData> ev);

	list<shared_ptr<client>> clients;

public:
	bool init();

	bool run();

	bool badAccess;

	manager();
	~manager();
};
