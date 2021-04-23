#ifndef ROBOKEN_DRIVERS_DRIVEERS_H
#define ROBOKEN_DRIVERS_DRIVEERS_H

#include "spi_comm/spi_comm.h"
#include "motor/motor.h"
#include "multi_motor/multi_motor.h"
#include "servo/servo.h"
#include "switch/switch.h"
#include "encoder/encoder.h"
#include "gyro/gyro.h"
#include "solenoid/solenoid.h"

#include "controller/controller.h"

namespace roboken
{

void drivers_initializer(void);

}

#endif /*ROBOKEN_DRIVERS_DRIVEERS_H*/