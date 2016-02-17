//
// Created by esa on 1/28/16.
//

#include "Serial.h"
#include "coords.h"

#include <stdio.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <ostream>
#include <iostream>

Serial::Serial(std::string port) {
    fd = open(port.c_str(), O_RDONLY | O_NOCTTY | O_NDELAY);

    if(fd == -1) {
        perror("Error opening port");
    }

    //fcntl(fd, F_SETFL, FNDELAY); // Set non-blocking mode
    fcntl(fd, F_SETFL, 0);

    struct termios options;
    tcgetattr(fd, &options);

    cfsetispeed(&options, B9600);
    cfsetospeed(&options, B9600);

    options.c_cflag &= ~PARENB; // 8N1
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;

    options.c_cflag |= (CLOCAL | CREAD);

    options.c_lflag &= ~(ISIG | ICANON | ECHO | ECHOE); // RAW input



    tcsetattr(fd, TCSANOW, &options);
}

Serial::~Serial() {
    close(fd);
}

coords_t Serial::read_coords() {
    coords_t coords;

    uint8_t buf[4];
    while(true) {
        read(fd, buf, 1);

        if(buf[0] == 0xD8) {
            printf("Package begin!\n");
            read(fd, buf+0, 1);
            read(fd, buf+1, 1);
            read(fd, buf+2, 1);
            read(fd, buf+3, 1);
            coords.lifted = false;
            coords.x = (uint16_t) (buf[1] * 256 + buf[0]);
            coords.y = (uint16_t) (buf[3] * 256 + buf[1]);

            if(coords.x < 33000 && coords.y < 33000) return coords;
        } else if (buf[0] == 0x98){
            printf("Finger up?\n");
            read(fd, buf+0, 1);
            read(fd, buf+1, 1);
            read(fd, buf+2, 1);
            read(fd, buf+3, 1);
            coords.lifted = true;
            coords.x = (uint16_t) (buf[1] * 256 + buf[0]);
            coords.y = (uint16_t) (buf[3] * 256 + buf[1]);

            if(coords.x < 33000 && coords.y < 33000) return coords;
        }
    }
}