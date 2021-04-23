/**************************************************
* UARTDefLib.h 更新履歴
* 2017/1/5
*   Ver1.0.0    一次完成
***************************************************/
#ifndef UART_DEF_LIB_H_
#define UART_DEF_LIB_H_

#include "use_pin.h"

#ifdef ROBOKEN_CONTROLLER_ENABLE

// 通信ピン
#define TX1 p28
#define RX1 p27

#define TX2 p9
#define RX2 p10

#define TX3 p13
#define RX3 p14

// UART番号
#define UART1   0
#define UART2   1
#define UART3   2

/****** 通信用基板 *******/ 
// 無線モジュールマクロ
#define XBEE            0x01
#define FEP             0x02
#define PROPO           0x03
#define USE_LCD         0x04
#define FEP_LCD         0x06
#define GET_PULSE       0x80
#define PROPO_PULSE     0x83

// 通信終了コード
#define COMM_FINISH     0xFF

#endif /*ROBOKEN_CONTROLLER_ENABLE*/

#endif