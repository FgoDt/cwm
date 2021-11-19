#include "display.h"
#include <iostream>

using namespace std;

lemonDisplay::lemonDisplay()
{
    xdisplay = nullptr;
    rootWindow = 0;
    height = 0;
    width = 0;
}

bool lemonDisplay::open(const char *name)
{
    xdisplay = XOpenDisplay(name);
    if (xdisplay == nullptr)
    {
        cout << "open display error" << endl;
        return false;
    }
    rootWindow = XDefaultRootWindow(xdisplay);
    if (rootWindow == 0)
    {
        cout << "get default root window error" << endl;
        return false;
    }
    return true;
}

lemonDisplay::~lemonDisplay()
{
    XCloseDisplay(xdisplay);
}
