//
// Created by esa on 1/28/16.
//

#ifndef TOUCHINPUT_SERIAL_H
#define TOUCHINPUT_SERIAL_H

#include <string>
#include "coords.h"

class Serial {
public:
    Serial(std::string port);
    ~Serial();
    coords_t read_coords();

private:
    int fd;
};


#endif //TOUCHINPUT_SERIAL_H
