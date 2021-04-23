#ifndef ROBOKEN_DRIVERS_SERVO_SERVO_H
#define ROBOKEN_DRIVERS_SERVO_SERVO_H

#include "spi_comm/spi_comm.h"

namespace roboken
{

struct servo_param_t{
    uint8_t slot;
    uint8_t port;
};

class Servo
{
private:
    SpiComm     m_comm;

    uint8_t     m_port;
    uint16_t    m_now_pulse;
    bool        m_is_lock;

public:
    Servo(void);
    Servo(uint8_t slot, uint8_t port);
    Servo(struct servo_param_t *param);

    void servo_cons(uint8_t slot, uint8_t port);
    void servo_cons(struct servo_param_t *param);

    void init(void);

    void enable(void);
    void disable(void);

    void set(uint16_t pulse, bool is_lock = false);
};

}

#endif /*ROBOKEN_DRIVERS_SERVO_SERVO_H*/