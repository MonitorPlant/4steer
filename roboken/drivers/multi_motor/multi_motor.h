#ifndef ROBOKEN_DRIVERS_MULTIMOTOR_MULTIMOTOR_H
#define ROBOKEN_DRIVERS_MULTIMOTOR_MULTIMOTOR_H

#include <mbed.h>
#include "../comm/spi_comm/spi_comm.h"

namespace roboken
{

struct multi_motor_param_t{
    uint8_t slot;
    uint8_t index;
    bool invert_flg;
    float normal_coef;
    float reverse_coef;
    uint8_t normal_accel;
    uint8_t reverse_accel;
};

class MultiMotor
{
private:
    SpiComm     m_comm;

    uint8_t     m_index;    

    bool        m_invert_flg;

    // float       m_normal_coef;
    // float       m_reverse_coef;

    uint8_t     m_normal_accel;
    uint8_t     m_reverse_accel;

public:
    MultiMotor(void);
    MultiMotor(uint8_t slot, uint8_t index, bool invert_flg = true);
    MultiMotor(struct multi_motor_param_t *param);

    void multi_motor_cons(struct multi_motor_param_t *param);
    void multi_motor_cons(uint8_t slot, uint8_t index, bool invert_flg = true, float normal_coef = 1.0, float reverse_coef = 1.0, uint8_t normal_accel = 2, uint8_t reverse_accel = 2);

    void init(void);

    void set_invert(bool invert_flg);
    void set_coef(float normal_rotation, float reverse_rotation);
    void set_accel(uint8_t normal_rotation, uint8_t reverse_rotation);

    void set_power(int power);
    void set_power(uint8_t power, bool invert_flg);
};

}

#endif /*ROBOKEN_DRIVERS_MULTIMOTOR_MULTIMOTOR_H*/