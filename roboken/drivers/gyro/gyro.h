#ifndef ROBOKEN_DRIVERS_GYRO_GYRO_H
#define ROBOKEN_DRIVERS_GYRO_GYRO_H

#include <mbed.h>
#include "../comm/spi_comm/spi_comm.h"

namespace roboken
{

struct gyro_param_t{
    uint8_t slot;
};
    
class Gyro
{
private:
    SpiComm                 m_comm;

    uint16_t                m_befo_yaw_raw;

	float					m_offset;
	float					m_yaw;
    float                   m_befo_yaw;
	int16_t					m_rata_counter;

    void get_raw_value(uint16_t* raw);

    float convert_angle(uint16_t raw);
	// void getStndardAccelYaw(float *yaw);

	// float changeYawvalue( uint16_t yaw );

public:
    Gyro(void);
	Gyro(uint8_t slot);
    Gyro(struct gyro_param_t *param);

	void gyro_cons(uint8_t slot);
    void gyro_cons(struct gyro_param_t *param);

	void init(void);

	void set_offset( void );

	float yaw(bool update = true);

	bool isboot(bool update = true);

	void update();
};

}

#endif /*ROBOKEN_DRIVERS_GYRO_GYRO_H*/