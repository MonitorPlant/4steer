#ifndef ROBOKEN_DEBUGGER_XBEE_DEBUG_XBEE_DEBUG_H
#define ROBOKEN_DEBUGGER_XBEE_DEBUG_XBEE_DEBUG_H

#include <mbed.h>
#include "../debug_basic.h"
#include "DigitalOut.h"

namespace roboken
{

class XbeeDebug : public DebugBasic
{
private:
    static UnbufferedSerial    *m_uart;
    DigitalOut          *m_error_led;

public:    
    XbeeDebug();
    ~XbeeDebug(){}

    void init(void);

    void info(char *str);

    void warning(const char *func, size_t line, char *str);

    void error(const char *func, size_t line, char *str);

    static uint8_t read_org(void);
};

}

#endif /*ROBOKEN_DEBUGGER_XBEE_DEBUG_XBEE_DEBUG_H*/
