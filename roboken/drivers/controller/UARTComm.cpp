/**************************************************
* UART_COMM.h 更新履歴
* 2016/6/24
*   Ver1.0.0    一次完成
***************************************************/

#include "UARTComm.h"
#include "SerialBase.h"
#include "UnbufferedSerial.h"
#include "use_pin.h"


#ifdef ROBOKEN_CONTROLLER_ENABLE

namespace uart_lib
{
    UARTComm::UARTComm(PinName tx, PinName rx, int baudrate) : UnbufferedSerial(tx, rx, baudrate)
    {
        this->format(8);
    }
    
    // void UARTComm::uart_start(void (*fptr)(void))
    // {
    //     RawSerial::attach(fptr, RawSerial::RxIrq);
    // }
    
    // void UARTComm::uart_stop(void)
    // {
    //     RawSerial::attach(NULL, RawSerial::RxIrq);
    // }
}

#endif /*ROBOKEN_CONTROLLER_ENABLE*/

