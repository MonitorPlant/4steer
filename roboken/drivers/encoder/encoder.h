#ifndef ROBOKEN_DRIVERS_ENCODER_ENCODER_H
#define ROBOKEN_DRIVERS_ENCODER_ENCODER_H

#include <mbed.h>
#include "../comm/spi_comm/spi_comm.h"

namespace roboken
{

struct encoder_param_t{
    uint8_t slot;
    uint8_t enc1_port;
    uint8_t enc2_port;
    bool    enc1_invert;
    bool    enc2_invert;
};

class Encoder
{
private:
    SpiComm     m_comm;

    int16_t     m_befo_enc1;
    int16_t     m_befo_enc2;

    uint8_t     m_enc1_port;
    uint8_t     m_enc2_port;

    bool        m_enc1_invert;
    bool        m_enc2_invert;

    uint8_t number_to_mask(uint8_t port);

public:
    Encoder(void);
    //port is 1 ~ 4, 0 is disable.
    Encoder(uint8_t slot, uint8_t enc1_port, uint8_t enc2_port, bool enc1_invert = true, bool enc2_invert = true);
    Encoder(struct encoder_param_t *param);

    void encoder_cons(uint8_t slot, uint8_t enc1_port, uint8_t enc2_port, bool enc1_invert = true, bool enc2_invert = true);
    void encoder_cons(struct encoder_param_t *param);

    void init(void);

    int16_t get_enc1(void);
    int16_t get_enc2(void);
    void get_double(int16_t *enc1, int16_t *enc2);
};

}

#endif /*ROBOKEN_DRIVERS_ENCODER_ENCODER_H*/