#include "manager.h"
#include "client.h"
#include <iostream>
#include <unistd.h>

using namespace std;

static manager *ithis = nullptr;

static int errorHandler(Display *display, XErrorEvent *event)
{
	if (event->error_code == BadAccess)
	{
		if (ithis != nullptr)
		{
			ithis->badAccess = true;
		}
	}
	return 0;
}

manager::manager()
{
	lDisplay = make_shared<lemonDisplay>();
	levent = make_unique<lemonEvent>(lDisplay);
	cout << "manager create" << endl;
}

manager::~manager()
{
}

bool manager::init()
{
	lDisplay->open(nullptr);
	ithis = this;
	XSetErrorHandler(errorHandler);
	XSelectInput(lDisplay->xdisplay, lDisplay->rootWindow, SubstructureNotifyMask | SubstructureNotifyMask);
	XSync(lDisplay->xdisplay, 0);
	if (badAccess)
	{
		cout << "has other wm" << endl;
		return false;
	}
	cout << "ok" << endl;
	return true;
}

bool manager::run()
{
	if (badAccess)
	{
		cout << "bad access" << endl;
		return false;
	}

	int i = 0;
	while (i < 100000)
	{
		i++;
		auto event = pollEvent();
		//parseEvent(event);
		handleEvent(event);
		dispatchEvent(event);
		//usleep(1 * 1000);
	}

	return true;
}

shared_ptr<lemonEventData> manager::pollEvent()
{
	auto evdata = levent->poll();
	cout << "go event :" << evdata->desc->c_str() << endl;

	return evdata;
}

//bool manager::parseEvent(shared_ptr<lemonEventData> ev)
//{
//return false;
//}

bool manager::handleEvent(shared_ptr<lemonEventData> ev)
{
	if (ev->xevent.type == CreateNotify)
	{
		shared_ptr<client> cli = make_shared<client>(ev->xevent.xcreatewindow.window);
		clients.push_back(cli);
		cout << "add client: " << cli->window() << " total size: " << clients.size() << endl;
		ev->handled = true;
	}
	else if (ev->xevent.type == DestroyNotify)
	{
		for (auto cli : clients)
		{
			if (cli->window() == ev->xevent.xcreatewindow.window)
			{
				clients.remove(cli);
				cout << "remove client: " << cli->window() << " total size: " << clients.size() << endl;
				ev->handled = true;
				break;
			}
		}
	}
	return false;
}

bool manager::dispatchEvent(shared_ptr<lemonEventData> ev)
{
	if (ev->handled)
	{
		return true;
	}

	for (auto cli : clients)
	{
		//try find client, use map event can get window id
		if (cli->canHandleEvent(ev))
		{
			cli->processEvent(ev);
			break;
		}
	}

	if (!ev->handled)
	{
		cout << "not handle for event: " << ev->desc->c_str() << endl;
	}

	return false;
}