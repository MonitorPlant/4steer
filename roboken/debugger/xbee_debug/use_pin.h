#ifndef ROBOKEN_DEBUGGER_XBEE_DEBUG_USE_PIN_H
#define ROBOKEN_DEBUGGER_XBEE_DEBUG_USE_PIN_H

#include <mbed.h>

#ifdef TARGET_LPC1768

    #define ROBO_DEBUG_XBEE_TX   (p9)
    #define ROBO_DEBUG_XBEE_RX   (p10)

    #define ROBO_DEBUG_LED       (LED1)

#elif TARGET_NUCLEO_F303K8

    #define ROBO_DEBUG_XBEE_TX   (A7)
    #define ROBO_DEBUG_XBEE_RX   (A2)

    #define ROBO_DEBUG_LED       (LED3)

#else

    #define ROBO_DEBUG_XBEE_TX   (NC)
    #define ROBO_DEBUG_XBEE_RX   (NC)

    #define ROBO_DEBUG_LED       (NC)

#endif

#endif /*ROBOKEN_DEBUGGER_XBEE_DEBUG_USE_PIN_H*/