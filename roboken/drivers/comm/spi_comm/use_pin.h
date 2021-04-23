#ifndef ROBOKEN_DRIVERS_SPI_COMM_USE_PIN_H
#define ROBOKEN_DRIVERS_SPI_COMM_USE_PIN_H

#include <mbed.h>

#ifdef TARGET_LPC1768

    #define ROBO_SPI_DEV_MOSI   (p11)
    #define ROBO_SPI_DEV_MISO   (p12)
    #define ROBO_SPI_DEV_SCK    (p13)

    #define ROBO_SPI_DEV_CLOCK  (800000)

    #define ROBO_SPI_DEV_SS1    (p25)
    #define ROBO_SPI_DEV_SS2    (p24)
    #define ROBO_SPI_DEV_SS3    (p23)
    #define ROBO_SPI_DEV_SS4    (p22)

    #define ROBO_SPI_DEV_SELECT1    (p29)
    #define ROBO_SPI_DEV_SELECT2    (p26)
    #define ROBO_SPI_DEV_SELECT3    (p30)

#elif TARGET_NUCLEO_F303K8

    #define ROBO_SPI_DEV_MOSI   (A6)
    #define ROBO_SPI_DEV_MISO   (A5)
    #define ROBO_SPI_DEV_SCK    (A4)

    #define ROBO_SPI_DEV_CLOCK  (800000)

    #define ROBO_SPI_DEV_SS1    (A0)
    #define ROBO_SPI_DEV_SS2    (NC)
    #define ROBO_SPI_DEV_SS3    (NC)
    #define ROBO_SPI_DEV_SS4    (NC)

    #define ROBO_SPI_DEV_SELECT1    (D9)
    #define ROBO_SPI_DEV_SELECT2    (D8)
    #define ROBO_SPI_DEV_SELECT3    (D7)

#else

    #define ROBO_SPI_DEV_MOSI   (NC)
    #define ROBO_SPI_DEV_MISO   (NC)
    #define ROBO_SPI_DEV_SCK    (NC)

    #define ROBO_SPI_DEV_CLOCK  (1000000)

    #define ROBO_SPI_DEV_SS1    (NC)
    #define ROBO_SPI_DEV_SS2    (NC)
    #define ROBO_SPI_DEV_SS3    (NC)
    #define ROBO_SPI_DEV_SS4    (NC)

    #define ROBO_SPI_DEV_SELECT1    (NC)
    #define ROBO_SPI_DEV_SELECT2    (NC)
    #define ROBO_SPI_DEV_SELECT3    (NC)

#endif

#endif /*ROBOKEN_DRIVERS_SPI_COMM_USE_PIN_H*/