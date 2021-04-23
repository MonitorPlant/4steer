#ifndef ROBOKEN_DRIVERS_COMM_SPI_COMM_SPI_COMM_H
#define ROBOKEN_DRIVERS_COMM_SPI_COMM_SPI_COMM_H

#include <mbed.h>
#include "../comm_basic.h"
#include "mode_define.h"

namespace roboken
{

class SpiComm : CommBasic
{
private:
    uint8_t     m_slot;

    static spi_t            m_spi;
    static BusOut*          m_ss;
    static BusOut*          m_select;
    static uint8_t          m_befo_slot;

    static Mutex            m_locker;

    void transfer_nolock(char* send_buff, char* read_buff);

    inline void enable_ss(void)
    {
        *m_select = this->m_slot % 8;
        *m_ss = 0b00001111 & ~(0b00000001 << (this->m_slot / 8));
    }

    static inline void disable_ss(void)
    {
        *m_ss = 0b00001111;
    }

public:
    SpiComm();

    static void spi_comm_init(void);

    void init(int16_t address);
    
    bool transfer(const char* send_buff, uint8_t send_len, char* read_buff, uint8_t read_len);
};

}

#endif /*ROBOKEN_DRIVERS_COMM_SPI_COMM_SPI_COMM_H*/