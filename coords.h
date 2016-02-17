//
// Created by esa on 1/28/16.
//

#ifndef TOUCHINPUT_COORDS_H
#define TOUCHINPUT_COORDS_H

#include <stdint.h>

typedef struct {
    uint16_t x;
    uint16_t y;
    bool lifted;
} coords_t;

#endif //TOUCHINPUT_COORDS_H
