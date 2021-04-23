#ifndef ROBOKEN_DRIVERS_CONTROLLER_USE_PIN_H
#define ROBOKEN_DRIVERS_CONTROLLER_USE_PIN_H

#include <mbed.h>

#ifdef TARGET_LPC1768
    #define ROBOKEN_CONTROLLER_ENABLE

    #define ROBO_CONTROLLER_TX      (p9)
    #define ROBO_CONTROLLER_RX      (p10)

    #define ROBO_CONTROLLER_SEFETY  (p8)

#elif TARGET_NUCLEO_F303K8
    // #define ROBOKEN_CONTROLLER_ENABLE

    #define ROBO_CONTROLLER_TX      (NC)
    #define ROBO_CONTROLLER_RX      (NC)

    #define ROBO_CONTROLLER_SEFETY  (A1)

#else

    #define ROBO_DEBUG_XBEE_TX   (NC)
    #define ROBO_DEBUG_XBEE_RX   (NC)

    #define ROBO_DEBUG_LED       (NC)

#endif

#endif /*ROBOKEN_DRIVERS_CONTROLLER_USE_PIN_H*/