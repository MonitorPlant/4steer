#include "switch.h"

namespace roboken
{
    
Switch::Switch(void)
{
}


Switch::Switch(uint8_t slot, bool is_initside)
{
    this->switch_cons(slot, is_initside);
}

Switch::Switch(struct switch_param_t *param)
{
    this->switch_cons(param);
}

void Switch::switch_cons(uint8_t slot, bool is_initside)
{
    this->m_comm.init(slot - 1);
    this->m_is_initside = is_initside;
}

void Switch::switch_cons(struct switch_param_t *param)
{
    this->switch_cons(param->slot, param->is_initside);
}

bool Switch::get(void)
{
    char send_buffer[2] = {ROBO_SPI_DEV_MODE_SWITCH, 0};
    if(this->m_is_initside)
    {
        send_buffer[1] = 1;
    }else{
        send_buffer[1] = 0;
    }

    char read_buffer[1];

    this->m_comm.transfer(send_buffer, 2, read_buffer, 1);

    if(read_buffer[0] == 1)
    {
        return true;
    }else{
        return false;
    }
}

}