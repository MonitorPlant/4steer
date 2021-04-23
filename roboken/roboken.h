#ifndef ROBOKEN_ROBOKEN_H
#define ROBOKEN_ROBOKEN_H

#include "debugger/debugger.h"
#include "drivers/drivers.h"


namespace roboken
{

inline void sleep_ms(uint16_t ms)
{
    ThisThread::sleep_for((Kernel::Clock::duration_u32)ms);
}

void initializer(void);


void safety_on(void);

void safety_off(void);

}

#endif /*ROBOKEN_ROBOKEN_H*/