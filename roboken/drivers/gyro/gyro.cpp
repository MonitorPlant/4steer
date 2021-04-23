/*
 * ArduinoGyro.cpp
 *
 *  Created on: 2019/09/12
 *      Author: robo_iiyama1
 */

#include "gyro.h"

namespace roboken
{

Gyro::Gyro(void)
{
}

Gyro::Gyro(uint8_t slot)
{
    this->gyro_cons(slot);
}

Gyro::Gyro(struct gyro_param_t *param)
{
    this->gyro_cons(param);
}

void Gyro::gyro_cons(struct gyro_param_t *param)
{
    this->gyro_cons(param->slot);
}

void Gyro::gyro_cons(uint8_t slot)
{
    this->m_comm.init(slot - 1);
}

void Gyro::init(void)
{
    this->m_befo_yaw_raw = 0;
    this->m_offset = 0;
    this->m_yaw = 0;
    this->m_befo_yaw = 0;
    this->m_rata_counter = 0;
}

void Gyro::set_offset(void)
{
    this->m_offset = this->m_yaw;
}

float Gyro::yaw(bool update)
{
    if(update)
    {
        this->update();
    }

    return this->m_yaw;
}

void Gyro::update(void)
{
    uint16_t raw_yaw;

    this->get_raw_value(&raw_yaw);
    this->m_yaw = this->convert_angle(raw_yaw);

    this->m_yaw -= this->m_offset;
}

void Gyro::get_raw_value(uint16_t* raw)
{
    uint16_t yaw_raw;

    char send_buffer[1] = {ROBO_SPI_DEV_MODE_ARDUINO};
    char read_buffer[2];

    if(this->m_comm.transfer(send_buffer, 1, read_buffer, 2))
    {
        yaw_raw = ((unsigned short)read_buffer[0]<<8) | (unsigned short)read_buffer[1];
    }else{
        yaw_raw = this->m_befo_yaw_raw;
    }

    this->m_befo_yaw_raw = yaw_raw;

    *raw = yaw_raw;
}

float Gyro::convert_angle(uint16_t raw)
{
    float nativeYow = ((float)raw)/((float)100);

	if((0 <= (int)nativeYow && (int)nativeYow < 10) && (350 < (int)this->m_befo_yaw && (int)this->m_befo_yaw <= 360 ))
	{
		this->m_rata_counter++;
	}else  if((0 <= (int)this->m_befo_yaw && (int)this->m_befo_yaw < 10) && (350 < (int)nativeYow && (int)nativeYow<=360)){
		this->m_rata_counter--;
	}

	this->m_befo_yaw = nativeYow;

	return nativeYow + (this->m_rata_counter*360) - this->m_rata_counter;
}

}


