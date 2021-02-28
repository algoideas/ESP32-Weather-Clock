#ifndef TOUCH_H
#define TOUCH_H

#include <lvgl.h>

// adjust pressure sensitivity - note works 'backwards'
#define MINPRESSURE 200
#define MAXPRESSURE 1000

class Touch
{
private:


public:
	void init();
};

#endif