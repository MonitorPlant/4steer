#ifndef ROBOKEN_DEBUGGER_DEBUGGER_H
#define ROBOKEN_DEBUGGER_DEBUGGER_H

#include <mbed.h>
#include "debug_basic.h"

// #define ROBO_DEBUG_ON

#ifdef ROBO_DEBUG_ON
    #define ROBO_DEBUG_INIT(device) roboken::Debugger::initializer(device)
    #define ROBO_INFO(...)          roboken::Debugger::info(__VA_ARGS__)
    #define ROBO_WARNING(...)       roboken::Debugger::warning(__func__, __LINE__, __VA_ARGS__)
    #define ROBO_ERROR(...)         roboken::Debugger::error(__func__, __LINE__, __VA_ARGS__)
#else
    #define ROBO_DEBUG_INIT(...)
    #define ROBO_INFO(...)
    #define ROBO_WARNING(...)
    #define ROBO_ERROR(...)
#endif /*ROBO_DEBUG_ON*/

namespace roboken
{

class Debugger
{
private:
    static DebugBasic *m_device;
    static Mutex    m_locker;

public:
    Debugger(void);

    enum debug_device{
        device_xbee = 0,
        device_serial = 1,
        device_file = 2
    };

    static void initializer(debug_device device);

    static void info(const char *fmt, ...);

    static void warning(const char *func, size_t line, const char *fmt, ...);

    static void error(const char *func, size_t line, const char *fmt, ...);

    static void read(void* buffer, size_t size);
};

}

#endif /*ROBOKEN_DEBUGGER_DEBUGGER_H*/
