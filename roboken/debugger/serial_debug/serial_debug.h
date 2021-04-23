#ifndef ROBOKEN_DEBUGGER_SERIAL_DEBUG_SERIAL_DEBUG_H
#define ROBOKEN_DEBUGGER_SERIAL_DEBUG_SERIAL_DEBUG_H

#include <mbed.h>
#include "../debug_basic.h"

namespace roboken
{

class SerialDebug : public DebugBasic
{
private:
public:
    SerialDebug();
    ~SerialDebug(){}
    
    void init(void);

    void info(char *str);

    void warning(const char *func, size_t line, char *str);

    void error(const char *func, size_t line, char *str);
};

}

#endif /*ROBOKEN_DEBUGGER_SERIAL_DEBUG_SERIAL_DEBUG_H*/