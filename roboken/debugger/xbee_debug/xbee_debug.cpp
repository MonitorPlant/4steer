#include "xbee_debug.h"
#include "DigitalOut.h"
#include "use_pin.h"

#include <cstdarg>
#include <cstring>

namespace roboken
{

UnbufferedSerial    *XbeeDebug::m_uart;


XbeeDebug::XbeeDebug()
{
}

void XbeeDebug::init(void)
{
    this->m_uart = new UnbufferedSerial(ROBO_DEBUG_XBEE_TX, ROBO_DEBUG_XBEE_RX, 19200);

    this->m_error_led = new DigitalOut(ROBO_DEBUG_LED);
}

void XbeeDebug::info(char *str)
{   
    // char send_str[1024];
    // sprintf(send_str, "%s\n\r", str);
    size_t str_len = strlen(str);
    str[str_len] = '\n';
    str[str_len + 1] = '\r';
    str[str_len + 2] = '\0';

    // printf("%s\n", str);

    this->m_uart->write(str, strlen(str));
}

    
void XbeeDebug::warning(const char *func, size_t line, char *str)
{
    // char send_str[1024];
    // sprintf(send_str, "[Warning(\"%s\":%d)]:%s\n\r", func, line, str);
    size_t str_len = strlen(str);
    str[str_len] = '\n';
    str[str_len + 1] = '\r';
    str[str_len + 2] = '\0';

    this->m_uart->write(str, strlen(str));
}

void XbeeDebug::error(const char *func, size_t line, char *str)
{   
    // char send_str[1024];
    // sprintf(send_str, "[Error(\"%s\":%d)]:%s\n\r", func, line, str);
    size_t str_len = strlen(str);
    str[str_len] = '\n';
    str[str_len + 1] = '\r';
    str[str_len + 2] = '\0';

    this->m_uart->write(str, strlen(str));

    this->m_error_led->write(!this->m_error_led->read());
}

uint8_t XbeeDebug::read_org(void)
{
    uint8_t receive_data;
    m_uart->read(&receive_data, 1);

    return receive_data;
}

}
