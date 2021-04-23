#include "drivers.h"
#include "comm/spi_comm/spi_comm.h"
#include "controller.h"
#include "solenoid.h"

namespace roboken
{

void drivers_initializer(void)
{
    SpiComm::spi_comm_init();

    roboken::Solenoid::solenoid_init();
    roboken::Controller::Initializer();
}

}