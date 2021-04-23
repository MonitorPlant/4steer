/**************************************************
* UART_COMM.h 更新履歴
* 2016/6/24
*   Ver1.0.0    一次完成
***************************************************/

#ifndef UART_COMM_H_
#define UART_COMM_H_

#include "UnbufferedSerial.h"
#include "mbed.h"
#include "use_pin.h"


#ifdef ROBOKEN_CONTROLLER_ENABLE

namespace uart_lib
{
    // RawSerial ClassはSerial Classと違いRTOSや割込みハンドラで使用可
    class UARTComm : public UnbufferedSerial
    {
    public:
        UARTComm(PinName tx, PinName rx, int baudrate);
        // void uart_start(void (*fptr)(void));
        // void uart_stop(void);
    };
}

#endif /*ROBOKEN_CONTROLLER_ENABLE*/

#endif
