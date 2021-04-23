#include "motor.h"

namespace roboken
{

Motor::Motor(void)
{
}

Motor::Motor(uint8_t slot, bool invert_flg)
{
    this->motor_cons(slot, invert_flg);
}

Motor::Motor(struct motor_param_t *param)
{
    this->motor_cons(param);
}


void Motor::motor_cons(struct motor_param_t *param)
{
    this->motor_cons(param->slot, param->invert_flg, param->normal_coef, param->reverse_coef, param->normal_accel, param->reverse_accel);
}

void Motor::motor_cons(uint8_t slot, bool invert_flg, float normal_coef, float reverse_coef, uint8_t normal_accel, uint8_t reverse_accel)
{
    m_comm.init(slot - 1);

    this->m_invert_flg = invert_flg;
    // this->m_normal_coef = normal_coef;
    // this->m_reverse_coef = reverse_coef;
    this->m_normal_accel = normal_accel;
    this->m_reverse_accel = reverse_accel;
}

void Motor::init(void)
{
    char send_buffer[4] = {ROBO_SPI_DEV_MODE_INIT, ROBO_SPI_DEV_MOT, this->m_normal_accel, this->m_reverse_accel};

    this->m_comm.transfer(send_buffer, 4, NULL, 0);
}

void Motor::set_invert(bool invert_flg)
{
    this->m_invert_flg = invert_flg;
}

void Motor::set_coef(float normal_rotation, float reverse_rotation)
{
    // if(0 <= normal_rotation)
    // {
    //     this->m_normal_coef = normal_rotation;
    // }

    // if(0 <=reverse_rotation)
    // {
    //     this->m_reverse_coef = reverse_rotation;
    // }
}

void Motor::set_accel(uint8_t normal_rotation, uint8_t reverse_rotation)
{
    char normal_send_buffer[2] = {ROBO_SPI_DEV_MODE_ACCELH, normal_rotation};
    char reverse_send_buffer[2] = {ROBO_SPI_DEV_MODE_ACCELL, reverse_rotation};

    this->m_normal_accel = normal_rotation;
    this->m_reverse_accel = reverse_rotation;

    this->m_comm.transfer(normal_send_buffer, 2, NULL, 0);
    this->m_comm.transfer(reverse_send_buffer, 2, NULL, 0);
}

void Motor::set_power(int power)
{
    if(power < 0)
    {
        this->set_power(power * (-1), false);
    }else{
        this->set_power(power, true);
    }
}

void Motor::set_power(uint8_t power, bool invert_flg)
{
    char send_buffer[2] = {ROBO_SPI_DEV_MODE_NORMAL, 0};

    // if(invert_flg)
    // {
    //     power *= this->m_normal_coef;
    // }else{
    //     power *= this->m_reverse_coef;
    // }

    if(100 < power)
    {
        power = 100;
    }

	if(invert_flg == this->m_invert_flg)
	{
        send_buffer[1] = 0x80 + ((0x80 * power) / 100);
        this->m_comm.transfer(send_buffer, 2, NULL, 0);
	}else{
        send_buffer[1] = 0x80 - ((0x80 * power) / 100);
        this->m_comm.transfer(send_buffer, 2, NULL, 0);
	}
}

}