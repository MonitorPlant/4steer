#ifndef ROBOKEN_DRIVERS_SWITCH_SWITCH_H
#define ROBOKEN_DRIVERS_SWITCH_SWITCH_H

#include "spi_comm/spi_comm.h"

namespace roboken
{

struct switch_param_t{
    uint8_t slot;
    bool is_initside;
};

class Switch
{
private:
    SpiComm     m_comm;

    bool        m_is_initside;

public:
    Switch(void);
    Switch(uint8_t slot, bool is_initside);
    Switch(struct switch_param_t *param);

    void switch_cons(uint8_t slot, bool is_initside);
    void switch_cons(struct switch_param_t *param);

    bool get(void);
};

}

#endif /*ROBOKEN_DRIVERS_SWITCH_SWITCH_H*/