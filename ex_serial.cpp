#include <iostream>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pigpiod_if2.h>
#include <unistd.h>

#include "cclientsession.h"
#include "cutils.h"
#include "cserial.h"

using namespace pigpio_cpp;
using namespace std;

#define TEST_WRITTING
//#define TEST_READING

int main() 
{
	ClientSession s("localhost");
	
	s.start();
	
	if(!s.isRunning())
	{
		cout << "Failed to run a PIGPIO session\n";
	}
	cout << "Session: " << s.sessionID() << " started.\n";
	
	Serial serial(s.sessionID(), "/dev/ttyS0", 9600);
	
	serial.open();
	
	if(serial.isConnected())
	{
		cout << "Serial [" << serial.device() 
			 << "] (" << serial.baudrate() << ") is opened"
			 << " with handler: " << serial.portHandler() << endl;
		
		#ifdef TEST_WRITTING	 
		for(int i=0; i<100; i++)
		{
			int res;
			res = serial.writeLine((char *)"\nHello from RPi3");
			
			SerialResponseError resError = (SerialResponseError)res;
			switch(resError)
			{
				case Succeed:
					cout << "Serial write: OK!\n";
					break;
				case BadHandler:
					cout << "Serial write: bad handler.\n";
					break;
				case BadParameters:
					cout << "Serial write: bad parameters.\n";
					break;
				case Failed:
					cout << "Serial write: failed!\n";
					break;
				default:
					cout << "Serial write: unknown error.\n";
					break;
			}
			
			waitFor(1);
		}
		#endif
		
		#ifdef TEST_READING
		while(true)
		{
			/*
			 * Send: "test\n" using a serial terminal.
			 */
			int res;
			char *buffer = new char[32];
			while(!(serial.dataAvailable()>4)) {}
			
			res = serial.read(buffer, 32);
			buffer[res-1] = 0;
			if(res > 0)
			{
				cout << "Message received: ["
					 << buffer << "] with length: "
					 << res << " bytes\n";
					 serial.writeLine((char *)"OK!\n");
				if(strcmp(buffer, "exit") == 0)
				{
					cout << "Exit command received.\n";
					break;
				}
			}
			else
			{
				SerialResponseError resError = (SerialResponseError)res;
				switch(resError)
				{
					case BadHandler:
						cout << "Serial read: bad handler.\n";
						break;
					case NoData:
						cout << "Serial read: no data.\n";
						break;
					case ReadFailed:
						cout << "Serial read: read failed.\n";
						break;
					default:
						cout << "Serial read: unknown error.\n";
						break;
				}
			}
		}
		#endif
		
		cout << endl;
		serial.close();
	}

	cout << "Session: " << s.sessionID() << " stopped.\n";
	s.stop();

	return 0;
}
