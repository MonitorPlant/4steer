#include "serial_debug.h"
#include "use_pin.h"

#include <cstdarg>
#include <cstring>

namespace roboken
{

SerialDebug::SerialDebug()
{
}

void SerialDebug::init(void)
{
}

void SerialDebug::info(char *str)
{   
    printf("%s\n", str);
}

    
void SerialDebug::warning(const char *func, size_t line, char *str)
{
    printf("[Warning(\"%s\":%d)]:%s\n", func, line, str);
}

void SerialDebug::error(const char *func, size_t line, char *str)
{   
    printf("[Error(\"%s\":%d)]:%s\n", func, line, str);
}

}
