/**************************************************
* UARTLib.h 更新履歴
* 2016/6/24
*   Ver1.0.0    一次完成
***************************************************/

#include "UARTLib.h"
#include "DigitalOut.h"
#include "PinNames.h"
#include "cmsis_os2.h"
#include "use_pin.h"


#ifdef ROBOKEN_CONTROLLER_ENABLE

namespace uart_lib
{
    UARTLib::UARTLib(int uartBuff, int baud)
    {
        switch(uartBuff)
        {
            case UART1:
                uart = new UARTComm(TX1, RX1, baud);
                break;
            case UART2:
                uart = new UARTComm(TX2, RX2, baud);
                break;
            case UART3:
                uart = new UARTComm(TX3, RX3, baud);
                break;
        }
    
        initPin = new DigitalOut(p15);

        // initPin->mode(OpenDrain);
        // initPin->output_high();
    
        wireless = 0;
    }
    /****************************************************************************/
    /******************************** 関数 **************************************/
    /****************************************************************************/
    /************************** 通信用基板通信 ***************************************/
    // // 文字列の長さを取得
    // unsigned int UARTLib::strLen(char *str)
    // {
    //     unsigned i = 0;
        
    //     while(*str++)
    //         i++;
            
    //     return i;
    // }
    
    // // 文字列を結合
    // void UARTLib::strCat(char *str1, char *str2)
    // {
    //     int i, j;
    //     unsigned int len = strLen(str1);
        
    //     for(i = len, j = 0; ; i++, j++)
    //     {
    //         str1[i] = str2[j];
            
    //         if(!str2[j])
    //             break;
    //     }
    // }
    
    // // UART割り込み開始
    // void UARTLib::uartStart(void (*fptr)(void))
    // {
    //     uart->uart_start(fptr);
    // }
    
    // // UART割り込み停止
    // void UARTLib::uartStop(void)
    // {
    //     uart->uart_stop();
    // }
    
    int UARTLib::getc(void)
    {
        char data;
        uart->read(&data, 1);
        return (int)data;
    }
    
    void UARTLib::putc(int data)
    {
        char buffer = data;
        uart->write(&buffer, 1);
    }
    
    bool UARTLib::readable(void)
    {
        return uart->readable();
    }
    
    // void UARTLib::sendToLCD(char data1, char data2)
    // {
    //     char buff[] = "00";
    
    //     buff[0] = data1;
    //     buff[1] = data2;
    
    //     for(int i = 0;i < 2;i++)
    //     {
    //         if(buff[i] == 0)
    //             buff[i] = 1;
    //     }
    
    //     uart->printf("%s\r", buff);
    // }
    
    // void UARTLib::sendToLCD(char data)
    // {
    //     if(data == 0)
    //         data = 1;
    
    //     uart->putc(data);
    // }
    
    // 通信用基板初期化-無線モジュール選択関数-再送機能付き
    void UARTLib::setWireless(int mode)
    {
        int returnMode = -1;
    
        initPin->write(1);

        DigitalOut led2(LED2);
    
        while(returnMode != mode)
        {
            led2.write(led2.read());
            this->putc(mode);
    
            for(int timeout = 0; timeout < 30000; timeout++)
            {
                if(uart->readable())
                {
                    returnMode = this->getc();
                    if(returnMode == mode)
                        this->putc(COMM_FINISH);
                    break;
                }
            }
            osDelay(1);
        }
        led2.write(0);
    
        initPin->write(0);
    
        wireless = mode;
    }
}

#endif /*ROBOKEN_CONTROLLER_ENABLE*/
