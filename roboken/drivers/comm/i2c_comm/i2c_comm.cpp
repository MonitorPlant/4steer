// #include "i2c_comm.h"
// #include "../../../debugger/debugger.h"
// #include "../spi_comm/spi_comm.h"

// namespace roboken
// {

// I2C*             I2cComm::m_i2c;
// Mutex*           I2cComm::m_locker;

// I2cComm::I2cComm()
// {
// }

// void I2cComm::i2c_comm_init(void)
// {
//     // m_i2c = new I2C(D4, D5);
//     // m_i2c->frequency(100000);
    
//     // m_locker = new Mutex();
// }

// void I2cComm::init(int16_t address)
// {
//     // this->m_address = (uint8_t)(address << 1);
// }

// void I2cComm::transfer(const char* send_buff, uint8_t send_len, char* read_buff, uint8_t read_len)
// {
//     // this->m_locker->lock();
//     // SpiComm::spi_comm_lock();
//     // this->m_i2c->lock();
//     // this->m_i2c->start();

//     // if(0 < send_len)
//     // {
//     //     this->m_i2c->write(this->m_address, send_buff, send_len);
//     // }

//     // wait_us(100);
    
//     // if(0 < read_len)
//     // {
//     //     this->m_i2c->read(this->m_address, read_buff, read_len);
//     // }

//     // this->m_i2c->stop();
//     // this->m_i2c->unlock();
//     // SpiComm::spi_comm_unlock();
//     // this->m_locker->unlock();
// }

// }