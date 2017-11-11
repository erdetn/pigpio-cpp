
#include <pigpiod_if2.h>

using namespace std;

#ifndef CUTILS_H
#define CUTILS_H

#define waitFor time_sleep

#define IOCallback          CBFunc_t
#define IOCallbackExtended  CBFuncEx_t

namespace pigpio_cpp
{
	enum PinState{
		HIGH = 1,
		LOW  = 0
	};
	
	
}
#endif

