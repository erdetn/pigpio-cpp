#include <iostream>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pigpiod_if2.h>

#include "cclientsession.h"
#include "cutils.h"
#include "cdigitaloutputpin.h"
#include "cdigitalinputpin.h"

#define GP04 4
#define GP18 18
#define GP17 17
#define GP07 7

using namespace pigpio_cpp;
using namespace std;

void event4(int pi, unsigned user_gpio, unsigned level, uint32_t tick);
void event18(int pi, unsigned user_gpio, unsigned level, 
			  uint32_t tick, void *userData);

int main() 
{
	int testUserData;
	ClientSession s("localhost");
	
	s.start();
	
	if(!s.isRunning())
	{
		cout << "Failed to run a PIGPIO session\n";
	}
	cout << "Session: " << s.sessionID() << " started.\n";
	
	DigitalOutputPin gp17(17, s.sessionID());
	
	if(gp17.isAssigned())
	{
		cout << "Pin 17 is assigned.\n";
		gp17.setHigh();
		cout << "Pin 17 set to: " << gp17.pinState() << endl;
		waitFor(0.5);
		gp17.setLow();
		cout << "Pin 17 set to: " << gp17.pinState() << endl;
	}
	
	DigitalInputPin gp4(GP04, s.sessionID());
	DigitalInputPin gp18(GP18, s.sessionID());
	
	gp4.signal(OnRisingEdge, event4);
	
	testUserData = 20;
	gp18.signal(OnFallingEdge, event18, (void *)testUserData);
	
	if(gp4.isAssigned() && gp18.isAssigned())
	{
		cout << "Pin 4 and 18 as assigned.\n";
			
		gp4.setPullResistor(PullDown);
		gp18.setPullResistor(PullUp);
		
		for(int i=0; i<20; i++) 
		{
			cout << "[GP04]: " << gp4.pinState() << endl;
			waitFor(1.0);
			cout << "[GP18]: " << gp18.pinState() << endl;
			waitFor(1.0);
		}
	}

	cout << "Session: " << s.sessionID() << " stopped.\n";
	s.stop();

	return 0;
}

void event4(int pi, unsigned user_gpio, unsigned level, uint32_t tick)
{
	static int numTriggered = 0;
	
	cout << "{"<< numTriggered++ << "} Callback: " 
		 << "[" << pi << "]: <"
		 << user_gpio << "> L= " << level << endl;
}

void event18(int pi, unsigned user_gpio, unsigned level, 
			 uint32_t tick, void *userData)
{
	static int numTriggered = 0;
	int userNumber;
	
	userNumber = (int)userData;
	
	cout << "{"<< numTriggered++ << "} Callback: " 
		 << "[" << pi << "]: <"
		 << user_gpio << "> L= " << level 
		 << "  user_data: " << userNumber << endl;
}

