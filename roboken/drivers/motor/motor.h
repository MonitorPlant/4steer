#ifndef ROBOKEN_DRIVERS_MOTOR_MOTOR_H
#define ROBOKEN_DRIVERS_MOTOR_MOTOR_H

#include <mbed.h>
#include "../comm/spi_comm/spi_comm.h"

namespace roboken
{

struct motor_param_t{
    uint8_t slot;
    bool invert_flg;
    float normal_coef;
    float reverse_coef;
    uint8_t normal_accel;
    uint8_t reverse_accel;
};

class Motor
{
private:
    SpiComm     m_comm;

    bool        m_invert_flg;

    // float       m_normal_coef;
    // float       m_reverse_coef;

    uint8_t     m_normal_accel;
    uint8_t     m_reverse_accel;

public:
    Motor(void);
    Motor(uint8_t slot, bool invert_flg = true);
    Motor(struct motor_param_t *param);

    void motor_cons(struct motor_param_t *param);
    void motor_cons(uint8_t slot, bool invert_flg = true, float normal_coef = 1.0, float reverse_coef = 1.0, uint8_t normal_accel = 2, uint8_t reverse_accel = 2);

    void init(void);

    void set_invert(bool invert_flg);
    void set_coef(float normal_rotation, float reverse_rotation);
    void set_accel(uint8_t normal_rotation, uint8_t reverse_rotation);

    void set_power(int power);
    void set_power(uint8_t power, bool invert_flg);
};

}

#endif /*ROBOKEN_DRIVERS_MOTOR_MOTOR_H*/