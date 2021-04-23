#include <cstdint>
#include <mbed.h>
#include <math.h>
#include "DigitalOut.h"
#include "PinNames.h"
#include "SerialBase.h"
#include "UnbufferedSerial.h"
#include "controller.h"
#include "encoder.h"
#include "mbed.h"
#include "debugger.h"
#include "multi_motor.h"
#include "roboken.h"
#include "roboken/roboken.h"
#include "steer.h"
#include "switch.h"
#include "xbee_debug.h"

roboken::Controller con;

int main(void) {
    roboken::initializer();
    roboken::Debugger::initializer(roboken::Debugger::device_xbee);
    con.AbsStart();

    Steer steer;
    steer.init();

    // roboken::Encoder enc(11, 1, 2, true, false);
    // enc.init();

    // while(true) {
    //     roboken::Debugger::info("x:%d y:%d", enc.get_enc1(), enc.get_enc2());
    //     osDelay(40);
    // }

    while(true) {
        steer.update_coord();
    }


    while(true) {
        steer.rotate_steer(0, 0, 0, 0);
    }

    return 0;
}

