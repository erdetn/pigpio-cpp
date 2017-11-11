#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pigpiod_if2.h>

#include "csession.h"
#include "cutils.h"

using namespace std;

#ifndef DIGITALINPUTPIN_H
#define DIGITALINPUTPIN_H

namespace pigpio_cpp
{
	enum PullResistor
	{
		Clear    = PI_PUD_OFF,
		PullUp   = PI_PUD_UP,
		PullDown = PI_PUD_DOWN 
	};
	
	enum Edge
	{
		OnRisingEdge  = RISING_EDGE,
		OnFallingEdge = FALLING_EDGE,
		OnEitherEdge  = EITHER_EDGE
	};
	
	class DigitalInputPin
	{
	private:
		int      m_pin;
		int      m_sessionID;
		bool     m_isAssigned;
		int      m_callback_id;
		
	public:
		DigitalInputPin(const int pin, const int sessionId);
		~DigitalInputPin();
		
		int setPullResistor(PullResistor pullResistor);
		
		PinState pinState() const;
		int pin() const;
		bool isAssigned() const;	
		
		bool signal(Edge edge, IOCallback event);
		bool signal(Edge edge, IOCallbackExtended event, void *userData);
	};
}
#endif
