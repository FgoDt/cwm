#include <iostream>
#include <memory>

#include "display.h"
#include "manager.h"

using namespace std;

int main()
{
    cout << "start lemon window manager" << endl;

    unique_ptr<manager> lmanager = make_unique<manager>();

    auto ret = lmanager->init();
    if (!ret)
    {
        cout << "init display error exit" << endl;
        exit(-1);
    }

    lmanager->run();

    return 0;
}