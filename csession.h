#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pigpiod_if2.h>

using namespace std;

#ifndef SESSION_H
#define SESSION_H

namespace pigpio_cpp
{
	class Session
	{
	private:
		char  *m_daemonHostAddress;
		char  *m_daemonHostPort;
		bool   m_isRunning;
		int    m_sessionId;
		
	public:
		Session(const char *daemonHostAddress);
		Session(const char *daemonHostAddress, 
			const char *daemonHostPort);
				
		~Session();
		
		void start();
		void stop();
		bool isRunning() const;
		int sessionID() const;
	};
	
}

#endif
