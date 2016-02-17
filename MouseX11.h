//
// Created by esa on 1/29/16.
//

#ifndef TOUCHINPUT_MOUSEX11_H
#define TOUCHINPUT_MOUSEX11_H


#include "coords.h"

#include <X11/Xlib.h>

class MouseX11 {
public:
    MouseX11();

    void move(coords_t coords);

private:
    Display *dpy;
};


#endif //TOUCHINPUT_MOUSEX11_H
