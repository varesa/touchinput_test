#include <iostream>

#include "Serial.h"
#include "MouseUInput.h"
#include "coords.h"
#include "MouseX11.h"

using namespace std;

int main() {
    cout << "Hello, World!" << endl;

    Serial *serial = new Serial("/dev/ttyUSB0");
    MouseX11 *mouse = new MouseX11();

    coords_t coords;


    while(true) {
        coords_t coords = serial->read_coords();
        printf("%d, %d\n", coords.x, coords.y);
        fflush(stdout);

        coords.x = 1024 - (coords.x - 300) / 32.5 - 20;
        coords.y = coords.y / 44 + 15;


        mouse->move(coords);
    }

    return 0;
}