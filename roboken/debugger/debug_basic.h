#ifndef ROBOKEN_DEBUGGER_DEBUG_BASIC_H
#define ROBOKEN_DEBUGGER_DEBUG_BASIC_H

#include <cstring>

namespace roboken
{

class DebugBasic
{
public:
    virtual void init(void) = 0;

    virtual void info(char *str) = 0;

    virtual void warning(const char *func, size_t line, char *str) = 0;

    virtual void error(const char *func, size_t line, char *str) = 0;

    virtual ~DebugBasic(){}
};

}

#endif /*ROBOKEN_DEBUGGER_DEBUG_BASIC_H*/