#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pigpiod_if2.h>

#include "cutils.h"

using namespace std;

#ifndef DIGITALOUTPUTPIN_H
#define DIGITALOUTPUTPIN_H

namespace pigpio_cpp
{
	class DigitalOutputPin
	{
	private:
		int      m_pin;
		int      m_sessionID;
		bool     m_isAssigned;
		
	public:
		DigitalOutputPin(const int pin, const int sessionId);
		
		int setHigh();
		int setLow();
		
		PinState pinState() const;
		int pin() const;
		bool isAssigned() const;		
	};
}
#endif
