#include "cdigitaloutputpin.h"

namespace pigpio_cpp
{
	
DigitalOutputPin::DigitalOutputPin(const int pin, const int sessionId)
{
	int res; 
	
	this->m_pin = pin;
	this->m_sessionID = sessionId;
	
	res = set_mode(m_sessionID, m_pin, PI_OUTPUT);
	
	m_isAssigned = (res == 0);
}

int DigitalOutputPin::setHigh()
{
	int res;
	res = gpio_write(m_sessionID, m_pin, 1);
	
	return res;
}

int DigitalOutputPin::setLow()
{
	int res;
	res = gpio_write(m_sessionID, m_pin, 0);
	
	return res;
}

PinState DigitalOutputPin::pinState() const
{
	int res;
	res = gpio_read(m_sessionID, m_pin);
	
	return (PinState)res;
}

int DigitalOutputPin::pin() const
{
	return this->m_pin;
}

bool DigitalOutputPin::isAssigned() const
{
	return this->m_isAssigned; 
}	
}
