#ifndef ROBOKEN_DRIVERS_SPI_COMM_MODE_DEFINE_H
#define ROBOKEN_DRIVERS_SPI_COMM_MODE_DEFINE_H

#include <mbed.h>

#define ROBO_SPI_DEV_DUMMY  (0x55)

#define ROBO_SPI_DEV_MOT        (0x30)
#define ROBO_SPI_DEV_AIR        (0x40)
#define ROBO_SPI_DEV_SERVO      (0x60)
#define ROBO_SPI_DEV_SERVO_AIR  (0x90)
#define ROBO_SPI_DEV_DUCTED_FUN (0xa0)

#define ROBO_SPI_DEV_MD_SWR     (0x00)
#define ROBO_SPI_DEV_MD_SWL     (0x01)

#define ROBO_SPI_DEV_MMD_1      (0x00)
#define ROBO_SPI_DEV_MMD_2      (0x01)
#define ROBO_SPI_DEV_MMD_3      (0x02)

#define ROBO_SPI_DEV_MODE_INIT      (0x0F)
// MD-Motor_Driver
#define ROBO_SPI_DEV_MODE_NORMAL    (0xF0)
#define ROBO_SPI_DEV_MODE_ENC	    (0xB0)	// MOT | ENC_ON
#define ROBO_SPI_DEV_MODE_SWITCH	(0x0B)
#define ROBO_SPI_DEV_MODE_ACCELH    (0x10)
#define ROBO_SPI_DEV_MODE_ACCELL	(0x20)
#define ROBO_SPI_DEV_MODE_FREEMODE  (0x7c)
// AD-Air_Driver
#define ROBO_SPI_DEV_MODE_AIR       (0xD0)
// SD-Servo_Driver
#define ROBO_SPI_DEV_MODE_SERVO		(0x09)
// SR-Sensor Receiver
#define ROBO_SPI_DEV_MODE_ARDUINO   (0x21)

#endif /*ROBOKEN_DRIVERS_SPI_COMM_MODE_DEFINE_H*/