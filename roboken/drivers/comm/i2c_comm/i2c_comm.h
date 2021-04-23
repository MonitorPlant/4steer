// #ifndef ROBOKEN_DRIVERS_COMM_I2C_COMM_I2C_COMM_H
// #define ROBOKEN_DRIVERS_COMM_I2C_COMM_I2C_COMM_H

// #include <mbed.h>
// #include "../comm_basic.h"

// namespace roboken
// {

// class I2cComm : CommBasic
// {
// private:
//     uint8_t                 m_address;

//     static I2C*             m_i2c;
//     static Mutex*           m_locker;

// public:
//     I2cComm();

//     static void i2c_comm_init(void);

//     void init(int16_t address);
    
//     void transfer(const char* send_buff, uint8_t send_len, char* read_buff, uint8_t read_len);
// };

// }

// #endif  /*ROBOKEN_DRIVERS_COMM_I2C_COMM_I2C_COMM_H*/
