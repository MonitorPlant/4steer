#include "spi_comm.h"
#include "use_pin.h"
#include "../../../debugger/debugger.h"

namespace roboken
{

spi_t       SpiComm::m_spi;
BusOut*     SpiComm::m_ss;
BusOut*     SpiComm::m_select;
uint8_t     SpiComm::m_befo_slot;

Mutex      SpiComm::m_locker;

SpiComm::SpiComm()
{
}

void SpiComm::spi_comm_init(void)
{
    spi_init(&m_spi, ROBO_SPI_DEV_MOSI, ROBO_SPI_DEV_MISO, ROBO_SPI_DEV_SCK, NC);
    spi_format(&m_spi, 8, 1, 0);
    spi_frequency(&m_spi, ROBO_SPI_DEV_CLOCK);
    
    m_befo_slot = 0;

    m_ss = new BusOut(ROBO_SPI_DEV_SS1, ROBO_SPI_DEV_SS2, ROBO_SPI_DEV_SS3, ROBO_SPI_DEV_SS4);
    m_select = new BusOut(ROBO_SPI_DEV_SELECT1, ROBO_SPI_DEV_SELECT2, ROBO_SPI_DEV_SELECT3);

    disable_ss();
}

void SpiComm::init(int16_t address)
{
    this->m_slot = (uint8_t)address;
}

bool SpiComm::transfer(const char* send_buff, uint8_t send_len, char* read_buff, uint8_t read_len)
{
    bool is_succes = false;

    // mode, data1, data2, data3, data4, checksum, dummy
    char tx_buffer[7] = {ROBO_SPI_DEV_DUMMY, ROBO_SPI_DEV_DUMMY, ROBO_SPI_DEV_DUMMY, ROBO_SPI_DEV_DUMMY, ROBO_SPI_DEV_DUMMY, ROBO_SPI_DEV_DUMMY, ROBO_SPI_DEV_DUMMY};
    // none, mode, data1, data2, data3, data4, checksum
    char rx_buffer[7];

    if(send_len != 0)
    {
        memcpy(tx_buffer, send_buff, sizeof(char) * send_len);
    }
    tx_buffer[5] = tx_buffer[0] + tx_buffer[1] + tx_buffer[2] + tx_buffer[3] + tx_buffer[4];

    if(read_len != 0)
    {
        memset(read_buff, 0x00, sizeof(char) * read_len);
    }

    // ROBO_INFO("%d, %d, %d", this->m_slot, send_len, read_len);
    
    // ROBO_INFO("%d, %d, %d, %d, %d, %d", tx_buffer[0], tx_buffer[1], tx_buffer[2], tx_buffer[3], tx_buffer[4], tx_buffer[5]);
    // ROBO_INFO("%d, %d, %d, %d, %d, %d", rx_buffer[1], rx_buffer[2], rx_buffer[3], rx_buffer[4], rx_buffer[5], rx_buffer[6]);

    for(size_t i=0; i < 3; i++)
    {
        this->m_locker.lock();
        // this->m_spi->lock();

        this->transfer_nolock(tx_buffer, rx_buffer);

        // this->m_spi->unlock();
        this->m_locker.unlock();

        char culc_checksum = rx_buffer[1] + rx_buffer[2] + rx_buffer[3] + rx_buffer[4] + rx_buffer[5];
        if(rx_buffer[6] == culc_checksum)
        {
            if(read_len != 0)
            {
                memcpy(read_buff, &rx_buffer[2], sizeof(char) * read_len);
            }

            is_succes = true;
            break;
        }else{
            // ROBO_INFO("%d, %d, %d, %d, %d, %d", tx_buffer[0], tx_buffer[1], tx_buffer[2], tx_buffer[3], tx_buffer[4], tx_buffer[5]);
            // ROBO_INFO("%d, %d, %d, %d, %d, %d", rx_buffer[1], rx_buffer[2], rx_buffer[3], rx_buffer[4], rx_buffer[5], rx_buffer[6]);
            ROBO_ERROR("spi failed!, slot:%d", (int)(this->m_slot + 1));
        }

        ThisThread::yield();
    }

    return is_succes;
}

void SpiComm::transfer_nolock(char* send_buff, char* read_buff)
{
    if(this->m_befo_slot == this->m_slot)
    {
        wait_us(30);
    }
    this->m_befo_slot = this->m_slot;

    this->enable_ss();

    // this->m_spi->write(send_buff[0]);                   wait_us(10);
    // read_buff[1] = this->m_spi->write(send_buff[1]);    wait_us(1);
    // read_buff[2] = this->m_spi->write(send_buff[2]);    wait_us(1);
    // read_buff[3] = this->m_spi->write(send_buff[3]);    wait_us(1);
    // read_buff[4] = this->m_spi->write(send_buff[4]);    wait_us(1); 
    // read_buff[5] = this->m_spi->write(send_buff[5]);    wait_us(5);
    // read_buff[6] = this->m_spi->write(send_buff[6]);

    spi_master_write(&m_spi, send_buff[0]);                   wait_us(10);
    read_buff[1] = spi_master_write(&m_spi, send_buff[1]);    wait_us(1);
    read_buff[2] = spi_master_write(&m_spi, send_buff[2]);    wait_us(1);
    read_buff[3] = spi_master_write(&m_spi, send_buff[3]);    wait_us(1);
    read_buff[4] = spi_master_write(&m_spi, send_buff[4]);    wait_us(1); 
    read_buff[5] = spi_master_write(&m_spi, send_buff[5]);    wait_us(5);
    read_buff[6] = spi_master_write(&m_spi, send_buff[6]);

    // m_spi->write(send_buff, 7, read_buff, 7);

    disable_ss();
}

}