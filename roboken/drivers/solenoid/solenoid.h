#ifndef ROBOKEN_DRIVERS_SOLENOID_SOLENOID_H
#define ROBOKEN_DRIVERS_SOLENOID_SOLENOID_H

#include "spi_comm/spi_comm.h"

#include <mbed.h>

namespace roboken
{

struct solenoid_param_t{
    uint8_t slot;
    uint8_t port;
};

class Solenoid
{
private:
    SpiComm     m_comm;

    uint8_t     m_port;
    
    uint8_t     *m_current_status;
    uint8_t     *m_current_isInit;

    static Mutex    m_locker;
    static uint8_t  m_all_status[32];
    static uint8_t  m_all_isInit[32];

public:
    static void solenoid_init(void);

    Solenoid(void);
    Solenoid(uint8_t slot, uint8_t port);   //port is 1 ~ 8
    Solenoid(struct solenoid_param_t *param);

    void solenoid_cons(uint8_t slot, uint8_t port);
    void solenoid_cons(struct solenoid_param_t *param);

    void init(void);

    void on(void);
    void off(void);
};

}

#endif /*ROBOKEN_DRIVERS_SOLENOID_SOLENOID_H*/