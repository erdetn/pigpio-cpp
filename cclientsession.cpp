#include "cclientsession.h"

namespace pigpio_cpp
{

ClientSession::ClientSession(const char *daemonHostAddress)
{
	m_daemonHostAddress = new char[strlen(daemonHostAddress)+1];
	strcpy(m_daemonHostAddress, daemonHostAddress);
	
	m_daemonHostPort = NULL;
	
	this->m_sessionId = -1;
	this->m_isRunning = false;
}

ClientSession::ClientSession(const char *daemonHostAddress, const char *daemonHostPort)
{
	m_daemonHostAddress = new char[strlen(daemonHostAddress)+1];
	strcpy(m_daemonHostAddress, daemonHostAddress);
	
	m_daemonHostPort = new char[strlen(daemonHostPort)+1];
	strcpy(m_daemonHostPort, daemonHostPort);
	
	this->m_sessionId = -1;
	this->m_isRunning = false;
}

ClientSession::~ClientSession()
{
	delete this->m_daemonHostAddress;
	delete this->m_daemonHostPort;
}

void ClientSession::start()
{	
	this->m_sessionId = pigpio_start(this->m_daemonHostAddress, this->m_daemonHostPort);
	this->m_isRunning = (this->m_sessionId>-1);
}

void ClientSession::stop()
{
	pigpio_stop(this->m_sessionId); 	
	this->m_isRunning = false;
}

bool ClientSession::isRunning() const
{
	return this->m_isRunning;
}

int ClientSession::sessionID() const
{
	return this->m_sessionId;
}
}
