#include "solenoid.h"
#include "mode_define.h"
#include <string.h>

namespace roboken
{

Mutex    Solenoid::m_locker;
uint8_t  Solenoid::m_all_status[32];
uint8_t  Solenoid::m_all_isInit[32];

void Solenoid::solenoid_init(void)
{
    memset(m_all_status, 0x00, sizeof(uint8_t) * 32);
    memset(m_all_isInit, 0x00, sizeof(uint8_t) * 32);
}

Solenoid::Solenoid(void)
{
}

Solenoid::Solenoid(uint8_t slot, uint8_t port)
{
    this->m_comm.init(slot - 1);
    solenoid_cons(slot, port);
}

Solenoid::Solenoid(struct solenoid_param_t *param)
{
    solenoid_cons(param);
}

void Solenoid::solenoid_cons(uint8_t slot, uint8_t port)
{
    this->m_locker.lock();
    this->m_current_status = &this->m_all_status[slot];
    this->m_current_isInit = &this->m_all_isInit[slot];
    this->m_locker.unlock();

    this->m_port = port;
}

void Solenoid::solenoid_cons(struct solenoid_param_t *param)
{
    this->solenoid_cons(param->slot, param->port);
}

void Solenoid::init(void)
{
    uint8_t is_howto_init;
    this->m_locker.lock();
    if(*this->m_current_isInit == 0)
    {
        *this->m_current_isInit = 1;
        is_howto_init = 1;
    }else{
        is_howto_init = 0;
    }
    this->m_locker.unlock();

    if(is_howto_init == 1)
    {
        char send_buffer[2] = {ROBO_SPI_DEV_MODE_INIT, ROBO_SPI_DEV_AIR};
        this->m_comm.transfer(send_buffer, 2, NULL, 0);
    }
}

void Solenoid::on(void)
{
    uint8_t mask = 0x01 << (this->m_port - 1);
    uint8_t send_data[2] = {ROBO_SPI_DEV_MODE_AIR, 0};

    this->m_locker.lock();
    *this->m_current_status |= mask;
    send_data[1] = *this->m_current_status;
    this->m_locker.unlock();

    this->m_comm.transfer((char*)send_data, 2, NULL, 0);
}

void Solenoid::off(void)
{
    uint8_t mask = 0x01 << (this->m_port - 1);
    uint8_t send_data[2] = {ROBO_SPI_DEV_MODE_AIR, 0};

    this->m_locker.lock();
    *this->m_current_status &= (~mask);
    send_data[1] = *this->m_current_status;
    this->m_locker.unlock();

    this->m_comm.transfer((char*)send_data, 2, NULL, 0);
}

}