/**************************************************
* UARTLib.h 更新履歴
* 2016/6/24
*   Ver1.0.0    一次完成
***************************************************/

#ifndef UART_LIB_H_
#define UART_LIB_H_

#include "DigitalOut.h"
#include <UARTDefLib.h>
#include "UARTComm.h"
#include "use_pin.h"
// #include <StdDefLib.h>

#ifdef ROBOKEN_CONTROLLER_ENABLE

using namespace uart_lib;

namespace uart_lib
{ 
    class UARTLib
    {
    private:
        UARTComm *uart;
        DigitalOut *initPin;
    
        // 無線モード
        int wireless;
        // // 文字列の長さを取得
        // unsigned int strLen(char *str);
        // // 文字列を結合
        // void strCat(char *str1, char *str2);
    
    public:
        UARTLib(int uartBuff, int baud);
    
        // // UART割り込み開始
        // void uartStart(void (*fptr)(void));
        // // UART割り込み停止
        // void uartStop(void);
    
        // 入出力関数
        int getc(void);
        void putc(int data);
        bool readable(void);
    
        // //LCD出力関数
        // void sendToLCD(char data1, char data2);
        // void sendToLCD(char data);
    
        // 通信用基板初期化-無線モジュール選択関数-再送機能付き
        void setWireless(int mode);
    };
}

#endif /*ROBOKEN_CONTROLLER_ENABLE*/

#endif
