#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pigpiod_if2.h>

using namespace std;

#ifndef CLIENT_SESSION_H
#define CLIENT_SESSION_H

namespace pigpio_cpp
{
	class ClientSession
	{
	private:
		char  *m_daemonHostAddress;
		char  *m_daemonHostPort;
		bool   m_isRunning;
		int    m_sessionId;
		
	public:
		ClientSession(const char *daemonHostAddress);
		ClientSession(const char *daemonHostAddress, const char *daemonHostPort);
				
		~ClientSession();
		
		void start();
		void stop();
		bool isRunning() const;
		int sessionID() const;
	};
	
}
#endif
