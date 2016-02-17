//
// Created by esa on 1/29/16.
//

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <stdlib.h>
#include "MouseX11.h"
#include "coords.h"

MouseX11::MouseX11() {
    dpy = XOpenDisplay(0);
}

/*ButtonPress event, serial 36, synthetic NO, window 0x2a00001,
root 0x1c5, subw 0x2a00002, time 176900672, (57,47), root:(94,148),
                                                          state 0x10, button 1, same_screen YES
*/

XButtonEvent createButtonEvent(Display *display, Window &win, Window &winRoot, bool press,
                               int keycode, int modifiers) {
    XButtonEvent event;

    event.display     = display;
    event.window      = win;
    event.root        = winRoot;
    event.subwindow   = None;
    event.time        = CurrentTime;
    event.x           = 1;
    event.y           = 1;
    event.x_root      = 1;
    event.y_root      = 1;
    event.same_screen = True;
    event.button      = 1;
    event.state       = modifiers;

    if(press)
        event.type = ButtonPress;
    else
        event.type = ButtonRelease;

    return event;
}

XKeyEvent createKeyEvent(Display *display, Window &win, Window &winRoot, bool press,
                         int keycode, int modifiers) {
    XKeyEvent event;

    event.display     = display;
    event.window      = win;
    event.root        = winRoot;
    event.subwindow   = None;
    event.time        = CurrentTime;
    event.x           = 1;
    event.y           = 1;
    event.x_root      = 1;
    event.y_root      = 1;
    event.same_screen = True;
    event.keycode     = XKeysymToKeycode(display, keycode);
    event.state       = modifiers;

    if(press)
        event.type = KeyPress;
    else
        event.type = KeyRelease;

    return event;
}


void MouseX11::move(coords_t coords) {
    Window root_window = XRootWindow(dpy, 0);
    XSelectInput(dpy, root_window, KeyReleaseMask);
    XWarpPointer(dpy, None, root_window, 0, 0, 0, 0, coords.x, coords.y);
    XSync(dpy, false);
    XFlush(dpy);

    if (coords.lifted) {
        system("xdotool click 1");
    }
}