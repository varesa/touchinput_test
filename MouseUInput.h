//
// Created by esa on 1/28/16.
//

#ifndef TOUCHINPUT_MOUSE_H
#define TOUCHINPUT_MOUSE_H


#include "coords.h"

class MouseUInput {
public:
    MouseUInput();
    void move(coords_t coords);

private:
    int fd;
};


#endif //TOUCHINPUT_MOUSE_H
