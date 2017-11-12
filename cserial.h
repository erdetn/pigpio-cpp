#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pigpiod_if2.h>

#include "csession.h"
#include "cutils.h"

#ifndef SERIAL_H
#define SERIAL_H

namespace pigpio_cpp
{

enum SerialResponseError
{
	Succeed       = 0,
	BadHandler    = PI_BAD_HANDLE,
	BadParameters = PI_BAD_PARAM,
	Failed        = PI_SER_WRITE_FAILED,
	NoData        = PI_SER_READ_NO_DATA,
	ReadFailed    = PI_SER_READ_FAILED
};

class Serial
{
	private:
	int   m_sessionID;
	int   m_baudRate;
	int   m_portHandler;
	bool  m_isConnected;
	char *m_serialDevice;
	
	public:
	Serial(const int sessionID, const char *serialDevice, const int baudRate);
	~Serial();
	
	void open();
	void close();
	
	int write(unsigned char byte);
	int write(char *payload, int length);
	
	int writeLine(char *line);
	
	unsigned char readByte();
	int read(char *buffer, int bufferCapacity);
	
	int  dataAvailable() const;
	int  portHandler() const;
	int  baudrate() const;
	bool isConnected() const;
	const char *device() const;
};
}
#endif
