#include "servo.h"
#include "mode_define.h"

namespace roboken
{

Servo::Servo(void)
{
}


Servo::Servo(uint8_t slot, uint8_t port)
{
    this->servo_cons(slot, port);
}

Servo::Servo(struct servo_param_t *param)
{
    this->servo_cons(param);
}

void Servo::servo_cons(uint8_t slot, uint8_t port)
{
    this->m_comm.init(slot - 1);
    this->m_port = port;
    this->m_now_pulse = 1000;
    this->m_is_lock = true;
}

void Servo::servo_cons(struct servo_param_t *param)
{
    this->servo_cons(param->slot, param->port);
}

void Servo::init(void)
{
    char send_buffer[3] = {ROBO_SPI_DEV_MODE_INIT, ROBO_SPI_DEV_SERVO, 4};
    this->m_comm.transfer(send_buffer, 3, NULL, 0);
}

void Servo::enable(void)
{
	const char sendBuffer[5] = {ROBO_SPI_DEV_MODE_SERVO, this->m_port, (char)(this->m_now_pulse&0xFF), (char)((this->m_now_pulse>>8)&0xFF), 0x01};

	this->m_comm.transfer(sendBuffer, 5, NULL, 0);

    this->m_is_lock = false;
}

void Servo::disable(void)
{
    const char sendBuffer[5] = {ROBO_SPI_DEV_MODE_SERVO, this->m_port, (char)(this->m_now_pulse&0xFF), (char)((this->m_now_pulse>>8)&0xFF), 0x00};

	this->m_comm.transfer(sendBuffer, 5, NULL, 0);

    this->m_is_lock = true;
}

void Servo::set(uint16_t pulse, bool is_lock)
{
    this->m_now_pulse = pulse;
    this->m_is_lock = is_lock;
    char sendBuffer[5] = {ROBO_SPI_DEV_MODE_SERVO, this->m_port, (char)(pulse&0xFF), (char)((pulse>>8)&0xFF), 0};

    if(this->m_is_lock)
    {
        sendBuffer[4] = 0;
    }else{
        sendBuffer[4] = 0x01;
    }

	this->m_comm.transfer(sendBuffer, 5, NULL, 0);
}

}