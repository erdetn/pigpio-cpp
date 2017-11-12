#include "cserial.h"

namespace pigpio_cpp
{

Serial::Serial(const int sessionID, const char *serialDevice, const int baudRate)
{
	m_sessionID = sessionID;
	m_baudRate  = baudRate;
	m_portHandler = -1;
	m_isConnected = false;
	
	m_serialDevice = new char[strlen(serialDevice)+1];
	strcpy(m_serialDevice, serialDevice);
}

Serial::~Serial()
{
	if(m_serialDevice != NULL)
		delete m_serialDevice;
}
	
void Serial::open()
{
	if(m_serialDevice == NULL)
		return;
		
	m_portHandler = serial_open(m_sessionID,
								m_serialDevice,
								m_baudRate,
								0);
	if(m_portHandler < 0)
		return;
	
	m_isConnected = true;	
}

void Serial::close()
{
	if(m_isConnected)
		serial_close(m_sessionID, m_portHandler);
}

int Serial::write(unsigned char byte)
{
	return serial_write_byte(m_sessionID, m_portHandler, byte);
}

int Serial::write(char *payload, int length)
{
	return serial_write(m_sessionID, m_portHandler, payload, length);
}

int Serial::writeLine(char *payload)
{
	return serial_write(m_sessionID, m_portHandler, 
						payload, strlen(payload));
}
	
unsigned char Serial::readByte()
{
	return serial_read_byte(m_sessionID, m_portHandler);
}

int Serial::read(char *buffer, int bufferCapacity)
{
	return serial_read(m_sessionID, m_portHandler,
					   buffer, bufferCapacity);
}

int Serial::dataAvailable() const
{
	return serial_data_available(m_sessionID, m_portHandler);
}

int Serial::portHandler() const
{
	return m_portHandler;
}

int Serial::baudrate() const
{
	return m_baudRate;
}

bool Serial::isConnected() const
{
	return m_isConnected;
}

const char* Serial::device() const
{
	return (const char*)m_serialDevice;
}
}
