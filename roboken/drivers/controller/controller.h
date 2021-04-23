/*
 * UartController.h
 *
 *  Created on: 2019/01/15
 *      Author: robo_iiyama1
 */

#ifndef ROBOKEN_DRIVERS_Controller_Controller_H
#define ROBOKEN_DRIVERS_Controller_Controller_H

#include "use_pin.h"

#ifdef ROBOKEN_CONTROLLER_ENABLE

#include "DigitalOut.h"
namespace roboken
{
	
class Controller
{
private:
	struct befoControllerData
	{
//		osThreadId 	threadId;

		bool 		Right_up;
		bool 		Right_down;
		bool 		Right_right;
		bool 		Right_left;
		bool		Right_R1;
		bool 		Right_R2;

		bool 		Left_up;
		bool		Left_down;
		bool 		Left_right;
		bool 		Left_left;
		bool 		Left_L1;
		bool 		Left_L2;
	};

	struct befoControllerData 	m_befoConData;

    static mbed::DigitalOut* m_safety;

	void init( void );

	static void checker( void );

    static void safety_on(void);
    static void safety_off(void);

public:
	Controller( void );

	static void Initializer( void );

	void Start( void );
	void AbsStart( void );


	bool isStart( void );
	bool isSafety( void );

	bool toggle( void );

	bool Right_up( void );
	bool Right_upPush( void );

	bool Right_down( void );
	bool Right_downPush( void );

	bool Right_right( void );
	bool Right_rightPush( void );

	bool Right_left( void );
	bool Right_leftPush( void );

	bool Right_R1( void );
	bool Right_R1Push( void );

	bool Right_R2( void );
	bool Right_R2Push( void );

	bool Left_up( void );
	bool Left_upPush( void );

	bool Left_down( void );
	bool Left_downPush( void );

	bool Left_right( void );
	bool Left_rightPush( void );

	bool Left_left( void );
	bool Left_leftPush( void );

	bool Left_L1( void );
	bool Left_L1Push( void );

	bool Left_L2( void );
	bool Left_L2Push( void );
};

}
#else /*ROBOKEN_CONTROLLER_ENABLE*/
namespace roboken
{
	
class Controller
{
private:
    bool safety_flg;
    mbed::DigitalOut* m_safety;

    void safety_on(void)
    {
        this->m_safety->write(1);
    }

    void safety_off(void)
    {
        this->m_safety->write(0);
    }

public:
	Controller( void )
    {
        this->safety_flg = true; 
        this->m_safety = new DigitalOut(ROBO_CONTROLLER_SEFETY);
        this->m_safety->write(1);
    }

	static void Initializer( void ){}

	void Start( void )
    {
        this->safety_flg = false;
        this->safety_off();
    }

	void AbsStart( void )
    {
        this->Start();
    }

	bool isStart( void ){return !safety_flg;}
	bool isSafety( void ){return safety_flg;}

	bool toggle( void ){return false;}

	bool Right_up( void ){return false;}
	bool Right_upPush( void ){return false;}

	bool Right_down( void ){return false;}
	bool Right_downPush( void ){return false;}

	bool Right_right( void ){return false;}
	bool Right_rightPush( void ){return false;}

	bool Right_left( void ){return false;}
	bool Right_leftPush( void ){return false;}

	bool Right_R1( void ){return false;}
	bool Right_R1Push( void ){return false;}

	bool Right_R2( void ){return false;}
	bool Right_R2Push( void ){return false;}

	bool Left_up( void ){return false;}
	bool Left_upPush( void ){return false;}

	bool Left_down( void ){return false;}
	bool Left_downPush( void ){return false;}

	bool Left_right( void ){return false;}
	bool Left_rightPush( void ){return false;}

	bool Left_left( void ){return false;}
	bool Left_leftPush( void ){return false;}

	bool Left_L1( void ){return false;}
	bool Left_L1Push( void ){return false;}

	bool Left_L2( void ){return false;}
	bool Left_L2Push( void ){return false;}
};

}
#endif /*ROBOKEN_CONTROLLER_ENABLE*/


#endif /* ROBOKEN_DRIVERS_Controller_Controller_H */
