#include "multi_motor.h"

namespace roboken
{

MultiMotor::MultiMotor(void)
{
}

MultiMotor::MultiMotor(uint8_t slot, uint8_t index, bool invert_flg)
{
    this->multi_motor_cons(slot, index, invert_flg);
}

MultiMotor::MultiMotor(struct multi_motor_param_t *param)
{
    this->multi_motor_cons(param);
}


void MultiMotor::multi_motor_cons(struct multi_motor_param_t *param)
{
    this->multi_motor_cons(param->slot, param->index, param->invert_flg, param->normal_coef, param->reverse_coef, param->normal_accel, param->reverse_accel);
}

void MultiMotor::multi_motor_cons(uint8_t slot, uint8_t index, bool invert_flg, float normal_coef, float reverse_coef, uint8_t normal_accel, uint8_t reverse_accel)
{
    m_comm.init(slot - 1);

    this->m_index = index - 1;
    this->m_invert_flg = invert_flg;
    // this->m_normal_coef = normal_coef;
    // this->m_reverse_coef = reverse_coef;
    this->m_normal_accel = normal_accel;
    this->m_reverse_accel = reverse_accel;
}

void MultiMotor::init(void)
{
    char send_buffer[4] = {ROBO_SPI_DEV_MODE_INIT, ROBO_SPI_DEV_MOT, this->m_normal_accel, this->m_reverse_accel};

    this->m_comm.transfer(send_buffer, 4, NULL, 0);
}

void MultiMotor::set_invert(bool invert_flg)
{
    this->m_invert_flg = invert_flg;
}

void MultiMotor::set_coef(float normal_rotation, float reverse_rotation)
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

void MultiMotor::set_accel(uint8_t normal_rotation, uint8_t reverse_rotation)
{
    char normal_send_buffer[2] = {ROBO_SPI_DEV_MODE_ACCELH, normal_rotation};
    char reverse_send_buffer[2] = {ROBO_SPI_DEV_MODE_ACCELL, reverse_rotation};

    this->m_normal_accel = normal_rotation;
    this->m_reverse_accel = reverse_rotation;

    this->m_comm.transfer(normal_send_buffer, 2, NULL, 0);
    this->m_comm.transfer(reverse_send_buffer, 2, NULL, 0);
}

void MultiMotor::set_power(int power)
{
    if(power < 0)
    {
        this->set_power(power * (-1), false);
    }else{
        this->set_power(power, true);
    }
}

void MultiMotor::set_power(uint8_t power, bool invert_flg)
{
    char send_buffer[3] = {ROBO_SPI_DEV_MODE_NORMAL, 0, this->m_index};

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
        this->m_comm.transfer(send_buffer, 3, NULL, 0);
	}else{
        send_buffer[1] = 0x80 - ((0x80 * power) / 100);
        this->m_comm.transfer(send_buffer, 3, NULL, 0);
	}
}

}