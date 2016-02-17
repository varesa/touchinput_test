//
// Created by esa on 1/28/16.
//

#include <fcntl.h>
#include <stdio.h>
#include <sys/ioctl.h>

#include <linux/input.h>
#include <linux/uinput.h>
#include <string.h>
#include <unistd.h>

#include "MouseUInput.h"

MouseUInput::MouseUInput() {
    fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
    if(fd == -1) {
        perror("Unable to open input device");
    }

    if(ioctl(fd, UI_SET_EVBIT, EV_ABS) < 0) perror("error");
    if(ioctl(fd, UI_SET_ABSBIT, ABS_X) < 0) perror("error");
    if(ioctl(fd, UI_SET_ABSBIT, ABS_Y) < 0) perror("error");

    struct uinput_user_dev uidev;
    memset(&uidev, 0, sizeof(uidev));

    snprintf(uidev.name, UINPUT_MAX_NAME_SIZE, "serial-touch");

    uidev.id.bustype = BUS_RS232;
    uidev.id.vendor = 0x1;
    uidev.id.product = 0x1;
    uidev.id.version = 1;

    uidev.absmin[ABS_X] = 0;
    uidev.absmin[ABS_Y] = 0;
    uidev.absmax[ABS_X] = 1024;
    uidev.absmax[ABS_Y] = 1024;

    write(fd, &uidev, sizeof(uidev));
    if(ioctl(fd, UI_DEV_CREATE) < 0) perror("error");
}

void MouseUInput::move(coords_t coords) {
    struct input_event ev[2];
    memset(&ev, 0, sizeof(struct input_event)*2);
    ev[0].type = EV_ABS;
    ev[0].code = ABS_X;
    ev[0].value = coords.x;
    ev[1].type = EV_ABS;
    ev[1].code = ABS_Y;
    ev[1].value = coords.y;

    write(fd, ev, sizeof(ev));
}