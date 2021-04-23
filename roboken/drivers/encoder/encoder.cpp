#include "encoder.h"

namespace roboken
{

Encoder::Encoder(void)
{

}
    
Encoder::Encoder(uint8_t slot, uint8_t enc1_port, uint8_t enc2_port, bool enc1_invert, bool enc2_invert)
{
    this->encoder_cons(slot, enc1_port, enc2_port, enc1_invert, enc2_invert);
}

Encoder::Encoder(struct encoder_param_t *param)
{
    this->encoder_cons(param);
}

void Encoder::encoder_cons(uint8_t slot, uint8_t enc1_port, uint8_t enc2_port, bool enc1_invert, bool enc2_invert)
{
    this->m_comm.init(slot - 1);
    this->m_enc1_port = enc1_port;
    this->m_enc2_port = enc2_port;
    this->m_enc1_invert = enc1_invert;
    this->m_enc2_invert = enc2_invert;

    this->m_befo_enc1 = 0;
    this->m_befo_enc2 = 0;
}

void Encoder::encoder_cons(struct encoder_param_t *param)
{
    this->encoder_cons(param->slot, param->enc1_port, param->enc2_port, param->enc1_invert, param->enc2_invert);
}

void Encoder::init(void)
{
    char send_buffer[5] = {ROBO_SPI_DEV_MODE_INIT, 0x01, 0, 0x00, ROBO_SPI_DEV_DUMMY};

    send_buffer[2] = this->number_to_mask(1) | this->number_to_mask(2) | this->number_to_mask(3) | this->number_to_mask(4);//this->number_to_mask(this->m_enc1_port) | this->number_to_mask(this->m_enc2_port);

    this->m_comm.transfer(send_buffer, 5, NULL, 0);
}

int16_t Encoder::get_enc1(void)
{
    int16_t enc1;
    char send_buffer[2] = {ROBO_SPI_DEV_MODE_ENC, 0};
    char read_buffer[4];

    send_buffer[1] = (this->m_enc1_port << 4);

    if(this->m_comm.transfer(send_buffer, 2, read_buffer, 4))
    {
        enc1 = (read_buffer[0] << 8) | read_buffer[1];

        if(!this->m_enc1_invert)
        {
            enc1 *= -1;
        }
    }else{
        enc1 = this->m_befo_enc1;
    }

    this->m_befo_enc1 = enc1;

    return enc1;
}

int16_t Encoder::get_enc2(void)
{
    int16_t enc2;
    char send_buffer[2] = {ROBO_SPI_DEV_MODE_ENC, 0};
    char read_buffer[4];

    send_buffer[1] = this->m_enc2_port;

    if(this->m_comm.transfer(send_buffer, 2, read_buffer, 4))
    {
        enc2 = (read_buffer[2] << 8) | read_buffer[3];

        if(!this->m_enc2_invert)
        {
            enc2 *= -1;
        }
    }else{
        enc2 = this->m_befo_enc2;
    }

    this->m_befo_enc2 = enc2;

    return enc2;
}

void Encoder::get_double(int16_t *enc1, int16_t *enc2)
{
    int16_t __enc1, __enc2;
    char send_buffer[2] = {ROBO_SPI_DEV_MODE_ENC, 0};
    char read_buffer[4];

    send_buffer[1] = (this->m_enc1_port << 4) | this->m_enc2_port;

    if(this->m_comm.transfer(send_buffer, 2, read_buffer, 4))
    {
        __enc1 = (read_buffer[0] << 8) | read_buffer[1];
        __enc2 = (read_buffer[2] << 8) | read_buffer[3];

        if(!this->m_enc1_invert)
        {
            __enc1 *= -1;
        }

        if(!this->m_enc2_invert)
        {
            __enc2 *= -1;
        }
    }else{
        __enc1 = this->m_befo_enc1;
        __enc2 = this->m_befo_enc2;
    }

    this->m_befo_enc1 = __enc1;
    this->m_befo_enc2 = __enc2;

    *enc1 = __enc1;
    *enc2 = __enc2;
    
}

uint8_t Encoder::number_to_mask(uint8_t port)
{
    uint8_t mask;
    switch( port )
	{
	case 1:
		mask = 0x01;
		break;

	case 2:
		mask = 0x02;
		break;

	case 3:
		mask = 0x04;
		break;

	case 4:
		mask = 0x08;
		break;

	case 0:
		mask = 0x00;
		break;

	default:
		mask = 0x00;
		break;
	}

    return mask;
}

}