#pragma once

extern "C"
{
#include <X11/Xlib.h>
}

using namespace std;

class lemonDisplay
{
private:
    //int errorHandler(Display *display, XErrorEvent *event);

public:
    lemonDisplay();
    ~lemonDisplay();

    bool open(const char *name);

    int height;
    int width;
    Display *xdisplay;
    Window rootWindow;
};
