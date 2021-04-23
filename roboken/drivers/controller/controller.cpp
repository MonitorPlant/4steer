/*
 * Controller.cpp
 *
 *  Created on: 2019/01/15
 *      Author: robo_iiyama1
 */

#include "controller.h"
#include "ThisThread.h"
#include "Thread.h"

#ifdef ROBOKEN_CONTROLLER_ENABLE

#include <mbed.h>
#include "DigitalOut.h"
#include "use_pin.h"
#include "UARTLib.h"

#define RT_THREADSTART (123)

namespace roboken
{

struct MonitorInfo
{
	Mutex			   *__locker;

	bool 				__safetyFlg;
	bool 				__startFlg;
	unsigned char 		__ConState[2];
};

static Thread* 				g_CheckerThread;
static MonitorInfo			g_monitor;

DigitalOut* Controller::m_safety;

void Controller::checker( void  )
{
    UARTLib uartCon( UART1, 19200 );

    ThisThread::flags_wait_any(RT_THREADSTART);

	Timer	conTimer;
	bool communicating;

	safety_on();
	communicating = false;

	uartCon.setWireless( FEP );
	g_monitor.__locker->lock();
	g_monitor.__startFlg = true;
	g_monitor.__locker->unlock();

	conTimer.start();
	conTimer.reset();

	while(true)
	{
		if( uartCon.readable() == true )
		{
			unsigned char getData = uartCon.getc();
			if( getData & 0x40 )
			{
				g_monitor.__locker->lock();
				g_monitor.__ConState[0] = getData;
				g_monitor.__locker->unlock();
			}else{
				g_monitor.__locker->lock();
				g_monitor.__ConState[1] = getData;
				g_monitor.__locker->unlock();
				conTimer.reset();
			}
		}

		if( 200 < conTimer.read_ms() )
		{
			if( communicating == true )
			{
				safety_on();
				g_monitor.__locker->lock();
				g_monitor.__safetyFlg = true;
				g_monitor.__locker->unlock();
				communicating = false;
			}
		}else{
			if( communicating == false )
			{
				safety_off();
				g_monitor.__locker->lock();
				g_monitor.__safetyFlg = false;
				g_monitor.__locker->unlock();
				communicating = true;
			}
		}
        ThisThread::yield();
	}
}


Controller::Controller( void )
{
}

void Controller::init( void )
{
	memset( &m_befoConData, 0x00, sizeof( struct befoControllerData ) );
    m_safety = new DigitalOut(ROBO_CONTROLLER_SEFETY);
}


void Controller::Initializer( void )
{
	g_monitor.__ConState[0] = 0x40;
	g_monitor.__ConState[1] = 0x00;
	g_monitor.__startFlg = false;
	g_monitor.__safetyFlg = true;

	g_monitor.__locker = new Mutex();

    g_CheckerThread = new Thread();
	// // g_CheckerThread = new Thread( checker, NULL );
    g_CheckerThread->start(callback(Controller::checker));
    ThisThread::yield();
}


void Controller::Start( void )
{
	this->init();

    g_CheckerThread->flags_set(RT_THREADSTART);
}


void Controller::AbsStart( void )
{
	this->init();

	g_monitor.__locker->lock();
    this->safety_off();
	g_monitor.__startFlg = true;
	g_monitor.__locker->unlock();
}

bool Controller::isStart( void )
{
	g_monitor.__locker->lock();
	bool startFlg = g_monitor.__startFlg;
	g_monitor.__locker->unlock();

	return startFlg;
}

bool Controller::isSafety( void )
{
	g_monitor.__locker->lock();
	bool safetyFlg = g_monitor.__safetyFlg;
	g_monitor.__locker->unlock();

	return safetyFlg;
}

void Controller::safety_on(void)
{
    m_safety->write(1);
}

void Controller::safety_off(void)
{
    m_safety->write(0);
}

bool Controller::toggle( void )
{
	g_monitor.__locker->lock();
	unsigned char conState = g_monitor.__ConState[0];
	g_monitor.__locker->unlock();

	if( (conState&0x80) == 0 )
	{
		return false;
	}
	return true;
}


bool Controller::Right_up( void )
{
	g_monitor.__locker->lock();
	unsigned char conState = g_monitor.__ConState[0];
	g_monitor.__locker->unlock();

	if( (conState&0x20) == 0 )
	{
		return false;
	}
	return true;
}

bool Controller::Right_upPush( void )
{
	bool resault = false;
	if( this->Right_up() )
	{
		if( m_befoConData.Right_up == false )
		{
			resault = true;
			m_befoConData.Right_up = true;
		}
	}else{
		m_befoConData.Right_up = false;
	}
	return resault;
}


bool Controller::Right_down( void )
{
	g_monitor.__locker->lock();
	unsigned char conState =  g_monitor.__ConState[0];
	g_monitor.__locker->unlock();

	if( (conState&0x10) == 0 )
	{
		return false;
	}
	return true;
}

bool Controller::Right_downPush( void )
{
	bool resault = false;
	if( this->Right_down() )
	{
		if( m_befoConData.Right_down == false )
		{
			resault = true;
			m_befoConData.Right_down = true;
		}
	}else{
		m_befoConData.Right_down = false;
	}
	return resault;
}


bool Controller::Right_right( void )
{
	g_monitor.__locker->lock();
	unsigned char conState = g_monitor.__ConState[0];
	g_monitor.__locker->unlock();

	if( (conState&0x08) == 0 )
	{
		return false;
	}
	return true;
}

bool Controller::Right_rightPush( void )
{
	bool resault = false;
	if( this->Right_right() )
	{
		if( m_befoConData.Right_right == false )
		{
			resault = true;
			m_befoConData.Right_right = true;
		}
	}else{
		m_befoConData.Right_right = false;
	}
	return resault;
}


bool Controller::Right_left( void )
{
	g_monitor.__locker->lock();
	unsigned char conState =  g_monitor.__ConState[0];
	g_monitor.__locker->unlock();

	if( (conState&0x04) == 0 )
	{
		return false;
	}
	return true;
}

bool Controller::Right_leftPush( void )
{
	bool resault = false;
	if( this->Right_left() )
	{
		if( m_befoConData.Right_left == false )
		{
			resault = true;
			m_befoConData.Right_left = true;
		}
	}else{
		m_befoConData.Right_left = false;
	}
	return resault;
}


bool Controller::Right_R1( void )
{
	g_monitor.__locker->lock();
	unsigned char conState =  g_monitor.__ConState[1];
	g_monitor.__locker->unlock();

	if( (conState&0x02) == 0 )
	{
		return false;
	}
	return true;
}

bool Controller::Right_R1Push( void )
{
	bool resault = false;
	if( this->Right_R1() )
	{
		if( m_befoConData.Right_R1 == false )
		{
			resault = true;
			m_befoConData.Right_R1 = true;
		}
	}else{
		m_befoConData.Right_R1 = false;
	}
	return resault;
}


bool Controller::Right_R2( void )
{
	g_monitor.__locker->lock();
	unsigned char conState = g_monitor.__ConState[0];
	g_monitor.__locker->unlock();

	if( (conState&0x02) == 0 )
	{
		return false;
	}
	return true;
}

bool Controller::Right_R2Push( void )
{
	bool resault = false;
	if( this->Right_R2() )
	{
		if( m_befoConData.Right_R2 == false )
		{
			resault = true;
			m_befoConData.Right_R2 = true;
		}
	}else{
		m_befoConData.Right_R2 = false;
	}
	return resault;
}


bool Controller::Left_up( void )
{
	g_monitor.__locker->lock();
	unsigned char conState = g_monitor.__ConState[1];
	g_monitor.__locker->unlock();

	if( (conState&0x20) == 0 )
	{
		return false;
	}
	return true;
}

bool Controller::Left_upPush( void )
{
	bool resault = false;
	if( this->Left_up() )
	{
		if( m_befoConData.Left_up == false )
		{
			resault = true;
			m_befoConData.Left_up = true;
		}
	}else{
		m_befoConData.Left_up = false;
	}
	return resault;
}


bool Controller::Left_down( void )
{
	g_monitor.__locker->lock();
	unsigned char conState = g_monitor.__ConState[1];
	g_monitor.__locker->unlock();

	if( (conState&0x10) == 0 )
	{
		return false;
	}
	return true;
}

bool Controller::Left_downPush( void )
{
	bool resault = false;
	if( this->Left_down() )
	{
		if( m_befoConData.Left_down == false )
		{
			resault = true;
			m_befoConData.Left_down = true;
		}
	}else{
		m_befoConData.Left_down = false;
	}
	return resault;
}


bool Controller::Left_right( void )
{
	g_monitor.__locker->lock();
	unsigned char conState = g_monitor.__ConState[1];
	g_monitor.__locker->unlock();

	if( (conState&0x08) == 0 )
	{
		return false;
	}
	return true;
}

bool Controller::Left_rightPush( void )
{
	bool resault = false;
	if( this->Left_right() )
	{
		if( m_befoConData.Left_right == false )
		{
			resault = true;
			m_befoConData.Left_right = true;
		}
	}else{
		m_befoConData.Left_right = false;
	}
	return resault;
}


bool Controller::Left_left( void )
{
	g_monitor.__locker->lock();
	unsigned char conState = g_monitor.__ConState[1];
	g_monitor.__locker->unlock();

	if( (conState&0x04) == 0 )
	{
		return false;
	}
	return true;
}

bool Controller::Left_leftPush( void )
{
	bool resault = false;
	if( this->Left_left() )
	{
		if( m_befoConData.Left_left == false )
		{
			resault = true;
			m_befoConData.Left_left = true;
		}
	}else{
		m_befoConData.Left_left = false;
	}
	return resault;
}


bool Controller::Left_L1( void )
{
	g_monitor.__locker->lock();
	unsigned char conState = g_monitor.__ConState[1];
	g_monitor.__locker->unlock();

	if( (conState&0x01) == 0 )
	{
		return false;
	}
	return true;
}

bool Controller::Left_L1Push( void )
{
	bool resault = false;
	if( this->Left_L1() )
	{
		if( m_befoConData.Left_L1 == false )
		{
			resault = true;
			m_befoConData.Left_L1 = true;
		}
	}else{
		m_befoConData.Left_L1 = false;
	}
	return resault;
}


bool Controller::Left_L2( void )
{
	g_monitor.__locker->lock();
	unsigned char conState = g_monitor.__ConState[0];
	g_monitor.__locker->unlock();

	if( (conState&0x01) == 0 )
	{
		return false;
	}
	return true;
}

bool Controller::Left_L2Push( void )
{
	bool resault = false;
	if( this->Left_L2() )
	{
		if( m_befoConData.Left_L2 == false )
		{
			resault = true;
			m_befoConData.Left_L2 = true;
		}
	}else{
		m_befoConData.Left_L2 = false;
	}
	return resault;
}

}

#endif /*ROBOKEN_CONTROLLER_ENABLE*/

