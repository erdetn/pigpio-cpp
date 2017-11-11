#include "cdigitalinputpin.h"

namespace pigpio_cpp
{
	
DigitalInputPin::DigitalInputPin(const int pin, const int sessionId)
{
	int res; 
	
	this->m_pin = pin;
	this->m_sessionID = sessionId;
	
	res = set_mode(m_sessionID, m_pin, PI_INPUT);
	
	m_isAssigned = (res == 0);
	
	this->setPullResistor(PullDown);
	
	m_callback_id = -1;
}

DigitalInputPin::~DigitalInputPin()
{
	if(m_callback_id > -1)
	{
		callback_cancel(m_callback_id);
	}
}

int DigitalInputPin::setPullResistor(PullResistor pullResistor)
{
	int res;
	res = set_pull_up_down(m_sessionID, m_pin, (int)pullResistor);
	
	return res;
}

PinState DigitalInputPin::pinState() const
{
	int res;
	res = gpio_read(m_sessionID, m_pin);
	
	return (PinState)res;
}

int DigitalInputPin::pin() const
{
	return this->m_pin;
}

bool DigitalInputPin::isAssigned() const
{
	return this->m_isAssigned; 
}

bool DigitalInputPin::signal(Edge edge, IOCallback event)
{
	m_callback_id = callback(m_sessionID, m_pin, (unsigned)edge, event);
	return (m_callback_id > -1);
}

bool DigitalInputPin::signal(Edge edge, IOCallbackExtended event, void *userData)
{
	m_callback_id = callback_ex(m_sessionID, m_pin, (unsigned)edge,
								event, userData);
	return (m_callback_id > -1);
}

}
