#ifndef ROBOKEN_DRIVERS_COMM_COMM_BASIC_H
#define ROBOKEN_DRIVERS_COMM_COMM_BASIC_H

#include <mbed.h>

namespace roboken
{

class CommBasic
{
private:

public:
    virtual ~CommBasic(){}

    virtual void init(int16_t address) = 0;
    
    virtual bool transfer(const char* send_buff, uint8_t send_len, char* read_buff, uint8_t read_len) = 0;
};

}

#endif /*ROBOKEN_DRIVERS_COMM_COMM_BASIC_H*/