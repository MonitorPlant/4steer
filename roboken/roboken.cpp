#include "roboken.h"
#include "roboken/drivers/controller/use_pin.h"

namespace roboken
{

void initializer(void)
{
    sleep_ms(1000);
    ROBO_DEBUG_INIT(roboken::Debugger::device_xbee);
    drivers_initializer();

    safety_off();
}

void safety_on(void)
{
    DigitalOut safety(ROBO_CONTROLLER_SEFETY, 1);
}

void safety_off(void)
{
    DigitalOut safety(ROBO_CONTROLLER_SEFETY, 0);
}


}
