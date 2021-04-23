#include "debugger.h"
#include <cstdarg>

#include "xbee_debug/xbee_debug.h"
#include "serial_debug/serial_debug.h"

namespace roboken
{

DebugBasic*     Debugger::m_device;
Mutex           Debugger::m_locker;


Debugger::Debugger(void)
{
}

void Debugger::initializer(debug_device device)
{
    switch(device)
    {
        case device_xbee:
            m_device = new XbeeDebug();
            break;

        case device_serial:
            m_device = new SerialDebug();
            break;
        
        case device_file:
            break;
        
        default:
            m_device = new SerialDebug();
            break;
    }
    m_device->init();

    info("\n\rdebug start");
}

void Debugger::info(const char *fmt, ...)
{
    va_list args;
    int copy_len;
    char send_str[128];
    
    va_start(args, fmt);
    copy_len = vsprintf(send_str, fmt, args);
    va_end(args);

    if(0 <= copy_len && copy_len < 124)
    {
        m_locker.lock();
        m_device->info(send_str);
        m_locker.unlock();
    }
}

void Debugger::warning(const char *func, size_t line, const char *fmt, ...)
{
    va_list args;
    int copy_len;
    char send_str[128];

    va_start(args, fmt);
    copy_len = vsprintf(send_str, fmt, args);
    va_end(args);

    if(0 <= copy_len && copy_len < 124)
    {
        m_locker.lock();
        m_device->warning(func, line, send_str);
        m_locker.unlock();
    }
}

void Debugger::error(const char *func, size_t line, const char *fmt, ...)
{
    va_list args;
    int copy_len;
    char send_str[128];

    va_start(args, fmt);
    copy_len = vsprintf(send_str, fmt, args);
    va_end(args);
    
    if(0 <= copy_len && copy_len < 124)
    {
        m_locker.lock();
        m_device->error(func, line, send_str);
        m_locker.unlock();
    }
}

}
